void printScan() {
   TFile *_file0 = TFile::Open("ntuple.root");
   TTree *tr = (TTree*) _file0->Get("hgcalTriggerNtuplizer/HGCalTriggerNtuple");
   tr->Scan("genjet_pt:genjet_eta:genjet_phi","genjet_pt>44.54665&&genjet_pt<44.54666");
}
