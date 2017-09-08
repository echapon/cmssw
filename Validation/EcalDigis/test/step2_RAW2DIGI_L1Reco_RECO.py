# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --process RECO --repacked --conditions 75X_dataRun2_PromptHI_v3 --scenario HeavyIons -s RAW2DIGI,L1Reco,RECO --datatier AOD --customise Configuration/DataProcessing/RecoTLR.customiseRun2CommonHI --data --eventcontent AOD --no_exec --filein /store/hidata/HIRun2015/HIMinimumBias1/RAW/v1/000/262/703/00000/D0A0C193-DB94-E511-B5C4-02163E011FB1.root
import FWCore.ParameterSet.Config as cms

<<<<<<< HEAD
#######################################################
# MASTER SWICTHes
#######################################################

dataset = 'HIPhoton40AndZ'
runEmulator = False
emulScenario = 2016
=======

# MASTER SWICTH
dataset = 'HIPhoton40AndZ'
runEmulator = False
emulScenario = 2016
# dataset = 'HIEWQExo'
>>>>>>> e0e59d06736... Add modified files
trigger = '' # 'HLT_HIFullTrack12_L1Centrality010_v2' # 'HLT_L1MinimumBiasHF1OR_v1' # 'HLT_HIL1Tech7_NoBPTX_v1'
# trigger = 'HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1'
# HLTPaths = ['HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1'], # (300Hz, fed into MinimumBias1)
# HLTPaths = ['HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1'], #  (3Hz, fed into MinimumBias1)
# HLTPaths = ['HLT_HIUCC020_v3'], # UCC 3Hz
<<<<<<< HEAD
nEvents = 300

doReco = False       # do we want to get a reco file?
doFullDQM  = False       # do we want to get a detailed DQM file?
# note: if we don't want reco neither DQM, we'll assume we'll just run the ECAL re-emulation validation, which is also DQM but a small file
doECALvalid = (not doReco) and (not doFullDQM)

#######################################################
=======
>>>>>>> e0e59d06736... Add modified files

process = cms.Process('RECO')
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
# process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('CommonTools.ParticleFlow.EITopPAG_cff')
<<<<<<< HEAD
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
if doFullDQM:
   process.load('DQMOffline.Configuration.DQMOfflineHeavyIons_cff')
