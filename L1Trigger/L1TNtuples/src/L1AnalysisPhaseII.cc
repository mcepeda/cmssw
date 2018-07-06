#include "L1Trigger/L1TNtuples/interface/L1AnalysisPhaseII.h"
#include "L1Trigger/L1TMuon/interface/MicroGMTConfiguration.h"

L1Analysis::L1AnalysisPhaseII::L1AnalysisPhaseII()
{
}

L1Analysis::L1AnalysisPhaseII::~L1AnalysisPhaseII()
{

}

void L1Analysis::L1AnalysisPhaseII::SetEm(const edm::Handle<l1t::EGammaBxCollection> em, unsigned maxL1Extra)
{
  for (int ibx = em->getFirstBX(); ibx <= em->getLastBX(); ++ibx) {
    for (l1t::EGammaBxCollection::const_iterator it=em->begin(ibx); it!=em->end(ibx) && l1extra_.nEGs<maxL1Extra; it++){
      if (it->pt() > 10){
      //std::cout <<"Inside the tree maker"<< it->eta()<<"   "<<it->pt()<<std::endl;
	l1extra_.egEt .push_back(it->pt());
	l1extra_.egEta.push_back(it->eta());
	l1extra_.egPhi.push_back(it->phi());
	l1extra_.egIEt .push_back(it->hwPt());
	l1extra_.egIEta.push_back(it->hwEta());
	l1extra_.egIPhi.push_back(it->hwPhi());
	l1extra_.egIso.push_back(it->hwIso());
	l1extra_.egBx .push_back(ibx);
	l1extra_.egTowerIPhi.push_back(it->towerIPhi());
	l1extra_.egTowerIEta.push_back(it->towerIEta());
	l1extra_.egRawEt.push_back(it->rawEt());
	l1extra_.egIsoEt.push_back(it->isoEt());
	l1extra_.egFootprintEt.push_back(it->footprintEt());
	l1extra_.egNTT.push_back(it->nTT());
	l1extra_.egShape.push_back(it->shape());
	l1extra_.egTowerHoE.push_back(it->towerHoE());
	l1extra_.nEGs++;
      }
    }
  }
}


void L1Analysis::L1AnalysisPhaseII::SetTau(const edm::Handle<l1t::TauBxCollection> tau, unsigned maxL1Extra)
{
  for (int ibx = tau->getFirstBX(); ibx <= tau->getLastBX(); ++ibx) {
    for (l1t::TauBxCollection::const_iterator it=tau->begin(ibx); it!=tau->end(ibx) && l1extra_.nTaus<maxL1Extra; it++){
      if (it->pt() > 0){
	l1extra_.tauEt .push_back(it->et());
	l1extra_.tauEta.push_back(it->eta());
	l1extra_.tauPhi.push_back(it->phi());
	l1extra_.tauIEt .push_back(it->hwPt());
	l1extra_.tauIEta.push_back(it->hwEta());
	l1extra_.tauIPhi.push_back(it->hwPhi());
	l1extra_.tauIso.push_back(it->hwIso());
	l1extra_.tauBx .push_back(ibx);
	l1extra_.tauTowerIPhi.push_back(it->towerIPhi());
	l1extra_.tauTowerIEta.push_back(it->towerIEta());
	l1extra_.tauRawEt.push_back(it->rawEt());
	l1extra_.tauIsoEt.push_back(it->isoEt());
	l1extra_.tauNTT.push_back(it->nTT());
	l1extra_.tauHasEM.push_back(it->hasEM());
	l1extra_.tauIsMerged.push_back(it->isMerged());
	l1extra_.tauHwQual.push_back(it->hwQual());
	l1extra_.nTaus++;
      }
    }
  }
}


void L1Analysis::L1AnalysisPhaseII::SetJet(const edm::Handle<l1t::JetBxCollection> jet, unsigned maxL1Extra)
{
  for (int ibx = jet->getFirstBX(); ibx <= jet->getLastBX(); ++ibx) {
    for (l1t::JetBxCollection::const_iterator it=jet->begin(ibx); it!=jet->end(ibx) && l1extra_.nJets<maxL1Extra; it++){
      if (it->pt() > 0){
	l1extra_.jetEt .push_back(it->et());
	l1extra_.jetEta.push_back(it->eta());
	l1extra_.jetPhi.push_back(it->phi());
	l1extra_.jetIEt .push_back(it->hwPt());
	l1extra_.jetIEta.push_back(it->hwEta());
	l1extra_.jetIPhi.push_back(it->hwPhi());
	l1extra_.jetBx .push_back(ibx);
	l1extra_.jetRawEt.push_back(it->rawEt());
	l1extra_.jetSeedEt.push_back(it->seedEt());
	l1extra_.jetTowerIEta.push_back(it->towerIEta());
	l1extra_.jetTowerIPhi.push_back(it->towerIPhi());
	l1extra_.jetPUEt.push_back(it->puEt());
	l1extra_.jetPUDonutEt0.push_back(it->puDonutEt(0));
	l1extra_.jetPUDonutEt1.push_back(it->puDonutEt(1));
	l1extra_.jetPUDonutEt2.push_back(it->puDonutEt(2));
	l1extra_.jetPUDonutEt3.push_back(it->puDonutEt(3));
	l1extra_.nJets++;
      }
    }
  }
}


