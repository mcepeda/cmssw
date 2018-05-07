#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1ExtraUpgrade.h"

L1Analysis::L1AnalysisL1ExtraUpgrade::L1AnalysisL1ExtraUpgrade()
{
}

L1Analysis::L1AnalysisL1ExtraUpgrade::~L1AnalysisL1ExtraUpgrade()
{

}

void L1Analysis::L1AnalysisL1ExtraUpgrade::SetEG(const edm::Handle<l1extra::L1EmParticleCollection> eg, unsigned maxL1Extra)
{
 for(l1extra::L1EmParticleCollection::const_iterator it=eg->begin(); it!=eg->end() && l1extra_.nEG<maxL1Extra; it++){  
      l1extra_.egEt .push_back(it->et());
      l1extra_.egEta.push_back(it->eta());
      l1extra_.egPhi.push_back(it->phi());
      l1extra_.egBx .push_back(it->bx());
      l1extra_.nEG++;
    }
}

void L1Analysis::L1AnalysisL1ExtraUpgrade::SetIsoEG(const edm::Handle<l1extra::L1EmParticleCollection> isoEG, unsigned maxL1Extra)
{
  for(l1extra::L1EmParticleCollection::const_iterator it=isoEG->begin(); it!=isoEG->end() && l1extra_.nIsoEG<maxL1Extra; it++){
      l1extra_.isoEGEt .push_back(it->et());
      l1extra_.isoEGEta.push_back(it->eta());
      l1extra_.isoEGPhi.push_back(it->phi());
      l1extra_.isoEGBx .push_back(it->bx());
      l1extra_.nIsoEG++;
    }
}

// TrkEG
void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkEG(const edm::Handle<l1t::L1TkElectronParticleCollection> tkEG, unsigned maxL1Extra)
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
// TrkEG (with TrackPt 7 GeV )
void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkEG2(const edm::Handle<l1t::L1TkElectronParticleCollection> tkEG2, unsigned maxL1Extra)
{
  for(l1t::L1TkElectronParticleCollection::const_iterator it=tkEG2->begin(); it!=tkEG2->end() && l1extra_.nTkEG2<maxL1Extra; it++){
    l1extra_.tkEG2Et .push_back(it->et());
    l1extra_.tkEG2Eta.push_back(it->eta());
    l1extra_.tkEG2Phi.push_back(it->phi());
    l1extra_.tkEG2zVtx.push_back(it->getTrkzVtx());
    l1extra_.tkEG2TrkIso.push_back(it->getTrkIsol());
    l1extra_.tkEG2Bx.push_back(0);//it->bx());
    l1extra_.nTkEG2++;
  }
}


// TrkIsoEG
void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkIsoEG(const edm::Handle<l1t::L1TkElectronParticleCollection> tkIsoEG, unsigned maxL1Extra)
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
void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkEM(const edm::Handle<l1t::L1TkEmParticleCollection> tkEM, unsigned maxL1Extra)
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


void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTau(const edm::Handle<l1extra::L1JetParticleCollection> tau, unsigned maxL1Extra)
{
      //std::cout << "Filling L1 Extra tauJets" << std::endl;      
   for(l1extra::L1JetParticleCollection::const_iterator it=tau->begin(); it!=tau->end() && l1extra_.nTau<maxL1Extra; it++){
      
     // printf("L1tauJet (et,eta,phi,bx,) (%f,%f,%f,%d)\n",it->et(),it->eta(),it->phi(),it->bx() );
      l1extra_.tauEt .push_back(it->et());
      l1extra_.tauEta.push_back(it->eta());
      l1extra_.tauPhi.push_back(it->phi());
      l1extra_.tauBx .push_back(it->bx());
      l1extra_.nTau++;
    }
}

void L1Analysis::L1AnalysisL1ExtraUpgrade::SetIsoTau(const edm::Handle<l1extra::L1JetParticleCollection> isoTau, unsigned maxL1Extra)
{
      //std::cout << "Filling L1 Extra tauJets" << std::endl;      
   for(l1extra::L1JetParticleCollection::const_iterator it=isoTau->begin(); it!=isoTau->end() && l1extra_.nIsoTau<maxL1Extra; it++){
      
     // printf("L1tauJet (et,eta,phi,bx,) (%f,%f,%f,%d)\n",it->et(),it->eta(),it->phi(),it->bx() );
      l1extra_.isoTauEt .push_back(it->et());
      l1extra_.isoTauEta.push_back(it->eta());
      l1extra_.isoTauPhi.push_back(it->phi());
      l1extra_.isoTauBx .push_back(it->bx());
      l1extra_.nIsoTau++;
    }
}

//TkTau
void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkTau(const edm::Handle<l1t::L1TkTauParticleCollection> tkTau, unsigned maxL1Extra)
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


void L1Analysis::L1AnalysisL1ExtraUpgrade::SetJet(const edm::Handle<l1extra::L1JetParticleCollection> jet, unsigned maxL1Extra)
{
//      std::cout << "Filling L1 Extra cenJets" << maxL1Extra << " " << cenJet->size() << std::endl;      
 
  for(l1extra::L1JetParticleCollection::const_iterator it=jet->begin(); it!=jet->end() && l1extra_.nJets<maxL1Extra; it++){
      //printf("L1CenJet (et,eta,phi,bx,) (%f,%f,%f,%d) \n",it->et(),it->eta(),it->phi(),it->bx() );
//      std::cout << "L1 CenJets et,eta,phi,bx = " << it->et() << ", " << it->eta() <<", " <<it->phi() <<", " << it->bx() << std::endl;
      l1extra_.jetEt .push_back(it->et());
      l1extra_.jetEta.push_back(it->eta());
      l1extra_.jetPhi.push_back(it->phi());
      l1extra_.jetBx .push_back(it->bx());
      l1extra_.nJets++;
    }
}

