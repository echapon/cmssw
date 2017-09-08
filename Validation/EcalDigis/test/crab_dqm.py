from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

dataset = 'HIMinimumBias1'
# dataset = 'HIEWQExo'
runEmulator = True
emulScenario = 2016
runRange = '262784' # '263322' # for MB
# runRange = '262921' # for EWQExo
# trigger = ''
trigger = 'HLT_HIFullTrack12_L1Centrality010_v2' # 'HLT_L1MinimumBiasHF1OR_v1'
# trigger = 'HLT_HIL1Centralityext50100MinimumumBiasHF2AND_v1'

runEmulStr = ''
if runEmulator:
   runEmulStr = 'reEmul_scenar%i' % (emulScenario)
else:
   runEmulStr = 'noEmul'

config.General.requestName = 'ECAL_%s_%s_%s_DQMonly_20170512' % (dataset, trigger, runEmulStr)
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_RAW2DIGI_L1Reco_RECO_DQMonly.py'
config.JobType.inputFiles = [ 'EcalSRSettings_LTH1.5_HTH2.5GeV_ZS4.5_6.5ADC_mc.db', 
'EcalSRSettings_LTH2.5_HTH5.5GeV_ZS5_7ADC_ZS2.5_3.5ADC_mc.db',
'EcalSRSettings_LTH2_HTH3GeV_ZS4.5_6.5ADC_ZS2_3ADC_mc.db',
'EcalSRSettings_LTH2.5_HTH4.5GeV_ZS4.5_6.5ADC_mc.db',
'EcalSRSettings_LTH2_HTH3.5GeV_ZS4.5_7ADC_ZS2_3ADC_mc.db',
'EcalSRSettings_LTH2_HTH3GeV_ZS5.5_8ADC_mc.db' ] 
config.JobType.maxMemoryMB = 4000

config.Data.inputDataset = '/%s/HIRun2015-v1/RAW' % (dataset)
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 1
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
config.Data.runRange = runRange
config.Data.outLFNDirBase = '/store/group/cmst3/user/echapon/ECAL_studies' 
config.Data.publication = False
config.Data.outputDatasetTag = 'reco_%s_%s_%s_DQMonly_20170512' % (dataset, trigger, runEmulStr)

config.Site.storageSite = 'T2_CH_CERN'
