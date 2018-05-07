import FWCore.ParameterSet.Config as cms



l1ExtraUpgradeTreeProducer = cms.EDAnalyzer("L1ExtraUpgradeTreeProducer",
   nonIsoEmToken = cms.InputTag("l1extraParticles","NonIsolated"),
   isoEmToken = cms.InputTag("l1extraParticles","Isolated"), # not too sure about these, is eg="iso+noniso"? check

   tkEGToken = cms.InputTag("L1TkElectrons","EG"),

   tkIsoEGToken = cms.InputTag("L1TkIsoElectrons","EG"),
   tkEMToken = cms.InputTag("L1TkPhotons","EG"), 
    
   tauJetToken = cms.InputTag("l1extraParticles","Tau"), # is this right? 
   isoTauJetToken = cms.InputTag("l1extraParticles","IsoTau"), # is this right?
   tkTauToken = cms.InputTag("L1TkTauFromCalo",""), # ?

   cenJetToken = cms.InputTag("l1extraParticles","Central"),   # L1Jets, but are these right? do they use the HGC?                                            

   tkMuonToken = cms.InputTag("L1TkMuons",""),                                            

   tkJetToken = cms.InputTag("L1TkJets","Central"),                                            

   fwdJetToken = cms.InputTag("l1extraParticles","Forward"),

   muonToken = cms.InputTag("l1extraParticles"), 
   metToken = cms.InputTag("l1extraParticles","MET"),
   tkMetToken = cms.InputTag("L1TkEtMiss","MET"),

   mhtToken = cms.InputTag("l1extraParticles","MHT"),
   tkMhtToken = cms.InputTag("L1TkHTMissVtx",""),
   maxL1Extra = cms.uint32(20)
)