if doECALvalid:
   # DQM services
   process.load("DQMServices.Core.DQM_cfg")
   process.load("DQMServices.Components.DQMEnvironment_cfi")
   process.dqmSaver.workflow = "/HIRun2015/Commissioning/RAW"
   #process.load("CalibCalorimetry.Configuration.Ecal_FakeConditions_cff")
   #process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
   process.load("DQM.Integration.config.FrontierCondition_GT_Offline_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(nEvents)
=======
process.load('DQMOffline.Configuration.DQMOfflineHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(30)
>>>>>>> e0e59d06736... Add modified files
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/hidata/HIRun2015/HIPhoton40AndZ/RAW/v1/000/262/921/00000/02EE59B5-5898-E511-90D2-02163E0140EE.root'),
    # fileNames = cms.untracked.vstring('file:/tmp/echapon/D0A0C193-DB94-E511-B5C4-02163E011FB1.root'),
    secondaryFileNames = cms.untracked.vstring()
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

<<<<<<< HEAD
if doReco:
   process.AODoutput = cms.OutputModule("PoolOutputModule",
       compressionAlgorithm = cms.untracked.string('LZMA'),
       compressionLevel = cms.untracked.int32(4),
       dataset = cms.untracked.PSet(
           dataTier = cms.untracked.string('AOD'),
           filterName = cms.untracked.string('')
       ),
       eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
       fileName = cms.untracked.string('step2_RAW2DIGI_L1Reco_RECO.root'),
       # outputCommands = process.AODEventContent.outputCommands
       outputCommands = process.FEVTDEBUGEventContent.outputCommands
   )

if doFullDQM:
   process.DQMoutput = cms.OutputModule("DQMRootOutputModule",
       dataset = cms.untracked.PSet(
           dataTier = cms.untracked.string('DQMIO'),
           filterName = cms.untracked.string('')
       ),
       fileName = cms.untracked.string('step2_RAW2DIGI_L1Reco_RECO_EI_DQM_inDQM.root'),
       outputCommands = process.DQMEventContent.outputCommands,
       splitLevel = cms.untracked.int32(0)
   )
=======
process.AODoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AOD'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    fileName = cms.untracked.string('step2_RAW2DIGI_L1Reco_RECO.root'),
    outputCommands = process.AODEventContent.outputCommands
)

process.DQMoutput = cms.OutputModule("DQMRootOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('DQMIO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step2_RAW2DIGI_L1Reco_RECO_EI_DQM_inDQM.root'),
    outputCommands = process.DQMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)
>>>>>>> e0e59d06736... Add modified files

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
# process.endjob_step = cms.EndPath(process.endOfProcess)
process.eventinterpretaion_step = cms.Path(process.EIsequence)
<<<<<<< HEAD
if doFullDQM:
   process.dqmoffline_step = cms.Path(process.DQMOfflineHeavyIons)
   process.DQMoutput_step = cms.EndPath(process.DQMoutput)
if doReco:
   process.AODoutput_step = cms.EndPath(process.AODoutput)
=======
process.dqmoffline_step = cms.Path(process.DQMOfflineHeavyIons)
process.AODoutput_step = cms.EndPath(process.AODoutput)
process.DQMoutput_step = cms.EndPath(process.DQMoutput)
>>>>>>> e0e59d06736... Add modified files

# initialize  MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

###############################################
# Re-emulation
###############################################

# Added by Stathes
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

# geometry (Only Ecal)
#process.load("Geometry.EcalCommonData.EcalOnly_cfi")
#process.load("Geometry.CaloEventSetup.CaloGeometry_cff")
#process.load("Geometry.CaloEventSetup.EcalTrigTowerConstituents_cfi")
#process.load("Geometry.EcalMapping.EcalMapping_cfi")
#process.load("Geometry.EcalMapping.EcalMappingRecord_cfi")

<<<<<<< HEAD
=======
# DQM services
# process.load("DQMServices.Core.DQM_cfg")
# process.load("DQMServices.Components.DQMEnvironment_cfi")
# process.dqmSaver.workflow = "/HIRun2015/Commissioning/RAW"
# #process.load("CalibCalorimetry.Configuration.Ecal_FakeConditions_cff")
# #process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
# process.load("DQM.Integration.config.FrontierCondition_GT_Offline_cfi")
>>>>>>> e0e59d06736... Add modified files

# Local database for emulator setup (to change ZS thresholds!)
#----------------------------------------------------------------------
#To overwrite Selective readout settings with settings from a local DB (sqlite file): 
#process.load("CondCore.CondDB.CondDB_cfi")
# from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

if runEmulator:
   if emulScenario == 2016:
      ### do NOT do nothing
      # print 'do nothing with the global tag for scenario 2016'
      process.GlobalTag.toGet = cms.VPSet(
            cms.PSet(record = cms.string("EcalSRSettingsRcd"),
               tag = cms.string("EcalSRSettings_LTH1.5_HTH2.5GeV_ZS4.5_6.5ADC_mc"),
               connect = cms.string("sqlite_file:EcalSRSettings_LTH1.5_HTH2.5GeV_ZS4.5_6.5ADC_mc.db")
               )
            )
   elif emulScenario == 0: # or emulScenario == 2016:
      process.GlobalTag.toGet = cms.VPSet(
            cms.PSet(record = cms.string("EcalSRSettingsRcd"),
               tag = cms.string("EcalSRSettings_LTH2.5_HTH5.5GeV_ZS5_7ADC_ZS2.5_3.5ADC_mc"),
               connect = cms.string("sqlite_file:EcalSRSettings_LTH2.5_HTH5.5GeV_ZS5_7ADC_ZS2.5_3.5ADC_mc.db")
               )
            )
   elif emulScenario == 1:
      process.GlobalTag.toGet = cms.VPSet(
            cms.PSet(record = cms.string("EcalSRSettingsRcd"),
               # Scenario 1
               tag = cms.string("EcalSRSettings_LTH2.5_HTH4.5GeV_ZS4.5_6.5ADC_mc"),
               connect = cms.string("sqlite_file:EcalSRSettings_LTH2.5_HTH4.5GeV_ZS4.5_6.5ADC_mc.db")
               )
            )
   elif emulScenario == 2 or emulScenario == 6:
      process.GlobalTag.toGet = cms.VPSet(
            cms.PSet(record = cms.string("EcalSRSettingsRcd"),
               # Scenario 2 and 6 (same db file)
               tag = cms.string("EcalSRSettings_LTH2_HTH3GeV_ZS5.5_8ADC_mc"),
               connect = cms.string("sqlite_file:EcalSRSettings_LTH2_HTH3GeV_ZS5.5_8ADC_mc.db")
               )
            )
   elif emulScenario == 3:
      process.GlobalTag.toGet = cms.VPSet(
            cms.PSet(record = cms.string("EcalSRSettingsRcd"),
               # Scenario 3
               tag = cms.string("EcalSRSettings_LTH2_HTH3GeV_ZS4.5_6.5ADC_ZS2_3ADC_mc"),
               connect = cms.string("sqlite_file:EcalSRSettings_LTH2_HTH3GeV_ZS4.5_6.5ADC_ZS2_3ADC_mc.db")
               )
            )
   elif emulScenario == 4:
      process.GlobalTag.toGet = cms.VPSet(
            cms.PSet(record = cms.string("EcalSRSettingsRcd"),
               # Scenario 4
               tag = cms.string("EcalSRSettings_LTH2_HTH3.5GeV_ZS4.5_7ADC_ZS2_3ADC_mc"),
               connect = cms.string("sqlite_file:EcalSRSettings_LTH2_HTH3.5GeV_ZS4.5_7ADC_ZS2_3ADC_mc.db")
               )
            )
   elif emulScenario == 5:
      process.GlobalTag.toGet = cms.VPSet(
            cms.PSet(record = cms.string("EcalSRSettingsRcd"),
               # Scenario 5
               tag = cms.string("EcalSRSettings_LTH2.5_HTH5.5GeV_ZS5_7ADC_ZS2.5_3.5ADC_mc"),
               connect = cms.string("sqlite_file:EcalSRSettings_LTH2.5_HTH5.5GeV_ZS5_7ADC_ZS2.5_3.5ADC_mc.db")
               #             tag = cms.string("EcalSRSettings_beam2017_option4b_v00_mc"),
               #             connect = cms.string("sqlite_file:EcalSRSettings_beam2017_option4b_v00_mc.db")
               )
            )

#----------------------------------------------------------------------

# Sequence info:
# 0. ecalEBunpacker runs: 
#    - it will provide the Trigger Prims (i.e. LI, HI trigger towers, their Et etc).
#    - the name of the output is "EcalTriggerPrimitives"
#    - if input file is data, then the TPs are data
# 1. ecalDigiSequence defined but only "simEcalDigis" runs:
# ecalDigiSequence = cms.Sequence(simEcalTriggerPrimitiveDigis*simEcalDigis*simEcalPreshowerDigis)
#    - Here the simEcalDigis, reads EB and EE digis and TPs from the unpacker
#    - Output names are "egDigis" and "eeDigis"
#    - simEcalDigis also output the "ebSrFlags" and "eeSrFlags"
#    - The user may invoke emulation (EcalSelectiveReadoutSuppressor.cc) uncommenting
#    the flags at the end of this macro.
#    The difference is that the simEcalDigis re-does zero suppression from scratch.
#    It uses the input TTPrimitives getting from there the suppressed Et(), but then
#    it redefines LI,MI,HI etc. Of course I would hope nothing changes as far as the 
#    TTPrims are concerned, but the ZS being repeated should cut more data and 
#    reduce the DCC load!
# 2. ecalSelectiveReadoutValidation runs:
#    Its input can be the output of the unpacker, or the output of the simEcalDigis.
#    - It simply makes a number of SR validation histograms based on the input digis.
#    - If we want to plot the emulated ADC FIR histograms, these histograms are calculated 
#      in the validation code by applying the FIR weights on ADC samples coming from the 
#      input digis. So the ADC FIR histograms depend on the input ebDigis eeDigis.
#

# ECAL Unpacker:
process.load("EventFilter.EcalRawToDigi.EcalUnpackerMapping_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")
process.ecalEBunpacker.silentMode = cms.untracked.bool(True)

#
# ECAL digitization sequence
#
process.load("SimCalorimetry.Configuration.ecalDigiSequence_cff")
process.simEcalDigis.trigPrimProducer = cms.string('ecalEBunpacker')# Label name of input ECAL trigger primitive collection
process.simEcalDigis.trigPrimCollection =  cms.string('EcalTriggerPrimitives')# Input trigger prim collection
process.simEcalDigis.digiProducer = cms.string('ecalEBunpacker')#Input Label of EB EE digi collections
process.simEcalDigis.EBdigiCollection = cms.string('ebDigis')#Input Digis
process.simEcalDigis.EEdigiCollection = cms.string('eeDigis')#Input Digis
process.simEcalDigis.EBSRPdigiCollection = cms.string('SRebDigis')#output Digis (emulated)
process.simEcalDigis.EESRPdigiCollection = cms.string('SReeDigis')#output Digis (emulated)
#Note that the output flags have names (default): ebSrFlags,eeSrFlags


#
# Ecal selective readout validation module, ecalSelectiveReadoutValidation:
#
process.load("Validation.EcalDigis.ecalSelectiveReadoutValidation_cfi")
process.ecalSelectiveReadoutValidation.outputFile = 'srvalid_hists.root'
<<<<<<< HEAD
process.ecalSelectiveReadoutValidation.verbose = cms.untracked.bool(True);
=======
process.ecalSelectiveReadoutValidation.verbose = cms.untracked.bool(False);
>>>>>>> e0e59d06736... Add modified files

#INPUTS:
process.ecalSelectiveReadoutValidation.EbUnsuppressedDigiCollection = cms.InputTag("simEcalUnsuppressedDigis")
process.ecalSelectiveReadoutValidation.EeUnsuppressedDigiCollection = cms.InputTag("simEcalUnsuppressedDigis")
#changed:
if not runEmulator:
   #DQM: here we use straight the data (no emulator)
   #     the output of the unpacker will be used by the ecalSelectiveReadoutValidation.
   process.ecalSelectiveReadoutValidation.EbDigiCollection = cms.InputTag("ecalEBunpacker","ebDigis")#input digis to SRValid
   process.ecalSelectiveReadoutValidation.EeDigiCollection = cms.InputTag("ecalEBunpacker","eeDigis")#input digis to SRValid
   process.ecalSelectiveReadoutValidation.EbSrFlagCollection = cms.InputTag("ecalEBunpacker","")#input flags
   process.ecalSelectiveReadoutValidation.EeSrFlagCollection = cms.InputTag("ecalEBunpacker","")#input flags
   process.ecalSelectiveReadoutValidation.TrigPrimCollection = cms.InputTag("ecalEBunpacker", "EcalTriggerPrimitives")
else:
   #
   #My MC script: (if you turn on the emulator uncomment the following).
   # Here we force the simEcalDigis to do the zero suppression and their output will go 
   # to the ecalSelectiveReadoutValidation.
   process.ecalSelectiveReadoutValidation.EbDigiCollection = cms.InputTag("simEcalDigis","SRebDigis")#input digis to SRValid
   process.ecalSelectiveReadoutValidation.EeDigiCollection = cms.InputTag("simEcalDigis","SReeDigis")#input digis to SRValid
   process.ecalSelectiveReadoutValidation.EbSrFlagCollection = cms.InputTag("simEcalDigis","ebSrFlags")#input is the output of simEcalDigis
   process.ecalSelectiveReadoutValidation.EeSrFlagCollection = cms.InputTag("simEcalDigis","eeSrFlags")#input
   process.ecalSelectiveReadoutValidation.TrigPrimCollection = cms.InputTag("simEcalDigis", "simEcalTriggerPrimitives")
   # process.ecalSelectiveReadoutValidation.TrigPrimCollection = cms.InputTag("ecalDigis", "EcalTriggerPrimitives")
<<<<<<< HEAD

   from SimCalorimetry.EcalSimProducers.ecaldigi_cfi import *
   from SimCalorimetry.EcalSelectiveReadoutProducers.ecalDigis_cfi import *

=======
>>>>>>> e0e59d06736... Add modified files
   if emulScenario == 2016:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 4.5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6.5
      process.simEcalDigis.trigPrimBypassLTH = cms.double(3)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(5) 
   elif emulScenario == 0:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 7
      process.simEcalDigis.trigPrimBypassLTH = cms.double(5.)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(11.) 
   elif emulScenario == 1:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 4.5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6.5
      process.simEcalDigis.trigPrimBypassLTH = cms.double(5.)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(9.) 
   elif emulScenario == 2:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 5.5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 8
      process.simEcalDigis.trigPrimBypassLTH = cms.double(4.)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(6.) 
   elif emulScenario == 3:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 4.5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6.5
      process.simEcalDigis.trigPrimBypassLTH = cms.double(4.)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(6.) 
   elif emulScenario == 4:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 4.5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 7
      process.simEcalDigis.trigPrimBypassLTH = cms.double(4.)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(7.) 
   elif emulScenario == 5:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 7
      process.simEcalDigis.trigPrimBypassLTH = cms.double(5.)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(11.) 
   elif emulScenario == 99: # dummy, for testing purposes
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 99
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 99
      process.simEcalDigis.trigPrimBypassLTH = cms.double(99.)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(99.) 
   elif emulScenario == 2015:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 2.75
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6
      process.simEcalDigis.trigPrimBypassLTH = cms.double(2)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(4) 
   elif emulScenario == 20161:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 4.5
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6
      process.simEcalDigis.trigPrimBypassLTH = cms.double(2)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(4) 
   elif emulScenario == 20162:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 2.75
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6.5
      process.simEcalDigis.trigPrimBypassLTH = cms.double(2)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(4) 
   elif emulScenario == 20163:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 2.75
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6
      process.simEcalDigis.trigPrimBypassLTH = cms.double(3)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(4) 
   elif emulScenario == 20164:
      process.ecalSelectiveReadoutValidation.ebZsThrADCCount = 2.75
      process.ecalSelectiveReadoutValidation.eeZsThrADCCount = 6
      process.simEcalDigis.trigPrimBypassLTH = cms.double(2)
      process.simEcalDigis.trigPrimBypassHTH = cms.double(5) 
# end

#process.ecalSelectiveReadoutValidation.EbSrFlagFromTTCollection = cms.InputTag("simEcalDigis","ebSrFlags")
#process.ecalSelectiveReadoutValidation.EeSrFlagFromTTCollection = cms.InputTag("simEcalDigis","eeSrFlags")
###process.ecalSelectiveReadoutValidation.EbRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB")
###process.ecalSelectiveReadoutValidation.EventHeaderCollection = cms.InputTag("ecalEBunpacker")
#process.ecalSelectiveReadoutValidation.ecalDccZs1stSample = 2
#process.ecalSelectiveReadoutValidation.dccWeights = [ -0.374, -0.374, -0.3629, 0.2721, 0.4681, 0.3707 ]
process.ecalSelectiveReadoutValidation.histDir = ''
process.ecalSelectiveReadoutValidation.histograms = [ 'all' ]
#process.ecalSelectiveReadoutValidation.useEventRate = False
process.ecalSelectiveReadoutValidation.LocalReco = cms.bool(False) # local pulse Ampl reco
process.ecalSelectiveReadoutValidation.IsDATA    = cms.bool(True)


process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck")

process.tpparams12 = cms.ESSource("EmptyESSource",
    recordName = cms.string('EcalTPGPhysicsConstRcd'),
    iovIsRunNotTime = cms.bool(True),
    firstValid = cms.vuint32(1)
)

# # trigger filter
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.TriggerFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
      TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
      HLTPaths = [trigger],
      #andOr = cms.bool(True),   # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
      throw = True, ## throw exception on unknown path names
      )

