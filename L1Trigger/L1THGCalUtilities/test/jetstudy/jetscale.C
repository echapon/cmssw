const double rhoUE_clu = 0;
const double rhoUE_clutow = 2.468;
const double rhoUE_tow = 2.483;

const int nbins_abseta = 11;
const int nbins_pt = 8;
double bins_abseta[12] = {1.55, 1.65, 1.72, 1.8, 1.9, 2.1, 2.3, 2.5, 2.6, 2.68, 2.75, 2.85};
double bins_pt[9] = {20, 40, 50, 60, 75, 100, 140, 200, 1000};

TGraph *findMinMax(TGraph2D *tg2d, bool domin) {
   map<double,double> tm;
   double *xx = tg2d->GetX();
   double *yy = tg2d->GetY();
   for (int i=0; i<tg2d->GetN(); i++) {
      double ae = xx[i];
      double pt = yy[i];

      if (tm.find(ae)==tm.end()
            || (domin && pt<tm[ae])
            || (!domin && pt>tm[ae]))
         tm[ae] = pt;
   }

   TGraph *ans = new TGraph(tm.size());
   int i=0;
   for (auto it=tm.begin(); it!=tm.end(); ++it) {
      double ae = it->first;
      double pt = it->second;
      ans->SetPoint(i, ae, pt);
      i++;
   }

   return ans;
}

TGraph *findMin(TGraph2D *tg2d) {
   return findMinMax(tg2d, true);
}

TGraph *findMax(TGraph2D *tg2d) {
   return findMinMax(tg2d, false);
}

void createScaleFile(TString filein, TString jetcol, TString gencuts = "abs(eta)>1.6&&abs(eta)<2.8&&pt>40", TString fileout="file.root", TString ptvar = "pt") {
   TFile *f = TFile::Open(filein);
   if (!fin) {
      cout << "createScaleFile: " << filein << " does not exist, skipping." << endl;
      return;
   }
   TTree *tr = (TTree*) f->Get("tree");

   TProfile2D *tprof2d = new TProfile2D("tprof2d","",nbins_abseta,bins_abseta,nbins_pt,bins_pt);
   TProfile2D *tprof2d_pt = new TProfile2D("tprof2d_pt","",nbins_abseta,bins_abseta,nbins_pt,bins_pt);
   // TString var = "abs(recjet_eta):recjet_pt:(recjet_pt-recjet_genpt)/recjet_genpt";
   TString var = "recjet_" + ptvar + "/recjet_genpt:recjet_genpt:abs(recjet_eta)";
   TString varpt = "recjet_" + ptvar + ":recjet_genpt:abs(recjet_eta)";
   gencuts.ReplaceAll("pt", "recjet_genpt");
   gencuts.ReplaceAll("eta", "recjet_geneta");
   gencuts.ReplaceAll("phi", "recjet_genphi");
   var.ReplaceAll("recjet",jetcol);
   varpt.ReplaceAll("recjet",jetcol);
   gencuts.ReplaceAll("recjet",jetcol);
   tr->Draw(var + ">>tprof2d",gencuts,"prof");
   tr->Draw(varpt + ">>tprof2d_pt",gencuts,"prof");
   TGraph2D *tg2d = new TGraph2D(nbins_abseta*nbins_pt);
   TGraph *tg = new TGraph(nbins_abseta*nbins_pt);
   for (int i=0; i<nbins_abseta; i++) {
      double eta = (bins_abseta[i]+bins_abseta[i+1])/2.;
      for (int j=0; j<nbins_pt; j++) {
         double pt = tprof2d_pt->GetBinContent(i+1,j+1); // replace the gen pt with the average raw reco pt in that bin
         tg2d->SetPoint(i*nbins_pt+j, eta, pt, tprof2d->GetBinContent(i+1,j+1));
         tg->SetPoint(i*nbins_pt+j, eta, pt);
         // cout << eta << " " << pt << " " << tprof2d->GetBinContent(i+1,j+1) << endl;
      }
   }
   tg2d->SaveAs(fileout);

   // plotting
   gStyle->SetPadRightMargin(0.15);
   TCanvas c;
   tg2d->Draw("COLZ");
   tg2d->GetHistogram()->GetXaxis()->SetTitle("rec jet |#eta|");
   tg2d->GetHistogram()->GetYaxis()->SetTitle("rec jet p_{T} [GeV]");
   tg2d->GetHistogram()->GetZaxis()->SetTitle("rec p_{T} / gen p_{T}");

   // plot our custom interpolation
   TGraph *gmin = findMin(tg2d);
   TGraph *gmax = findMax(tg2d);
   TH2D *h2d = tg2d->GetHistogram();
   TAxis *xaxis = h2d->GetXaxis();
   TAxis *yaxis = h2d->GetYaxis();
   for (int i=1; i<=xaxis->GetNbins(); i++) {
      double abseta = xaxis->GetBinCenter(i);
      for (int j=1; j<=yaxis->GetNbins(); j++) {
         double pt = yaxis->GetBinCenter(j);
         if (pt<gmin->Eval(abseta)) pt = gmin->Eval(abseta);
         if (pt>gmax->Eval(abseta)) pt = gmax->Eval(abseta);
         if (abseta<bins_abseta[0]) abseta = 1.6;
         if (abseta>bins_abseta[nbins_abseta]) abseta = 2.8;
         h2d->SetBinContent(i,j,tg2d->Interpolate(abseta,pt));
      }
   }
   h2d->Draw("COLZ same");

   tg->Draw("P");
   gmin->Draw("L");
   gmax->Draw("L");
   c.SaveAs(fileout.ReplaceAll(".root",".pdf"));
}

