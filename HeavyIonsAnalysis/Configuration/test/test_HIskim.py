import FWCore.ParameterSet.Config as cms


process = cms.Process("test")

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('test onia skim'),
    name = cms.untracked.string('$Source: /cvs/CMSSW/CMSSW/Configuration/Skimming/test/test_tauSkim.py,v $')
)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

# process.load("Configuration.StandardSequences.MagneticField_38T_cff")
# process.load("Configuration.StandardSequences.GeometryExtended_cff")
# process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc_hi', '')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       'file:b2jpsi_753reco.root'
        ),
)

process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
      ignoreTotal=cms.untracked.int32(0),
      oncePerEventMode = cms.untracked.bool(False)
      )
process.Timing = cms.Service("Timing")
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.MessageLogger.warnings = cms.untracked.PSet(
      threshold = cms.untracked.string('WARNING')
      )

process.source.inputCommands = cms.untracked.vstring("keep *", "drop *_MEtoEDMConverter_*_*")

process.load("HeavyIonsAnalysis.Configuration.onia_peripheral_cff")
process.hltZMMHI.TriggerResultsTag = cms.InputTag('TriggerResults','','RECO')
process.hltZMMHI.HLTPaths = ["*"] # here for the peripheral we need only this path; for the Central PD we need both this one, together with teh L2 and L3 jpsi and Upsilon paths
process.oniaFilter = cms.Path(process.zMMSkimSequence)

process.aodoutput = cms.OutputModule("PoolOutputModule",
                                        dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AOD'),
        filterName = cms.untracked.string('HI_onia')),
                                        SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('oniaFilter')),
                                        outputCommands = process.AODEventContent.outputCommands,
                                        fileName = cms.untracked.string('skimmed.root')
                                        )
process.output_step = cms.EndPath(process.aodoutput)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.schedule = cms.Schedule(process.oniaFilter,process.endjob_step,process.output_step)