void L1Analysis::L1AnalysisPhaseII::SetMuon(const edm::Handle<l1t::MuonBxCollection> muon, unsigned maxL1Extra)
{
  for (int ibx = muon->getFirstBX(); ibx <= muon->getLastBX(); ++ibx) {
    for (l1t::MuonBxCollection::const_iterator it=muon->begin(ibx); it!=muon->end(ibx) && l1extra_.nMuons<maxL1Extra; it++){
      if (it->pt() > 0){
	l1extra_.muonEt .push_back(it->et());
	l1extra_.muonEta.push_back(it->eta());
	l1extra_.muonPhi.push_back(it->phi());
	l1extra_.muonEtaAtVtx.push_back(it->etaAtVtx());
	l1extra_.muonPhiAtVtx.push_back(it->phiAtVtx());
	l1extra_.muonIEt .push_back(it->hwPt());
	l1extra_.muonIEta.push_back(it->hwEta());
	l1extra_.muonIPhi.push_back(it->hwPhi());
	l1extra_.muonIEtaAtVtx.push_back(it->hwEtaAtVtx());
	l1extra_.muonIPhiAtVtx.push_back(it->hwPhiAtVtx());
	l1extra_.muonIDEta.push_back(it->hwDEtaExtra());
	l1extra_.muonIDPhi.push_back(it->hwDPhiExtra());
	l1extra_.muonChg.push_back(it->charge());
	l1extra_.muonIso.push_back(it->hwIso());
	l1extra_.muonQual.push_back(it->hwQual());
	l1extra_.muonTfMuonIdx.push_back(it->tfMuonIndex());
	l1extra_.muonBx .push_back(ibx);
	l1extra_.nMuons++;
      }
    }
  }
}

void L1Analysis::L1AnalysisPhaseII::SetMuonKF(const edm::Handle<l1t::RegionalMuonCandBxCollection> muonKF, unsigned maxL1Extra)
{
  for (int ibx = muonKF->getFirstBX(); ibx <= muonKF->getLastBX(); ++ibx) {
    for (l1t::RegionalMuonCandBxCollection::const_iterator it=muonKF->begin(ibx); it!=muonKF->end(ibx) && l1extra_.nMuonsKF<maxL1Extra; it++){
      if (it->hwPt() > 0){
      l1extra_.muonKFEt .push_back(it->hwPt()*0.5);
      l1extra_.muonKFEta.push_back(it->hwEta()*0.010875);
      l1extra_.muonKFPhi.push_back(l1t::MicroGMTConfiguration::calcGlobalPhi( it->hwPhi(), it->trackFinderType(), it->processor() )*2*M_PI/576);
      l1extra_.muonKFChg.push_back(pow(-1,it->hwSign()));
      l1extra_.muonKFQual.push_back(it->hwQual());
      l1extra_.muonKFBx .push_back(ibx);
      l1extra_.nMuonsKF++;
      }
    }
  }
}
  // RegionalMuons are a bit ugly... why not global muons?? 
  /// Get compressed pT (returned int * 0.5 = pT (GeV))
  //    const int hwPt() const { return m_hwPt; };
  //        /// Get compressed local phi (returned int * 2*pi/576 = local phi in rad)
  //            const int hwPhi() const { return m_hwPhi; };
  //                /// Get compressed eta (returned int * 0.010875 = eta)
  //                    const int hwEta() const { return m_hwEta; };
  //                        /// Get charge sign bit (charge = (-1)^(sign))
  //                        const int hwSign() const { return m_hwSign; };


