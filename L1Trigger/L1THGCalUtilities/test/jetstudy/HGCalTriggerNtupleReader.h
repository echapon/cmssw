//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 22 14:08:26 2020 by ROOT version 6.20/07
// from TTree HGCalTriggerNtuple/HGCalTriggerNtuple
// found on file: ntuple.root
//////////////////////////////////////////////////////////

#ifndef HGCalTriggerNtupleReader_h
#define HGCalTriggerNtupleReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "fastjet/PseudoJet.hh"

// Header file for the classes stored in the TTree if any.
#include <vector>

using namespace std;

class HGCalTriggerNtupleReader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           lumi;
   Int_t           gen_n;
   Int_t           gen_PUNumInt;
   Float_t         gen_TrueNumInt;
   Float_t         vtx_x;
   Float_t         vtx_y;
   Float_t         vtx_z;
   vector<float>   *gen_eta;
   vector<float>   *gen_phi;
   vector<float>   *gen_pt;
   vector<float>   *gen_energy;
   vector<int>     *gen_charge;
   vector<int>     *gen_pdgid;
   vector<int>     *gen_status;
   vector<vector<int> > *gen_daughters;
   vector<float>   *genpart_eta;
   vector<float>   *genpart_phi;
   vector<float>   *genpart_pt;
   vector<float>   *genpart_energy;
   vector<float>   *genpart_dvx;
   vector<float>   *genpart_dvy;
   vector<float>   *genpart_dvz;
   vector<float>   *genpart_ovx;
   vector<float>   *genpart_ovy;
   vector<float>   *genpart_ovz;
   vector<int>     *genpart_mother;
   vector<float>   *genpart_exphi;
   vector<float>   *genpart_exeta;
   vector<float>   *genpart_exx;
   vector<float>   *genpart_exy;
   vector<float>   *genpart_fbrem;
   vector<int>     *genpart_pid;
   vector<int>     *genpart_gen;
   vector<int>     *genpart_reachedEE;
   vector<bool>    *genpart_fromBeamPipe;
   vector<vector<float> > *genpart_posx;
   vector<vector<float> > *genpart_posy;
   vector<vector<float> > *genpart_posz;
   Int_t           genjet_n;
   vector<float>   *genjet_energy;
   vector<float>   *genjet_pt;
   vector<float>   *genjet_eta;
   vector<float>   *genjet_phi;
   vector<float>   *gentau_pt;
   vector<float>   *gentau_eta;
   vector<float>   *gentau_phi;
   vector<float>   *gentau_energy;
   vector<float>   *gentau_mass;
   vector<float>   *gentau_vis_pt;
   vector<float>   *gentau_vis_eta;
   vector<float>   *gentau_vis_phi;
   vector<float>   *gentau_vis_energy;
   vector<float>   *gentau_vis_mass;
   vector<vector<float> > *gentau_products_pt;
   vector<vector<float> > *gentau_products_eta;
   vector<vector<float> > *gentau_products_phi;
   vector<vector<float> > *gentau_products_energy;
   vector<vector<float> > *gentau_products_mass;
   vector<vector<int> > *gentau_products_id;
   vector<int>     *gentau_decayMode;
   vector<int>     *gentau_totNproducts;
   vector<int>     *gentau_totNgamma;
   vector<int>     *gentau_totNpiZero;
   vector<int>     *gentau_totNcharged;
   Int_t           tc_n;
   vector<unsigned int> *tc_id;
   vector<int>     *tc_subdet;
   vector<int>     *tc_zside;
   vector<int>     *tc_layer;
   vector<int>     *tc_wafer;
   vector<int>     *tc_waferu;
   vector<int>     *tc_waferv;
   vector<int>     *tc_wafertype;
   vector<int>     *tc_panel_number;
   vector<int>     *tc_panel_sector;
   vector<int>     *tc_cell;
   vector<int>     *tc_cellu;
   vector<int>     *tc_cellv;
   vector<unsigned int> *tc_data;
   vector<unsigned int> *tc_uncompressedCharge;
   vector<unsigned int> *tc_compressedCharge;
   vector<float>   *tc_pt;
   vector<float>   *tc_mipPt;
   vector<float>   *tc_energy;
   vector<float>   *tc_eta;
   vector<float>   *tc_phi;
   vector<float>   *tc_x;
   vector<float>   *tc_y;
   vector<float>   *tc_z;
   vector<unsigned int> *tc_cluster_id;
   vector<unsigned int> *tc_multicluster_id;
   vector<float>   *tc_multicluster_pt;
   Int_t           ts_n;
   vector<unsigned int> *ts_id;
   vector<int>     *ts_subdet;
   vector<int>     *ts_zside;
   vector<int>     *ts_layer;
   vector<int>     *ts_wafer;
   vector<int>     *ts_wafertype;
   vector<int>     *ts_panel_number;
   vector<int>     *ts_panel_sector;
   vector<unsigned int> *ts_data;
   vector<float>   *ts_pt;
   vector<float>   *ts_mipPt;
   vector<float>   *ts_energy;
   vector<float>   *ts_eta;
   vector<float>   *ts_phi;
   vector<float>   *ts_x;
   vector<float>   *ts_y;
   vector<float>   *ts_z;
   Int_t           cl3d_n;
   vector<unsigned int> *cl3d_id;
   vector<float>   *cl3d_pt;
   vector<float>   *cl3d_energy;
   vector<float>   *cl3d_eta;
   vector<float>   *cl3d_phi;
   vector<int>     *cl3d_clusters_n;
   vector<vector<unsigned int> > *cl3d_clusters_id;
   vector<int>     *cl3d_showerlength;
   vector<int>     *cl3d_coreshowerlength;
   vector<int>     *cl3d_firstlayer;
   vector<int>     *cl3d_maxlayer;
   vector<float>   *cl3d_seetot;
   vector<float>   *cl3d_seemax;
   vector<float>   *cl3d_spptot;
   vector<float>   *cl3d_sppmax;
   vector<float>   *cl3d_szz;
   vector<float>   *cl3d_srrtot;
   vector<float>   *cl3d_srrmax;
   vector<float>   *cl3d_srrmean;
   vector<float>   *cl3d_emaxe;
   vector<float>   *cl3d_hoe;
   vector<float>   *cl3d_meanz;
   vector<float>   *cl3d_layer10;
   vector<float>   *cl3d_layer50;
   vector<float>   *cl3d_layer90;
   vector<float>   *cl3d_ntc67;
   vector<float>   *cl3d_ntc90;
   vector<float>   *cl3d_bdteg;
   vector<int>     *cl3d_quality;
   vector<vector<float> > *cl3d_ipt;
   vector<vector<float> > *cl3d_ienergy;
   Int_t           tower_n;
   vector<float>   *tower_pt;
   vector<float>   *tower_energy;
   vector<float>   *tower_eta;
   vector<float>   *tower_phi;
   vector<float>   *tower_etEm;
   vector<float>   *tower_etHad;
   vector<int>     *tower_iEta;
   vector<int>     *tower_iPhi;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_gen_n;   //!
   TBranch        *b_gen_PUNumInt;   //!
   TBranch        *b_gen_TrueNumInt;   //!
   TBranch        *b_vtx_x;   //!
   TBranch        *b_vtx_y;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_energy;   //!
   TBranch        *b_gen_charge;   //!
   TBranch        *b_gen_pdgid;   //!
   TBranch        *b_gen_status;   //!
   TBranch        *b_gen_daughters;   //!
   TBranch        *b_genpart_eta;   //!
   TBranch        *b_genpart_phi;   //!
   TBranch        *b_genpart_pt;   //!
   TBranch        *b_genpart_energy;   //!
   TBranch        *b_genpart_dvx;   //!
   TBranch        *b_genpart_dvy;   //!
   TBranch        *b_genpart_dvz;   //!
   TBranch        *b_genpart_ovx;   //!
   TBranch        *b_genpart_ovy;   //!
   TBranch        *b_genpart_ovz;   //!
   TBranch        *b_genpart_mother;   //!
   TBranch        *b_genpart_exphi;   //!
   TBranch        *b_genpart_exeta;   //!
   TBranch        *b_genpart_exx;   //!
   TBranch        *b_genpart_exy;   //!
   TBranch        *b_genpart_fbrem;   //!
   TBranch        *b_genpart_pid;   //!
   TBranch        *b_genpart_gen;   //!
   TBranch        *b_genpart_reachedEE;   //!
   TBranch        *b_genpart_fromBeamPipe;   //!
   TBranch        *b_genpart_posx;   //!
   TBranch        *b_genpart_posy;   //!
   TBranch        *b_genpart_posz;   //!
   TBranch        *b_genjet_n;   //!
   TBranch        *b_genjet_energy;   //!
   TBranch        *b_genjet_pt;   //!
   TBranch        *b_genjet_eta;   //!
   TBranch        *b_genjet_phi;   //!
   TBranch        *b_gentau_pt;   //!
   TBranch        *b_gentau_eta;   //!
   TBranch        *b_gentau_phi;   //!
   TBranch        *b_gentau_energy;   //!
   TBranch        *b_gentau_mass;   //!
   TBranch        *b_gentau_vis_pt;   //!
   TBranch        *b_gentau_vis_eta;   //!
   TBranch        *b_gentau_vis_phi;   //!
   TBranch        *b_gentau_vis_energy;   //!
   TBranch        *b_gentau_vis_mass;   //!
   TBranch        *b_gentau_products_pt;   //!
   TBranch        *b_gentau_products_eta;   //!
   TBranch        *b_gentau_products_phi;   //!
   TBranch        *b_gentau_products_energy;   //!
   TBranch        *b_gentau_products_mass;   //!
   TBranch        *b_gentau_products_id;   //!
   TBranch        *b_gentau_decayMode;   //!
   TBranch        *b_gentau_totNproducts;   //!
   TBranch        *b_gentau_totNgamma;   //!
   TBranch        *b_gentau_totNpiZero;   //!
   TBranch        *b_gentau_totNcharged;   //!
   TBranch        *b_tc_n;   //!
   TBranch        *b_tc_id;   //!
   TBranch        *b_tc_subdet;   //!
   TBranch        *b_tc_zside;   //!
   TBranch        *b_tc_layer;   //!
   TBranch        *b_tc_wafer;   //!
   TBranch        *b_tc_waferu;   //!
   TBranch        *b_tc_waferv;   //!
   TBranch        *b_tc_wafertype;   //!
   TBranch        *b_tc_panel_number;   //!
   TBranch        *b_tc_panel_sector;   //!
   TBranch        *b_tc_cell;   //!
   TBranch        *b_tc_cellu;   //!
   TBranch        *b_tc_cellv;   //!
   TBranch        *b_tc_data;   //!
   TBranch        *b_tc_uncompressedCharge;   //!
   TBranch        *b_tc_compressedCharge;   //!
   TBranch        *b_tc_pt;   //!
   TBranch        *b_tc_mipPt;   //!
   TBranch        *b_tc_energy;   //!
   TBranch        *b_tc_eta;   //!
   TBranch        *b_tc_phi;   //!
   TBranch        *b_tc_x;   //!
   TBranch        *b_tc_y;   //!
   TBranch        *b_tc_z;   //!
   TBranch        *b_tc_cluster_id;   //!
   TBranch        *b_tc_multicluster_id;   //!
   TBranch        *b_tc_multicluster_pt;   //!
   TBranch        *b_ts_n;   //!
   TBranch        *b_ts_id;   //!
   TBranch        *b_ts_subdet;   //!
   TBranch        *b_ts_zside;   //!
   TBranch        *b_ts_layer;   //!
   TBranch        *b_ts_wafer;   //!
   TBranch        *b_ts_wafertype;   //!
   TBranch        *b_ts_panel_number;   //!
   TBranch        *b_ts_panel_sector;   //!
   TBranch        *b_ts_data;   //!
   TBranch        *b_ts_pt;   //!
   TBranch        *b_ts_mipPt;   //!
   TBranch        *b_ts_energy;   //!
   TBranch        *b_ts_eta;   //!
   TBranch        *b_ts_phi;   //!
   TBranch        *b_ts_x;   //!
   TBranch        *b_ts_y;   //!
   TBranch        *b_ts_z;   //!
   TBranch        *b_cl3d_n;   //!
   TBranch        *b_cl3d_id;   //!
   TBranch        *b_cl3d_pt;   //!
   TBranch        *b_cl3d_energy;   //!
   TBranch        *b_cl3d_eta;   //!
   TBranch        *b_cl3d_phi;   //!
   TBranch        *b_cl3d_clusters_n;   //!
   TBranch        *b_cl3d_clusters_id;   //!
   TBranch        *b_cl3d_showerlength;   //!
   TBranch        *b_cl3d_coreshowerlength;   //!
   TBranch        *b_cl3d_firstlayer;   //!
   TBranch        *b_cl3d_maxlayer;   //!
   TBranch        *b_cl3d_seetot;   //!
   TBranch        *b_cl3d_seemax;   //!
   TBranch        *b_cl3d_spptot;   //!
   TBranch        *b_cl3d_sppmax;   //!
   TBranch        *b_cl3d_szz;   //!
   TBranch        *b_cl3d_srrtot;   //!
   TBranch        *b_cl3d_srrmax;   //!
   TBranch        *b_cl3d_srrmean;   //!
   TBranch        *b_cl3d_emaxe;   //!
   TBranch        *b_cl3d_hoe;   //!
   TBranch        *b_cl3d_meanz;   //!
   TBranch        *b_cl3d_layer10;   //!
   TBranch        *b_cl3d_layer50;   //!
   TBranch        *b_cl3d_layer90;   //!
   TBranch        *b_cl3d_ntc67;   //!
   TBranch        *b_cl3d_ntc90;   //!
   TBranch        *b_cl3d_bdteg;   //!
   TBranch        *b_cl3d_quality;   //!
   TBranch        *b_cl3d_ipt;   //!
   TBranch        *b_cl3d_ienergy;   //!
   TBranch        *b_tower_n;   //!
   TBranch        *b_tower_pt;   //!
   TBranch        *b_tower_energy;   //!
   TBranch        *b_tower_eta;   //!
   TBranch        *b_tower_phi;   //!
   TBranch        *b_tower_etEm;   //!
   TBranch        *b_tower_etHad;   //!
   TBranch        *b_tower_iEta;   //!
   TBranch        *b_tower_iPhi;   //!

   HGCalTriggerNtupleReader(TTree *tree=0);
   virtual ~HGCalTriggerNtupleReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString filename_out, bool doPUsub, int evtdisplaynb = -1);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     drawEventDisplay(TString name, vector<fastjet::PseudoJet> inputs, vector<fastjet::PseudoJet> jets);
   virtual void     drawEventDisplay2(TString name, vector<fastjet::PseudoJet> inputs, vector<fastjet::PseudoJet> jets);

};

