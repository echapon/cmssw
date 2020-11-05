#include "MyCanvas.C"

#include "TFile.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TH2.h"
#include "TTree.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLatex.h"

TString basepath = "/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/trees/rphi_thr6p5/";
// TString basepath = "/home/emilien/Documents/Postdoc_IHEP/HGCAL/TPG_clustering_study";
TString outputpath = "plots/rphi_thr6p5/";

TH1D* myFitSlicesY(TH2F *h2d, bool domean, int slicenb = -1, TString canvname = "");

void checkNumDen(TH1 *hnum, TH1 *hden);

void drawComparison(TString file_uncltow, TString file_fulltow, TString output_tag = "test") {
  TFile *funcl = TFile::Open(file_uncltow);
  if (!funcl || !funcl->IsOpen()) {
     cout << "drawComparison: " << file_uncltow << " does not exist, skipping." << endl;
     return;
  }
  TFile *ffull = TFile::Open(file_fulltow);
  if (!ffull || !ffull->IsOpen()) {
     cout << "drawComparison: " << file_fulltow << " does not exist, skipping." << endl;
     return;
  }

  // EFFICIENCIES

  TEfficiency *effclu_pt = (TEfficiency *)funcl->Get("jets/clu/eff_clu_pt");
  TEfficiency *effclu_pt_p = (TEfficiency *)funcl->Get("jets/clu/eff_clu_pt_p");
  TEfficiency *effclu_pt_m = (TEfficiency *)funcl->Get("jets/clu/eff_clu_pt_m");
  TEfficiency *effclu_eta = (TEfficiency *)funcl->Get("jets/clu/eff_clu_eta");
  TEfficiency *effunclclutow_pt = (TEfficiency *)funcl->Get("jets/clutow/eff_clutow_pt");
  TEfficiency *effunclclutow_pt_p = (TEfficiency *)funcl->Get("jets/clutow/eff_clutow_pt_p");
  TEfficiency *effunclclutow_pt_m = (TEfficiency *)funcl->Get("jets/clutow/eff_clutow_pt_m");
  TEfficiency *effunclclutow_eta = (TEfficiency *)funcl->Get("jets/clutow/eff_clutow_eta");
  TEfficiency *efffulltow_pt = (TEfficiency *)ffull->Get("jets/tow/eff_tow_pt");
  TEfficiency *efffulltow_pt_p = (TEfficiency *)ffull->Get("jets/tow/eff_tow_pt_p");
  TEfficiency *efffulltow_pt_m = (TEfficiency *)ffull->Get("jets/tow/eff_tow_pt_m");
  TEfficiency *efffulltow_eta = (TEfficiency *)ffull->Get("jets/tow/eff_tow_eta");

  TGraphAsymmErrors *gclu_pt = effclu_pt->CreateGraph();
  TGraphAsymmErrors *gclu_pt_p = effclu_pt_p->CreateGraph();
  TGraphAsymmErrors *gclu_pt_m = effclu_pt_m->CreateGraph();
  TGraphAsymmErrors *gclu_eta = effclu_eta->CreateGraph();
  TGraphAsymmErrors *gunclclutow_pt = effunclclutow_pt->CreateGraph();
  TGraphAsymmErrors *gunclclutow_pt_p = effunclclutow_pt_p->CreateGraph();
  TGraphAsymmErrors *gunclclutow_pt_m = effunclclutow_pt_m->CreateGraph();
  TGraphAsymmErrors *gunclclutow_eta = effunclclutow_eta->CreateGraph();
  TGraphAsymmErrors *gfulltow_pt = efffulltow_pt->CreateGraph();
  TGraphAsymmErrors *gfulltow_pt_p = efffulltow_pt_p->CreateGraph();
  TGraphAsymmErrors *gfulltow_pt_m = efffulltow_pt_m->CreateGraph();
  TGraphAsymmErrors *gfulltow_eta = efffulltow_eta->CreateGraph();

  MyCanvas c_pt("canv_eff_pt_" + output_tag, "gen jet p_{T} [GeV]", "Efficiency");
  MyCanvas c_pt_p("canv_eff_pt_p_" + output_tag, "gen jet p_{T} [GeV] (#eta>0)", "Efficiency");
  MyCanvas c_pt_m("canv_eff_pt_m_" + output_tag, "gen jet p_{T} [GeV] (#eta<0)", "Efficiency");
  MyCanvas c_eta("canv_eff_eta_" + output_tag, "gen jet #eta", "Efficiency");

  c_pt.SetLegendPosition(0.34, .45, .88, .68);
  c_pt_p.SetLegendPosition(0.34, .45, .88, .68);
  c_pt_m.SetLegendPosition(0.34, .45, .88, .68);
  c_eta.SetLegendPosition(0.34, .45, .88, .68);

  c_pt.CanvasWithThreeGraphsRatioPlot(gclu_pt,
                                      gfulltow_pt,
                                      gunclclutow_pt,
                                      "clu",
                                      "tow (full)",
                                      "clu and tow (unclustered)",
                                      "X / (clu and uncl. tow.)",
                                      kBlue,
                                      kGreen + 1,
                                      kRed,
                                      "EP",
                                      "EP",
                                      "EP");
  c_pt_p.CanvasWithThreeGraphsRatioPlot(gclu_pt_p,
                                        gfulltow_pt_p,
                                        gunclclutow_pt_p,
                                        "clu",
                                        "tow (full)",
                                        "clu and tow (unclustered)",
                                        "X / (clu and uncl. tow.)",
                                        kBlue,
                                        kGreen + 1,
                                        kRed,
                                        "EP",
                                        "EP",
                                        "EP");
  c_pt_m.CanvasWithThreeGraphsRatioPlot(gclu_pt_m,
                                        gfulltow_pt_m,
                                        gunclclutow_pt_m,
                                        "clu",
                                        "tow (full)",
                                        "clu and tow (unclustered)",
                                        "X / (clu and uncl. tow.)",
                                        kBlue,
                                        kGreen + 1,
                                        kRed,
                                        "EP",
                                        "EP",
                                        "EP");
  c_eta.CanvasWithThreeGraphsRatioPlot(gclu_eta,
                                       gfulltow_eta,
                                       gunclclutow_eta,
                                       "clu",
                                       "tow (full)",
                                       "clu and tow (unclustered)",
                                       "X / (clu and uncl. tow.)",
                                       kBlue,
                                       kGreen + 1,
                                       kRed,
                                       "EP",
                                       "EP",
                                       "EP");

  c_pt.PrintCanvas();
  c_pt_p.PrintCanvas();
  c_pt_m.PrintCanvas();
  c_eta.PrintCanvas();

  // RESOLUTIONS

  TProfile *profdpt_clu_pt = ((TH2F *)funcl->Get("resolution/clu/hdpt_clu_pt"))->ProfileX();
  TProfile *profdpt_clu_eta = ((TH2F *)funcl->Get("resolution/clu/hdpt_clu_eta"))->ProfileX();
  TProfile *profdeta_clu_pt = ((TH2F *)funcl->Get("resolution/clu/hdeta_clu_pt"))->ProfileX();
  TProfile *profdeta_clu_eta = ((TH2F *)funcl->Get("resolution/clu/hdeta_clu_eta"))->ProfileX();
  TProfile *profdphi_clu_pt = ((TH2F *)funcl->Get("resolution/clu/hdphi_clu_pt"))->ProfileX();
  TProfile *profdphi_clu_eta = ((TH2F *)funcl->Get("resolution/clu/hdphi_clu_eta"))->ProfileX();
  TProfile *profdpt_unclclutow_pt = ((TH2F *)funcl->Get("resolution/clutow/hdpt_clutow_pt"))->ProfileX();
  TProfile *profdpt_unclclutow_eta = ((TH2F *)funcl->Get("resolution/clutow/hdpt_clutow_eta"))->ProfileX();
  TProfile *profdeta_unclclutow_pt = ((TH2F *)funcl->Get("resolution/clutow/hdeta_clutow_pt"))->ProfileX();
  TProfile *profdeta_unclclutow_eta = ((TH2F *)funcl->Get("resolution/clutow/hdeta_clutow_eta"))->ProfileX();
  TProfile *profdphi_unclclutow_pt = ((TH2F *)funcl->Get("resolution/clutow/hdphi_clutow_pt"))->ProfileX();
  TProfile *profdphi_unclclutow_eta = ((TH2F *)funcl->Get("resolution/clutow/hdphi_clutow_eta"))->ProfileX();
  TProfile *profdpt_fulltow_pt = ((TH2F *)ffull->Get("resolution/tow/hdpt_tow_pt"))->ProfileX();
  TProfile *profdpt_fulltow_eta = ((TH2F *)ffull->Get("resolution/tow/hdpt_tow_eta"))->ProfileX();
  TProfile *profdeta_fulltow_pt = ((TH2F *)ffull->Get("resolution/tow/hdeta_tow_pt"))->ProfileX();
  TProfile *profdeta_fulltow_eta = ((TH2F *)ffull->Get("resolution/tow/hdeta_tow_eta"))->ProfileX();
  TProfile *profdphi_fulltow_pt = ((TH2F *)ffull->Get("resolution/tow/hdphi_tow_pt"))->ProfileX();
  TProfile *profdphi_fulltow_eta = ((TH2F *)ffull->Get("resolution/tow/hdphi_tow_eta"))->ProfileX();

  MyCanvas c_dpt_pt("canv_resol_dpt_pt_" + output_tag, "gen jet p_{T} [GeV]", "<reco p_{T} - gen p_{T}> [GeV]");
  MyCanvas c_dpt_eta("canv_resol_dpt_eta_" + output_tag, "gen jet #eta", "<reco p_{T} - gen p_{T}> [GeV]");
  MyCanvas c_deta_pt("canv_resol_deta_pt_" + output_tag, "gen jet p_{T} [GeV]", "<reco #eta - gen #eta>");
  MyCanvas c_deta_eta("canv_resol_deta_eta_" + output_tag, "gen jet #eta", "<reco #eta - gen #eta>");
  MyCanvas c_dphi_pt("canv_resol_dphi_pt_" + output_tag, "gen jet p_{T} [GeV]", "<reco #phi - gen #phi>");
  MyCanvas c_dphi_eta("canv_resol_dphi_eta_" + output_tag, "gen jet #eta", "<reco #phi - gen #phi>");

  c_dpt_pt.SetLegendPosition(0.34, .45, .88, .68);
  c_dpt_eta.SetLegendPosition(0.34, .45, .88, .68);
  c_deta_pt.SetLegendPosition(0.34, .45, .88, .68);
  c_deta_eta.SetLegendPosition(0.34, .45, .88, .68);
  c_dphi_pt.SetLegendPosition(0.34, .45, .88, .68);
  c_dphi_eta.SetLegendPosition(0.34, .45, .88, .68);

  c_dpt_pt.CanvasWithThreeHistogramsRatioPlot(profdpt_clu_pt,
                                              profdpt_fulltow_pt,
                                              profdpt_unclclutow_pt,
                                              "clu",
                                              "tow (full)",
                                              "clu and tow (unclustered)",
                                              "X / (clu and uncl. tow.)",
                                              kBlue,
                                              kGreen + 1,
                                              kRed,
                                              "EP",
                                              "EP",
                                              "EP");
  c_dpt_eta.CanvasWithThreeHistogramsRatioPlot(profdpt_clu_eta,
                                               profdpt_fulltow_eta,
                                               profdpt_unclclutow_eta,
                                               "clu",
                                               "tow (full)",
                                               "clu and tow (unclustered)",
                                               "X / (clu and uncl. tow.)",
                                               kBlue,
                                               kGreen + 1,
                                               kRed,
                                               "EP",
                                               "EP",
                                               "EP");
  c_deta_pt.CanvasWithThreeHistogramsRatioPlot(profdeta_clu_pt,
                                               profdeta_fulltow_pt,
                                               profdeta_unclclutow_pt,
                                               "clu",
                                               "tow (full)",
                                               "clu and tow (unclustered)",
                                               "X / (clu and uncl. tow.)",
                                               kBlue,
                                               kGreen + 1,
                                               kRed,
                                               "EP",
                                               "EP",
                                               "EP");
  c_deta_eta.CanvasWithThreeHistogramsRatioPlot(profdeta_clu_eta,
                                                profdeta_fulltow_eta,
                                                profdeta_unclclutow_eta,
                                                "clu",
                                                "tow (full)",
                                                "clu and tow (unclustered)",
                                                "X / (clu and uncl. tow.)",
                                                kBlue,
                                                kGreen + 1,
                                                kRed,
                                                "EP",
                                                "EP",
                                                "EP");
  c_dphi_pt.CanvasWithThreeHistogramsRatioPlot(profdphi_clu_pt,
                                               profdphi_fulltow_pt,
                                               profdphi_unclclutow_pt,
                                               "clu",
                                               "tow (full)",
                                               "clu and tow (unclustered)",
                                               "X / (clu and uncl. tow.)",
                                               kBlue,
                                               kGreen + 1,
                                               kRed,
                                               "EP",
                                               "EP",
                                               "EP");
  c_dphi_eta.CanvasWithThreeHistogramsRatioPlot(profdphi_clu_eta,
                                                profdphi_fulltow_eta,
                                                profdphi_unclclutow_eta,
                                                "clu",
                                                "tow (full)",
                                                "clu and tow (unclustered)",
                                                "X / (clu and uncl. tow.)",
                                                kBlue,
                                                kGreen + 1,
                                                kRed,
                                                "EP",
                                                "EP",
                                                "EP");

  c_dpt_pt.PrintCanvas();
  c_dpt_eta.PrintCanvas();
  c_deta_pt.PrintCanvas();
  c_deta_eta.PrintCanvas();
  c_dphi_pt.PrintCanvas();
  c_dphi_eta.PrintCanvas();

  funcl->Close();
  ffull->Close();
}

