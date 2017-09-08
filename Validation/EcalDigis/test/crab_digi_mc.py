from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

runEmulator = True
emulScenario = 2016

runEmulStr = ''
if runEmulator:
   runEmulStr = 'reEmul_scenar%i' % (emulScenario)
else:
   runEmulStr = 'noEmul'

config.General.requestName = 'ECAL_MC_dijet80_digi_%s_20170901' % runEmulStr
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_DIGI_L1_DIGI2RAW_HLT_PU.py'
config.JobType.maxMemoryMB = 4500
config.JobType.inputFiles = [ 'EcalSRSettings_LTH1.5_HTH2.5GeV_ZS4.5_6.5ADC_mc.db', 
'EcalSRSettings_LTH2.5_HTH5.5GeV_ZS5_7ADC_ZS2.5_3.5ADC_mc.db',
'EcalSRSettings_LTH2_HTH3GeV_ZS4.5_6.5ADC_ZS2_3ADC_mc.db',
'EcalSRSettings_LTH2.5_HTH4.5GeV_ZS4.5_6.5ADC_mc.db',
'EcalSRSettings_LTH2_HTH3.5GeV_ZS4.5_7ADC_ZS2_3ADC_mc.db',
'EcalSRSettings_LTH2_HTH3GeV_ZS5.5_8ADC_mc.db' ] 

config.Data.inputDataset = '/Pythia6_Dijet80_pp502_Hydjet_Cymbal_MB/HiFall15-75X_mcRun2_HeavyIon_v14-v1/GEN-SIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = 50
# config.Data.outLFNDirBase = '/store/group/cmst3/user/%s/PrivateMC_pA_8p16TeV/' % (getUsernameFromSiteDB())
# config.Data.outLFNDirBase = '/store/user/echapon/ECAL_studies' 
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/echapon/ECAL_studies' 
config.Data.publication = True
config.Data.outputDatasetTag = config.General.requestName

config.Site.storageSite = 'T2_CH_CERN'
# config.Site.whitelist = ['T2_US_MIT'] # because the EPOS dataset is at MIT