// TkJet
void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkJet(const edm::Handle<l1t::L1TkJetParticleCollection> tkJet, unsigned maxL1Extra)
{
  //      std::cout << "Filling L1 Extra cenJets" << maxL1Extra << " " << cenJet->size() << std::endl;

  for(l1t::L1TkJetParticleCollection::const_iterator it=tkJet->begin(); it!=tkJet->end() && l1extra_.nTkJets<maxL1Extra; it++){
    l1extra_.tkJetEt .push_back(it->et());
    l1extra_.tkJetEta.push_back(it->eta());
    l1extra_.tkJetPhi.push_back(it->phi());
    l1extra_.tkJetzVtx.push_back(it->getJetVtx());
    l1extra_.tkJetBx .push_back(0);//it->bx());
    l1extra_.nTkJets++;
  }
}


void L1Analysis::L1AnalysisL1ExtraUpgrade::SetFwdJet(const edm::Handle<l1extra::L1JetParticleCollection> fwdJet, unsigned maxL1Extra)
{
      //std::cout << "Filling L1 Extra fwdJets" << std::endl;      
   for(l1extra::L1JetParticleCollection::const_iterator it=fwdJet->begin(); it!=fwdJet->end() && l1extra_.nFwdJets<maxL1Extra; it++){ 
      //printf("L1fwdJet (et,eta,phi,bx,) (%f,%f,%f,%d)\n",it->et(),it->eta(),it->phi(),it->bx() );
      l1extra_.fwdJetEt .push_back(it->et());
      l1extra_.fwdJetEta.push_back(it->eta());
      l1extra_.fwdJetPhi.push_back(it->phi());
      l1extra_.fwdJetBx .push_back(it->bx());
      l1extra_.nFwdJets++;
    }
}

void L1Analysis::L1AnalysisL1ExtraUpgrade::SetMuon(const edm::Handle<l1extra::L1MuonParticleCollection> muon, unsigned maxL1Extra)
{
  for(l1extra::L1MuonParticleCollection::const_iterator it=muon->begin(); it!=muon->end() && l1extra_.nMuons<maxL1Extra; it++){
      
      l1extra_.muonEt .push_back( it->et());
      l1extra_.muonEta.push_back(it->eta());
      l1extra_.muonPhi.push_back(it->phi());
      l1extra_.muonChg.push_back(it->charge());
      l1extra_.muonIso.push_back(it->isIsolated());
      l1extra_.muonMip.push_back(it->isMip());
      l1extra_.muonFwd.push_back(it->isForward());
      l1extra_.muonRPC.push_back(it->isRPC());
      l1extra_.muonBx .push_back(it->bx());

      l1extra_.muonQuality .push_back(it->gmtMuonCand().quality());
      /*      		
      std::cout << "gmtmuon cand: pt " << it->gmtMuonCand().ptValue() 
		<< "; ptExtra " << it->et() 
		<< "; qual " << it->gmtMuonCand().quality() 
		<< std::endl;
      */
      l1extra_.nMuons++;
    }
}

void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkMuon(const edm::Handle<l1t::L1TkMuonParticleCollection> muon, unsigned maxL1Extra)
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


void L1Analysis::L1AnalysisL1ExtraUpgrade::SetMet(const edm::Handle<l1extra::L1EtMissParticleCollection> mets)
{
  for(l1extra::L1EtMissParticleCollection::const_iterator it=mets->begin(); it!=mets->end(); it++) {
    l1extra_.et.    push_back( it->etTotal() ); 
    l1extra_.met.   push_back( it->et() );
    l1extra_.metPhi.push_back( it->phi() );
    l1extra_.metBx. push_back( it->bx() );
    l1extra_.nMet++;
  }
}

// TkMet
void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkMet(const edm::Handle<l1t::L1TkEtMissParticleCollection> tkMets)
{
  for(l1t::L1TkEtMissParticleCollection::const_iterator it=tkMets->begin(); it!=tkMets->end(); it++) {
    l1extra_.tkEt.    push_back( it->etTotal() );
    l1extra_.tkMet.   push_back( it->etMiss() );
    l1extra_.tkMetPhi.push_back( it->phi() );
    l1extra_.tkMetBx. push_back( it->bx() );
    l1extra_.nTkMet++;
  }
}


void L1Analysis::L1AnalysisL1ExtraUpgrade::SetMht(const edm::Handle<l1extra::L1EtMissParticleCollection> mhts)
{
  for(l1extra::L1EtMissParticleCollection::const_iterator it=mhts->begin(); it!=mhts->end(); it++) {
    l1extra_.ht.    push_back( it->etTotal() );
    l1extra_.mht.   push_back( it->et() );
    l1extra_.mhtPhi.push_back( it->phi() );
    l1extra_.mhtBx. push_back( it->bx() );
    l1extra_.nMht++;
  }
}

void L1Analysis::L1AnalysisL1ExtraUpgrade::SetTkMht(const edm::Handle<l1t::L1TkHTMissParticleCollection> tkMhts)
{
  for(l1t::L1TkHTMissParticleCollection::const_iterator it=tkMhts->begin(); it!=tkMhts->end(); it++) {
    l1extra_.tkHt.    push_back( it->EtTotal() );
    l1extra_.tkMht.   push_back( it->EtMiss() );
    l1extra_.tkMhtPhi.push_back( it->phi() );
    l1extra_.tkMhtBx. push_back( it->bx() );
    l1extra_.nTkMht++;
  }
}