void createScaleFiles(TString basepath = "./") {
   createScaleFile(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root", "clujet", "", basepath+"jec_VBF_NoPU_clu.root");
   createScaleFile(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root", "clutowjet", "", basepath+"jec_VBF_NoPU_unclclutow.root");
   createScaleFile(basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_NoPU.root", "towjet", "", basepath+"jec_VBF_NoPU_fulltow.root");

   createScaleFile(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200_offset.root", "clujet", "", basepath+"jec_VBF_PU200_clu_offset.root", "ptoff");
   createScaleFile(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200_offset.root", "clutowjet", "", basepath+"jec_VBF_PU200_unclclutow_offset.root", "ptoff");
   createScaleFile(basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_PU200_offset.root", "towjet", "", basepath+"jec_VBF_PU200_fulltow_offset.root", "ptoff");

   createScaleFile(basepath+"unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root", "clujet", "", basepath+"jec_VBF_PUsub_clu.root");
   createScaleFile(basepath+"unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root", "clutowjet", "", basepath+"jec_VBF_PUsub_unclclutow.root");
   createScaleFile(basepath+"fulltowers/PUsub/output_VBF_HToInvisible_PU200.root", "towjet", "", basepath+"jec_VBF_PUsub_fulltow.root");
}

void applyJEC(TString filein, TString fileout, TString basepath="./") {
   TFile *fin = TFile::Open(filein);
   if (!fin) {
      cout << "applyJEC: " << filein << " does not exist, skipping." << endl;
      return;
   }
   TFile *fout = TFile::Open(fileout, "RECREATE");

   // read JEC files
   TFile *f_jec_clu, *f_jec_unclclutow, *f_jec_fulltow;
   TGraph2D *g2d_jec_clu, *g2d_jec_unclclutow, *g2d_jec_fulltow;
   TString suffix = "";
   if (filein.Contains("offset")) suffix = "_offset";
   if (filein.Contains("PU200") && filein.Contains("noPUsub")) {
      f_jec_clu = TFile::Open(basepath+"jec_VBF_PU200_clu"+suffix+".root");
      f_jec_unclclutow = TFile::Open(basepath+"jec_VBF_PU200_unclclutow"+suffix+".root");
      f_jec_fulltow = TFile::Open(basepath+"jec_VBF_PU200_fulltow"+suffix+".root");
   } else if (filein.Contains("NoPU")) {
      f_jec_clu = TFile::Open(basepath+"jec_VBF_NoPU_clu"+suffix+".root");
      f_jec_unclclutow = TFile::Open(basepath+"jec_VBF_NoPU_unclclutow"+suffix+".root");
      f_jec_fulltow = TFile::Open(basepath+"jec_VBF_NoPU_fulltow"+suffix+".root");
   } else {
      f_jec_clu = TFile::Open(basepath+"jec_VBF_PUsub_clu"+suffix+".root");
      f_jec_unclclutow = TFile::Open(basepath+"jec_VBF_PUsub_unclclutow"+suffix+".root");
      f_jec_fulltow = TFile::Open(basepath+"jec_VBF_PUsub_fulltow"+suffix+".root");
   }
   g2d_jec_clu = (TGraph2D*) f_jec_clu->Get("Graph2D");
   g2d_jec_unclclutow = (TGraph2D*) f_jec_unclclutow->Get("Graph2D");
   g2d_jec_fulltow = (TGraph2D*) f_jec_fulltow->Get("Graph2D");

   cout << "Applying JEC: " << filein << " -> " << fileout << endl;
   cout << "using " << f_jec_clu->GetName() << ", " << f_jec_unclclutow->GetName() << ", " << f_jec_fulltow->GetName() << endl;

   // need the min/max graphs
   TGraph *gmin_jec_clu = findMin(g2d_jec_clu);
   TGraph *gmax_jec_clu = findMax(g2d_jec_clu);
   TGraph *gmin_jec_unclclutow = findMin(g2d_jec_unclclutow);
   TGraph *gmax_jec_unclclutow = findMax(g2d_jec_unclclutow);
   TGraph *gmin_jec_fulltow = findMin(g2d_jec_fulltow);
   TGraph *gmax_jec_fulltow = findMax(g2d_jec_fulltow);

   // setup new tree
   fin->cd();
   TTree *oldtree = (TTree*) fin->Get("tree");
   fout->cd();
   oldtree->SetBranchStatus("*",1);
   TTree *newtree = oldtree->CloneTree(0);

   // branch setup
   TString ptvar = filein.Contains("offset") ? "ptoff" : "pt";
   vector<float> *clujet_pt=0; oldtree->SetBranchAddress("clujet_"+ptvar,&clujet_pt);
   vector<float> *clujet_eta=0; oldtree->SetBranchAddress("clujet_eta",&clujet_eta);
   vector<float> *clutowjet_pt=0; oldtree->SetBranchAddress("clutowjet_"+ptvar,&clutowjet_pt);
   vector<float> *clutowjet_eta=0; oldtree->SetBranchAddress("clutowjet_eta",&clutowjet_eta);
   vector<float> *towjet_pt=0; oldtree->SetBranchAddress("towjet_"+ptvar,&towjet_pt);
   vector<float> *towjet_eta=0; oldtree->SetBranchAddress("towjet_eta",&towjet_eta);

   vector<float> clujet_ptcor; newtree->Branch("clujet_ptcor",&clujet_ptcor);
   vector<float> clutowjet_ptcor; newtree->Branch("clutowjet_ptcor",&clutowjet_ptcor);
   vector<float> towjet_ptcor; newtree->Branch("towjet_ptcor",&towjet_ptcor);

   // loop
   const auto nentries = oldtree->GetEntries();
   for (auto i : ROOT::TSeqI(nentries)) {
      oldtree->GetEntry(i);

      clujet_ptcor.clear();
      clutowjet_ptcor.clear();
      towjet_ptcor.clear();

      for (int j=0; j<clujet_pt->size(); j++) {
         float pt = clujet_pt->at(j);
         float abseta = fabs(clujet_eta->at(j));
         if (pt<gmin_jec_clu->Eval(abseta)) pt = gmin_jec_clu->Eval(abseta);
         if (pt>gmax_jec_clu->Eval(abseta)) pt = gmax_jec_clu->Eval(abseta);
         if (abseta<bins_abseta[0]) abseta = 1.6;
         if (abseta>bins_abseta[nbins_abseta]) abseta = 2.8;
         float resp = g2d_jec_clu->Interpolate(abseta,pt);
         if (resp<1e-3 || resp>1e3) resp=1;
         float ptcor = clujet_pt->at(j) / resp;
         clujet_ptcor.push_back(ptcor);
      }
      for (int j=0; j<clutowjet_pt->size(); j++) {
         float pt = clutowjet_pt->at(j);
         float abseta = fabs(clutowjet_eta->at(j));
         if (pt<gmin_jec_unclclutow->Eval(abseta)) pt = gmin_jec_unclclutow->Eval(abseta);
         if (pt>gmax_jec_unclclutow->Eval(abseta)) pt = gmax_jec_unclclutow->Eval(abseta);
         if (abseta<bins_abseta[0]) abseta = 1.6;
         if (abseta>bins_abseta[nbins_abseta]) abseta = 2.8;
         float resp = g2d_jec_unclclutow->Interpolate(abseta,pt);
         if (resp<1e-3 || resp>1e3) resp=1;
         float ptcor = clutowjet_pt->at(j) / resp;
         clutowjet_ptcor.push_back(ptcor);
      }
      for (int j=0; j<towjet_pt->size(); j++) {
         float pt = towjet_pt->at(j);
         float abseta = fabs(towjet_eta->at(j));
         if (pt<gmin_jec_fulltow->Eval(abseta)) pt = gmin_jec_fulltow->Eval(abseta);
         if (pt>gmax_jec_fulltow->Eval(abseta)) pt = gmax_jec_fulltow->Eval(abseta);
         if (abseta<bins_abseta[0]) abseta = 1.6;
         if (abseta>bins_abseta[nbins_abseta]) abseta = 2.8;
         float resp = g2d_jec_fulltow->Interpolate(abseta,pt);
         if (resp<1e-3 || resp>1e3) resp=1;
         float ptcor = towjet_pt->at(j) / resp;
         towjet_ptcor.push_back(ptcor);
      }

      newtree->Fill();
   }

   fout->Write();
   fout->Close();
   fin->Close();
}

void applyJEC(TString basepath="./") {
   applyJEC(basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root",basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_cor.root",basepath);
   applyJEC(basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offset.root",basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offcor.root",basepath);
   applyJEC(basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_NoPU.root",basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_NoPU_cor.root",basepath);
   applyJEC(basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_PU200_offset.root",basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_PU200_offcor.root",basepath);
   applyJEC(basepath+"fulltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root",basepath+"fulltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_cor.root",basepath);
   applyJEC(basepath+"fulltowers/PUsub/output_VBF_HToInvisible_PU200.root",basepath+"fulltowers/PUsub/output_VBF_HToInvisible_PU200_cor.root",basepath);
   applyJEC(basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root",basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_cor.root",basepath);
   applyJEC(basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offset.root",basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offcor.root",basepath);
   applyJEC(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root",basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU_cor.root",basepath);
   applyJEC(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200_offset.root",basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200_offcor.root",basepath);
   applyJEC(basepath+"unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root",basepath+"unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_cor.root",basepath);
   applyJEC(basepath+"unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root",basepath+"unclunseltowers/PUsub/output_VBF_HToInvisible_PU200_cor.root",basepath);
}

void applyOffset(TString filein, TString fileout) {
   TFile *fin = TFile::Open(filein);
   if (!fin) {
      cout << "applyOffset: " << filein << " does not exist, skipping." << endl;
      return;
   }
   TFile *fout = TFile::Open(fileout, "RECREATE");

   // setup new tree
   fin->cd();
   TTree *oldtree = (TTree*) fin->Get("tree");
   fout->cd();
   oldtree->SetBranchStatus("*",1);
   TTree *newtree = oldtree->CloneTree(0);

   // branch setup
   float rho_clu; oldtree->SetBranchAddress("rho_clu",&rho_clu);
   float rho_clutow; oldtree->SetBranchAddress("rho_clutow",&rho_clutow);
   float rho_tow; oldtree->SetBranchAddress("rho_tow",&rho_tow);
   vector<float> *clujet_pt=0; oldtree->SetBranchAddress("clujet_pt",&clujet_pt);
   vector<float> *clujet_eta=0; oldtree->SetBranchAddress("clujet_eta",&clujet_eta);
   vector<float> *clujet_area=0; oldtree->SetBranchAddress("clujet_area",&clujet_area);
   vector<float> *clutowjet_pt=0; oldtree->SetBranchAddress("clutowjet_pt",&clutowjet_pt);
   vector<float> *clutowjet_eta=0; oldtree->SetBranchAddress("clutowjet_eta",&clutowjet_eta);
   vector<float> *clutowjet_area=0; oldtree->SetBranchAddress("clutowjet_area",&clutowjet_area);
   vector<float> *towjet_pt=0; oldtree->SetBranchAddress("towjet_pt",&towjet_pt);
   vector<float> *towjet_eta=0; oldtree->SetBranchAddress("towjet_eta",&towjet_eta);
   vector<float> *towjet_area=0; oldtree->SetBranchAddress("towjet_area",&towjet_area);

   vector<float> clujet_ptoff; newtree->Branch("clujet_ptoff",&clujet_ptoff);
   vector<float> clutowjet_ptoff; newtree->Branch("clutowjet_ptoff",&clutowjet_ptoff);
   vector<float> towjet_ptoff; newtree->Branch("towjet_ptoff",&towjet_ptoff);

   // beta functions
   TF1 fclu("fclu","pol3",1.4,3.2);
   TF1 fclutow("fclutow","pol3",1.4,3.2);
   TF1 ftow("ftow","pol3",1.4,3.2);
   ftow.SetParameters(-3.16924,3.17969,-0.555375,-0.0247883);

   // parameters for clu and clutow depend on how clusters were generated
   if filein.Contains("/fixphismooth/") {
      fclu.SetParameters(-5.87156,-0.389373,2.23095,-0.43595);
      fclutow.SetParameters(-5.12634,5.94146,-1.83501,0.17018);
   } else if filein.Contains("/noarea/") {
      fclu.SetParameters(-12.7411,15.1547,-6.14957,0.867665);
      fclutow.SetParameters(-5.32816,6.23085,-1.96033,0.187501);
   } else if filein.Contains("/rphi_thr6p5/") {
      fclu.SetParameters(-15.6655,15.2532,-5.17996,0.651576);
      fclutow.SetParameters(-5.20646,6.06419,-1.8944,0.17948);
   } else if filein.Contains("/xyseed/") {
      fclu.SetParameters(4.7857,-14.3544,8.77443,-1.48954);
      fclutow.SetParameters(-4.32072,4.79285,-1.29292,0.0853122);
   } else { // default
      fclu.SetParameters(-37.6418,41.0612,-15.6948,2.11851);
      fclutow.SetParameters(-5.63153,6.61603,-2.13003,0.212677);
   }

   // loop
   const auto nentries = oldtree->GetEntries();
   for (auto i : ROOT::TSeqI(nentries)) {
      oldtree->GetEntry(i);

      clujet_ptoff.clear();
      clutowjet_ptoff.clear();
      towjet_ptoff.clear();

      for (int j=0; j<clujet_pt->size(); j++) {
         float beta = fclu(fabs(clujet_eta->at(j)));
         float Coffset = 1. - (rho_clu - rhoUE_clu) * beta * clujet_area->at(j) / clujet_pt->at(j);
         float ptoff = Coffset * clujet_pt->at(j);
         clujet_ptoff.push_back(ptoff);
      }
      for (int j=0; j<clutowjet_pt->size(); j++) {
         float beta = fclutow(fabs(clutowjet_eta->at(j)));
         float Coffset = 1. - (rho_clutow- rhoUE_clutow) * beta * clutowjet_area->at(j) / clutowjet_pt->at(j);
         float ptoff = Coffset * clutowjet_pt->at(j);
         clutowjet_ptoff.push_back(ptoff);
      }
      for (int j=0; j<towjet_pt->size(); j++) {
         float beta = ftow(fabs(towjet_eta->at(j)));
         float Coffset = 1. - (rho_tow - rhoUE_tow) * beta * towjet_area->at(j) / towjet_pt->at(j);
         float ptoff = Coffset * towjet_pt->at(j);
         towjet_ptoff.push_back(ptoff);
      }

      newtree->Fill();
   }

   fout->Write();
   fout->Close();
   fin->Close();
}

void applyOffset() {
   applyOffset(basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root",basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_offset.root",basepath);
   applyOffset(basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root",basepath+"fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offset.root",basepath);
   applyOffset(basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_NoPU.root",basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_NoPU_offset.root",basepath);
   applyOffset(basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_PU200.root",basepath+"fulltowers/noPUsub/output_VBF_HToInvisible_PU200_offset.root",basepath);
   applyOffset(basepath+"fulltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root",basepath+"fulltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offset.root",basepath);
   applyOffset(basepath+"fulltowers/PUsub/output_VBF_HToInvisible_PU200.root",basepath+"fulltowers/PUsub/output_VBF_HToInvisible_PU200_offset.root",basepath);
   applyOffset(basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root",basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_offset.root",basepath);
   applyOffset(basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root",basepath+"unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offset.root",basepath);
   applyOffset(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root",basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU_offset.root",basepath);
   applyOffset(basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root",basepath+"unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200_offset.root",basepath);
   applyOffset(basepath+"unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root",basepath+"unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_offset.root",basepath);
   applyOffset(basepath+"unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root",basepath+"unclunseltowers/PUsub/output_VBF_HToInvisible_PU200_offset.root",basepath);
}
