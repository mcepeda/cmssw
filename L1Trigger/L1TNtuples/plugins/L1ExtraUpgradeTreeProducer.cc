// -*- C++ -*-
//
// Package:    UserCode/L1TriggerDPG
// Class:      L1ExtraUpgradeTreeProducer
// 
/**\class L1ExtraUpgradeTreeProducer L1ExtraUpgradeTreeProducer.cc UserCode/L1TriggerDPG/src/L1ExtraUpgradeTreeProducer.cc

Description: Produce L1 Extra tree

Implementation:
     
*/
//
// Original Author:  Alex Tapper
//         Created:  
// $Id: L1ExtraUpgradeTreeProducer.cc,v 1.5 2013/01/06 21:55:55 jbrooke Exp $
//
//


// system include files
#include <memory>

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

// data formats
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"

#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticleFwd.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkPrimaryVertex.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkEtMissParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkEtMissParticleFwd.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkEmParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkEmParticleFwd.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkElectronParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkElectronParticleFwd.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkJetParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkJetParticleFwd.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkTauParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkTauParticleFwd.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkHTMissParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkHTMissParticleFwd.h"


// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"

#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1ExtraUpgrade.h"

//
// class declaration
//

class L1ExtraUpgradeTreeProducer : public edm::EDAnalyzer {
public:
  explicit L1ExtraUpgradeTreeProducer(const edm::ParameterSet&);
  ~L1ExtraUpgradeTreeProducer();
  
  
private:
  virtual void beginJob(void) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

public:
  
  L1Analysis::L1AnalysisL1ExtraUpgrade* l1Extra;
  L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat * l1ExtraData;

private:

  unsigned maxL1Extra_;

  // output file
  edm::Service<TFileService> fs_;
  
  // tree
  TTree * tree_;

  edm::EDGetTokenT<l1extra::L1EmParticleCollection> nonIsoEmToken_;
  edm::EDGetTokenT<l1extra::L1EmParticleCollection> isoEmToken_;
  edm::EDGetTokenT<l1extra::L1JetParticleCollection> tauJetToken_;
  edm::EDGetTokenT<l1extra::L1JetParticleCollection> isoTauJetToken_;
  edm::EDGetTokenT<l1extra::L1JetParticleCollection> cenJetToken_;
  edm::EDGetTokenT<l1extra::L1JetParticleCollection> fwdJetToken_;
  edm::EDGetTokenT<l1extra::L1MuonParticleCollection> muonToken_;
  edm::EDGetTokenT<l1extra::L1EtMissParticleCollection> metToken_;
  edm::EDGetTokenT<l1extra::L1EtMissParticleCollection> mhtToken_;

  edm::EDGetTokenT<l1t::L1TkElectronParticleCollection> tkEGToken_;
  edm::EDGetTokenT<l1t::L1TkElectronParticleCollection> tkIsoEGToken_;
  edm::EDGetTokenT<l1t::L1TkEmParticleCollection> tkEMToken_;
  edm::EDGetTokenT<l1t::L1TkMuonParticleCollection> tkMuonToken_;
  edm::EDGetTokenT<l1t::L1TkTauParticleCollection> tkTauToken_;
  edm::EDGetTokenT<l1t::L1TkJetParticleCollection> tkJetToken_;
  edm::EDGetTokenT<l1t::L1TkEtMissParticleCollection> tkMetToken_;
  edm::EDGetTokenT<l1t::L1TkHTMissParticleCollection> tkMhtToken_;

};