// functions for custom plots
void drawEfficiency(TString sample = "VBF_HToInvisible",
                    TString PUtype = "noPU",
                    TString xvariable0 = "abseta",
                    TString gencuts0 = "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                    TString recocuts0 = "",
                    double DRmatch = 0.2) {
  TString tagPU1 = (PUtype == "noPU") ? "NoPU" : "PU200";
  TString tagPU2 = (PUtype == "PUsub") ? "PUsub" : "noPUsub";
  TString suffix = (tagPU1 == "PU200" && tagPU2 == "noPUsub") ? "_offcor" : "_cor";
  TString file_uncltow = basepath + "/unclunseltowers//" + tagPU2 + "/output_" + sample + "_" + tagPU1 + suffix + ".root";
  TString file_fulltow = basepath + "/fulltowers/" + tagPU2 + "/output_" + sample + "_" + tagPU1 + suffix + ".root";
  TFile *funcl = TFile::Open(file_uncltow);
  if (!funcl || !funcl->IsOpen()) {
     cout << "drawEfficiency: " << file_uncltow << " does not exist, skipping." << endl;
     return;
  }
  TTree *truncl = (TTree *)funcl->Get("tree");
  TFile *ffull = TFile::Open(file_fulltow);
  if (!ffull || !ffull->IsOpen()) {
     cout << "drawEfficiency: " << file_fulltow << " does not exist, skipping." << endl;
     return;
  }
  TTree *trfull = (TTree *)ffull->Get("tree");

  if (recocuts0 == "")
    recocuts0 = "1";
  if (gencuts0 == "")
    gencuts0 = "1";

  TString xaxistitle;
  int nbins = 1;
  float xmin = 1, xmax = 2;
  if (xvariable0 == "pt") {
    xaxistitle = "gen jet p_{T} [GeV]";
    nbins = 20;
    xmin = 0;
    xmax = 200;
  } else if (xvariable0 == "eta") {
    xaxistitle = "gen jet #eta";
    nbins = 34;
    xmin = -3.4;
    xmax = 3.4;
  } else if (xvariable0 == "abseta") {
    nbins = 18;
    xmin = 1.4;
    xmax = 3.2;
    xaxistitle = "gen jet |#eta|";
  } else if (xvariable0 == "phi") {
    nbins = 20;
    xmin = -TMath::Pi();
    xmax = TMath::Pi();
    xaxistitle = "gen jet #phi";
  } else if (xvariable0 == "PU") {
    nbins = 6;
    xmin = 170;
    xmax = 230;
    xaxistitle = "true #mu";
  } else {
    cout << "ERROR: " << xvariable0 << "is not a valid x variable." << endl;
  }

  TH1F *h_gen = new TH1F("h_gen", ";" + xaxistitle + ";Entries", nbins, xmin, xmax);
  TH1F *h_clu = new TH1F("h_clu", ";" + xaxistitle + ";Entries", nbins, xmin, xmax);
  TH1F *h_fulltow = new TH1F("h_fulltow", ";" + xaxistitle + ";Entries", nbins, xmin, xmax);
  TH1F *h_unclclutow = new TH1F("h_unclclutow", ";" + xaxistitle + ";Entries", nbins, xmin, xmax);

  // fill the histograms
  TString xvariable = xvariable0;
  TString gencuts = gencuts0;
  TString recocuts = recocuts0;
  gencuts.ReplaceAll("pt", "genjet_pt");
  gencuts.ReplaceAll("eta", "genjet_eta");
  gencuts.ReplaceAll("phi", "genjet_phi");
  recocuts.ReplaceAll("pt", "clujet_pt");
  // recocuts.ReplaceAll("ptoff", "clujet_ptoff");
  recocuts.ReplaceAll("eta", "clujet_eta");
  recocuts.ReplaceAll("phi", "clujet_phi");
  xvariable = "genjet_" + xvariable;
  if (xvariable.Contains("PU")) xvariable = "gen_PUNumInt";
  if (xvariable == "genjet_abseta")
    xvariable = "abs(genjet_eta)";

  cout << gencuts.Data() << endl;
  truncl->Draw(xvariable + ">>h_gen", gencuts, "goff");

  xvariable.ReplaceAll("genjet_", "clujet_gen");
  gencuts.ReplaceAll("genjet_", "clujet_gen");
  cout << gencuts.Data() << endl;
  truncl->Draw(
      xvariable + ">>h_clu", "(" + gencuts + ")&&(" + recocuts + Form(")&&(clujet_genDR<%f)", DRmatch), "goff");

  xvariable.ReplaceAll("clujet", "towjet");
  recocuts.ReplaceAll("clujet", "towjet");
  gencuts.ReplaceAll("clujet_gen", "towjet_gen");
  cout << gencuts.Data() << endl;
  trfull->Draw(
      xvariable + ">>h_fulltow", "(" + gencuts + ")&&(" + recocuts + Form(")&&(towjet_genDR<%f)", DRmatch), "goff");

  xvariable.ReplaceAll("towjet", "clutowjet");
  recocuts.ReplaceAll("towjet", "clutowjet");
  gencuts.ReplaceAll("towjet_gen", "clutowjet_gen");
  cout << gencuts.Data() << endl;
  truncl->Draw(xvariable + ">>h_unclclutow",
               "(" + gencuts + ")&&(" + recocuts + Form(")&&(clutowjet_genDR<%f)", DRmatch),
               "goff");

  // compute efficiencies
  // for (int i=1; i<= h_gen->GetNbinsX(); i++) cout << h_gen->GetBinContent(i) << " " <<  h_clu->GetBinContent(i) << endl;
  checkNumDen(h_clu, h_gen);
  TGraphAsymmErrors *gclu = new TGraphAsymmErrors(h_clu, h_gen);
  // for (int i=1; i<= h_gen->GetNbinsX(); i++) cout << h_gen->GetBinContent(i) << " " <<  h_fulltow->GetBinContent(i) << endl;
  checkNumDen(h_fulltow, h_gen);
  TGraphAsymmErrors *gfulltow = new TGraphAsymmErrors(h_fulltow, h_gen);
  // for (int i=1; i<= h_gen->GetNbinsX(); i++) cout << h_gen->GetBinContent(i) << " " <<  h_unclclutow->GetBinContent(i) << endl;
  checkNumDen(h_unclclutow, h_gen);
  TGraphAsymmErrors *gunclclutow = new TGraphAsymmErrors(h_unclclutow, h_gen);

  TString canvtitle;
  if (gencuts0 == "1")
    gencuts0 = "none";
  if (recocuts0 == "1")
    recocuts0 = "none";
  canvtitle = outputpath + "eff/canv_" + sample + "_" + PUtype + "_" + xvariable0;
  canvtitle +=
      "_gencuts_" + gencuts0.ReplaceAll(" ", "").ReplaceAll("&&", "AND").ReplaceAll("||", "OR").ReplaceAll("!", "NOT");
  canvtitle += "_recocuts_" +
               recocuts0.ReplaceAll(" ", "").ReplaceAll("&&", "AND").ReplaceAll("||", "OR").ReplaceAll("!", "NOT");
  canvtitle.ReplaceAll(".", "p");
  canvtitle.ReplaceAll(">", "GT");
  canvtitle.ReplaceAll("<", "LT");
  canvtitle.ReplaceAll("(", "");
  canvtitle.ReplaceAll(")", "");
  MyCanvas myc(canvtitle, xaxistitle, "Efficiency");
  myc.SetLegendPosition(0.34, .45, .88, .68);
  myc.SetYRange(0.5, 1.04);
  myc.CanvasWithThreeGraphsRatioPlot(gclu,
                                     gfulltow,
                                     gunclclutow,
                                     "clu",
                                     "tow (full)",
                                     "clu and tow (unclustered)",
                                     "X / (clu and uncl. tow.)",
                                     kBlue,
                                     kGreen + 1,
                                     kRed,
                                     "P",
                                     "P",
                                     "P");

  // add text to the plot
  myc.c->cd();
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.02);
  double xlatex = .18, ylatex = 0.97, dylatex = 0.025;
  latex.DrawLatex(xlatex, ylatex, sample + " " + PUtype);
  ylatex -= dylatex;
  latex.DrawLatex(xlatex, ylatex, "gen cuts: " + gencuts0);
  ylatex -= dylatex;
  latex.DrawLatex(xlatex, ylatex, "reco cuts: " + recocuts0 + Form("; DR(gen,reco)<%.2f", DRmatch));
  ylatex -= dylatex;

  myc.PrintCanvas();
}

