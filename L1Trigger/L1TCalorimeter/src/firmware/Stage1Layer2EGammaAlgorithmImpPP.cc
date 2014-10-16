///step03
/// \class l1t::Stage1Layer2EGammaAlgorithm
///
/// Description: interface for MP firmware
///
/// Implementation:
///
/// \author: Kalanand Mishra - Fermilab
///

#include "L1Trigger/L1TCalorimeter/interface/Stage1Layer2EGammaAlgorithmImp.h"
#include "DataFormats/L1TCalorimeter/interface/CaloRegion.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegionDetId.h"
#include "L1Trigger/L1TCalorimeter/interface/PUSubtractionMethods.h"
#include "L1Trigger/L1TCalorimeter/interface/JetFinderMethods.h"
#include "L1Trigger/L1TCalorimeter/interface/legacyGtHelper.h"

using namespace std;
using namespace l1t;


Stage1Layer2EGammaAlgorithmImpPP::Stage1Layer2EGammaAlgorithmImpPP(CaloParamsStage1* params) : params_(params) {};

Stage1Layer2EGammaAlgorithmImpPP::~Stage1Layer2EGammaAlgorithmImpPP(){};



void l1t::Stage1Layer2EGammaAlgorithmImpPP::processEvent(const std::vector<l1t::CaloEmCand> & EMCands, const std::vector<l1t::CaloRegion> & regions, const std::vector<l1t::Jet> * jets, std::vector<l1t::EGamma>* egammas) {


  double egLsb=params_->egLsb();
  double jetLsb=params_->jetLsb();
  int egSeedThreshold= floor( params_->egSeedThreshold()/egLsb + 0.5);
  int jetSeedThreshold= floor( params_->jetSeedThreshold()/jetLsb + 0.5);
  double egRelativeJetIsolationBarrelCut = params_->egRelativeJetIsolationBarrelCut();
  double egRelativeJetIsolationEndcapCut = params_->egRelativeJetIsolationEndcapCut();

  int egMinPtRelativeJetIsolation = params_->egMinPtRelativeJetIsolation();
  int egMaxPtRelativeJetIsolation = params_->egMaxPtRelativeJetIsolation();
  int egMinPt3x3HoE = params_->egMinPt3x3HoE();
  int egMaxPt3x3HoE = params_->egMaxPt3x3HoE();



  std::string regionPUSType = params_->regionPUSType();
  std::vector<double> regionPUSParams = params_->regionPUSParams();

  std::vector<l1t::CaloRegion> *subRegions = new std::vector<l1t::CaloRegion>();
  std::vector<l1t::EGamma> *preGtEGammas = new std::vector<l1t::EGamma>();


  //Region Correction will return uncorrected subregions if
  //regionPUSType is set to None in the config
  RegionCorrection(regions, subRegions, regionPUSParams, regionPUSType);

  // ----- need to cluster jets in order to compute jet isolation ----
  std::vector<l1t::Jet> *unCorrJets = new std::vector<l1t::Jet>();
  // slidingWindowJetFinder(jetSeedThreshold, subRegions, unCorrJets);
  TwelveByTwelveFinder(jetSeedThreshold, subRegions, unCorrJets);


  for(CaloEmCandBxCollection::const_iterator egCand = EMCands.begin();
      egCand != EMCands.end(); egCand++) {

    int eg_et = egCand->hwPt();
    int eg_eta = egCand->hwEta();
    int eg_phi = egCand->hwPhi();
    //std::cout << "eg_et: " << eg_et << " thresh: " << egSeedThreshold << std::endl;
    if(eg_et <= egSeedThreshold) continue;

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > egLorentz(0,0,0,0);

    int quality = 1;
    int isoFlag = 0;
    int isoFlagRct = 0;


    // 3x3 HoE, computed in 3x3

    if(eg_et>=egMaxPt3x3HoE && egMinPt3x3HoE >= eg_et) {
                 if(egCand->hwIso()) isoFlagRct =1;
    }
    else {isoFlagRct =1;}   
 
    // ------- isolation and H/E ---------------
    // double isolation = Isolation(eg_eta, eg_phi, *subRegions);
    //if( eg_et > 0 && (isolation / eg_et ) > relativeIsolationCut^&& eg_et<egMaxPtRelativeJetIsolation) isoFlag  = 0;

    double jet_pt=AssociatedJetPt(eg_eta,eg_phi,unCorrJets);
    jet_pt=jet_pt*jetLsb;
    bool isinBarrel = (eg_eta>=7 && eg_eta<=14);
    if (jet_pt>0 && eg_et>=egMinPtRelativeJetIsolation && eg_et<egMaxPtRelativeJetIsolation){
      double jetIsolationEG = jet_pt - eg_et;        // Jet isolation
      double relativeJetIsolationEG = jetIsolationEG / eg_et;

      if(isinBarrel && relativeJetIsolationEG < egRelativeJetIsolationBarrelCut) isoFlag=1;
      if(!isinBarrel && relativeJetIsolationEG < egRelativeJetIsolationEndcapCut) isoFlag=1;
    }else{ // no associated jet; assume it's an isolated eg
      isoFlag=1;
    }


    // double hoe = HoverE(eg_et, eg_eta, eg_phi, *subRegions);


    bool fullIsoFlag=isoFlag&&isoFlagRct;

    // ------- fill the EG candidate vector ---------
    l1t::EGamma theEG(*&egLorentz, eg_et, eg_eta, eg_phi, quality, fullIsoFlag);
    //?? if( hoe < HoverECut) egammas->push_back(theEG);
    preGtEGammas->push_back(theEG);
  }

  EGammaToGtScales(params_, preGtEGammas, egammas);


  //the EG candidates should be sorted, highest pT first.
  // do not truncate the EG list, GT converter handles that
  auto comp = [&](l1t::EGamma i, l1t::EGamma j)-> bool {
    return (i.hwPt() < j.hwPt() );
  };

  delete subRegions;
  delete unCorrJets;
  delete preGtEGammas;

  std::sort(egammas->begin(), egammas->end(), comp);
  std::reverse(egammas->begin(), egammas->end());
}





