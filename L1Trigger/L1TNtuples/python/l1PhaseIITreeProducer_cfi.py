import FWCore.ParameterSet.Config as cms

l1PhaseIITree = cms.EDAnalyzer("L1PhaseIITreeProducer",
   egToken = cms.untracked.InputTag("simCaloStage2Digis"),
   jetToken = cms.untracked.InputTag("simCaloStage2Digis"),
   muonLegacyToken = cms.untracked.InputTag("muonLegacyInStage2FormatDigis","legacyMuon"),
   muonToken = cms.untracked.InputTag("simGmtStage2Digis"),
   sumToken = cms.untracked.InputTag("simCaloStage2Digis"),
   tauTokens = cms.untracked.VInputTag("simCaloStage2Digis"),
   egCrystalTokens = cms.VInputTag(cms.InputTag("l1EGammaCrystalsProducer","L1EGammaCollectionBXVWithCuts"),cms.InputTag("l1EGammaEEProducer","L1EGammaCollectionBXVWithCuts")),

   tkEGToken = cms.InputTag("L1TkElectrons","EG"),
   tkIsoEGToken = cms.InputTag("L1TkIsoElectrons","EG"),
   tkEMToken = cms.InputTag("L1TkPhotons","EG"), 

   tkEGCrystalTokens = cms.VInputTag( cms.InputTag("L1TkElectronsCrystal","EG"),cms.InputTag("L1TkElectronsHGC","EG") ),
   tkEMCrystalTokens = cms.VInputTag( cms.InputTag("L1TkPhotonsCrystal","EG"),cms.InputTag("L1TkPhotonsHGC","EG") ),


   tkTauToken = cms.InputTag("L1TkTauFromCalo",""), # ?
   tkMuonToken = cms.InputTag("L1TkMuons",""),                                            
   tkJetToken = cms.InputTag("L1TkJets","Central"),                                            
   tkMetToken = cms.InputTag("L1TkEtMiss","MET"),
   tkMhtToken = cms.InputTag("L1TkHTMissVtx",""),

   ak4L1Calo = cms.InputTag("ak4L1Calo"),
   ak4L1PF = cms.InputTag("ak4L1PF"),
   ak4L1TK = cms.InputTag("ak4L1TightTKV"),
 
   muonKalman = cms.InputTag("simKBmtfDigis","BMTF"),

   l1CaloMet = cms.InputTag("l1MetCalo"),
   l1PFMet = cms.InputTag("l1MetPF"),
   l1TKMet = cms.InputTag("l1MetTightTKV"),

   maxL1Extra = cms.uint32(20)
)

