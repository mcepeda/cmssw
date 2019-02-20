import FWCore.ParameterSet.Config as cms

# Phase I EG seeds - obsolete! 
from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkElectrons
pL1TkElectrons = cms.Path( L1TkElectrons )

from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkIsoElectrons
pL1TkIsoElectrons = cms.Path( L1TkIsoElectrons )

from L1Trigger.L1TTrackMatch.L1TkEmParticleProducer_cfi import L1TkPhotons
pL1TkPhotons = cms.Path( L1TkPhotons )

# Phase II EG seeds, Barrel (Crystal):

from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkElectronsCrystal
pL1TkElectronsCrystal = cms.Path( L1TkElectronsCrystal )

from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkElectronsLooseCrystal
pL1TkElectronsLooseCrystal = cms.Path( L1TkElectronsLooseCrystal )

from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkIsoElectronsCrystal
pL1TkIsoElectronsCrystal = cms.Path( L1TkIsoElectronsCrystal )

from L1Trigger.L1TTrackMatch.L1TkEmParticleProducer_cfi import L1TkPhotonsCrystal
pL1TkPhotonsCrystal = cms.Path( L1TkPhotonsCrystal )

# Phase II EG seeds, Endcap (HGC):
# Two objects for now to follow 2017 discussions, merging collections would be nice...

from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkElectronsHGC
pL1TkElectronsHGC = cms.Path( L1TkElectronsHGC )

from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkIsoElectronsHGC
pL1TkIsoElectronsHGC = cms.Path( L1TkIsoElectronsHGC )

from L1Trigger.L1TTrackMatch.L1TkElectronTrackProducer_cfi import L1TkElectronsLooseHGC
pL1TkElectronsLooseHGC = cms.Path( L1TkElectronsLooseHGC )

from L1Trigger.L1TTrackMatch.L1TkEmParticleProducer_cfi import L1TkPhotonsHGC
pL1TkPhotonsHGC = cms.Path( L1TkPhotonsHGC )



from L1Trigger.L1TTrackMatch.L1TrackerJetProducer_cfi import L1TrackerJets
pL1TrackerJets = cms.Path( L1TrackerJets)

from L1Trigger.L1TTrackMatch.L1TkCaloJetProducer_cfi import L1TkCaloJets
pL1TkCaloJets = cms.Path( L1TkCaloJets)

from L1Trigger.L1TTrackMatch.L1TkPrimaryVertexProducer_cfi import L1TkPrimaryVertex
pL1TkPrimaryVertex = cms.Path( L1TkPrimaryVertex )

from L1Trigger.L1TTrackMatch.L1TrackerEtMissProducer_cfi import L1TrackerEtMiss
pL1TrkMET = cms.Path( L1TrackerEtMiss )

from L1Trigger.L1TTrackMatch.L1TkHTMissProducer_cfi import L1TkCaloHTMissVtx, L1TrackerHTMiss
pL1TkCaloHTMissVtx = cms.Path( L1TkCaloHTMissVtx )
pL1TrackerHTMiss = cms.Path( L1TrackerHTMiss )

from L1Trigger.L1TTrackMatch.L1TkMuonProducer_cfi import L1TkMuons
pL1TkMuon = cms.Path( L1TkMuons )

from L1Trigger.L1TTrackMatch.L1TkGlbMuonProducer_cfi import L1TkGlbMuons
pL1TkGlbMuon = cms.Path( L1TkGlbMuons )

from L1Trigger.L1TTrackMatch.L1TkTauFromCaloProducer_cfi import L1TkTauFromCalo
pL1TkTauFromCalo = cms.Path( L1TkTauFromCalo )