# ## SEQUENCE
process.TriggerSelectionSequence = cms.Sequence(
      process.TriggerFilter
      )

<<<<<<< HEAD
if doECALvalid:
   process.p1 = cms.Path(
         process.ecalEBunpacker
         # *process.simEcalTriggerPrimitiveDigis
         *process.simEcalDigis*process.ecalSelectiveReadoutValidation
         *process.dqmSaver
         )
else:
   process.p1 = cms.Path(
         process.ecalEBunpacker
         # *process.simEcalTriggerPrimitiveDigis
         *process.simEcalDigis*process.ecalSelectiveReadoutValidation
         )
=======
process.p1 = cms.Path(
      process.ecalEBunpacker
      # *process.simEcalTriggerPrimitiveDigis
      *process.simEcalDigis*process.ecalSelectiveReadoutValidation
      # *process.dqmSaver
      )
>>>>>>> e0e59d06736... Add modified files

# if trigger != '':
#    process.p1 = cms.Path(
#          process.TriggerSelectionSequence*
#          process.ecalEBunpacker*process.simEcalTriggerPrimitiveDigis*process.simEcalDigis*process.ecalSelectiveReadoutValidation
#          # *process.dqmSaver
#          )

#SP#process.DQM.collectorHost = ''

#
# switch Modify ECAL SR
#
# to work you need (1) to uncomment the bypass flags below,
# (2) you need to uncomment the 4 lines above (see "turn on the emulator" above)
if runEmulator:
<<<<<<< HEAD
   process.simEcalDigis.trigPrimBypass = cms.bool(True) # uncomment to bypass
   process.simEcalDigis.trigPrimBypassMode = cms.int32(1) #bypass mode (uncomment)