void L1Analysis::L1AnalysisPhaseII::SetSum(const edm::Handle<l1t::EtSumBxCollection> sums, unsigned maxL1Extra)
{
  for (int ibx = sums->getFirstBX(); ibx <= sums->getLastBX(); ++ibx) {
    for (l1t::EtSumBxCollection::const_iterator it=sums->begin(ibx); it!=sums->end(ibx) && l1extra_.nSums<maxL1Extra; it++) {
      int type = static_cast<int>( it->getType() ); 
      l1extra_.sumType. push_back( type ); 
      l1extra_.sumEt. push_back( it->et() ); 
      l1extra_.sumPhi.push_back( it->phi() );
      l1extra_.sumIEt. push_back( it->hwPt() ); 
      l1extra_.sumIPhi.push_back( it->hwPhi() );
      l1extra_.sumBx. push_back( ibx );
      l1extra_.nSums++;
    }
  }
}

// TrkEG
void L1Analysis::L1AnalysisPhaseII::SetTkEG(const edm::Handle<l1t::L1TkElectronParticleCollection> tkEG, unsigned maxL1Extra)
{
  for(l1t::L1TkElectronParticleCollection::const_iterator it=tkEG->begin(); it!=tkEG->end() && l1extra_.nTkEG<maxL1Extra; it++){
    l1extra_.tkEGEt .push_back(it->et());
    l1extra_.tkEGEta.push_back(it->eta());
    l1extra_.tkEGPhi.push_back(it->phi());
    l1extra_.tkEGzVtx.push_back(it->getTrkzVtx());
    l1extra_.tkEGTrkIso.push_back(it->getTrkIsol());
    l1extra_.tkEGBx.push_back(0);//it->bx());
    l1extra_.nTkEG++;
  }
}

//EG (seeded by Barrel Crystals)
void L1Analysis::L1AnalysisPhaseII::SetEGCrystal(const edm::Handle<l1t::EGammaBxCollection> EGCrystal, unsigned maxL1Extra)
{
  for(l1t::EGammaBxCollection::const_iterator it=EGCrystal->begin(); it!=EGCrystal->end() && l1extra_.nEGCrystal<maxL1Extra; it++){
    if (it->et() > 10){
    l1extra_.EGCrystalEt .push_back(it->et());
    l1extra_.EGCrystalEta.push_back(it->eta());
    l1extra_.EGCrystalPhi.push_back(it->phi());
    l1extra_.EGCrystalIso.push_back(it->isoEt());
    l1extra_.EGCrystalHwQual.push_back(it->hwQual());
    l1extra_.EGCrystalBx.push_back(0);//it->bx());
    l1extra_.nEGCrystal++;
  }
}
}

// TrkEG (seeded by Barrel Crystals)
void L1Analysis::L1AnalysisPhaseII::SetTkEGCrystal(const edm::Handle<l1t::L1TkElectronParticleCollection> tkEGCrystal, unsigned maxL1Extra)
{
  for(l1t::L1TkElectronParticleCollection::const_iterator it=tkEGCrystal->begin(); it!=tkEGCrystal->end() && l1extra_.nTkEGCrystal<maxL1Extra; it++){
    if (it->et() > 10){
    l1extra_.tkEGCrystalEt .push_back(it->et());
    l1extra_.tkEGCrystalEta.push_back(it->eta());
    l1extra_.tkEGCrystalPhi.push_back(it->phi());
    l1extra_.tkEGCrystalzVtx.push_back(it->getTrkzVtx());
    l1extra_.tkEGCrystalTrkIso.push_back(it->getTrkIsol());
    l1extra_.tkEGCrystalBx.push_back(0);//it->bx());
    l1extra_.nTkEGCrystal++;
  }}
}

void L1Analysis::L1AnalysisPhaseII::SetTkEMCrystal(const edm::Handle<l1t::L1TkEmParticleCollection> tkEMCrystal, unsigned maxL1Extra)
{
  for(l1t::L1TkEmParticleCollection::const_iterator it=tkEMCrystal->begin(); it!=tkEMCrystal->end() && l1extra_.nTkEMCrystal<maxL1Extra; it++){
    if (it->et() > 10){
    l1extra_.tkEMCrystalEt .push_back(it->et());
    l1extra_.tkEMCrystalEta.push_back(it->eta());
    l1extra_.tkEMCrystalPhi.push_back(it->phi());
    l1extra_.tkEMCrystalTrkIso.push_back(it->getTrkIsol());
    l1extra_.tkEMCrystalBx.push_back(0);//it->bx());
    l1extra_.nTkEMCrystal++;
  }}
}