/// -----  Compute isolation sum --------------------
double l1t::Stage1Layer2EGammaAlgorithmImpPP::Isolation(int ieta, int iphi,
							const std::vector<l1t::CaloRegion> & regions)  const {
  double isolation = 0;

  for(CaloRegionBxCollection::const_iterator region = regions.begin();
      region != regions.end(); region++) {

    int regionPhi = region->hwPhi();
    int regionEta = region->hwEta();
    unsigned int deltaPhi = iphi - regionPhi;
    if (std::abs(deltaPhi) == L1CaloRegionDetId::N_PHI-1)
      deltaPhi = -deltaPhi/std::abs(deltaPhi); //18 regions in phi

    unsigned int deltaEta = std::abs(ieta - regionEta);

    if ((deltaPhi + deltaEta) > 0 && deltaPhi < 2 && deltaEta < 2)
      isolation += region->hwPt();
  }

  // set output
  return isolation;
}




double l1t::Stage1Layer2EGammaAlgorithmImpPP::AssociatedJetPt(int ieta, int iphi,
							      const std::vector<l1t::Jet> * jets)  const {

  bool Debug=false;

  if (Debug) cout << "Number of jets: " << jets->size() << endl;
  double pt = -1;


  for(JetBxCollection::const_iterator itJet = jets->begin();
      itJet != jets->end(); ++itJet){

    int jetEta = itJet->hwEta();
    int jetPhi = itJet->hwPhi();
    if (Debug) cout << "Matching ETA: " << ieta << " " << jetEta << endl;
    if (Debug) cout << "Matching PHI: " << iphi << " " << jetPhi << endl;
    if ((jetEta == ieta) && (jetPhi == iphi)){
      pt = itJet->hwPt();
      break;
    }
  }

  // set output
  return pt;
}



/// -----  Compute H/E --------------------
double l1t::Stage1Layer2EGammaAlgorithmImpPP::HoverE(int et, int ieta, int iphi,
						     const std::vector<l1t::CaloRegion> & regions)  const {
  int hadronicET = 0;

  for(CaloRegionBxCollection::const_iterator region = regions.begin();
      region != regions.end(); region++) {

    int regionET = region->hwPt();
    int regionPhi = region->hwPhi();
    int regionEta = region->hwEta();

    if(iphi == regionPhi && ieta == regionEta) {
      hadronicET = regionET;
      break;
    }
  }

  hadronicET -= et;

  double hoe = 0.0;

  if( hadronicET >0 && et > 0)
    hoe =  (double) hadronicET / (double) et;

  // set output
  return hoe;
}