=======
   from SimCalorimetry.EcalSimProducers.ecaldigi_cfi import *
   from SimCalorimetry.EcalSelectiveReadoutProducers.ecalDigis_cfi import *
   # process.simEcalDigis.trigPrimBypass = cms.bool(True) # uncomment to bypass
   # process.simEcalDigis.trigPrimBypassMode = cms.int32(1) #bypass mode (uncomment)
>>>>>>> e0e59d06736... Add modified files
   # # process.simEcalDigis.trigPrimBypassLTH = cms.double(5.)# 2xGeV
   # # process.simEcalDigis.trigPrimBypassHTH = cms.double(11.)# 2xGeV
   #switch to apply selective readout decision on the digis and produce
   process.simEcalDigis.produceDigis = cms.untracked.bool(True)
<<<<<<< HEAD
   # process.simEcalTriggerPrimitiveDigis.Label = cms.string('simEcalUnsuppressedDigis')
   # process.simEcalTriggerPrimitiveDigis.Label = cms.string('simEcalEBunpacker')
   # process.simEcalTriggerPrimitiveDigis.InstanceEB = cms.string('simEcalDigis')
   # process.simEcalTriggerPrimitiveDigis.InstanceEE = cms.string('simEcalDigis')
=======
   # process.simEcalTriggerPrimitiveDigis.Label = cms.string('ecalUnsuppressedDigis')
   # process.simEcalTriggerPrimitiveDigis.Label = cms.string('ecalEBunpacker')
   # process.simEcalTriggerPrimitiveDigis.InstanceEB = cms.string('ecalDigis')
   # process.simEcalTriggerPrimitiveDigis.InstanceEE = cms.string('ecalDigis')
