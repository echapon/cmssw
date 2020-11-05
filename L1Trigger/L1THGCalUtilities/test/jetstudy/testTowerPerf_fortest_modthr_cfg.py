import FWCore.ParameterSet.Config as cms 

from Configuration.Eras.Era_Phase2C8_cff import Phase2C8
process = cms.Process('DIGI',Phase2C8)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2026D41Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2026D41_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedHLLHC14TeV_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

# Input source
process.source = cms.Source("PoolSource",
       # fileNames = cms.untracked.vstring('/store/relval/CMSSW_10_6_0_patch2/RelValDiQ_Pt20To300_Etam1p6Tom2p9/GEN-SIM-DIGI-RAW/106X_upgrade2023_realistic_v3_2023D41noPU-v1/20000/FDC6A85D-81B1-924D-920D-2AB6F6168F1E.root'),
       # fileNames = cms.untracked.vstring('/store/mc/PhaseIITDRSpring19DR/VBF_HToInvisible_M125_14TeV_powheg_pythia8/GEN-SIM-DIGI-RAW/NoPU_106X_upgrade2023_realistic_v3-v2/130000/EF41B2E3-2C44-1947-86D3-3A3729C31527.root'),
       fileNames = cms.untracked.vstring(options.inputFiles),
       inputCommands=cms.untracked.vstring(
           'keep *',
           'drop l1tEMTFHit2016Extras_simEmtfDigis_CSC_HLT',
           'drop l1tEMTFHit2016Extras_simEmtfDigis_RPC_HLT',
           'drop l1tEMTFHit2016s_simEmtfDigis__HLT',
           'drop l1tEMTFTrack2016Extras_simEmtfDigis__HLT',
           'drop l1tEMTFTrack2016s_simEmtfDigis__HLT',
           'drop FTLClusteredmNewDetSetVector_mtdClusters_FTLBarrel_RECO',
           'drop FTLClusteredmNewDetSetVector_mtdClusters_FTLEndcap_RECO',
           'drop MTDTrackingRecHitedmNewDetSetVector_mtdTrackingRecHits__RECO',
           'drop BTLDetIdBTLSampleFTLDataFrameTsSorted_mix_FTLBarrel_HLT',
           'drop ETLDetIdETLSampleFTLDataFrameTsSorted_mix_FTLEndcap_HLT',
           ),
       # skipEvents = cms.untracked.uint32(107)#178)
       )

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.20 $'),
    annotation = cms.untracked.string('SingleElectronPt10_cfi nevts:10'),
    name = cms.untracked.string('Applications')
)

# Output definition
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("ntuple.root")
    )

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')

# load HGCAL TPG simulation
process.load('L1Trigger.L1THGCal.hgcalTriggerPrimitives_cff')

# To add truth-matched calo cells and downstream objects
#process.load('L1Trigger.L1THGCalUtilities.caloTruthCells_cff')
#process.hgcalTriggerPrimitives += process.caloTruthCells
#process.load('L1Trigger.L1THGCalUtilities.caloTruthCellsNtuples_cff')

process.hgcl1tpg_step = cms.Path(process.hgcalTriggerPrimitives)


# load ntuplizer
process.load('L1Trigger.L1THGCalUtilities.hgcalTriggerNtuples_cff')
# do not store digis
process.hgcalTriggerNtuplizer = cms.EDAnalyzer(
      "HGCalTriggerNtupleManager",
      Ntuples = cms.VPSet(
         process.ntuple_event,
         process.ntuple_gen,
         process.ntuple_genjet,
         # process.ntuple_gentau,
         # process.ntuple_digis,
         process.ntuple_triggercells,
         process.ntuple_triggersums,
         process.ntuple_clusters,
         process.ntuple_multiclusters,
         process.ntuple_towers
         )
      )
process.ntuple_step = cms.Path(process.hgcalTriggerNtuples)

# Schedule definition
process.schedule = cms.Schedule(process.hgcl1tpg_step, process.ntuple_step)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

# customise towers
from L1Trigger.L1THGCal.customTowers import *
custom_towers_unclustered_tc(process)
# custom_towers_all_tc(process)

# custom threshold
# from L1Trigger.L1THGCal.customHistoSeeding import *
# custom_3dclustering_histoThreshold(process,seed_threshold=cms.double(6.5))

# # customise 3D cluster seeding
# from L1Trigger.L1THGCal.customHistoSeeding import *
# custom_3dclustering_XYHistoMax(process)
