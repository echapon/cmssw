#define HGCalTriggerNtupleReader_cxx
#include "HGCalTriggerNtupleReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TEfficiency.h>
#include <TVector2.h>
#include <Math/Vector4D.h>
#include <TGraph.h>
#include <TText.h>
#include <TMath.h>
#include <TStyle.h>

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"

#include <iostream>
#include <vector>
using namespace fastjet;
using namespace std;

// PARAMETERS
constexpr float kRmatch = 0.3;//0.1;
constexpr float kRjet = 0.4; // for anti-kt with FastJet
constexpr float kMinRapBkgEst = 1.6; // for rho calculation by FastJet
constexpr float kMaxRapBkgEst = 2.9; // for rho calculation by FastJet
constexpr float kGridSpacingBkgEst = 0.5; // for rho calculation by FastJet
constexpr float kJetRawPtMin = 10;
constexpr float kJetPtMin = 20;
constexpr float kJetPtMin2 = 40;
constexpr float kJetAbsEtaMin = 1.4;
constexpr float kJetAbsEtaMax = 3.2;

void HGCalTriggerNtupleReader::Loop(TString filename_out, bool doPUsub, int evtdisplaynb)
{
//   In a ROOT session, you can do:
//      root> .L HGCalTriggerNtupleReader.C
//      root> HGCalTriggerNtupleReader t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
   fChain->SetBranchStatus("*",0);  // disable all branches
   fChain->SetBranchStatus("gen_PUNumInt",1);  // activate branchname
   fChain->SetBranchStatus("gen_TrueNumInt",1);  // activate branchname
   fChain->SetBranchStatus("vtx_*",1);  // activate branchname
   fChain->SetBranchStatus("genjet_*",1);  // activate branchname
   fChain->SetBranchStatus("cl3d_n",1);  // activate branchname
   fChain->SetBranchStatus("cl3d_pt",1);  // activate branchname
   fChain->SetBranchStatus("cl3d_eta",1);  // activate branchname
   fChain->SetBranchStatus("cl3d_phi",1);  // activate branchname
   fChain->SetBranchStatus("cl3d_energy",1);  // activate branchname
   fChain->SetBranchStatus("tower_*",1);  // activate branchname
   fChain->SetBranchStatus("*_n",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nentries2 = fChain->GetEntries();

   // output file
   TFile *f = TFile::Open(filename_out,"RECREATE");

   // HISTOGRAMS
   // event variables
   TH1F *h_gen_PUNumInt = new TH1F("h_gen_PUNumInt",";gen PU;Entries",50,0,250);
   TH1F *h_gen_TrueNumInt = new TH1F("h_gen_TrueNumInt",";gen PU;Entries",50,0,250);
   TH1F *h_vtx_x = new TH1F("h_vtx_x",";vtx x [cm];Entries",20,-0.05,0.05);
   TH1F *h_vtx_y = new TH1F("h_vtx_y",";vtx y [cm];Entries",20,-0.05,0.05);
   TH1F *h_vtx_z = new TH1F("h_vtx_z",";vtx z [cm];Entries",50,-25,25);
   TH1F *h_rho_clu = new TH1F("h_rho_clu",";#rho (clu) [GeV]",100,0,100);
   TH1F *h_sigma_clu = new TH1F("h_sigma_clu",";#sigma (clu) [GeV]",50,0,50);
   TH1F *h_rho_tow = new TH1F("h_rho_tow",";#rho (tow) [GeV]",100,0,100);
   TH1F *h_sigma_tow = new TH1F("h_sigma_tow",";#sigma (tow) [GeV]",50,0,50);
   TH1F *h_rho_clutow = new TH1F("h_rho_clutow",";#rho (clutow) [GeV]",100,0,100);
   TH1F *h_sigma_clutow = new TH1F("h_sigma_clutow",";#sigma (clutow) [GeV]",50,0,50);

   // jet histograms
   gDirectory->mkdir("jets");
   gDirectory->cd("jets");
   gDirectory->mkdir("gen");
   gDirectory->cd("gen");
   TH1F *h_gen_pt = new TH1F("h_gen_pt",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_gen_pt_p = new TH1F("h_gen_pt_p",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_gen_pt_m = new TH1F("h_gen_pt_m",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_gen_eta = new TH1F("h_gen_eta",";gen jet #eta;Entries",34,-3.4,3.4);
   TH1F *h_gen_eta_p = new TH1F("h_gen_eta_p",";gen jet |#eta|;Entries",18,1.4,3.2);
   TH1F *h_gen_eta_m = new TH1F("h_gen_eta_m",";gen jet |#eta|;Entries",18,1.4,3.2);
   f->cd("jets");
   gDirectory->mkdir("clu");
   gDirectory->cd("clu");
   TH1F *h_clu_pt = new TH1F("h_clu_pt",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_clu_pt_p = new TH1F("h_clu_pt_p",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_clu_pt_m = new TH1F("h_clu_pt_m",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_clu_eta = new TH1F("h_clu_eta",";gen jet #eta;Entries",34,-3.4,3.4);
   TH1F *h_clu_eta_p = new TH1F("h_clu_eta_p",";gen jet |#eta|;Entries",18,1.4,3.2);
   TH1F *h_clu_eta_m = new TH1F("h_clu_eta_m",";gen jet |#eta|;Entries",18,1.4,3.2);
   f->cd("jets");
   gDirectory->mkdir("clutow");
   gDirectory->cd("clutow");
   TH1F *h_clutow_pt = new TH1F("h_clutow_pt",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_clutow_pt_p = new TH1F("h_clutow_pt_p",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_clutow_pt_m = new TH1F("h_clutow_pt_m",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_clutow_eta = new TH1F("h_clutow_eta",";gen jet #eta;Entries",34,-3.4,3.4);
   TH1F *h_clutow_eta_p = new TH1F("h_clutow_eta_p",";gen jet |#eta|;Entries",18,1.4,3.2);
   TH1F *h_clutow_eta_m = new TH1F("h_clutow_eta_m",";gen jet |#eta|;Entries",18,1.4,3.2);
   f->cd("jets");
   gDirectory->mkdir("tow");
   gDirectory->cd("tow");
   TH1F *h_tow_pt = new TH1F("h_tow_pt",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_tow_pt_p = new TH1F("h_tow_pt_p",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_tow_pt_m = new TH1F("h_tow_pt_m",";gen jet p_{T} [GeV];Entries",20,0,200);
   TH1F *h_tow_eta = new TH1F("h_tow_eta",";gen jet #eta;Entries",34,-3.4,3.4);
   TH1F *h_tow_eta_p = new TH1F("h_tow_eta_p",";gen jet |#eta|;Entries",18,1.4,3.2);
   TH1F *h_tow_eta_m = new TH1F("h_tow_eta_m",";gen jet |#eta|;Entries",18,1.4,3.2);

   // resolution plots
   f->cd();
   f->mkdir("resolution");
   f->cd("resolution");
   gDirectory->mkdir("clu");
   gDirectory->cd("clu");
   TH2F *hdpt_clu_pt = new TH2F("hdpt_clu_pt",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_clu_pt_p = new TH2F("hdpt_clu_pt_p",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_clu_pt_m = new TH2F("hdpt_clu_pt_m",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_clu_eta = new TH2F("hdpt_clu_eta",";gen jet #eta;rec p_{T} - gen p_{T} [GeV]",34,-3.4,3.4,200,-100,100);
   TH2F *hdpt_clu_eta_p = new TH2F("hdpt_clu_eta_p",";gen jet |#eta|;rec p_{T} - gen p_{T} [GeV]",18,1.4,3.2,200,-100,100);
   TH2F *hdpt_clu_eta_m = new TH2F("hdpt_clu_eta_m",";gen jet |#eta|;rec p_{T} - gen p_{T} [GeV]",18,1.4,3.2,200,-100,100);
   TH2F *hdeta_clu_pt = new TH2F("hdeta_clu_pt",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_clu_pt_p = new TH2F("hdeta_clu_pt_p",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_clu_pt_m = new TH2F("hdeta_clu_pt_m",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_clu_eta = new TH2F("hdeta_clu_eta",";gen jet #eta;rec #eta - gen #eta",34,-3.4,3.4,200,-1,1);
   TH2F *hdeta_clu_eta_p = new TH2F("hdeta_clu_eta_p",";gen jet |#eta|;rec #eta - gen #eta",18,1.4,3.2,200,-1,1);
   TH2F *hdeta_clu_eta_m = new TH2F("hdeta_clu_eta_m",";gen jet |#eta|;rec #eta - gen #eta",18,1.4,3.2,200,-1,1);
   TH2F *hdphi_clu_pt = new TH2F("hdphi_clu_pt",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_clu_pt_p = new TH2F("hdphi_clu_pt_p",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_clu_pt_m = new TH2F("hdphi_clu_pt_m",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_clu_eta = new TH2F("hdphi_clu_eta",";gen jet #eta;rec #phi - gen #phi",34,-3.4,3.4,200,-1,1);
   TH2F *hdphi_clu_eta_p = new TH2F("hdphi_clu_eta_p",";gen jet |#eta|;rec #phi - gen #phi",18,1.4,3.2,200,-1,1);
   TH2F *hdphi_clu_eta_m = new TH2F("hdphi_clu_eta_m",";gen jet |#eta|;rec #phi - gen #phi",18,1.4,3.2,200,-1,1);
   f->cd("resolution");
   gDirectory->mkdir("clutow");
   gDirectory->cd("clutow");
   TH2F *hdpt_clutow_pt = new TH2F("hdpt_clutow_pt",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_clutow_pt_p = new TH2F("hdpt_clutow_pt_p",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_clutow_pt_m = new TH2F("hdpt_clutow_pt_m",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_clutow_eta = new TH2F("hdpt_clutow_eta",";gen jet #eta;rec p_{T} - gen p_{T} [GeV]",34,-3.4,3.4,200,-100,100);
   TH2F *hdpt_clutow_eta_p = new TH2F("hdpt_clutow_eta_p",";gen jet |#eta|;rec p_{T} - gen p_{T} [GeV]",18,1.4,3.2,200,-100,100);
   TH2F *hdpt_clutow_eta_m = new TH2F("hdpt_clutow_eta_m",";gen jet |#eta|;rec p_{T} - gen p_{T} [GeV]",18,1.4,3.2,200,-100,100);
   TH2F *hdeta_clutow_pt = new TH2F("hdeta_clutow_pt",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_clutow_pt_p = new TH2F("hdeta_clutow_pt_p",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_clutow_pt_m = new TH2F("hdeta_clutow_pt_m",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_clutow_eta = new TH2F("hdeta_clutow_eta",";gen jet #eta;rec #eta - gen #eta",34,-3.4,3.4,200,-1,1);
   TH2F *hdeta_clutow_eta_p = new TH2F("hdeta_clutow_eta_p",";gen jet |#eta|;rec #eta - gen #eta",18,1.4,3.2,200,-1,1);
   TH2F *hdeta_clutow_eta_m = new TH2F("hdeta_clutow_eta_m",";gen jet |#eta|;rec #eta - gen #eta",18,1.4,3.2,200,-1,1);
   TH2F *hdphi_clutow_pt = new TH2F("hdphi_clutow_pt",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_clutow_pt_p = new TH2F("hdphi_clutow_pt_p",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_clutow_pt_m = new TH2F("hdphi_clutow_pt_m",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_clutow_eta = new TH2F("hdphi_clutow_eta",";gen jet #eta;rec #phi - gen #phi",34,-3.4,3.4,200,-1,1);
   TH2F *hdphi_clutow_eta_p = new TH2F("hdphi_clutow_eta_p",";gen jet |#eta|;rec #phi - gen #phi",18,1.4,3.2,200,-1,1);
   TH2F *hdphi_clutow_eta_m = new TH2F("hdphi_clutow_eta_m",";gen jet |#eta|;rec #phi - gen #phi",18,1.4,3.2,200,-1,1);
   f->cd("resolution");
   gDirectory->mkdir("tow");
   gDirectory->cd("tow");
   TH2F *hdpt_tow_pt = new TH2F("hdpt_tow_pt",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_tow_pt_p = new TH2F("hdpt_tow_pt_p",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_tow_pt_m = new TH2F("hdpt_tow_pt_m",";gen jet p_{T} [GeV];rec p_{T} - gen p_{T} [GeV]",20,0,200,200,-100,100);
   TH2F *hdpt_tow_eta = new TH2F("hdpt_tow_eta",";gen jet #eta;rec p_{T} - gen p_{T} [GeV]",34,-3.4,3.4,200,-100,100);
   TH2F *hdpt_tow_eta_p = new TH2F("hdpt_tow_eta_p",";gen jet |#eta|;rec p_{T} - gen p_{T} [GeV]",18,1.4,3.2,200,-100,100);
   TH2F *hdpt_tow_eta_m = new TH2F("hdpt_tow_eta_m",";gen jet |#eta|;rec p_{T} - gen p_{T} [GeV]",18,1.4,3.2,200,-100,100);
   TH2F *hdeta_tow_pt = new TH2F("hdeta_tow_pt",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_tow_pt_p = new TH2F("hdeta_tow_pt_p",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_tow_pt_m = new TH2F("hdeta_tow_pt_m",";gen jet p_{T} [GeV];rec #eta - gen #eta",20,0,200,200,-1,1);
   TH2F *hdeta_tow_eta = new TH2F("hdeta_tow_eta",";gen jet #eta;rec #eta - gen #eta",34,-3.4,3.4,200,-1,1);
   TH2F *hdeta_tow_eta_p = new TH2F("hdeta_tow_eta_p",";gen jet |#eta|;rec #eta - gen #eta",18,1.4,3.2,200,-1,1);
   TH2F *hdeta_tow_eta_m = new TH2F("hdeta_tow_eta_m",";gen jet |#eta|;rec #eta - gen #eta",18,1.4,3.2,200,-1,1);
   TH2F *hdphi_tow_pt = new TH2F("hdphi_tow_pt",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_tow_pt_p = new TH2F("hdphi_tow_pt_p",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_tow_pt_m = new TH2F("hdphi_tow_pt_m",";gen jet p_{T} [GeV];rec #phi - gen #phi",20,0,200,200,-1,1);
   TH2F *hdphi_tow_eta = new TH2F("hdphi_tow_eta",";gen jet #eta;rec #phi - gen #phi",34,-3.4,3.4,200,-1,1);
   TH2F *hdphi_tow_eta_p = new TH2F("hdphi_tow_eta_p",";gen jet |#eta|;rec #phi - gen #phi",18,1.4,3.2,200,-1,1);
   TH2F *hdphi_tow_eta_m = new TH2F("hdphi_tow_eta_m",";gen jet |#eta|;rec #phi - gen #phi",18,1.4,3.2,200,-1,1);

   f->cd();

   // NTUPLE
   TTree *tr = new TTree("tree","tree with jet info");
   int clujet_n=0, clutowjet_n=0, towjet_n=0;
   float rho_clu, rho_tow, rho_clutow;
   float sigma_clu, sigma_tow, sigma_clutow;
   vector<float> clujet_pt;
   vector<float> clujet_eta;
   vector<float> clujet_phi;
   vector<float> clujet_genpt;
   vector<float> clujet_geneta;
   vector<float> clujet_genphi;
   vector<float> clujet_genDR;
   vector<float> clujet_area;
   vector<float> clutowjet_pt;
   vector<float> clutowjet_eta;
   vector<float> clutowjet_phi;
   vector<float> clutowjet_genpt;
   vector<float> clutowjet_geneta;
   vector<float> clutowjet_genphi;
   vector<float> clutowjet_genDR;
   vector<float> clutowjet_area;
   vector<float> towjet_pt;
   vector<float> towjet_eta;
   vector<float> towjet_phi;
   vector<float> towjet_genpt;
   vector<float> towjet_geneta;
   vector<float> towjet_genphi;
   vector<float> towjet_genDR;
   vector<float> towjet_area;

   tr->Branch("gen_PUNumInt", &gen_PUNumInt, "gen_PUNumInt/I");
   tr->Branch("gen_TrueNumInt", &gen_TrueNumInt, "gen_TrueNumInt/I");
   tr->Branch("vtx_x", &vtx_x, "vtx_x/F");
   tr->Branch("vtx_y", &vtx_y, "vtx_y/F");
   tr->Branch("vtx_z", &vtx_z, "vtx_z/F");
   tr->Branch("tc_n", &tc_n, "tc_n/I");
   tr->Branch("ts_n", &ts_n, "ts_n/I");
   tr->Branch("cl3d_n", &cl3d_n, "cl3d_n/I");
   tr->Branch("tower_n", &tower_n, "tower_n/I");
   tr->Branch("genjet_n", &genjet_n, "genjet_n/I");
   tr->Branch("genjet_pt", genjet_pt);
   tr->Branch("genjet_eta", genjet_eta);
   tr->Branch("genjet_phi", genjet_phi);
   tr->Branch("clujet_n", &clujet_n, "clujet_n/I");
   tr->Branch("rho_clu", &rho_clu, "rho_clu/F");
   tr->Branch("sigma_clu", &sigma_clu, "sigma_clu/F");
   tr->Branch("clujet_pt", &clujet_pt);
   tr->Branch("clujet_eta", &clujet_eta);
   tr->Branch("clujet_phi", &clujet_phi);
   tr->Branch("clujet_genpt", &clujet_genpt);
   tr->Branch("clujet_geneta", &clujet_geneta);
   tr->Branch("clujet_genphi", &clujet_genphi);
   tr->Branch("clujet_genDR", &clujet_genDR);
   tr->Branch("clujet_area", &clujet_area);
   tr->Branch("clutowjet_n", &clutowjet_n, "clutowjet_n/I");
   tr->Branch("rho_clutow", &rho_clutow, "rho_clutow/F");
   tr->Branch("sigma_clutow", &sigma_clutow, "sigma_clutow/F");
   tr->Branch("clutowjet_pt", &clutowjet_pt);
   tr->Branch("clutowjet_eta", &clutowjet_eta);
   tr->Branch("clutowjet_phi", &clutowjet_phi);
   tr->Branch("clutowjet_genpt", &clutowjet_genpt);
   tr->Branch("clutowjet_geneta", &clutowjet_geneta);
   tr->Branch("clutowjet_genphi", &clutowjet_genphi);
   tr->Branch("clutowjet_genDR", &clutowjet_genDR);
   tr->Branch("clutowjet_area", &clutowjet_area);
   tr->Branch("towjet_n", &towjet_n, "towjet_n/I");
   tr->Branch("rho_tow", &rho_tow, "rho_tow/F");
   tr->Branch("sigma_tow", &sigma_tow, "sigma_tow/F");
   tr->Branch("towjet_pt", &towjet_pt);
   tr->Branch("towjet_eta", &towjet_eta);
   tr->Branch("towjet_phi", &towjet_phi);
   tr->Branch("towjet_genpt", &towjet_genpt);
   tr->Branch("towjet_geneta", &towjet_geneta);
   tr->Branch("towjet_genphi", &towjet_genphi);
   tr->Branch("towjet_genDR", &towjet_genDR);
   tr->Branch("towjet_area", &towjet_area);


   // FastJet objects
   JetDefinition jet_def(antikt_algorithm, kRjet);
   GridMedianBackgroundEstimator bge_clu(kMinRapBkgEst, kMaxRapBkgEst, kGridSpacingBkgEst, kGridSpacingBkgEst);
   GridMedianBackgroundEstimator bge_tow(kMinRapBkgEst, kMaxRapBkgEst, kGridSpacingBkgEst, kGridSpacingBkgEst);
   GridMedianBackgroundEstimator bge_clutow(kMinRapBkgEst, kMaxRapBkgEst, kGridSpacingBkgEst, kGridSpacingBkgEst);
   Subtractor subtractor_clu(&bge_clu);
   Subtractor subtractor_tow(&bge_tow);
   Subtractor subtractor_clutow(&bge_clutow);
   Selector jet_selector_raw = SelectorAbsEtaMin(kJetAbsEtaMin) * SelectorAbsEtaMax(kJetAbsEtaMax);
   Selector jet_selector = SelectorPtMin(kJetPtMin);
   double ghost_maxrap = 4.0;
   GhostedAreaSpec area_spec(ghost_maxrap);
   AreaDefinition area_def(active_area, area_spec);

   Long64_t nbytes = 0, nb = 0;
   cout << nentries << " " << nentries2 << endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      // cout << jentry << endl; // DEBUG
      if (evtdisplaynb>=0 && jentry != evtdisplaynb) continue;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (jentry % 1000 == 0) cout << jentry << " / " << nentries2 << endl;
      // if (jentry>100) break; // DEBUG

      // reset variables for tree
      clujet_pt.clear();
      clujet_eta.clear();
      clujet_phi.clear();
      clujet_genpt.clear();
      clujet_geneta.clear();
      clujet_genphi.clear();
      clujet_genDR.clear();
      clujet_area.clear();
      clutowjet_pt.clear();
      clutowjet_eta.clear();
      clutowjet_phi.clear();
      clutowjet_genpt.clear();
      clutowjet_geneta.clear();
      clutowjet_genphi.clear();
      clutowjet_genDR.clear();
      clutowjet_area.clear();
      towjet_pt.clear();
      towjet_eta.clear();
      towjet_phi.clear();
      towjet_genpt.clear();
      towjet_geneta.clear();
      towjet_genphi.clear();
      towjet_genDR.clear();
      towjet_area.clear();

      // generate the inputs to fastjet
      vector<PseudoJet> pj_clu, pj_tow, pj_clutow;
      for (int i=0; i<cl3d_n; i++) {
         ROOT::Math::PtEtaPhiEVector tmpvec(cl3d_pt->at(i), cl3d_eta->at(i), cl3d_phi->at(i), cl3d_energy->at(i));
         PseudoJet tmppj(tmpvec.Px(), tmpvec.Py(), tmpvec.Pz(), tmpvec.energy());
         pj_clu.push_back(tmppj);
         pj_clutow.push_back(tmppj);
      }
      for (int i=0; i<tower_n; i++) {
         ROOT::Math::PtEtaPhiEVector tmpvec(tower_pt->at(i), tower_eta->at(i), tower_phi->at(i), tower_energy->at(i));
         PseudoJet tmppj(tmpvec.Px(), tmpvec.Py(), tmpvec.Pz(), tmpvec.energy());
         pj_tow.push_back(tmppj);
         pj_clutow.push_back(tmppj);
      }

      // run the clustering
      ClusterSequenceArea cs_clu(pj_clu, jet_def, area_def);
      vector<PseudoJet> jets_clu = sorted_by_pt(jet_selector_raw(cs_clu.inclusive_jets(kJetRawPtMin)));
      // if (jets_clu.size()>0) cout << jets_clu[0].pt() << " " << jets_clu[0].eta() << " " << jets_clu[0].phi() << endl;
      ClusterSequenceArea cs_tow(pj_tow, jet_def, area_def);
      vector<PseudoJet> jets_tow = sorted_by_pt(jet_selector_raw(cs_tow.inclusive_jets(kJetRawPtMin)));
      ClusterSequenceArea cs_clutow(pj_clutow, jet_def, area_def);
      vector<PseudoJet> jets_clutow = sorted_by_pt(jet_selector_raw(cs_clutow.inclusive_jets(kJetRawPtMin)));


      // run the background estimation
      bge_clu.set_particles(pj_clu);
      rho_clu = bge_clu.rho();
      sigma_clu = bge_clu.sigma();
      bge_tow.set_particles(pj_tow);
      rho_tow = bge_tow.rho();
      sigma_tow = bge_tow.sigma();
      bge_clutow.set_particles(pj_clutow);
      rho_clutow = bge_clutow.rho();
      sigma_clutow = bge_clutow.sigma();
      // cout << rho_clu << " " << sigma_clu << ", " << rho_tow << " " << sigma_tow << ", " << rho_clutow << " " << sigma_clutow << endl;

      // get the subtracted jets
      vector<PseudoJet> subtracted_jets_clu = jet_selector(subtractor_clu(jets_clu));
      vector<PseudoJet> subtracted_jets_tow = jet_selector(subtractor_tow(jets_tow));
      vector<PseudoJet> subtracted_jets_clutow = jet_selector(subtractor_clutow(jets_clutow));

      // replace the default jets with the subtracted jets
      if (doPUsub) {
         jets_clu = subtracted_jets_clu;
         jets_tow = subtracted_jets_tow;
         jets_clutow = subtracted_jets_clutow;
      }

      if (evtdisplaynb >= 0) {
         drawEventDisplay2(Form("clu_%d",evtdisplaynb), pj_clu, jets_clu);
         drawEventDisplay2(Form("tow_%d",evtdisplaynb), pj_tow, jets_tow);
         drawEventDisplay2(Form("clutow_%d",evtdisplaynb), pj_clutow, jets_clutow);
         return;
      }

      // FILL HISTOGRAMS
      // event histos
      h_gen_PUNumInt->Fill(gen_PUNumInt);
      h_gen_TrueNumInt->Fill(gen_TrueNumInt);
      h_vtx_x->Fill(vtx_x);
      h_vtx_y->Fill(vtx_y);
      h_vtx_z->Fill(vtx_z);
      h_rho_clu->Fill(rho_clu);
      h_sigma_clu->Fill(sigma_clu);
      h_rho_tow->Fill(rho_tow);
      h_sigma_tow->Fill(sigma_tow);
      h_rho_clutow->Fill(rho_clutow);
      h_sigma_clutow->Fill(sigma_clutow);

      // gen jets
      for (int i=0; i<genjet_n; i++) {
         // cuts to remove regions with very small or 0 efficiency
         float genpt = genjet_pt->at(i);
         float geneta = genjet_eta->at(i);
         bool okpt = genpt > kJetPtMin;
         bool oketa = (fabs(geneta)>kJetAbsEtaMin) && (fabs(geneta)<kJetAbsEtaMax);
         if (!okpt || !oketa) continue;

         bool okpt2 = genpt > kJetPtMin2;

         h_gen_pt->Fill(genpt);
         if (okpt) h_gen_eta->Fill(geneta);
         if (geneta>0) {
            h_gen_pt_p->Fill(genpt);
            if (okpt) h_gen_eta_p->Fill(fabs(geneta));
         } else {
            h_gen_pt_m->Fill(genpt);
            if (okpt) h_gen_eta_m->Fill(fabs(geneta));
         }
         // if (genjet_pt->at(i)>100 && fabs(genjet_eta->at(i))>kJetAbsEtaMin && fabs(genjet_eta->at(i))<kJetAbsEtaMax) cout << jentry << " gen jet " << i << ": " << genjet_pt->at(i) << " " << genjet_eta->at(i) << " " << genjet_phi->at(i) << endl; // DEBUG
      }

      // cluster jets
      for (auto itjet : jets_clu) {
         // match the jet to a gen jet
         float genpt, geneta, genphi;
         float minDR = 999.;
         int jminDR = -1;
         if (genjet_n>0) { // only do gen matching in case there are gen jets
            for (int j=0; j<genjet_n; j++) {
               bool okpt = genjet_pt->at(j) > kJetPtMin;
               bool oketa = (fabs(genjet_eta->at(j))>kJetAbsEtaMin) && (fabs(genjet_eta->at(j))<kJetAbsEtaMax);
               if (!okpt || !oketa) continue;
               float deta = itjet.eta() - genjet_eta->at(j);
               float dphi = TVector2::Phi_mpi_pi(itjet.phi() - genjet_phi->at(j));
               float dR = sqrt(pow(deta,2) + pow(dphi, 2));
               if (dR < minDR) {
                  minDR = dR;
                  jminDR = j;
               }
            }
            if (minDR > kRmatch) continue; // no match: fake jet

            genpt = genjet_pt->at(jminDR);
            geneta = genjet_eta->at(jminDR);
            genphi = genjet_phi->at(jminDR);
         } else {
            genpt = -1;
            geneta = -999.;
            genphi = -999.;
         }

         clujet_pt.emplace_back(itjet.pt());
         clujet_eta.emplace_back(itjet.eta());
         clujet_phi.emplace_back(itjet.phi());
         clujet_area.emplace_back(itjet.area());
         clujet_genpt.emplace_back(genpt);
         clujet_geneta.emplace_back(geneta);
         clujet_genphi.emplace_back(genphi);
         clujet_genDR.emplace_back(minDR);

         // cuts to remove regions with very small or 0 efficiency
         bool okpt = genpt > kJetPtMin2;

         h_clu_pt->Fill(genpt);
         hdpt_clu_pt->Fill(genpt,itjet.pt()-genpt);
         hdeta_clu_pt->Fill(genpt,itjet.eta()-geneta);
         hdphi_clu_pt->Fill(genpt,itjet.phi()-genphi);
         if (okpt) {
            h_clu_eta->Fill(geneta);
            hdpt_clu_eta->Fill(geneta,itjet.pt()-genpt);
            hdeta_clu_eta->Fill(geneta,itjet.eta()-geneta);
            hdphi_clu_eta->Fill(geneta,itjet.phi()-genphi);
         }
         if (itjet.eta()>0) {
            h_clu_pt_p->Fill(genpt);
            hdpt_clu_pt_p->Fill(genpt,itjet.pt()-genpt);
            hdeta_clu_pt_p->Fill(genpt,itjet.eta()-geneta);
            hdphi_clu_pt_p->Fill(genpt,itjet.phi()-genphi);
            if (okpt) {
               h_clu_eta_p->Fill(fabs(geneta));
               hdpt_clu_eta_p->Fill(fabs(geneta),itjet.pt()-genpt);
               hdeta_clu_eta_p->Fill(fabs(geneta),itjet.eta()-geneta);
               hdphi_clu_eta_p->Fill(fabs(geneta),itjet.phi()-genphi);
            }
         } else {
            h_clu_pt_m->Fill(genpt);
            hdpt_clu_pt_m->Fill(genpt,itjet.pt()-genpt);
            hdeta_clu_pt_m->Fill(genpt,itjet.eta()-geneta);
            hdphi_clu_pt_m->Fill(genpt,itjet.phi()-genphi);
            if (okpt) {
               h_clu_eta_m->Fill(fabs(geneta));
               hdpt_clu_eta_m->Fill(fabs(geneta),itjet.pt()-genpt);
               hdeta_clu_eta_m->Fill(fabs(geneta),itjet.eta()-geneta);
               hdphi_clu_eta_m->Fill(fabs(geneta),itjet.phi()-genphi);
            }
         }
      } // loop on cluster jets

      // tower jets
      for (auto itjet : jets_tow) {
         // match the jet to a gen jet
         float genpt, geneta, genphi;
         float minDR = 999.;
         int jminDR = -1;
         if (genjet_n>0) { // only do gen matching in case there are gen jets
            for (int j=0; j<genjet_n; j++) {
               bool okpt = genjet_pt->at(j) > kJetPtMin;
               bool oketa = (fabs(genjet_eta->at(j))>kJetAbsEtaMin) && (fabs(genjet_eta->at(j))<kJetAbsEtaMax);
               if (!okpt || !oketa) continue;
               float deta = itjet.eta() - genjet_eta->at(j);
               float dphi = TVector2::Phi_mpi_pi(itjet.phi() - genjet_phi->at(j));
               float dR = sqrt(pow(deta,2) + pow(dphi, 2));
               if (dR < minDR) {
                  minDR = dR;
                  jminDR = j;
               }
            }
            if (minDR > kRmatch) continue; // no match: fake jet

            genpt = genjet_pt->at(jminDR);
            geneta = genjet_eta->at(jminDR);
            genphi = genjet_phi->at(jminDR);
         } else {
            genpt = -1;
            geneta = -999.;
            genphi = -999.;
         }

         towjet_pt.emplace_back(itjet.pt());
         towjet_eta.emplace_back(itjet.eta());
         towjet_phi.emplace_back(itjet.phi());
         towjet_area.emplace_back(itjet.area());
         towjet_genpt.emplace_back(genpt);
         towjet_geneta.emplace_back(geneta);
         towjet_genphi.emplace_back(genphi);
         towjet_genDR.emplace_back(minDR);

         // cuts to remove regions with very small or 0 efficiency
         bool okpt = genpt > kJetPtMin2;

         h_tow_pt->Fill(genpt);
         hdpt_tow_pt->Fill(genpt,itjet.pt()-genpt);
         hdeta_tow_pt->Fill(genpt,itjet.eta()-geneta);
         hdphi_tow_pt->Fill(genpt,itjet.phi()-genphi);
         if (okpt) {
            h_tow_eta->Fill(geneta);
            hdpt_tow_eta->Fill(geneta,itjet.pt()-genpt);
            hdeta_tow_eta->Fill(geneta,itjet.eta()-geneta);
            hdphi_tow_eta->Fill(geneta,itjet.phi()-genphi);
         }
         if (itjet.eta()>0) {
            h_tow_pt_p->Fill(genpt);
            hdpt_tow_pt_p->Fill(genpt,itjet.pt()-genpt);
            hdeta_tow_pt_p->Fill(genpt,itjet.eta()-geneta);
            hdphi_tow_pt_p->Fill(genpt,itjet.phi()-genphi);
            if (okpt) {
               h_tow_eta_p->Fill(fabs(geneta));
               hdpt_tow_eta_p->Fill(fabs(geneta),itjet.pt()-genpt);
               hdeta_tow_eta_p->Fill(fabs(geneta),itjet.eta()-geneta);
               hdphi_tow_eta_p->Fill(fabs(geneta),itjet.phi()-genphi);
            }
         } else {
            h_tow_pt_m->Fill(genpt);
            hdpt_tow_pt_m->Fill(genpt,itjet.pt()-genpt);
            hdeta_tow_pt_m->Fill(genpt,itjet.eta()-geneta);
            hdphi_tow_pt_m->Fill(genpt,itjet.phi()-genphi);
            if (okpt) {
               h_tow_eta_m->Fill(fabs(geneta));
               hdpt_tow_eta_m->Fill(fabs(geneta),itjet.pt()-genpt);
               hdeta_tow_eta_m->Fill(fabs(geneta),itjet.eta()-geneta);
               hdphi_tow_eta_m->Fill(fabs(geneta),itjet.phi()-genphi);
            }
         }
      } // loop on tower jets

      // cluster + tower jets
      for (auto itjet : jets_clutow) {
         // if (itjet.pt()>50) cout << jentry <<  " clutow jet: " << itjet.pt() << " " << itjet.eta() << " " << itjet.phi() << endl; // DEBUG
         // match the jet to a gen jet
         float genpt, geneta, genphi;
         float minDR = 999.;
         int jminDR = -1;
         if (genjet_n>0) { // only do gen matching in case there are gen jets
            for (int j=0; j<genjet_n; j++) {
               bool okpt = genjet_pt->at(j) > kJetPtMin;
               bool oketa = (fabs(genjet_eta->at(j))>kJetAbsEtaMin) && (fabs(genjet_eta->at(j))<kJetAbsEtaMax);
               if (!okpt || !oketa) continue;
               float deta = itjet.eta() - genjet_eta->at(j);
               float dphi = TVector2::Phi_mpi_pi(itjet.phi() - genjet_phi->at(j));
               float dR = sqrt(pow(deta,2) + pow(dphi, 2));
               if (dR < minDR) {
                  minDR = dR;
                  jminDR = j;
               }
            }
            if (minDR > kRmatch) continue; // no match: fake jet

            genpt = genjet_pt->at(jminDR);
            geneta = genjet_eta->at(jminDR);
            genphi = genjet_phi->at(jminDR);
         } else {
            genpt = -1;
            geneta = -999.;
            genphi = -999.;
         }

         clutowjet_pt.emplace_back(itjet.pt());
         clutowjet_eta.emplace_back(itjet.eta());
         clutowjet_phi.emplace_back(itjet.phi());
         clutowjet_area.emplace_back(itjet.area());
         clutowjet_genpt.emplace_back(genpt);
         clutowjet_geneta.emplace_back(geneta);
         clutowjet_genphi.emplace_back(genphi);
         clutowjet_genDR.emplace_back(minDR);

         // cuts to remove regions with very small or 0 efficiency
         bool okpt = genpt > kJetPtMin2;

         h_clutow_pt->Fill(genpt);
         hdpt_clutow_pt->Fill(genpt,itjet.pt()-genpt);
         hdeta_clutow_pt->Fill(genpt,itjet.eta()-geneta);
         hdphi_clutow_pt->Fill(genpt,itjet.phi()-genphi);
         if (okpt) {
            h_clutow_eta->Fill(geneta);
            hdpt_clutow_eta->Fill(geneta,itjet.pt()-genpt);
            hdeta_clutow_eta->Fill(geneta,itjet.eta()-geneta);
            hdphi_clutow_eta->Fill(geneta,itjet.phi()-genphi);
         }
         if (itjet.eta()>0) {
            h_clutow_pt_p->Fill(genpt);
            hdpt_clutow_pt_p->Fill(genpt,itjet.pt()-genpt);
            hdeta_clutow_pt_p->Fill(genpt,itjet.eta()-geneta);
            hdphi_clutow_pt_p->Fill(genpt,itjet.phi()-genphi);
            if (okpt) {
               h_clutow_eta_p->Fill(fabs(geneta));
               hdpt_clutow_eta_p->Fill(fabs(geneta),itjet.pt()-genpt);
               hdeta_clutow_eta_p->Fill(fabs(geneta),itjet.eta()-geneta);
               hdphi_clutow_eta_p->Fill(fabs(geneta),itjet.phi()-genphi);
            }
         } else {
            h_clutow_pt_m->Fill(genpt);
            hdpt_clutow_pt_m->Fill(genpt,itjet.pt()-genpt);
            hdeta_clutow_pt_m->Fill(genpt,itjet.eta()-geneta);
            hdphi_clutow_pt_m->Fill(genpt,itjet.phi()-genphi);
            if (okpt) {
               h_clutow_eta_m->Fill(fabs(geneta));
               hdpt_clutow_eta_m->Fill(fabs(geneta),itjet.pt()-genpt);
               hdeta_clutow_eta_m->Fill(fabs(geneta),itjet.eta()-geneta);
               hdphi_clutow_eta_m->Fill(fabs(geneta),itjet.phi()-genphi);
            }
         }
      } // loop on cluster+tower jets

      clujet_n = clujet_pt.size();
      clutowjet_n = clutowjet_pt.size();
      towjet_n = towjet_pt.size();
      tr->Fill();
   } // event loop

   // efficiencies
   f->cd("jets");
   gDirectory->cd("clu");
   TEfficiency *eff_clu_pt = new TEfficiency(*h_clu_pt,*h_gen_pt); eff_clu_pt->Write("eff_clu_pt");
   TEfficiency *eff_clu_pt_p = new TEfficiency(*h_clu_pt_p,*h_gen_pt_p); eff_clu_pt_p->Write("eff_clu_pt_p");
   TEfficiency *eff_clu_pt_m = new TEfficiency(*h_clu_pt_m,*h_gen_pt_m); eff_clu_pt_m->Write("eff_clu_pt_m");
   TEfficiency *eff_clu_eta = new TEfficiency(*h_clu_eta,*h_gen_eta); eff_clu_eta->Write("eff_clu_eta");
   TEfficiency *eff_clu_eta_p = new TEfficiency(*h_clu_eta_p,*h_gen_eta_p); eff_clu_eta_p->Write("eff_clu_eta_p");
   TEfficiency *eff_clu_eta_m = new TEfficiency(*h_clu_eta_m,*h_gen_eta_m); eff_clu_eta_m->Write("eff_clu_eta_m");
   f->cd("jets");
   gDirectory->cd("clutow");
   TEfficiency *eff_clutow_pt = new TEfficiency(*h_clutow_pt,*h_gen_pt); eff_clutow_pt->Write("eff_clutow_pt");
   TEfficiency *eff_clutow_pt_p = new TEfficiency(*h_clutow_pt_p,*h_gen_pt_p); eff_clutow_pt_p->Write("eff_clutow_pt_p");
   TEfficiency *eff_clutow_pt_m = new TEfficiency(*h_clutow_pt_m,*h_gen_pt_m); eff_clutow_pt_m->Write("eff_clutow_pt_m");
   TEfficiency *eff_clutow_eta = new TEfficiency(*h_clutow_eta,*h_gen_eta); eff_clutow_eta->Write("eff_clutow_eta");
   TEfficiency *eff_clutow_eta_p = new TEfficiency(*h_clutow_eta_p,*h_gen_eta_p); eff_clutow_eta_p->Write("eff_clutow_eta_p");
   TEfficiency *eff_clutow_eta_m = new TEfficiency(*h_clutow_eta_m,*h_gen_eta_m); eff_clutow_eta_m->Write("eff_clutow_eta_m");
   f->cd("jets");
   gDirectory->cd("tow");
   TEfficiency *eff_tow_pt = new TEfficiency(*h_tow_pt,*h_gen_pt); eff_tow_pt->Write("eff_tow_pt");
   TEfficiency *eff_tow_pt_p = new TEfficiency(*h_tow_pt_p,*h_gen_pt_p); eff_tow_pt_p->Write("eff_tow_pt_p");
   TEfficiency *eff_tow_pt_m = new TEfficiency(*h_tow_pt_m,*h_gen_pt_m); eff_tow_pt_m->Write("eff_tow_pt_m");
   TEfficiency *eff_tow_eta = new TEfficiency(*h_tow_eta,*h_gen_eta); eff_tow_eta->Write("eff_tow_eta");
   TEfficiency *eff_tow_eta_p = new TEfficiency(*h_tow_eta_p,*h_gen_eta_p); eff_tow_eta_p->Write("eff_tow_eta_p");
   TEfficiency *eff_tow_eta_m = new TEfficiency(*h_tow_eta_m,*h_gen_eta_m); eff_tow_eta_m->Write("eff_tow_eta_m");

   f->Write();
   f->Close();
}

void HGCalTriggerNtupleReader::drawEventDisplay(TString name, vector<PseudoJet> inputs, vector<PseudoJet> jets) {
   gStyle->SetOptStat(0);
   TCanvas canv;

   TGraph *g = new TGraph(inputs.size());
   g->SetMarkerStyle(kFullCircle);
   g->SetMarkerColor(kBlack);
   for (int i=0; i<inputs.size(); i++) g->SetPoint(i,inputs[i].eta(),inputs[i].phi());
   g->Draw("AP");

   for (int i=0; i<jets.size(); i++) {
      vector<PseudoJet> v = jets[i].constituents();
      TGraph *gg = new TGraph(v.size());
      gg->SetMarkerColor(2+i);
      gg->SetMarkerStyle(kFullCircle);
      for (int j=0; j<v.size(); j++) gg->SetPoint(j,v[j].eta(),v[j].phi());
      gg->Draw("P");

      TGraph *gj = new TGraph(1);
      gj->SetMarkerStyle(kFullStar);
      gj->SetMarkerColor(kGray+1);
      gj->SetPoint(0,jets[i].eta(),jets[i].phi());
      gj->Draw("P");
   }

   // draw the gen jets everywhere that passes the selection
   TGraph *gj2 = new TGraph(genjet_n);
   gj2->SetMarkerStyle(kOpenStar);
   gj2->SetMarkerColor(kGray+1);
   for (int i=0; i<genjet_n; i++) {
      if (genjet_pt->at(i) > kJetPtMin2 && fabs(genjet_eta->at(i)) > kJetAbsEtaMin && fabs(genjet_eta->at(i)) < kJetAbsEtaMax) {
         gj2->SetPoint(i,genjet_eta->at(i),TVector2::Phi_0_2pi(genjet_phi->at(i)));
         TText *t = new TText(genjet_eta->at(i)+0.1, TVector2::Phi_0_2pi(genjet_phi->at(i))+0.1, Form("%.0f",genjet_pt->at(i)));
         t->SetTextColor(kGray+1);
         t->Draw();
      } else {
         gj2->SetPoint(i,-999,-999);
      }
   }
   gj2->Draw("P");


   canv.SaveAs("evtdisp_" + name + ".pdf");
}

void HGCalTriggerNtupleReader::drawEventDisplay2(TString name, vector<PseudoJet> inputs, vector<PseudoJet> jets) {
   gStyle->SetOptStat(0);
   TCanvas canv;

   TH2F *hgen = new TH2F("hgen_"+name,";#eta;#phi;p_{T} or E_{T} [GeV]",60,-3,3,62,0,TMath::TwoPi());
   TH2F *hjets = new TH2F("hjets_"+name,";#eta;#phi;p_{T} or E_{T} [GeV]",60,-3,3,62,0,TMath::TwoPi());
   TH2F *hinputs = new TH2F("hinputs_"+name,";#eta;#phi;p_{T} or E_{T} [GeV]",60,-3,3,62,0,TMath::TwoPi());
   vector<TH2F*> hjetinputs;
   vector<double> v_geneta, v_genphi;

   // gen jets
   for (int i=0; i<genjet_n; i++) {
      if (genjet_pt->at(i) > kJetPtMin2 && fabs(genjet_eta->at(i)) > kJetAbsEtaMin && fabs(genjet_eta->at(i)) < kJetAbsEtaMax) {
         hgen->Fill(genjet_eta->at(i), TVector2::Phi_0_2pi(genjet_phi->at(i)), fabs(genjet_pt->at(i)));
         v_geneta.push_back(genjet_eta->at(i));
         v_genphi.push_back(TVector2::Phi_0_2pi(genjet_phi->at(i)));
         // cout << genjet_eta->at(i) << ", " << TVector2::Phi_0_2pi(genjet_phi->at(i)) << ": " << fabs(genjet_pt->at(i)) << endl;
      }
   }
   TGraph *ggen = new TGraph(v_geneta.size());
   for (int i=0; i<v_geneta.size(); i++) ggen->SetPoint(i,v_geneta[i],v_genphi[i]);

   for (int i=0; i<inputs.size(); i++) hinputs->Fill(inputs[i].eta(), TVector2::Phi_0_2pi(inputs[i].phi()), fabs(inputs[i].pt()));
   hinputs->SetFillColor(kWhite);
   // hinputs->SetMaximum(hgen->GetMaximum());
   hinputs->Draw("BOX same0");//("LEGO1 0 same0");

   for (int i=0; i<jets.size(); i++) {
      if (!(jets[i].pt() > kJetPtMin && fabs(jets[i].eta()) > kJetAbsEtaMin && fabs(jets[i].eta()) < kJetAbsEtaMax)) continue;
      hjets->Fill(jets[i].eta(), TVector2::Phi_0_2pi(jets[i].phi()), fabs(jets[i].pt()));
      hjetinputs.emplace_back(new TH2F(Form("hjetinputs%d_",i)+name,";#eta;#phi;p_{T} or E_{T} [GeV]",60,-3,3,62,0,TMath::TwoPi()));
      vector<PseudoJet> v = jets[i].constituents();
      hjetinputs.back()->SetFillColor(2+i);
      for (int j=0; j<v.size(); j++) hjetinputs.back()->Fill(v[j].eta(), TVector2::Phi_0_2pi(v[j].phi()), fabs(v[j].pt()));
      // hjetinputs.back()->SetMaximum(hgen->GetMaximum());
      hjetinputs.back()->Draw("BOX same0");//("LEGO1 0 same0");
   }
   // hjets->SetFillColor(kRed+1);
   // hjets->Draw("BOX same");//("LEGO1 0");
   hjets->SetMarkerColor(kRed+1);
   hjets->SetBarOffset(-1);
   hjets->Draw("TEXT same");

   // hgen->SetFillColor(kGray);
   // hgen->Draw("BOX");//("LEGO1 0");
   ggen->SetMarkerColor(kBlack);
   ggen->SetMarkerSize(2);
   ggen->SetMarkerStyle(kFullStar);
   ggen->SetLineColor(kBlack);
   ggen->Draw("P");
   hgen->SetMarkerColor(kBlack);
   hgen->SetBarOffset(2);
   hgen->Draw("TEXT same");
   // hgen->SetMaximum(hgen->GetMaximum());
   // hgen->Draw("LEGO1 0");
   hjets->Draw("TEXT same");

   canv.SaveAs("evtdisp_" + name + ".pdf");
}
