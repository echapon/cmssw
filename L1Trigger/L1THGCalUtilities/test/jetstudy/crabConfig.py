from CRABClient.UserUtilities import config
config = config()

# config.General.requestName = 'VBF_HToInvisible_PU200_unclseltowers_noarea_20201027'
config.General.requestName = 'RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_noarea_20201027'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'testTowerPerf_cfg.py'
config.JobType.outputFiles = ['ntuple.root']

# config.Data.inputDataset = '/VBF_HToInvisible_M125_14TeV_powheg_pythia8/PhaseIITDRSpring19DR-NoPU_106X_upgrade2023_realistic_v3-v2/GEN-SIM-DIGI-RAW'
# config.Data.inputDataset = '/VBF_HToInvisible_M125_14TeV_powheg_pythia8/PhaseIITDRSpring19DR-PU200_106X_upgrade2023_realistic_v3-v1/GEN-SIM-DIGI-RAW'
# config.Data.inputDataset = '/RelValDiQ_Pt20To300_Etam1p6Tom2p9/CMSSW_10_6_0_patch2-106X_upgrade2023_realistic_v3_2023D41noPU-v1/GEN-SIM-DIGI-RAW'
config.Data.inputDataset = '/RelValDiQ_Pt20To300_Etam1p6Tom2p9/CMSSW_10_6_0_patch2-PU25ns_106X_upgrade2023_realistic_v3_2023D41PU200-v1/GEN-SIM-DIGI-RAW'
config.Data.inputDBS = 'global'
# config.Data.splitting = 'FileBased'
# config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers' 
config.Data.publication = False
# config.Data.outputDatasetTag = config.General.requestName

config.Site.storageSite = 'T2_CH_CERN'
