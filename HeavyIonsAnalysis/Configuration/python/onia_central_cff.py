import FWCore.ParameterSet.Config as cms

# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
hltoniaMMHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
# hltoniaMMHI.HLTPaths = ["HLT_HIL1DoubleMu0"] # here for the central we need only this path; for the Central PD we need both this one, together with teh L2 and L3 jpsi and Upsilon paths
hltoniaMMHI.HLTPaths = ["*"] # don't apply any trigger requirement for now
hltoniaMMHI.throw = False
hltoniaMMHI.andOr = True

# selection of valid vertex
primaryVertexFilterForoniaMM = cms.EDFilter("VertexSelector",
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

# onia skim sequence
oniaMMcentralSkimSequence = cms.Sequence(
    hltoniaMMHI *
    primaryVertexFilterForoniaMM *
    muonSelector *
    muonFilter *
    dimuonMassCut *
    dimuonMassCutFilter
    )
