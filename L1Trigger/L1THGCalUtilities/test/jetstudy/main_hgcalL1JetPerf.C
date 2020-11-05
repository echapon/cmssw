#include "HGCalTriggerNtupleReader.C"
#include "TChain.h"
#include "TString.h"
#include <algorithm>
#include <iostream>

int main(int argc, const char** argv) {
   if (argc < 3 || argc > 5) return -1;

   TString filenames_in(argv[1]);
   TString filename_out(argv[2]);
   bool doPUsub = (argc==4 && TString(argv[3]=="doPU"));
   int evtdisplaynb = -1;
   if (argc==5) evtdisplaynb = atoi(argv[4]);

   TChain *tch = new TChain("hgcalTriggerNtuplizer/HGCalTriggerNtuple");
   cout << filenames_in.Data() << endl;
   tch->Add(filenames_in);

   HGCalTriggerNtupleReader thereader(tch);
   thereader.Loop(filename_out, doPUsub, evtdisplaynb);
}