>>>>>>> e0e59d06736... Add modified files

# # customise for PbPb (not needed thanks to the --repacked option in the cmsDriver command
# process.ecalEBunpacker.InputLabel = cms.InputTag('rawDataRepacker')

###############################################
# Schedule definition
# process.schedule = cms.Schedule(process.p1,process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.AODoutput_step)
<<<<<<< HEAD
process.schedule = cms.Schedule(process.p1
      # ,process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,
      # process.eventinterpretaion_step,
      # process.dqmoffline_step,process.AODoutput_step,process.DQMoutput_step
      )
      # process.dqmoffline_step,process.DQMoutput_step)

if (doReco or doFullDQM):
<<<<<<< HEAD
   process.schedule.append(process.raw2digi_step)
   process.schedule.append(process.L1Reco_step)
   process.schedule.append(process.reconstruction_step)
if doFullDQM:
   process.schedule.append(process.dqmoffline_step)
   process.schedule.append(process.DQMoutput_step)
=======
   process.schedule.append(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step)
if doFullDQM:
   process.schedule.append(process.dqmoffline_step,process.DQMoutput_step)
>>>>>>> 8c3ceb5cbb3... Add flags
if doReco:
   process.schedule.append(process.AODoutput_step)

=======
process.schedule = cms.Schedule(process.p1,process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,
      # process.eventinterpretaion_step,
      process.dqmoffline_step,process.AODoutput_step,process.DQMoutput_step)
      # process.dqmoffline_step,process.DQMoutput_step)