// TrkIsoEG
void L1Analysis::L1AnalysisPhaseII::SetTkIsoEG(const edm::Handle<l1t::L1TkElectronParticleCollection> tkIsoEG, unsigned maxL1Extra)
{
  for(l1t::L1TkElectronParticleCollection::const_iterator it=tkIsoEG->begin(); it!=tkIsoEG->end() && l1extra_.nTkIsoEG<maxL1Extra; it++){
    l1extra_.tkIsoEGEt .push_back(it->et());
    l1extra_.tkIsoEGEta.push_back(it->eta());
    l1extra_.tkIsoEGPhi.push_back(it->phi());
    l1extra_.tkIsoEGzVtx.push_back(it->getTrkzVtx());
    l1extra_.tkIsoEGTrkIso.push_back(it->getTrkIsol());
    l1extra_.tkIsoEGBx.push_back(0);//it->bx());
    l1extra_.nTkIsoEG++;
  }
}

//TkEM
void L1Analysis::L1AnalysisPhaseII::SetTkEM(const edm::Handle<l1t::L1TkEmParticleCollection> tkEM, unsigned maxL1Extra)
{
  for(l1t::L1TkEmParticleCollection::const_iterator it=tkEM->begin(); it!=tkEM->end() && l1extra_.nTkEM<maxL1Extra; it++){
    l1extra_.tkEMEt .push_back(it->et());
    l1extra_.tkEMEta.push_back(it->eta());
    l1extra_.tkEMPhi.push_back(it->phi());
    l1extra_.tkEMBx.push_back(0);//it->bx());
    l1extra_.tkEMTrkIso.push_back(it->getTrkIsol());
    l1extra_.nTkEM++;
  }
}




//TkTau
void L1Analysis::L1AnalysisPhaseII::SetTkTau(const edm::Handle<l1t::L1TkTauParticleCollection> tkTau, unsigned maxL1Extra)
{

  for(l1t::L1TkTauParticleCollection::const_iterator it=tkTau->begin(); it!=tkTau->end() && l1extra_.nTkTau<maxL1Extra; it++){

    l1extra_.tkTauEt.push_back(it->et());
    l1extra_.tkTauEta.push_back(it->eta());
    l1extra_.tkTauPhi.push_back(it->phi());
    l1extra_.tkTauzVtx.push_back(it->getTrkzVtx());
    l1extra_.tkTauTrkIso.push_back(it->getTrkIsol());
    l1extra_.tkTauBx.push_back(0);//it->bx());
    l1extra_.nTkTau++;
  }
}

// TkJet
void L1Analysis::L1AnalysisPhaseII::SetTkJet(const edm::Handle<l1t::L1TkJetParticleCollection> tkJet, unsigned maxL1Extra)
{

  for(l1t::L1TkJetParticleCollection::const_iterator it=tkJet->begin(); it!=tkJet->end() && l1extra_.nTkJets<maxL1Extra; it++){
    l1extra_.tkJetEt .push_back(it->et());
    l1extra_.tkJetEta.push_back(it->eta());
    l1extra_.tkJetPhi.push_back(it->phi());
    l1extra_.tkJetzVtx.push_back(it->getJetVtx());
    l1extra_.tkJetBx .push_back(0);//it->bx());
    l1extra_.nTkJets++;
  }
}

void L1Analysis::L1AnalysisPhaseII::SetTkMuon(const edm::Handle<l1t::L1TkMuonParticleCollection> muon, unsigned maxL1Extra)
{
  for(l1t::L1TkMuonParticleCollection::const_iterator it=muon->begin(); it!=muon->end() && l1extra_.nTkMuons<maxL1Extra; it++){

    l1extra_.tkMuonEt .push_back( it->pt());
    l1extra_.tkMuonEta.push_back(it->eta());
    l1extra_.tkMuonPhi.push_back(it->phi());
    l1extra_.tkMuonChg.push_back(it->charge());
    l1extra_.tkMuonTrkIso.push_back(it->getTrkIsol());
    //    l1extra_.tkMuonIso.push_back(it->isIsolated());
    // l1extra_.tkMuonMip.push_back(it->isMip());
    // l1extra_.tkMuonFwd.push_back(it->isForward());
    //l1extra_.tkMuonRPC.push_back(it->isRPC());
    l1extra_.tkMuonzVtx.push_back(it->getTrkzVtx());
    l1extra_.tkMuonBx .push_back(0); //it->bx());
    /*
    const edm::Ref<l1t::L1MuonParticleCollection> MuRef = it->getMuRef();
    unsigned int qualityBis = MuRef -> gmtMuonCand().quality();
    l1extra_.tkMuonQuality .push_back(qualityBis);
    */
    l1extra_.tkMuonQuality .push_back(it->quality());
    /*
    std::cout << "ptExtra pt " << it->pt()
	      << "; etaExtra " << it->eta()
	      << "; phiExtra " << it->phi()
	      << std::endl;
    */

    l1extra_.nTkMuons++;
  }
}