L1ExtraUpgradeTreeProducer::L1ExtraUpgradeTreeProducer(const edm::ParameterSet& iConfig){

  nonIsoEmToken_ = consumes<l1extra::L1EmParticleCollection>(iConfig.getParameter<edm::InputTag>("nonIsoEmToken"));
  isoEmToken_ = consumes<l1extra::L1EmParticleCollection>(iConfig.getParameter<edm::InputTag>("isoEmToken"));
  tauJetToken_ = consumes<l1extra::L1JetParticleCollection>(iConfig.getParameter<edm::InputTag>("tauJetToken"));
  isoTauJetToken_ = consumes<l1extra::L1JetParticleCollection>(iConfig.getParameter<edm::InputTag>("isoTauJetToken"));
  cenJetToken_ = consumes<l1extra::L1JetParticleCollection>(iConfig.getParameter<edm::InputTag>("cenJetToken"));
  fwdJetToken_ = consumes<l1extra::L1JetParticleCollection>(iConfig.getParameter<edm::InputTag>("fwdJetToken"));
  muonToken_ = consumes<l1extra::L1MuonParticleCollection>(iConfig.getParameter<edm::InputTag>("muonToken"));
  metToken_ = consumes<l1extra::L1EtMissParticleCollection>(iConfig.getParameter<edm::InputTag>("metToken"));
  mhtToken_ = consumes<l1extra::L1EtMissParticleCollection>(iConfig.getParameter<edm::InputTag>("mhtToken"));

  tkEGToken_ = consumes<l1t::L1TkElectronParticleCollection>(iConfig.getParameter<edm::InputTag>("tkEGToken"));
  tkIsoEGToken_ = consumes<l1t::L1TkElectronParticleCollection>(iConfig.getParameter<edm::InputTag>("tkIsoEGToken"));
  tkEMToken_ = consumes<l1t::L1TkEmParticleCollection>(iConfig.getParameter<edm::InputTag>("tkEMToken"));
  tkMuonToken_ = consumes<l1t::L1TkMuonParticleCollection>(iConfig.getParameter<edm::InputTag>("tkMuonToken"));
  tkTauToken_ = consumes<l1t::L1TkTauParticleCollection>(iConfig.getParameter<edm::InputTag>("tkTauToken"));
  tkJetToken_ = consumes<l1t::L1TkJetParticleCollection>(iConfig.getParameter<edm::InputTag>("tkJetToken"));
  tkMetToken_ = consumes<l1t::L1TkEtMissParticleCollection>(iConfig.getParameter<edm::InputTag>("tkMetToken"));
  tkMhtToken_ = consumes<l1t::L1TkHTMissParticleCollection>(iConfig.getParameter<edm::InputTag>("tkMhtToken"));


  maxL1Extra_ = iConfig.getParameter<unsigned int>("maxL1Extra");
 
  l1Extra     = new L1Analysis::L1AnalysisL1ExtraUpgrade();
  l1ExtraData = l1Extra->getData();
  
  // set up output
  tree_=fs_->make<TTree>("L1ExtraUpgradeTree", "L1ExtraUpgradeTree");
  tree_->Branch("L1ExtraUpgrade", "L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat", &l1ExtraData, 32000, 3);

}