>>>>>>> e0e59d06736... Add modified files
# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
from Configuration.DataProcessing.RecoTLR import customiseRun2CommonHI 

#call to customisation function customiseRun2CommonHI imported from Configuration.DataProcessing.RecoTLR
process = customiseRun2CommonHI(process)

# End of customisation functions

from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process)


#########################################################################
## my mass replace from https://github.com/cms-sw/cmssw/blob/master/FWCore/ParameterSet/python/MassReplace.py
#########################################################################
class MassSearchReplaceAnyInputTagVisitorUntracked(object):
    """Visitor that travels within a cms.Sequence, looks for a parameter and replace its value
       It will climb down within PSets, VPSets and VInputTags to find its target"""
    def __init__(self,paramSearch,paramReplace,verbose=False,moduleLabelOnly=False,skipLabelTest=False):
        self._paramSearch  = self.standardizeInputTagFmt(paramSearch)
        self._paramReplace = self.standardizeInputTagFmt(paramReplace)
        self._moduleName   = ''
        self._verbose=verbose
        self._moduleLabelOnly=moduleLabelOnly
        self._skipLabelTest=skipLabelTest
    def doIt(self,pset,base):
        if isinstance(pset, cms._Parameterizable):
            for name in pset.parameterNames_():
                # if I use pset.parameters_().items() I get copies of the parameter values
                # so I can't modify the nested pset
                value = getattr(pset,name)
                type = value.pythonTypeName()
                if type == 'cms.untracked.PSet' or type == 'cms.PSet':
                    self.doIt(value,base+"."+name)
                elif type == 'cms.VPSet' or type == 'cms.untracked.VPSet':
                    for (i,ps) in enumerate(value): self.doIt(ps, "%s.%s[%d]"%(base,name,i) )
                elif type == 'cms.VInputTag' or type == 'cms.untracked.VInputTag':
                    for (i,n) in enumerate(value):
                         # VInputTag can be declared as a list of strings, so ensure that n is formatted correctly
                         n = self.standardizeInputTagFmt(n)
                         if (n == self._paramSearch):
                            if self._verbose:print "Replace %s.%s[%d] %s ==> %s " % (base, name, i, self._paramSearch, self._paramReplace)
                            value[i] = self._paramReplace
                         elif self._moduleLabelOnly and n.moduleLabel == self._paramSearch.moduleLabel:
                            nrep = n; nrep.moduleLabel = self._paramReplace.moduleLabel
                            if self._verbose:print "Replace %s.%s[%d] %s ==> %s " % (base, name, i, n, nrep)
                            value[i] = nrep
                elif type.endswith('.InputTag'):
                    if value == self._paramSearch:
                        if self._verbose:print "Replace %s.%s %s ==> %s " % (base, name, self._paramSearch, self._paramReplace)
                        from copy import deepcopy
                        if 'untracked' in type:
                            setattr(pset, name, cms.untracked.InputTag(self._paramReplace.getModuleLabel(),
                                                                       self._paramReplace.getProductInstanceLabel(),
                                                                       self._paramReplace.getProcessName()))
                        else:
                            setattr(pset, name, deepcopy(self._paramReplace) )
                    elif self._moduleLabelOnly and value.moduleLabel == self._paramSearch.moduleLabel:
                        from copy import deepcopy
                        repl = deepcopy(getattr(pset, name))
                        repl.moduleLabel = self._paramReplace.moduleLabel
                        setattr(pset, name, repl)
                        if self._verbose:print "Replace %s.%s %s ==> %s " % (base, name, value, repl)


    @staticmethod
    def standardizeInputTagFmt(inputTag):
       ''' helper function to ensure that the InputTag is defined as cms.InputTag(str) and not as a plain str '''
       if not isinstance(inputTag, cms.InputTag):
          return cms.InputTag(inputTag)
       return inputTag

    def enter(self,visitee):
        label = ''
        if (not self._skipLabelTest):
            try:    label = visitee.label_()
            except AttributeError: label = '<Module not in a Process>'
        else:
            label = '<Module label not tested>'
        self.doIt(visitee, label)
    def leave(self,visitee):
        pass

