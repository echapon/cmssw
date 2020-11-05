all: hgcalL1JetPerf

hgcalL1JetPerf: HGCalTriggerNtupleReader.C HGCalTriggerNtupleReader.h main_hgcalL1JetPerf.C
	g++ main_hgcalL1JetPerf.C -o hgcalL1JetPerf `fastjet-config --cxxflags --libs --plugins` `root-config --cflags --ldflags --libs`