void drawScaleResolution(TString sample,
                          TString PUtype,
                          TString xvariable0,
                          TString yvariable0,
                          TString gencuts0,
                          TString recocuts0,
                          double DRmatch,
                          bool domean,
                          bool dofits,
                          int slicenb) {
  TString tagPU1 = (PUtype == "noPU") ? "NoPU" : "PU200";
  TString tagPU2 = (PUtype == "PUsub") ? "PUsub" : "noPUsub";
  TString suffix = (tagPU1 == "PU200" && tagPU2 == "noPUsub") ? "_offcor" : "_cor";
  TString file_uncltow = basepath + "/unclunseltowers//" + tagPU2 + "/output_" + sample + "_" + tagPU1 + suffix + ".root";
  TString file_fulltow = basepath + "/fulltowers/" + tagPU2 + "/output_" + sample + "_" + tagPU1 + suffix + ".root";
  TFile *funcl = TFile::Open(file_uncltow);
  if (!funcl || !funcl->IsOpen()) {
     cout << "drawScaleResolution: " << file_uncltow << " does not exist, skipping." << endl;
     return;
  }
  TTree *truncl = (TTree *)funcl->Get("tree");
  TFile *ffull = TFile::Open(file_fulltow);
  if (!ffull || !ffull->IsOpen()) {
     cout << "drawScaleResolution: " << file_fulltow << " does not exist, skipping." << endl;
     return;
  }
  TTree *trfull = (TTree *)ffull->Get("tree");

  if (recocuts0 == "")
    recocuts0 = "1";
  if (gencuts0 == "")
    gencuts0 = "1";

  TString xaxistitle;
  int nbinsx = 1;
  float xmin = 1, xmax = 2;
  if (xvariable0 == "pt") {
    xaxistitle = "gen jet p_{T} [GeV]";
    nbinsx = 20;
    xmin = 0;
    xmax = 200;
  } else if (xvariable0 == "eta") {
    xaxistitle = "gen jet #eta";
    nbinsx = 34;
    xmin = -3.4;
    xmax = 3.4;
  } else if (xvariable0 == "abseta") {
    nbinsx = 18;
    xmin = 1.4;
    xmax = 3.2;
    xaxistitle = "gen jet |#eta|";
  } else if (xvariable0 == "phi") {
    nbinsx = 20;
    xmin = -TMath::Pi();
    xmax = -TMath::Pi();
    xaxistitle = "gen jet #phi";
  } else {
    cout << "ERROR: " << xvariable0 << " is not a valid x variable." << endl;
  }

  TString yaxistitle, yvariable;
  int nbinsy = 1;
  float ymin = 1, ymax = 2;
  if (yvariable0 == "pt") {
    yaxistitle = "rec/gen";
    nbinsy = 200;
    ymin = 0;
    ymax = 5;
    yvariable = "clujet_pt / clujet_genpt";
  } else if (yvariable0 == "ptoff") {
    yaxistitle = "(cor rec)/gen";
    nbinsy = 200;
    ymin = 0;
    ymax = 5;
    yvariable = "clujet_ptoff / clujet_genpt";
  } else if (yvariable0 == "ptcor") {
    yaxistitle = "(cor rec)/gen";
    nbinsy = 200;
    ymin = 0;
    ymax = 5;
    yvariable = "clujet_ptcor / clujet_genpt";
  } else if (yvariable0 == "eta") {
    yaxistitle = "#Delta#eta";
    nbinsy = 80;
    ymin = -0.4;
    ymax = 0.4;
    yvariable = "clujet_eta-clujet_geneta";
  } else if (yvariable0 == "DR") {
    nbinsy = 80;
    ymin = 0;
    ymax = 0.4;
    yaxistitle = "DR";
    yvariable = "clujet_genDR";
  } else if (yvariable0 == "phi") {
    nbinsy = 80;
    ymin = -0.4;
    ymax = -0.4;
    yaxistitle = "#Delta#phi";
    yvariable = "TVector2::Phi_mpi_pi(clujet_phi-clujet_genphi)";
  } else {
    cout << "ERROR: " << yvariable0 << "is not a valid y variable." << endl;
  }

  TH2F *h_clu = new TH2F("h_clu", ";" + xaxistitle + ";" + yaxistitle, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
  TH2F *h_fulltow = new TH2F("h_fulltow", ";" + xaxistitle + ";" + yaxistitle, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
  TH2F *h_unclclutow =
      new TH2F("h_unclclutow", ";" + xaxistitle + ";" + yaxistitle, nbinsx, xmin, xmax, nbinsy, ymin, ymax);

  // fill the histograms
  TString xvariable = xvariable0;
  TString gencuts = gencuts0;
  TString recocuts = recocuts0;
  gencuts.ReplaceAll("pt", "genjet_pt");
  gencuts.ReplaceAll("eta", "genjet_eta");
  gencuts.ReplaceAll("phi", "genjet_phi");
  recocuts.ReplaceAll("pt", "clujet_pt");
  // recocuts.ReplaceAll("ptoff", "clujet_ptoff");
  recocuts.ReplaceAll("eta", "clujet_eta");
  recocuts.ReplaceAll("phi", "clujet_phi");
  xvariable = "genjet_" + xvariable;
  if (xvariable == "genjet_abseta")
    xvariable = "abs(genjet_eta)";

  xvariable.ReplaceAll("genjet_", "clujet_gen");
  gencuts.ReplaceAll("genjet_", "clujet_gen");
  cout << gencuts.Data() << endl;
  truncl->Draw(yvariable + ":" + xvariable + ">>h_clu",
               "(" + gencuts + ")&&(" + recocuts + Form(")&&(clujet_genDR<%f)", DRmatch),
               "goff");

  xvariable.ReplaceAll("clujet", "towjet");
  yvariable.ReplaceAll("clujet", "towjet");
  recocuts.ReplaceAll("clujet", "towjet");
  gencuts.ReplaceAll("clujet_gen", "towjet_gen");
  cout << gencuts.Data() << endl;
  trfull->Draw(yvariable + ":" + xvariable + ">>h_fulltow",
               "(" + gencuts + ")&&(" + recocuts + Form(")&&(towjet_genDR<%f)", DRmatch),
               "goff");

  xvariable.ReplaceAll("towjet", "clutowjet");
  yvariable.ReplaceAll("towjet", "clutowjet");
  recocuts.ReplaceAll("towjet", "clutowjet");
  gencuts.ReplaceAll("towjet_gen", "clutowjet_gen");
  cout << gencuts.Data() << endl;
  truncl->Draw(yvariable + ":" + xvariable + ">>h_unclclutow",
               "(" + gencuts + ")&&(" + recocuts + Form(")&&(clutowjet_genDR<%f)", DRmatch),
               "goff");

  TString canvtitle;
  if (gencuts0 == "1")
    gencuts0 = "none";
  if (recocuts0 == "1")
    recocuts0 = "none";
  canvtitle = outputpath + (domean ? "scale/" : "resol/") +
      "canv" + (domean ? "scale" : "res") + "_" + sample + "_" + PUtype + "_" + xvariable0 + "_" + yvariable0;
  canvtitle +=
      "_gencuts_" + gencuts0.ReplaceAll(" ", "").ReplaceAll("&&", "AND").ReplaceAll("||", "OR").ReplaceAll("!", "NOT");
  canvtitle += "_recocuts_" +
               recocuts0.ReplaceAll(" ", "").ReplaceAll("&&", "AND").ReplaceAll("||", "OR").ReplaceAll("!", "NOT");
  if (dofits)
    canvtitle += "_fit";
  canvtitle.ReplaceAll(".", "p");
  canvtitle.ReplaceAll(">", "GT");
  canvtitle.ReplaceAll("<", "LT");
  canvtitle.ReplaceAll("(", "");
  canvtitle.ReplaceAll(")", "");
  TString ylabel = "(reco-gen";
  if (yvariable.Contains("pt"))
    ylabel = "rec/gen";

  // print the 2D histos
  TCanvas c2d_clu;
  h_clu->Draw("COLZ");
  c2d_clu.SaveAs(canvtitle + "_2d_clu.pdf");
  TCanvas c2d_fulltow;
  h_fulltow->Draw("COLZ");
  c2d_fulltow.SaveAs(canvtitle + "_2d_fulltow.pdf");
  TCanvas c2d_unclclutow;
  h_unclclutow->Draw("COLZ");
  c2d_unclclutow.SaveAs(canvtitle + "_2d_unclclutow.pdf");

  // now compute the scale or resolution
  TH1D *h_clu_res, *h_fulltow_res, *h_unclclutow_res;

  // case 1: with fits
  if (dofits) {
     h_clu_res = myFitSlicesY(h_clu, domean, slicenb, canvtitle + Form("_clu_slicenb%d", slicenb));
     h_fulltow_res = myFitSlicesY(h_fulltow, domean, slicenb, canvtitle + Form("_fulltow_slicenb%d", slicenb));
     h_unclclutow_res = myFitSlicesY(h_unclclutow, domean, slicenb, canvtitle + Form("_unclclutow_slicenb%d", slicenb));
  } else {
     // case 2: no fits
     TProfile *tp_clu_res, *tp_fulltow_res, *tp_unclclutow_res;
     TString title = TString(";") + h_clu->GetXaxis()->GetTitle() + ";" + h_clu->GetYaxis()->GetTitle();
     int nbins = h_clu->GetXaxis()->GetNbins();
     double xmin = h_clu->GetXaxis()->GetXmin();
     double xmax = h_clu->GetXaxis()->GetXmax();

     if (domean) {
        tp_clu_res = (TProfile *)h_clu->ProfileX("_pfx", 1, -1);
        h_clu_res = new TH1D(TString(h_clu->GetName()) + "_hprof", title, nbins, xmin, xmax);
        tp_fulltow_res = (TProfile *)h_fulltow->ProfileX("_pfx", 1, -1);
        h_fulltow_res = new TH1D(TString(h_fulltow->GetName()) + "_hprof", title, nbins, xmin, xmax);
        tp_unclclutow_res = (TProfile *)h_unclclutow->ProfileX("_pfx", 1, -1);
        h_unclclutow_res = new TH1D(TString(h_unclclutow->GetName()) + "_hprof", title, nbins, xmin, xmax);
        for (int i = 1; i <= nbinsx; i++) {
           h_clu_res->SetBinContent(i, tp_clu_res->GetBinContent(i));
           h_clu_res->SetBinError(i, tp_clu_res->GetBinError(i));
           h_fulltow_res->SetBinContent(i, tp_fulltow_res->GetBinContent(i));
           h_fulltow_res->SetBinError(i, tp_fulltow_res->GetBinError(i));
           h_unclclutow_res->SetBinContent(i, tp_unclclutow_res->GetBinContent(i));
           h_unclclutow_res->SetBinError(i, tp_unclclutow_res->GetBinError(i));
        }
     } else {
        tp_clu_res = (TProfile *)h_clu->ProfileX("_pfx", 1, -1, "s");
        h_clu_res = new TH1D(TString(h_clu->GetName()) + "_hprof", title, nbins, xmin, xmax);
        tp_fulltow_res = (TProfile *)h_fulltow->ProfileX("_pfx", 1, -1, "s");
        h_fulltow_res = new TH1D(TString(h_fulltow->GetName()) + "_hprof", title, nbins, xmin, xmax);
        tp_unclclutow_res = (TProfile *)h_unclclutow->ProfileX("_pfx", 1, -1, "s");
        h_unclclutow_res = new TH1D(TString(h_unclclutow->GetName()) + "_hprof", title, nbins, xmin, xmax);
        for (int i = 1; i <= nbinsx; i++) {
           h_clu_res->SetBinContent(i, tp_clu_res->GetBinError(i));
           h_clu_res->SetBinError(i, 0);
           h_fulltow_res->SetBinContent(i, tp_fulltow_res->GetBinError(i));
           h_fulltow_res->SetBinError(i, 0);
           h_unclclutow_res->SetBinContent(i, tp_unclclutow_res->GetBinError(i));
           h_unclclutow_res->SetBinError(i, 0);
        }
     }
  }  // if (dofits)

  MyCanvas myc(canvtitle,
               xaxistitle,
               TString(domean ? "<" + ylabel + ">" : "#sigma(" + ylabel + ")/<" + ylabel + ">") +
               TString(dofits ? " (fit)" : ""));
  myc.SetLegendPosition(0.45, .8, .97, .93);
  if (domean) {
     myc.SetYRange(-0.01, 0.01);
  } else {
    myc.SetYRange(0, 0.15);
  }
  if (yvariable0 == "DR")
    myc.SetYRange(0, 0.1);
  if (domean && yvariable0.Contains("pt"))
    myc.SetYRange(0,2);
  if (!domean && yvariable0.Contains("pt"))
    myc.SetYRange(0, 0.6);
  myc.CanvasWithThreeHistogramsRatioPlot(h_clu_res,
                                         h_fulltow_res,
                                         h_unclclutow_res,
                                         "clu",
                                         "tow (full)",
                                         "clu and tow (unclustered)",
                                         "X / (clu and uncl. tow.)",
                                         kBlue,
                                         kGreen + 1,
                                         kRed,
                                         "E0",
                                         "E0",
                                         "E0");

  // add text to the plot
  myc.c->cd();
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.02);
  double xlatex = .18, ylatex = 0.97, dylatex = 0.025;
  latex.DrawLatex(xlatex, ylatex, sample + " " + PUtype);
  ylatex -= dylatex;
  latex.DrawLatex(xlatex, ylatex, "gen cuts: " + gencuts0);
  ylatex -= dylatex;
  latex.DrawLatex(xlatex, ylatex, "reco cuts: " + recocuts0 + Form("; DR(gen,reco)<%.2f", DRmatch));
  ylatex -= dylatex;

  myc.PrintCanvas();
}

void drawResolution(TString sample = "VBF_HToInvisible",
                     TString PUtype = "noPU",
                     TString xvariable0 = "abseta",
                     TString yvariable0 = "DR",
                     TString gencuts0 = "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                     TString recocuts0 = "",
                     double DRmatch = 0.2,
                     bool dofits = true,
                     int slicenb = -1) {
  drawScaleResolution(
      sample, PUtype, xvariable0, yvariable0, gencuts0, recocuts0, DRmatch, false, dofits, slicenb);
}

void drawScale(TString sample = "VBF_HToInvisible",
                TString PUtype = "noPU",
                TString xvariable0 = "abseta",
                TString yvariable0 = "DR",
                TString gencuts0 = "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                TString recocuts0 = "",
                double DRmatch = 0.2,
                bool dofits = true,
                int slicenb = -1) {
  drawScaleResolution(
      sample, PUtype, xvariable0, yvariable0, gencuts0, recocuts0, DRmatch, true, dofits, slicenb);
}

void drawDist(TString xvariable0 = "abseta", TString gencuts0 = "abs(eta)>1.6&&abs(eta)<2.8&&pt>40") {
  // TString file_relvalq = basepath + "/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root";
  // TString file_vbfhinv = basepath + "/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root";
  TString file_relvalq = basepath + "/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root";
  TString file_vbfhinv = basepath + "/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root";
  TFile *frelvalq = TFile::Open(file_relvalq);
  if (!frelvalq || !frelvalq->IsOpen()) {
     cout << "drawDist: " << file_relvalq << " does not exist, skipping." << endl;
     return;
  }
  TTree *trrelvalq = (TTree *)frelvalq->Get("tree");
  TFile *fvbfhinv = TFile::Open(file_vbfhinv);
  if (!fvbfhinv || !fvbfhinv->IsOpen()) {
     cout << "drawDist: " << file_vbfhinv << " does not exist, skipping." << endl;
     return;
  }
  TTree *trvbfhinv = (TTree *)fvbfhinv->Get("tree");

  if (gencuts0 == "")
    gencuts0 = "1";

  TString xaxistitle;
  int nbins = 1;
  float xmin = 1, xmax = 2;
  if (xvariable0 == "pt") {
    xaxistitle = "gen jet p_{T} [GeV]";
    nbins = 20;
    xmin = 0;
    xmax = 200;
  } else if (xvariable0 == "eta") {
    xaxistitle = "gen jet #eta";
    nbins = 34;
    xmin = -3.4;
    xmax = 3.4;
  } else if (xvariable0 == "abseta") {
    nbins = 18;
    xmin = 1.4;
    xmax = 3.2;
    xaxistitle = "gen jet |#eta|";
  } else if (xvariable0 == "phi") {
    nbins = 20;
    xmin = -TMath::Pi();
    xmax = -TMath::Pi();
    xaxistitle = "gen jet #phi";
  } else if (xvariable0 == "rho_clu") {
    nbins = 80;
    xmin = 0;
    xmax = 80;
    xaxistitle = "#rho (clu)";
  } else if (xvariable0 == "rho_clutow") {
    nbins = 70;
    xmin = 0;
    xmax = 350;
    xaxistitle = "#rho (clutow)";
  } else if (xvariable0 == "rho_tow") {
    nbins = 50;
    xmin = 0;
    xmax = 250;
    xaxistitle = "#rho (tow)";
  } else if (xvariable0 == "sigma_clu") {
    nbins = 80;
    xmin = 0;
    xmax = 40;
    xaxistitle = "#sigma (clu)";
  } else if (xvariable0 == "sigma_clutow") {
    nbins = 80;
    xmin = 0;
    xmax = 40;
    xaxistitle = "#sigma (clutow)";
  } else if (xvariable0 == "sigma_tow") {
    nbins = 80;
    xmin = 0;
    xmax = 40;
    xaxistitle = "#sigma (tow)";
  } else if (xvariable0 == "clujet_area") {
    nbins = 80;
    xmin = 0;
    xmax = 0.8;
    xaxistitle = "clujet area";
  } else if (xvariable0 == "clutowjet_area") {
    nbins = 80;
    xmin = 0;
    xmax = 0.8;
    xaxistitle = "clutowjet area";
  } else if (xvariable0 == "towjet_area") {
    nbins = 80;
    xmin = 0;
    xmax = 0.8;
    xaxistitle = "towjet area";
  } else if (xvariable0.Contains("gen_PUNumInt")) {
    nbins = 50;
    xmin = 0;
    xmax = 250;
    xaxistitle = "#mu";
  } else if (xvariable0.Contains("gen_TrueNumInt")) {
    nbins = 50;
    xmin = 0;
    xmax = 250;
    xaxistitle = "<#mu>";
  } else if (xvariable0.Contains("tc_n")) {
    nbins = 80;
    xmin = 0;
    xmax = 40000;
    xaxistitle = "# trigger cells";
  } else if (xvariable0.Contains("ts_n")) {
    nbins = 40;
    xmin = 0;
    xmax = 20000;
    xaxistitle = "# trigger sums";
  } else if (xvariable0.Contains("cl3d_n")) {
    nbins = 60;
    xmin = 0;
    xmax = 300;
    xaxistitle = "# 3D clusters";
  } else if (xvariable0.Contains("tower_n")) {
    nbins = 80;
    xmin = 2300;
    xmax = 2700;
    xaxistitle = "# trigger towers";
  } else {
    cout << "ERROR: " << xvariable0 << "is not a valid x variable." << endl;
  }

  TH1D *h_relvalq = new TH1D("h_relvalq", ";" + xaxistitle + ";Entries", nbins, xmin, xmax);
  TH1D *h_vbfhinv = new TH1D("h_vbfhinv", ";" + xaxistitle + ";Entries", nbins, xmin, xmax);

  // fill the histograms
  TString xvariable = xvariable0;
  TString gencuts = gencuts0;
  gencuts.ReplaceAll("pt", "genjet_pt");
  gencuts.ReplaceAll("eta", "genjet_eta");
  gencuts.ReplaceAll("phi", "genjet_phi");
  if (xvariable=="pt" || xvariable=="eta" || xvariable=="phi") xvariable = "genjet_" + xvariable;
  if (xvariable.Contains("abseta")) xvariable = "abs(genjet_eta)";

  cout << gencuts.Data() << endl;
  trrelvalq->Draw(xvariable + ">>h_relvalq", gencuts, "goff");
  trvbfhinv->Draw(xvariable + ">>h_vbfhinv", gencuts, "goff");

  h_relvalq->Scale(1. / h_relvalq->Integral());
  h_vbfhinv->Scale(1. / h_vbfhinv->Integral());

  TString canvtitle;
  if (gencuts0 == "1")
    gencuts0 = "none";
  canvtitle = outputpath + "/canv_dist_" + xvariable0;
  canvtitle +=
      "_gencuts_" + gencuts0.ReplaceAll(" ", "").ReplaceAll("&&", "AND").ReplaceAll("||", "OR").ReplaceAll("!", "NOT");
  canvtitle.ReplaceAll(".", "p");
  canvtitle.ReplaceAll(">", "GT");
  canvtitle.ReplaceAll("<", "LT");
  canvtitle.ReplaceAll("(", "");
  canvtitle.ReplaceAll(")", "");
  MyCanvas myc(canvtitle, xaxistitle, "a.u.");
  myc.SetLegendPosition(0.63, .41, 1., .64);
  // myc.SetYRange(0.5,1.04);
  myc.CanvasWithHistogramsRatioPlot(
      h_vbfhinv, h_relvalq, "VBF H#nu#nu", "q gun", "VBF H#nu#nu / q gun", kBlack, kRed, "hist", "hist");

  // add text to the plot
  myc.c->cd();
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.02);
  double xlatex = .18, ylatex = 0.97, dylatex = 0.025;
  latex.DrawLatex(xlatex, ylatex, "gen cuts: " + gencuts0);
  ylatex -= dylatex;

  myc.PrintCanvas();
}