#endif

#ifdef HGCalTriggerNtupleReader_cxx
HGCalTriggerNtupleReader::HGCalTriggerNtupleReader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ntuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ntuple.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("ntuple.root:/hgcalTriggerNtuplizer");
      dir->GetObject("HGCalTriggerNtuple",tree);

   }
   Init(tree);
}

HGCalTriggerNtupleReader::~HGCalTriggerNtupleReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HGCalTriggerNtupleReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HGCalTriggerNtupleReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HGCalTriggerNtupleReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   gen_eta = 0;
   gen_phi = 0;
   gen_pt = 0;
   gen_energy = 0;
   gen_charge = 0;
   gen_pdgid = 0;
   gen_status = 0;
   gen_daughters = 0;
   genpart_eta = 0;
   genpart_phi = 0;
   genpart_pt = 0;
   genpart_energy = 0;
   genpart_dvx = 0;
   genpart_dvy = 0;
   genpart_dvz = 0;
   genpart_ovx = 0;
   genpart_ovy = 0;
   genpart_ovz = 0;
   genpart_mother = 0;
   genpart_exphi = 0;
   genpart_exeta = 0;
   genpart_exx = 0;
   genpart_exy = 0;
   genpart_fbrem = 0;
   genpart_pid = 0;
   genpart_gen = 0;
   genpart_reachedEE = 0;
   genpart_fromBeamPipe = 0;
   genpart_posx = 0;
   genpart_posy = 0;
   genpart_posz = 0;
   genjet_energy = 0;
   genjet_pt = 0;
   genjet_eta = 0;
   genjet_phi = 0;
   gentau_pt = 0;
   gentau_eta = 0;
   gentau_phi = 0;
   gentau_energy = 0;
   gentau_mass = 0;
   gentau_vis_pt = 0;
   gentau_vis_eta = 0;
   gentau_vis_phi = 0;
   gentau_vis_energy = 0;
   gentau_vis_mass = 0;
   gentau_products_pt = 0;
   gentau_products_eta = 0;
   gentau_products_phi = 0;
   gentau_products_energy = 0;
   gentau_products_mass = 0;
   gentau_products_id = 0;
   gentau_decayMode = 0;
   gentau_totNproducts = 0;
   gentau_totNgamma = 0;
   gentau_totNpiZero = 0;
   gentau_totNcharged = 0;
   tc_id = 0;
   tc_subdet = 0;
   tc_zside = 0;
   tc_layer = 0;
   tc_wafer = 0;
   tc_waferu = 0;
   tc_waferv = 0;
   tc_wafertype = 0;
   tc_panel_number = 0;
   tc_panel_sector = 0;
   tc_cell = 0;
   tc_cellu = 0;
   tc_cellv = 0;
   tc_data = 0;
   tc_uncompressedCharge = 0;
   tc_compressedCharge = 0;
   tc_pt = 0;
   tc_mipPt = 0;
   tc_energy = 0;
   tc_eta = 0;
   tc_phi = 0;
   tc_x = 0;
   tc_y = 0;
   tc_z = 0;
   tc_cluster_id = 0;
   tc_multicluster_id = 0;
   tc_multicluster_pt = 0;
   ts_id = 0;
   ts_subdet = 0;
   ts_zside = 0;
   ts_layer = 0;
   ts_wafer = 0;
   ts_wafertype = 0;
   ts_panel_number = 0;
   ts_panel_sector = 0;
   ts_data = 0;
   ts_pt = 0;
   ts_mipPt = 0;
   ts_energy = 0;
   ts_eta = 0;
   ts_phi = 0;
   ts_x = 0;
   ts_y = 0;
   ts_z = 0;
   cl3d_id = 0;
   cl3d_pt = 0;
   cl3d_energy = 0;
   cl3d_eta = 0;
   cl3d_phi = 0;
   cl3d_clusters_n = 0;
   cl3d_clusters_id = 0;
   cl3d_showerlength = 0;
   cl3d_coreshowerlength = 0;
   cl3d_firstlayer = 0;
   cl3d_maxlayer = 0;
   cl3d_seetot = 0;
   cl3d_seemax = 0;
   cl3d_spptot = 0;
   cl3d_sppmax = 0;
   cl3d_szz = 0;
   cl3d_srrtot = 0;
   cl3d_srrmax = 0;
   cl3d_srrmean = 0;
   cl3d_emaxe = 0;
   cl3d_hoe = 0;
   cl3d_meanz = 0;
   cl3d_layer10 = 0;
   cl3d_layer50 = 0;
   cl3d_layer90 = 0;
   cl3d_ntc67 = 0;
   cl3d_ntc90 = 0;
   cl3d_bdteg = 0;
   cl3d_quality = 0;
   cl3d_ipt = 0;
   cl3d_ienergy = 0;
   tower_pt = 0;
   tower_energy = 0;
   tower_eta = 0;
   tower_phi = 0;
   tower_etEm = 0;
   tower_etHad = 0;
   tower_iEta = 0;
   tower_iPhi = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("gen_n", &gen_n, &b_gen_n);
   fChain->SetBranchAddress("gen_PUNumInt", &gen_PUNumInt, &b_gen_PUNumInt);
   fChain->SetBranchAddress("gen_TrueNumInt", &gen_TrueNumInt, &b_gen_TrueNumInt);
   fChain->SetBranchAddress("vtx_x", &vtx_x, &b_vtx_x);
   fChain->SetBranchAddress("vtx_y", &vtx_y, &b_vtx_y);
   fChain->SetBranchAddress("vtx_z", &vtx_z, &b_vtx_z);
   fChain->SetBranchAddress("gen_eta", &gen_eta, &b_gen_eta);
   fChain->SetBranchAddress("gen_phi", &gen_phi, &b_gen_phi);
   fChain->SetBranchAddress("gen_pt", &gen_pt, &b_gen_pt);
   fChain->SetBranchAddress("gen_energy", &gen_energy, &b_gen_energy);
   fChain->SetBranchAddress("gen_charge", &gen_charge, &b_gen_charge);
   fChain->SetBranchAddress("gen_pdgid", &gen_pdgid, &b_gen_pdgid);
   fChain->SetBranchAddress("gen_status", &gen_status, &b_gen_status);
   fChain->SetBranchAddress("gen_daughters", &gen_daughters, &b_gen_daughters);
   fChain->SetBranchAddress("genpart_eta", &genpart_eta, &b_genpart_eta);
   fChain->SetBranchAddress("genpart_phi", &genpart_phi, &b_genpart_phi);
   fChain->SetBranchAddress("genpart_pt", &genpart_pt, &b_genpart_pt);
   fChain->SetBranchAddress("genpart_energy", &genpart_energy, &b_genpart_energy);
   fChain->SetBranchAddress("genpart_dvx", &genpart_dvx, &b_genpart_dvx);
   fChain->SetBranchAddress("genpart_dvy", &genpart_dvy, &b_genpart_dvy);
   fChain->SetBranchAddress("genpart_dvz", &genpart_dvz, &b_genpart_dvz);
   fChain->SetBranchAddress("genpart_ovx", &genpart_ovx, &b_genpart_ovx);
   fChain->SetBranchAddress("genpart_ovy", &genpart_ovy, &b_genpart_ovy);
   fChain->SetBranchAddress("genpart_ovz", &genpart_ovz, &b_genpart_ovz);
   fChain->SetBranchAddress("genpart_mother", &genpart_mother, &b_genpart_mother);
   fChain->SetBranchAddress("genpart_exphi", &genpart_exphi, &b_genpart_exphi);
   fChain->SetBranchAddress("genpart_exeta", &genpart_exeta, &b_genpart_exeta);
   fChain->SetBranchAddress("genpart_exx", &genpart_exx, &b_genpart_exx);
   fChain->SetBranchAddress("genpart_exy", &genpart_exy, &b_genpart_exy);
   fChain->SetBranchAddress("genpart_fbrem", &genpart_fbrem, &b_genpart_fbrem);
   fChain->SetBranchAddress("genpart_pid", &genpart_pid, &b_genpart_pid);
   fChain->SetBranchAddress("genpart_gen", &genpart_gen, &b_genpart_gen);
   fChain->SetBranchAddress("genpart_reachedEE", &genpart_reachedEE, &b_genpart_reachedEE);
   fChain->SetBranchAddress("genpart_fromBeamPipe", &genpart_fromBeamPipe, &b_genpart_fromBeamPipe);
   fChain->SetBranchAddress("genpart_posx", &genpart_posx, &b_genpart_posx);
   fChain->SetBranchAddress("genpart_posy", &genpart_posy, &b_genpart_posy);
   fChain->SetBranchAddress("genpart_posz", &genpart_posz, &b_genpart_posz);
   fChain->SetBranchAddress("genjet_n", &genjet_n, &b_genjet_n);
   fChain->SetBranchAddress("genjet_energy", &genjet_energy, &b_genjet_energy);
   fChain->SetBranchAddress("genjet_pt", &genjet_pt, &b_genjet_pt);
   fChain->SetBranchAddress("genjet_eta", &genjet_eta, &b_genjet_eta);
   fChain->SetBranchAddress("genjet_phi", &genjet_phi, &b_genjet_phi);
   fChain->SetBranchAddress("gentau_pt", &gentau_pt, &b_gentau_pt);
   fChain->SetBranchAddress("gentau_eta", &gentau_eta, &b_gentau_eta);
   fChain->SetBranchAddress("gentau_phi", &gentau_phi, &b_gentau_phi);
   fChain->SetBranchAddress("gentau_energy", &gentau_energy, &b_gentau_energy);
   fChain->SetBranchAddress("gentau_mass", &gentau_mass, &b_gentau_mass);
   fChain->SetBranchAddress("gentau_vis_pt", &gentau_vis_pt, &b_gentau_vis_pt);
   fChain->SetBranchAddress("gentau_vis_eta", &gentau_vis_eta, &b_gentau_vis_eta);
   fChain->SetBranchAddress("gentau_vis_phi", &gentau_vis_phi, &b_gentau_vis_phi);
   fChain->SetBranchAddress("gentau_vis_energy", &gentau_vis_energy, &b_gentau_vis_energy);
   fChain->SetBranchAddress("gentau_vis_mass", &gentau_vis_mass, &b_gentau_vis_mass);
   fChain->SetBranchAddress("gentau_products_pt", &gentau_products_pt, &b_gentau_products_pt);
   fChain->SetBranchAddress("gentau_products_eta", &gentau_products_eta, &b_gentau_products_eta);
   fChain->SetBranchAddress("gentau_products_phi", &gentau_products_phi, &b_gentau_products_phi);
   fChain->SetBranchAddress("gentau_products_energy", &gentau_products_energy, &b_gentau_products_energy);
   fChain->SetBranchAddress("gentau_products_mass", &gentau_products_mass, &b_gentau_products_mass);
   fChain->SetBranchAddress("gentau_products_id", &gentau_products_id, &b_gentau_products_id);
   fChain->SetBranchAddress("gentau_decayMode", &gentau_decayMode, &b_gentau_decayMode);
   fChain->SetBranchAddress("gentau_totNproducts", &gentau_totNproducts, &b_gentau_totNproducts);
   fChain->SetBranchAddress("gentau_totNgamma", &gentau_totNgamma, &b_gentau_totNgamma);
   fChain->SetBranchAddress("gentau_totNpiZero", &gentau_totNpiZero, &b_gentau_totNpiZero);
   fChain->SetBranchAddress("gentau_totNcharged", &gentau_totNcharged, &b_gentau_totNcharged);
   fChain->SetBranchAddress("tc_n", &tc_n, &b_tc_n);
   fChain->SetBranchAddress("tc_id", &tc_id, &b_tc_id);
   fChain->SetBranchAddress("tc_subdet", &tc_subdet, &b_tc_subdet);
   fChain->SetBranchAddress("tc_zside", &tc_zside, &b_tc_zside);
   fChain->SetBranchAddress("tc_layer", &tc_layer, &b_tc_layer);
   fChain->SetBranchAddress("tc_wafer", &tc_wafer, &b_tc_wafer);
   fChain->SetBranchAddress("tc_waferu", &tc_waferu, &b_tc_waferu);
   fChain->SetBranchAddress("tc_waferv", &tc_waferv, &b_tc_waferv);
   fChain->SetBranchAddress("tc_wafertype", &tc_wafertype, &b_tc_wafertype);
   fChain->SetBranchAddress("tc_panel_number", &tc_panel_number, &b_tc_panel_number);
   fChain->SetBranchAddress("tc_panel_sector", &tc_panel_sector, &b_tc_panel_sector);
   fChain->SetBranchAddress("tc_cell", &tc_cell, &b_tc_cell);
   fChain->SetBranchAddress("tc_cellu", &tc_cellu, &b_tc_cellu);
   fChain->SetBranchAddress("tc_cellv", &tc_cellv, &b_tc_cellv);
   fChain->SetBranchAddress("tc_data", &tc_data, &b_tc_data);
   fChain->SetBranchAddress("tc_uncompressedCharge", &tc_uncompressedCharge, &b_tc_uncompressedCharge);
   fChain->SetBranchAddress("tc_compressedCharge", &tc_compressedCharge, &b_tc_compressedCharge);
   fChain->SetBranchAddress("tc_pt", &tc_pt, &b_tc_pt);
   fChain->SetBranchAddress("tc_mipPt", &tc_mipPt, &b_tc_mipPt);
   fChain->SetBranchAddress("tc_energy", &tc_energy, &b_tc_energy);
   fChain->SetBranchAddress("tc_eta", &tc_eta, &b_tc_eta);
   fChain->SetBranchAddress("tc_phi", &tc_phi, &b_tc_phi);
   fChain->SetBranchAddress("tc_x", &tc_x, &b_tc_x);
   fChain->SetBranchAddress("tc_y", &tc_y, &b_tc_y);
   fChain->SetBranchAddress("tc_z", &tc_z, &b_tc_z);
   fChain->SetBranchAddress("tc_cluster_id", &tc_cluster_id, &b_tc_cluster_id);
   fChain->SetBranchAddress("tc_multicluster_id", &tc_multicluster_id, &b_tc_multicluster_id);
   fChain->SetBranchAddress("tc_multicluster_pt", &tc_multicluster_pt, &b_tc_multicluster_pt);
   fChain->SetBranchAddress("ts_n", &ts_n, &b_ts_n);
   fChain->SetBranchAddress("ts_id", &ts_id, &b_ts_id);
   fChain->SetBranchAddress("ts_subdet", &ts_subdet, &b_ts_subdet);
   fChain->SetBranchAddress("ts_zside", &ts_zside, &b_ts_zside);
   fChain->SetBranchAddress("ts_layer", &ts_layer, &b_ts_layer);
   fChain->SetBranchAddress("ts_wafer", &ts_wafer, &b_ts_wafer);
   fChain->SetBranchAddress("ts_wafertype", &ts_wafertype, &b_ts_wafertype);
   fChain->SetBranchAddress("ts_panel_number", &ts_panel_number, &b_ts_panel_number);
   fChain->SetBranchAddress("ts_panel_sector", &ts_panel_sector, &b_ts_panel_sector);
   fChain->SetBranchAddress("ts_data", &ts_data, &b_ts_data);
   fChain->SetBranchAddress("ts_pt", &ts_pt, &b_ts_pt);
   fChain->SetBranchAddress("ts_mipPt", &ts_mipPt, &b_ts_mipPt);
   fChain->SetBranchAddress("ts_energy", &ts_energy, &b_ts_energy);
   fChain->SetBranchAddress("ts_eta", &ts_eta, &b_ts_eta);
   fChain->SetBranchAddress("ts_phi", &ts_phi, &b_ts_phi);
   fChain->SetBranchAddress("ts_x", &ts_x, &b_ts_x);
   fChain->SetBranchAddress("ts_y", &ts_y, &b_ts_y);
   fChain->SetBranchAddress("ts_z", &ts_z, &b_ts_z);
   fChain->SetBranchAddress("cl3d_n", &cl3d_n, &b_cl3d_n);
   fChain->SetBranchAddress("cl3d_id", &cl3d_id, &b_cl3d_id);
   fChain->SetBranchAddress("cl3d_pt", &cl3d_pt, &b_cl3d_pt);
   fChain->SetBranchAddress("cl3d_energy", &cl3d_energy, &b_cl3d_energy);
   fChain->SetBranchAddress("cl3d_eta", &cl3d_eta, &b_cl3d_eta);
   fChain->SetBranchAddress("cl3d_phi", &cl3d_phi, &b_cl3d_phi);
   fChain->SetBranchAddress("cl3d_clusters_n", &cl3d_clusters_n, &b_cl3d_clusters_n);
   fChain->SetBranchAddress("cl3d_clusters_id", &cl3d_clusters_id, &b_cl3d_clusters_id);
   fChain->SetBranchAddress("cl3d_showerlength", &cl3d_showerlength, &b_cl3d_showerlength);
   fChain->SetBranchAddress("cl3d_coreshowerlength", &cl3d_coreshowerlength, &b_cl3d_coreshowerlength);
   fChain->SetBranchAddress("cl3d_firstlayer", &cl3d_firstlayer, &b_cl3d_firstlayer);
   fChain->SetBranchAddress("cl3d_maxlayer", &cl3d_maxlayer, &b_cl3d_maxlayer);
   fChain->SetBranchAddress("cl3d_seetot", &cl3d_seetot, &b_cl3d_seetot);
   fChain->SetBranchAddress("cl3d_seemax", &cl3d_seemax, &b_cl3d_seemax);
   fChain->SetBranchAddress("cl3d_spptot", &cl3d_spptot, &b_cl3d_spptot);
   fChain->SetBranchAddress("cl3d_sppmax", &cl3d_sppmax, &b_cl3d_sppmax);
   fChain->SetBranchAddress("cl3d_szz", &cl3d_szz, &b_cl3d_szz);
   fChain->SetBranchAddress("cl3d_srrtot", &cl3d_srrtot, &b_cl3d_srrtot);
   fChain->SetBranchAddress("cl3d_srrmax", &cl3d_srrmax, &b_cl3d_srrmax);
   fChain->SetBranchAddress("cl3d_srrmean", &cl3d_srrmean, &b_cl3d_srrmean);
   fChain->SetBranchAddress("cl3d_emaxe", &cl3d_emaxe, &b_cl3d_emaxe);
   fChain->SetBranchAddress("cl3d_hoe", &cl3d_hoe, &b_cl3d_hoe);
   fChain->SetBranchAddress("cl3d_meanz", &cl3d_meanz, &b_cl3d_meanz);
   fChain->SetBranchAddress("cl3d_layer10", &cl3d_layer10, &b_cl3d_layer10);
   fChain->SetBranchAddress("cl3d_layer50", &cl3d_layer50, &b_cl3d_layer50);
   fChain->SetBranchAddress("cl3d_layer90", &cl3d_layer90, &b_cl3d_layer90);
   fChain->SetBranchAddress("cl3d_ntc67", &cl3d_ntc67, &b_cl3d_ntc67);
   fChain->SetBranchAddress("cl3d_ntc90", &cl3d_ntc90, &b_cl3d_ntc90);
   fChain->SetBranchAddress("cl3d_bdteg", &cl3d_bdteg, &b_cl3d_bdteg);
   fChain->SetBranchAddress("cl3d_quality", &cl3d_quality, &b_cl3d_quality);
   fChain->SetBranchAddress("cl3d_ipt", &cl3d_ipt, &b_cl3d_ipt);
   fChain->SetBranchAddress("cl3d_ienergy", &cl3d_ienergy, &b_cl3d_ienergy);
   fChain->SetBranchAddress("tower_n", &tower_n, &b_tower_n);
   fChain->SetBranchAddress("tower_pt", &tower_pt, &b_tower_pt);
   fChain->SetBranchAddress("tower_energy", &tower_energy, &b_tower_energy);
   fChain->SetBranchAddress("tower_eta", &tower_eta, &b_tower_eta);
   fChain->SetBranchAddress("tower_phi", &tower_phi, &b_tower_phi);
   fChain->SetBranchAddress("tower_etEm", &tower_etEm, &b_tower_etEm);
   fChain->SetBranchAddress("tower_etHad", &tower_etHad, &b_tower_etHad);
   fChain->SetBranchAddress("tower_iEta", &tower_iEta, &b_tower_iEta);
   fChain->SetBranchAddress("tower_iPhi", &tower_iPhi, &b_tower_iPhi);
   Notify();
}

Bool_t HGCalTriggerNtupleReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HGCalTriggerNtupleReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HGCalTriggerNtupleReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HGCalTriggerNtupleReader_cxx