// TkMet
void L1Analysis::L1AnalysisPhaseII::SetTkMet(const edm::Handle<l1t::L1TkEtMissParticleCollection> tkMets)
{
  for(l1t::L1TkEtMissParticleCollection::const_iterator it=tkMets->begin(); it!=tkMets->end(); it++) {
    l1extra_.tkEt.    push_back( it->etTotal() );
    l1extra_.tkMet.   push_back( it->etMiss() );
    l1extra_.tkMetPhi.push_back( it->phi() );
    l1extra_.tkMetBx. push_back( it->bx() );
    l1extra_.nTkMet++;
  }
}


void L1Analysis::L1AnalysisPhaseII::SetTkMht(const edm::Handle<l1t::L1TkHTMissParticleCollection> tkMhts)
{
  for(l1t::L1TkHTMissParticleCollection::const_iterator it=tkMhts->begin(); it!=tkMhts->end(); it++) {
    l1extra_.tkHt.    push_back( it->EtTotal() );
    l1extra_.tkMht.   push_back( it->EtMiss() );
    l1extra_.tkMhtPhi.push_back( it->phi() );
    l1extra_.tkMhtBx. push_back( it->bx() );
    l1extra_.nTkMht++;
  }
}

void L1Analysis::L1AnalysisPhaseII::SetCaloJet(const edm::Handle<reco::PFJetCollection> CaloJet, unsigned maxL1Extra)
{

  for(reco::PFJetCollection::const_iterator it=CaloJet->begin(); it!=CaloJet->end() && l1extra_.nAk4L1CaloJets<maxL1Extra; it++){
    l1extra_.ak4L1CaloJetEt .push_back(it->et());
    l1extra_.ak4L1CaloJetEta.push_back(it->eta());
    l1extra_.ak4L1CaloJetPhi.push_back(it->phi());
//    l1extra_.ak4L1CaloJetzVtx.push_back(it->getJetVtx());
    l1extra_.ak4L1CaloJetBx .push_back(0);//it->bx());
    l1extra_.nAk4L1CaloJets++;
  }
}

void L1Analysis::L1AnalysisPhaseII::SetPFJet(const edm::Handle<reco::PFJetCollection> PFJet, unsigned maxL1Extra)
{

  for(reco::PFJetCollection::const_iterator it=PFJet->begin(); it!=PFJet->end() && l1extra_.nAk4L1PFJets<maxL1Extra; it++){
    l1extra_.ak4L1PFJetEt .push_back(it->et());
    l1extra_.ak4L1PFJetEta.push_back(it->eta());
    l1extra_.ak4L1PFJetPhi.push_back(it->phi());
//    l1extra_.ak4L1PFJetzVtx.push_back(it->getJetVtx());
    l1extra_.ak4L1PFJetBx .push_back(0);//it->bx());
    l1extra_.nAk4L1PFJets++;
  }
}

void L1Analysis::L1AnalysisPhaseII::SetL1TKJet(const edm::Handle<reco::PFJetCollection> L1TKJet, unsigned maxL1Extra)
{

  for(reco::PFJetCollection::const_iterator it=L1TKJet->begin(); it!=L1TKJet->end() && l1extra_.nAk4L1TKJets<maxL1Extra; it++){
    l1extra_.ak4L1TKJetEt .push_back(it->et());
    l1extra_.ak4L1TKJetEta.push_back(it->eta());
    l1extra_.ak4L1TKJetPhi.push_back(it->phi());
//    l1extra_.ak4L1TKJetzVtx.push_back(it->getJetVtx());
    l1extra_.ak4L1TKJetBx .push_back(0);//it->bx());
    l1extra_.nAk4L1TKJets++;
  }

}

void L1Analysis::L1AnalysisPhaseII::SetL1METCalo(const edm::Handle< std::vector<reco::PFMET> > l1MetCalo)
{
  reco::PFMET met=l1MetCalo->at(0);
  l1extra_.l1MetCaloEt = met.et();
  l1extra_.l1MetCaloPhi = met.phi();
}

void L1Analysis::L1AnalysisPhaseII::SetL1METPF(const edm::Handle< std::vector<reco::PFMET> > l1MetPF)
{
  reco::PFMET met=l1MetPF->at(0);
  l1extra_.l1MetPFEt = met.et();
  l1extra_.l1MetPFPhi = met.phi();
}

void L1Analysis::L1AnalysisPhaseII::SetL1METTK(const edm::Handle< std::vector<reco::PFMET> > l1MetTK)
{
  reco::PFMET met=l1MetTK->at(0);
  l1extra_.l1MetTKEt = met.et();
  l1extra_.l1MetTKPhi = met.phi();
}





