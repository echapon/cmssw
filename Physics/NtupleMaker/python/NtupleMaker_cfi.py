import FWCore.ParameterSet.Config as cms

NtupleMaker = cms.EDAnalyzer("NtupleMaker",
   # -- flags -- #
	isMC = cms.untracked.bool(True), #
	putMuons = cms.untracked.bool(True), #
	putElectrons = cms.untracked.bool(True), #
	putDileptons = cms.untracked.bool(True), #
	putPhotons = cms.untracked.bool(True), #
	putJets = cms.untracked.bool(True), #
	putMETs = cms.untracked.bool(True), #
	putCentrality = cms.untracked.bool(True), #

	# -- Trigger -- #
	TriggerResults = cms.InputTag("TriggerResults", "", "HLT"), #
	TriggerObjects = cms.InputTag("..."), #
	TriggerSummary = cms.InputTag("..."), #

	# -- Object Tags -- #
	BeamSpot = cms.InputTag("offlineBeamSpot"), #
	Vertex = cms.InputTag("offlinePrimaryVerticesWithBS"), #
	PU = cms.InputTag("addPileupInfo"), #
   PFCandidates = cms.InputTag(""), #
	Muons = cms.InputTag("selectedPatMuons"), #
	Electrons = cms.InputTag("gedGsfElectrons"), #
	Photons = cms.InputTag("gedPhotons"), #
	Jets = cms.InputTag("selectedPatJets"), #
	MET = cms.InputTag("patMETs"), #
	GenParticles = cms.InputTag("genParticles"), #

	# -- electron information -- #
	rho = cms.InputTag("fixedGridRhoFastjetAll"), #
	miniRho = cms.InputTag(""), #
	eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium"), #
	eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight"), #
	Conversions = cms.InputTag("allConversions"), #

	# -- photon information -- #
	full5x5SigmaIEtaIEtaMap   = cms.InputTag("photonIDValueMapProducer:phoFull5x5SigmaIEtaIEta"), #
	phoChargedIsolation = cms.InputTag("photonIDValueMapProducer:phoChargedIsolation"), #
	phoNeutralHadronIsolation = cms.InputTag("photonIDValueMapProducer:phoNeutralHadronIsolation"), #
	phoPhotonIsolation = cms.InputTag("photonIDValueMapProducer:phoPhotonIsolation"), #
	effAreaChHadFile = cms.untracked.FileInPath("RecoEgamma/PhotonIdentification/data/PHYS14/effAreaPhotons_cone03_pfChargedHadrons_V2.txt"), #
	effAreaNeuHadFile= cms.untracked.FileInPath("RecoEgamma/PhotonIdentification/data/PHYS14/effAreaPhotons_cone03_pfNeutralHadrons_V2.txt"), #
	effAreaPhoFile   = cms.untracked.FileInPath("RecoEgamma/PhotonIdentification/data/PHYS14/effAreaPhotons_cone03_pfPhotons_V2.txt"), #
   phoMediumIdBoolMap = cms.InputTag(""), #
   phoMediumIdFullInfoMap = cms.InputTag(""), #
   mvaValuesMap = cms.InputTag(""), #
   mvaCategoriesMap = cms.InputTag(""), #

	# -- Else -- #
	Generator = cms.InputTag("generator"), #
   CentralitySrc    = cms.InputTag("pACentrality"),
   CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
)