def massSearchReplaceAnyInputTagUntracked(sequence, oldInputTag, newInputTag,verbose=False,moduleLabelOnly=False,skipLabelTest=False) :
    """Replace InputTag oldInputTag with newInputTag, at any level of nesting within PSets, VPSets, VInputTags..."""
    sequence.visit(MassSearchReplaceAnyInputTagVisitorUntracked(oldInputTag,newInputTag,verbose=verbose,moduleLabelOnly=moduleLabelOnly,skipLabelTest=skipLabelTest))

def massReplaceInputTagUntracked(process,old="rawDataCollector",new="rawDataRepacker",verbose=False,moduleLabelOnly=False,skipLabelTest=False):
    for s in process.paths_().keys():
        massSearchReplaceAnyInputTagUntracked(getattr(process,s), old, new, verbose, moduleLabelOnly, skipLabelTest)
    for s in process.endpaths_().keys():
        massSearchReplaceAnyInputTagUntracked(getattr(process,s), old, new, verbose, moduleLabelOnly, skipLabelTest)
    if process.schedule_() is not None:
        for task in process.schedule_()._tasks:
            massSearchReplaceAnyInputTagUntracked(task, old, new, verbose, moduleLabelOnly, skipLabelTest)
    return(process)
#########################################################################
## END my mass replace
#########################################################################

