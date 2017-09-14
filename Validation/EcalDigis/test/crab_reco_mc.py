from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'ECAL_MC_dijet30_digi_reEmul_scenar2016_step3_20170911_2'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step3mc_RAW2DIGI_L1Reco_RECO_EI_DQM.py'
config.JobType.maxMemoryMB = 4500

config.Data.inputDataset = '/Pythia6_Dijet30_pp502_Hydjet_Cymbal_MB/echapon-ECAL_MC_dijet30_digi_reEmul_scenar2016_20170901-da87b07ee2ff0df0d46706eade5e4cf7/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
# config.Data.outLFNDirBase = '/store/group/cmst3/user/%s/PrivateMC_pA_8p16TeV/' % (getUsernameFromSiteDB()) # for EOS
# config.Data.outLFNDirBase = '/store/user/%s/PrivateMC_pA_8p16TeV/' % (getUsernameFromSiteDB()) # for GRIF
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/echapon/ECAL_studies/' 
config.Data.publication = True
config.Data.outputDatasetTag = 'step3_20170911_2'

# config.Site.storageSite = 'T2_FR_GRIF_LLR'
config.Site.storageSite = 'T2_CH_CERN'
# config.Site.whitelist = ['T2_FR_GRIF_LLR']