void drawAll(double deltaR = 0.2) {
   gSystem->mkdir(outputpath);
   gSystem->mkdir(outputpath + "/eff");
   gSystem->mkdir(outputpath + "/scale");
   gSystem->mkdir(outputpath + "/resol");

   /////////////////////////////////
   //           raw jet pt
   /////////////////////////////////

   // efficiencies
  drawEfficiency("RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency("RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "", deltaR);
  drawEfficiency("RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "", deltaR);

  drawEfficiency("VBF_HToInvisible", "noPU", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency("VBF_HToInvisible", "noPU", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency("VBF_HToInvisible", "PU200", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency("VBF_HToInvisible", "PU200", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency("VBF_HToInvisible", "PU200", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "", deltaR);
  drawEfficiency("VBF_HToInvisible", "PUsub", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency("VBF_HToInvisible", "PUsub", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR);
  drawEfficiency("VBF_HToInvisible", "PUsub", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "", deltaR);

  // scales
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "pt",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "pt",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            true, 7);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            true, 7);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "noPU",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "",
  //           deltaR,
  //           false);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "noPU",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "",
  //           deltaR,
  //           true, 7);

  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "pt",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "pt",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            true, 7);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            true, 7);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PU200",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "",
  //           deltaR,
  //           false);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PU200",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "",
  //           deltaR,
  //           true, 7);

  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "pt",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "pt",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            true, 7);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "",
            deltaR,
            true, 7);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PUsub",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "",
  //           deltaR,
  //           false);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PUsub",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "",
  //           deltaR,
  //           true, 7);

  drawScale("VBF_HToInvisible", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);

  drawScale("VBF_HToInvisible", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);

  drawScale("VBF_HToInvisible", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawScale("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true, 7);

  // resolutions
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "pt",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "pt",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 true);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 true);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "noPU",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "",
  //                deltaR,
  //                false);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "noPU",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "",
  //                deltaR,
  //                true);

  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "pt",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "pt",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 true);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 true);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PU200",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "",
  //                deltaR,
  //                false);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PU200",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "",
  //                deltaR,
  //                true);

  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "pt",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "pt",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 true);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "",
                 deltaR,
                 true);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PUsub",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "",
  //                deltaR,
  //                false);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PUsub",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "",
  //                deltaR,
  //                true);

  drawResolution("VBF_HToInvisible", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);

  drawResolution("VBF_HToInvisible", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);

  drawResolution("VBF_HToInvisible", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "pt", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "", deltaR, true);

   /////////////////////////////////
   //       corrected jet pt
   /////////////////////////////////

   // efficiencies
  drawEfficiency("RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency("RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "ptcor>20", deltaR);
  drawEfficiency("RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "ptcor>20", deltaR);

  drawEfficiency("VBF_HToInvisible", "noPU", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency("VBF_HToInvisible", "noPU", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency("VBF_HToInvisible", "PU200", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency("VBF_HToInvisible", "PU200", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency("VBF_HToInvisible", "PU200", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "ptcor>20", deltaR);
  drawEfficiency("VBF_HToInvisible", "PUsub", "pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency("VBF_HToInvisible", "PUsub", "abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR);
  drawEfficiency("VBF_HToInvisible", "PUsub", "PU", "abs(eta)>1.6&&abs(eta)<2.8&&pt>80", "ptcor>20", deltaR);

  // scales
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "ptcor",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "ptcor",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            true, 7);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "noPU",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            true, 7);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "noPU",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "ptcor>20",
  //           deltaR,
  //           false);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "noPU",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "ptcor>20",
  //           deltaR,
  //           true, 7);

  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "ptcor",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "ptcor",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            true, 7);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PU200",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            true, 7);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PU200",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "ptcor>20",
  //           deltaR,
  //           false);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PU200",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "ptcor>20",
  //           deltaR,
  //           true, 7);

  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "ptcor",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "ptcor",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            true, 7);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            false);
  drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
            "PUsub",
            "abseta",
            "eta",
            "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
            "ptcor>20",
            deltaR,
            true, 7);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PUsub",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "ptcor>20",
  //           deltaR,
  //           false);
  // drawScale("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //           "PUsub",
  //           "abseta",
  //           "phi",
  //           "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //           "ptcor>20",
  //           deltaR,
  //           true, 7);

  drawScale("VBF_HToInvisible", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);

  drawScale("VBF_HToInvisible", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);

  drawScale("VBF_HToInvisible", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawScale("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);
  // drawScale("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawScale("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true, 7);

  // resolutions
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "ptcor",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "ptcor",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 true);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "noPU",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 true);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "noPU",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "ptcor>20",
  //                deltaR,
  //                false);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "noPU",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "ptcor>20",
  //                deltaR,
  //                true);

  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "ptcor",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "ptcor",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 true);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PU200",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 true);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PU200",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "ptcor>20",
  //                deltaR,
  //                false);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PU200",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "ptcor>20",
  //                deltaR,
  //                true);

  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "ptcor",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "ptcor",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 true);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution(
      "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 false);
  drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
                 "PUsub",
                 "abseta",
                 "eta",
                 "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
                 "ptcor>20",
                 deltaR,
                 true);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution(
  //     "RelValDiQ_Pt20To300_Etam1p6Tom2p9", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PUsub",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "ptcor>20",
  //                deltaR,
  //                false);
  // drawResolution("RelValDiQ_Pt20To300_Etam1p6Tom2p9",
  //                "PUsub",
  //                "abseta",
  //                "phi",
  //                "abs(eta)>1.6&&abs(eta)<2.8&&pt>40",
  //                "ptcor>20",
  //                deltaR,
  //                true);

  drawResolution("VBF_HToInvisible", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "noPU", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution("VBF_HToInvisible", "noPU", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution("VBF_HToInvisible", "noPU", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);

  drawResolution("VBF_HToInvisible", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PU200", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PU200", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PU200", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);

  drawResolution("VBF_HToInvisible", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "pt", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "ptcor", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "pt", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  drawResolution("VBF_HToInvisible", "PUsub", "abseta", "eta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PUsub", "pt", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);
  // drawResolution("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, false);
  // drawResolution("VBF_HToInvisible", "PUsub", "abseta", "phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", "ptcor>20", deltaR, true);

  // distributions
  drawDist("abseta", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40");
  drawDist("pt", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40");
  drawDist("phi", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40");
  drawDist("clujet_area", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40");
  drawDist("clutowjet_area", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40");
  drawDist("towjet_area", "abs(eta)>1.6&&abs(eta)<2.8&&pt>40");
}

TH1D* myFitSlicesY(TH2F *h2d, bool domean, int slicenb, TString canvname) {
   TProfile *tp = h2d->ProfileX("_pfx2",1,-1,"s");

   TF1 fgaus("fgaus","gaus(0)",h2d->GetYaxis()->GetXmin(),h2d->GetYaxis()->GetXmax());

   TString title = TString(";") + h2d->GetXaxis()->GetTitle() + ";" + h2d->GetYaxis()->GetTitle();
   int nbins = h2d->GetXaxis()->GetNbins();
   double xmin = h2d->GetXaxis()->GetXmin();
   double xmax = h2d->GetXaxis()->GetXmax();

   TH1D *ans = new TH1D(TString(h2d->GetName()) + "_fits", title, nbins, xmin, xmax);

   for (int i=1; i <= h2d->GetNbinsX()+1; i++) {
      TH1D *htemp = h2d->ProjectionY(Form("_py%d",i), i, i);
      if (htemp->GetEntries()>0) {
         double tmpmean = tp->GetBinContent(i);
         double tmpsigma = tp->GetBinError(i);
         fgaus.SetParameters(htemp->GetEntries(),tmpmean,tmpsigma);
         fgaus.SetRange(tmpmean-1.5*tmpsigma,tmpmean+1.5*tmpsigma);
         htemp->Fit(&fgaus,"QNRL");
         if (domean) {
            ans->SetBinContent(i,fgaus.GetParameter(1));
            ans->SetBinError(i,fgaus.GetParError(1));
         } else {
            ans->SetBinContent(i,fgaus.GetParameter(2));
            ans->SetBinError(i,fgaus.GetParError(2));
         }

         if (i==slicenb) {
            TCanvas canv(canvname);
            htemp->Draw();
            fgaus.Draw("same");
            TLatex latex;
            latex.SetNDC();
            latex.SetTextSize(0.02);
            double xlatex = .18, ylatex = 0.97, dylatex = 0.025;
            latex.DrawLatex(xlatex, ylatex, Form("%.2f < %s < %.2f", h2d->GetXaxis()->GetBinLowEdge(i), h2d->GetXaxis()->GetTitle(), h2d->GetXaxis()->GetBinUpEdge(i)));
            canv.SaveAs(canvname + ".pdf");
         }
      } else {
         ans->SetBinContent(i,0);
         ans->SetBinError(i,0);
      }
   }

   return ans;
}

void checkNumDen(TH1 *hnum, TH1 *hden) {
   if (hnum->GetNbinsX() != hden->GetNbinsX()) {
      cout << "ERROR! numerator and denominator have different numbers of bins." << endl;
      return;
   }

   for (int i=0; i<=hnum->GetNbinsX()+1; i++) {
      if (hnum->GetBinContent(i) > hden->GetBinContent(i))
         hnum->SetBinContent(i, hden->GetBinContent(i));
   }

   hnum->Sumw2(false);
}
