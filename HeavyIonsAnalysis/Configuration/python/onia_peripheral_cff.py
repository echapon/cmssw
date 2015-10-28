import FWCore.ParameterSet.Config as cms

# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
hltZMMHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
# hltZMMHI.HLTPaths = ["HLT_HIL1DoubleMu0"] # here for the peripheral we need only this path; for the Central PD we need both this one, together with teh L2 and L3 jpsi and Upsilon paths
hltZMMHI.HLTPaths = ["*"] # don't apply any trigger requirement for now
hltZMMHI.throw = False
hltZMMHI.andOr = True

# selection of valid vertex
primaryVertexFilterForZMM = cms.EDFilter("VertexSelector",
    src = cms.InputTag("hiSelectedVertex"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2"), 
    filter = cms.bool(True),   # otherwise it won't filter the events
    )

# selection of dimuons with mass in Jpsi or 
muonSelector = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muons"),
    cut = cms.string("(isTrackerMuon && isGlobalMuon) && pt > 1.5"),
    filter = cms.bool(True)
    )

muonFilter = cms.EDFilter("MuonCountFilter",
    src = cms.InputTag("muonSelector"),
    minNumber = cms.uint32(2)
    )

# opposite charge only 
dimuonMassCut = cms.EDProducer("CandViewShallowCloneCombiner",
    checkCharge = cms.bool(True),
    cut = cms.string(' (2.6 < mass < 3.5) || (7.0 < mass < 14.0)'),
    decay = cms.string("muonSelector@+ muonSelector@-")
    )

dimuonMassCutFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("dimuonMassCut"),
    minNumber = cms.uint32(1)
    )

# Z->mumu skim sequence
zMMSkimSequence = cms.Sequence(
    hltZMMHI *
    primaryVertexFilterForZMM *
    muonSelector *
    muonFilter *
    dimuonMassCut *
    dimuonMassCutFilter
    )