<<<<<<< HEAD
if runEmulator:
   if doFullDQM:
      massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,"ecalDigis","simEcalDigis")
      massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.InputTag("ecalDigis"),cms.InputTag("simEcalDigis"))
      massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.untracked.InputTag("ecalDigis"),cms.untracked.InputTag("simEcalDigis"))
   if doFullDQM or doReco:
      massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,"ecalDigis","simEcalDigis")
      massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.InputTag("ecalDigis"),cms.InputTag("simEcalDigis"))
      massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.untracked.InputTag("ecalDigis"),cms.untracked.InputTag("simEcalDigis"))
   for s in ["ebDigis", "eeDigis"]:
      if doFullDQM:
         massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.InputTag("ecalDigis",s),cms.InputTag("simEcalDigis",s))
         massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.untracked.InputTag("ecalDigis",s),cms.untracked.InputTag("simEcalDigis",s))
      if doFullDQM or doReco:
         massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.untracked.InputTag("ecalDigis",s),cms.untracked.InputTag("simEcalDigis",s))
         massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.InputTag("ecalDigis",s),cms.InputTag("simEcalDigis",s))

   # revert in a few places
   process.ecalDetIdToBeRecovered.ebSrFlagCollection = cms.InputTag("ecalDigis")
   process.ecalDetIdToBeRecovered.eeSrFlagCollection = cms.InputTag("ecalDigis")

=======
massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,"ecalDigis","simEcalDigis")
massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,"ecalDigis","simEcalDigis")
massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.InputTag("ecalDigis"),cms.InputTag("simEcalDigis"))
massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.InputTag("ecalDigis"),cms.InputTag("simEcalDigis"))
massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.untracked.InputTag("ecalDigis"),cms.untracked.InputTag("simEcalDigis"))
massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.untracked.InputTag("ecalDigis"),cms.untracked.InputTag("simEcalDigis"))
for s in ["EcalIntegrityBlockSizeErrors", "EcalIntegrityChIdErrors", "EcalIntegrityGainErrors",
"EcalIntegrityGainSwitchErrors", "EcalIntegrityMemBlockSizeErrors", "EcalIntegrityMemChIdErrors",
"EcalIntegrityMemGainErrors", "EcalIntegrityMemTtIdErrors", "EcalIntegrityTTIdErrors",
"EcalIntegrityTTIdErrors", "EcalTriggerPrimitives", "EcalTriggerPrimitives",
"ebDigis", "eeDigis"]:
   massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.InputTag("ecalDigis",s),cms.InputTag("simEcalDigis",s))
   massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.InputTag("ecalDigis",s),cms.InputTag("simEcalDigis",s))
   massSearchReplaceAnyInputTagUntracked(process.dqmoffline_step,cms.untracked.InputTag("ecalDigis",s),cms.untracked.InputTag("simEcalDigis",s))
   massSearchReplaceAnyInputTagUntracked(process.reconstruction_step,cms.untracked.InputTag("ecalDigis",s),cms.untracked.InputTag("simEcalDigis",s))

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)


# feed the re-emulated ECAL digis into the downstream reco chain
if runEmulator:
>>>>>>> e0e59d06736... Add modified files
   # process.ecalCompactTrigPrim.inColl = cms.InputTag("simEcalTriggerPrimitiveDigis","simEcalTriggerPrimitives")
   process.ecalCompactTrigPrim.inColl = cms.InputTag("ecalDigis","EcalTriggerPrimitives")
   process.ecalMultiFitUncalibRecHit.EBdigiCollection = cms.InputTag("simEcalDigis","SRebDigis")
   process.ecalMultiFitUncalibRecHit.EEdigiCollection = cms.InputTag("simEcalDigis","SReeDigis")
   # process.ecalRecHit.triggerPrimitiveDigiCollection = cms.InputTag("simEcalTriggerPrimitiveDigis","simEcalTriggerPrimitives")
   # process.ecalTPSkim.tpInputCollection = cms.InputTag("simEcalTriggerPrimitiveDigis","simEcalTriggerPrimitives")
   process.ecalRecHit.triggerPrimitiveDigiCollection = cms.InputTag("ecalDigis","EcalTriggerPrimitives")
   process.ecalTPSkim.tpInputCollection = cms.InputTag("ecalDigis","EcalTriggerPrimitives")

<<<<<<< HEAD
# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

=======
>>>>>>> e0e59d06736... Add modified files
if trigger != '':
   # filter all path with the production filter sequence
   process.superFilterPath = cms.Path(process.TriggerFilter)
   for path in process.paths:
      getattr(process,path)._seq = process.TriggerFilter * getattr(process,path)._seq 
   # process.AODoutput.SelectEvents = cms.untracked.PSet(
   #       SelectEvents = cms.vstring('TriggerFilter')
   #       )
   # process.DQMoutput.SelectEvents = cms.untracked.PSet(
   #       SelectEvents = cms.vstring('TriggerFilter')
   #       )