L1ExtraUpgradeTreeProducer::~L1ExtraUpgradeTreeProducer()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
L1ExtraUpgradeTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  
  l1Extra->Reset();

  edm::Handle<l1extra::L1EmParticleCollection> eg;
  edm::Handle<l1extra::L1EmParticleCollection> isoEG;
  edm::Handle<l1extra::L1JetParticleCollection> tau;
  edm::Handle<l1extra::L1JetParticleCollection> isoTau;
  edm::Handle<l1extra::L1JetParticleCollection> jet;
  edm::Handle<l1extra::L1JetParticleCollection> fwdJet;
  edm::Handle<l1extra::L1MuonParticleCollection> muon; ;
  edm::Handle<l1extra::L1EtMissParticleCollection> mets;
  edm::Handle<l1extra::L1EtMissParticleCollection> mhts;

  edm::Handle<l1t::L1TkElectronParticleCollection> tkEG;
  edm::Handle<l1t::L1TkElectronParticleCollection> tkIsoEG;
  edm::Handle<l1t::L1TkEmParticleCollection> tkEM;
  edm::Handle<l1t::L1TkMuonParticleCollection> tkMuon;
  edm::Handle<l1t::L1TkTauParticleCollection> tkTau;
  edm::Handle<l1t::L1TkJetParticleCollection> tkJet;
  edm::Handle<l1t::L1TkEtMissParticleCollection> tkMets;
  edm::Handle<l1t::L1TkHTMissParticleCollection> tkMhts;

  iEvent.getByToken(nonIsoEmToken_, eg);
  iEvent.getByToken(isoEmToken_, isoEG);
  iEvent.getByToken(tauJetToken_, tau);
  iEvent.getByToken(isoTauJetToken_, isoTau);
  iEvent.getByToken(cenJetToken_, jet);
  iEvent.getByToken(fwdJetToken_, fwdJet);
  iEvent.getByToken(muonToken_, muon);
  iEvent.getByToken(metToken_, mets);
  iEvent.getByToken(mhtToken_, mhts);


  iEvent.getByToken(tkEGToken_, tkEG);
  iEvent.getByToken(tkIsoEGToken_, tkIsoEG);
  iEvent.getByToken(tkEMToken_, tkEM);
  iEvent.getByToken(tkMuonToken_,tkMuon);
  iEvent.getByToken(tkTauToken_, tkTau);
  iEvent.getByToken(tkJetToken_, tkJet);
  iEvent.getByToken(tkMetToken_, tkMets);
  iEvent.getByToken(tkMhtToken_, tkMhts);


  if (eg.isValid()){ 
    l1Extra->SetEG(eg, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra EG not found.  Branch will not be filled" << std::endl;
  }

  if (isoEG.isValid()){ 
    l1Extra->SetIsoEG(isoEG, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra Iso EG not found. Branch will not be filled" << std::endl;
  }

  if (tkEG.isValid()){
    l1Extra->SetTkEG(tkEG, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkEG not found. Branch will not be filled" << std::endl;
  }

  if (tkIsoEG.isValid()){
    l1Extra->SetTkIsoEG(tkIsoEG, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkIsoEG not found. Branch will not be filled" << std::endl;
  }


  if (tkEM.isValid()){
    l1Extra->SetTkEM(tkEM, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkEM not found. Branch will not be filled" << std::endl;
  }

  if (tau.isValid()){ 
    l1Extra->SetTau(tau, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra Tau not found. Branch will not be filled" << std::endl;
  }

  if (isoTau.isValid()){ 
    l1Extra->SetIsoTau(isoTau, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra Iso Tau not found. Branch will not be filled" << std::endl;
  }
  if (tkTau.isValid()){
    l1Extra->SetTkTau(tkTau, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkTau not found. Branch will not be filled" << std::endl;
  }

  if (jet.isValid()){ 
    l1Extra->SetJet(jet, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra Jets not found. Branch will not be filled" << std::endl;
  }
  if (tkJet.isValid()){
    l1Extra->SetTkJet(tkJet, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkJets not found. Branch will not be filled" << std::endl;
  }


  if (fwdJet.isValid()){ 
    l1Extra->SetFwdJet(fwdJet, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade Fwd Jets not found. Branch will not be filled" << std::endl;
  }

  if (muon.isValid()){ 
    l1Extra->SetMuon(muon, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra Muons not found. Branch will not be filled" << std::endl;
  }
  if (tkMuon.isValid()){
    l1Extra->SetTkMuon(tkMuon, maxL1Extra_);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkMuons not found. Branch will not be filled" << std::endl;
  }


  if (mets.isValid()){ 
    l1Extra->SetMet(mets);
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra MET not found. Branch will not be filled" << std::endl;
  }
  if (tkMets.isValid()){
    l1Extra->SetTkMet(tkMets);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkMET not found. Branch will not be filled" << std::endl;
  }

  if (mhts.isValid()){ 
    l1Extra->SetMht(mhts);  
  } else {
    edm::LogWarning("MissingProduct") << "L1Extra MHT not found. Branch will not be filled" << std::endl;
  }
  if (tkMhts.isValid()){
    l1Extra->SetTkMht(tkMhts);
  } else {
    edm::LogWarning("MissingProduct") << "L1ExtraUpgrade TkMHT not found. Branch will not be filled" << std::endl;
  }


  tree_->Fill();

}

// ------------ method called once each job just before starting event loop  ------------
void 
L1ExtraUpgradeTreeProducer::beginJob(void)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1ExtraUpgradeTreeProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1ExtraUpgradeTreeProducer);
