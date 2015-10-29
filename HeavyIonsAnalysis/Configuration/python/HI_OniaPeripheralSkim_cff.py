import FWCore.ParameterSet.Config as cms

# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
hltPeripheralOniaMMHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
# hltPeripheralOniaMMHI.HLTPaths = ["HLT_HIL1DoubleMu0"] # here for the peripheral we need only this path; for the Peripheral PD we need both this one, together with teh L2 and L3 jpsi and Upsilon paths
hltPeripheralOniaMMHI.HLTPaths = ["*"] # don't apply any trigger requirement for now
hltPeripheralOniaMMHI.throw = False
hltPeripheralOniaMMHI.andOr = True

# selection of valid vertex
primaryVertexFilterForOniaMMPeripheral = cms.EDFilter("VertexSelector",
    src = cms.InputTag("hiSelectedVertex"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2"), 
    filter = cms.bool(True),   # otherwise it won't filter the events
    )

# selection of dimuons with mass in Jpsi or 
muonSelectorForOniaMMPeripheral = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muons"),
    cut = cms.string("(isTrackerMuon && isGlobalMuon) && pt > 1.5"),
    filter = cms.bool(True)
    )

muonFilterForOniaMMPeripheral = cms.EDFilter("MuonCountFilter",
    src = cms.InputTag("muonSelectorForOniaMMPeripheral"),
    minNumber = cms.uint32(2)
    )

# opposite charge only 
dimuonMassCutForOniaMMPeripheral = cms.EDProducer("CandViewShallowCloneCombiner",
    checkCharge = cms.bool(True),
    cut = cms.string(' (2.6 < mass < 3.5) || (7.0 < mass < 14.0)'),
    decay = cms.string("muonSelectorForOniaMMPeripheral@+ muonSelectorForOniaMMPeripheral@-")
    )

dimuonMassCutFilterForOniaMMPeripheral = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("dimuonMassCutForOniaMMPeripheral"),
    minNumber = cms.uint32(1)
    )

# onia skim sequence
oniaMMperipheralSkimSequence = cms.Sequence(
    hltPeripheralOniaMMHI *
    primaryVertexFilterForOniaMMPeripheral *
    muonSelectorForOniaMMPeripheral *
    muonFilterForOniaMMPeripheral *
    dimuonMassCutForOniaMMPeripheral *
    dimuonMassCutFilterForOniaMMPeripheral
    )
