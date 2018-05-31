# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --python_filename=rerun_step2_L1_onMCL1_FEVTHLTDEBUG.py --no_exec -s L1 --datatier GEN-SIM-DIGI-RAW -n 1 --era Phase2_timing --eventcontent FEVTDEBUGHLT --filein file:/afs/cern.ch/user/r/rekovic/release/CMSSW_9_3_2/src/step2_DIGI_PU200_10ev.root --conditions 93X_upgrade2023_realistic_v2 --beamspot HLLHC14TeV --geometry Extended2023D17 --fileout file:step2_ZEE_PU200_1ev_rerun-L1-L1Ntuple.root --customise=L1Trigger/L1TNtuples/customiseL1Ntuple.L1NtupleEMU
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('L1',eras.Phase2_trigger)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('L1Trigger.TrackFindingTracklet.L1TrackletTracks_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
       fileNames = cms.untracked.vstring('/store/mc/PhaseIIFall17D/TT_TuneCUETP8M2T4_14TeV-powheg-pythia8/GEN-SIM-DIGI-RAW/L1TnoPU_93X_upgrade2023_realistic_v5-v2/10000/005A283E-8354-E811-8F6B-0CC47A2AECDC.root'),
#       fileNames = cms.untracked.vstring('/store/relval/CMSSW_9_3_7/RelValTTbar_14TeV/GEN-SIM-DIGI-RAW/PU25ns_93X_upgrade2023_realistic_v5_2023D17PU200-v1/10000/FCC765BD-332D-E811-A1F2-0242AC130002.root'),
#    fileNames = cms.untracked.vstring('/store/relval/CMSSW_9_3_7/RelValNuGun/GEN-SIM-DIGI-RAW/PU25ns_93X_upgrade2023_realistic_v5_2023D17PU200-v1/10000/F0067730-182D-E811-BAB9-0242AC130002.root'),
# /store/relval/CMSSW_9_3_7/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-DIGI-RAW/93X_upgrade2023_realistic_v5_2023D17noPU-v2/10000/02FA84D0-8D2C-E811-A9EA-0CC47A4D767A.root'),
    secondaryFileNames = cms.untracked.vstring(),
    inputCommands = cms.untracked.vstring("keep *", 
        "drop l1tHGCalTowerMapBXVector_hgcalTriggerPrimitiveDigiProducer_towerMap_HLT",
        "drop l1tEMTFHit2016Extras_simEmtfDigis_CSC_HLT",
        "drop l1tEMTFHit2016Extras_simEmtfDigis_RPC_HLT",
        "drop l1tEMTFHit2016s_simEmtfDigis__HLT",
        "drop l1tEMTFTrack2016Extras_simEmtfDigis__HLT",
        "drop l1tEMTFTrack2016s_simEmtfDigis__HLT")
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW'),
#        filterName = cms.untracked.string('')
#    ),
    fileName = cms.untracked.string('file:test_reprocess.root'),
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '100X_upgrade2023_realistic_v1', '')


process.load('SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff')
process.load('CalibCalorimetry.CaloTPG.CaloTPGTranscoder_cfi')

process.load('L1Trigger.L1THGCal.hgcalTriggerPrimitives_cff')
process.hgcl1tpg_step = cms.Path(process.hgcalTriggerPrimitives)

process.load('SimCalorimetry.EcalEBTrigPrimProducers.ecalEBTriggerPrimitiveDigis_cff')
process.EcalEBtp_step = cms.Path(process.simEcalEBTriggerPrimitiveDigis)

#process.TTClusterAssociatorFromPixelDigis.digiSimLinks          = cms.InputTag( "simSiPixelDigis","Tracker" )
process.L1TrackTrigger_step = cms.Path(process.L1TrackletTracksWithAssociators)

process.VertexProducer.l1TracksInputTag = cms.InputTag("TTTracksFromTracklet", "Level1TTTracks")

# Path and EndPath definitions
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

process.load("L1Trigger.L1TNtuples.l1PhaseIITreeProducer_cfi")

process.L1TkElectronsCrystal = cms.EDProducer("L1TkElectronTrackProducer",
    DRmax = cms.double(0.2),
    DRmin = cms.double(0.03),
    DeltaZ = cms.double(0.6),
    ETmin = cms.double(-1.0),
    IsoCut = cms.double(-0.1),
    L1EGammaInputTag = cms.InputTag("l1EGammaCrystalsProducer","L1EGammaCollectionBXVWithCuts"),
    L1TrackInputTag = cms.InputTag("TTTracksFromTracklet","Level1TTTracks"),
    PTMINTRA = cms.double(2.0),
    RelativeIsolation = cms.bool(True),
    TrackChi2 = cms.double(10000000000.0),
    TrackEGammaDeltaEta = cms.double(10000000000.0),
    TrackEGammaDeltaPhi = cms.vdouble(0.07, 0.0, 0.0),
    TrackEGammaDeltaR = cms.vdouble(0.08, 0.0, 0.0),
    TrackMinPt = cms.double(10.0),
    label = cms.string('EG'),
    useTwoStubsPT = cms.bool(False)
)
process.L1TkPhotonsCrystal = cms.EDProducer("L1TkEmParticleProducer",
    CHI2MAX = cms.double(100.0),
    DRmax = cms.double(0.3),
    DRmin = cms.double(0.07),
    DeltaZMax = cms.double(999.0),
    ETmin = cms.double(-1),
    IsoCut = cms.double(0.23),
    L1EGammaInputTag = cms.InputTag("l1EGammaCrystalsProducer","L1EGammaCollectionBXVWithCuts"),
    L1TrackInputTag = cms.InputTag("TTTracksFromTracklet","Level1TTTracks"),
    L1VertexInputTag = cms.InputTag("NotUsed"),
    PTMINTRA = cms.double(2.0),
    PrimaryVtxConstrain = cms.bool(False),
    RelativeIsolation = cms.bool(True),
    ZMAX = cms.double(25.0),
    label = cms.string('EG')
)



process.runmenutree=cms.Path(process.L1TkElectronsCrystal*process.L1TkPhotonsCrystal*process.l1PhaseIITree)

# Schedule definition
#process.schedule = cms.Schedule(process.EcalEBtp_step,process.hgcl1tpg_step,process.L1TrackTrigger_step,process.L1simulation_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)
process.schedule = cms.Schedule(process.L1TrackTrigger_step,process.L1simulation_step,process.runmenutree,process.endjob_step)#,process.FEVTDEBUGHLToutput_step)
#process.schedule = cms.Schedule(process.L1TrackTrigger_step,process.L1simulation_step,process.FEVTDEBUGHLToutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('L1Ntuple.root')
)



# Automatic addition of the customisation function from L1Trigger.L1TNtuples.customiseL1Ntuple
from L1Trigger.L1TNtuples.customiseL1Ntuple import L1NtupleGEN

#call to customisation function L1NtupleEMU imported from L1Trigger.L1TNtuples.customiseL1Ntuple
process = L1NtupleGEN(process)

# End of customisation functions

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
