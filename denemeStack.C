//{
//#include "TStyle.h"

#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TPad.h"    
#include "TAttPad.h"
#include "TAttLine.h"
#include "TLegend.h"

void denemeStack(TString scene,TString samp)
{
    gROOT->Reset();
    //gROOT->Reset();
    gROOT->SetStyle("Plain");
    gStyle->SetOptStat(kFALSE);
    //aşağıdaki satırda "t" yazmazsam algılamıyor alttaki satır başlıktaki yazının boyutu
    gStyle->SetTitleSize(0.04,"t"); //0.33
    gStyle->SetTitleBorderSize(0); //başlığın etrafındaki çerçeve kalınlığı
    gStyle->SetTitleX(0.08); //graph title X location
    gStyle->SetTitleY(0.97); //graph title Y location 
    gStyle->SetPadBorderMode(0);
    gStyle->SetFrameBorderMode(0);
    //gStyle->SetLineStyleString(5,"400 200");
    //gStyle->SetLineStyleString(5,"20 12 4 12");
   ////
    cout << "******start drawing**********"+scene+" for "+samp<<endl;
   
    THStack *hs1=new THStack("hs1","Delphes Simulation		                14TeV,   300 fb^{-1}  "+scene);   
    	
    
        
    TH1F* Element_DiBoson;
    TFile *bkg1 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_DiBoson_300_his.root");
    Element_DiBoson= (TH1F*) bkg1->Get(samp);
    Element_DiBoson->SetFillColor(kGreen);
      

	
    TH1F* Element_BosonJets;
    TFile *bkg2 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_BosonJets_300_his.root");
    Element_BosonJets= (TH1F*) bkg2->Get(samp);
    Element_BosonJets->SetFillColor(kYellow);

    TH1F* Element_TTbar;
    TFile *bkg3 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_TTbar_300_his.root");
    Element_TTbar= (TH1F*) bkg3->Get(samp);
    Element_TTbar->SetFillColor(kRed+1);

    TH1F* Element_TopJets;
    TFile *bkg4 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_TopJets_300_his.root");
    Element_TopJets= (TH1F*) bkg4->Get(samp);
    Element_TopJets->SetFillColor(kOrange+1);

   TH1F* ML1;
    TFile *bkg5 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_ML1_300_his.root");
    ML1= (TH1F*) bkg5->Get(samp);
    ML1->SetLineStyle(2);
    ML1->SetLineWidth(3);
    ML1->SetLineColor(kBlue-10);
    //gStyle->GetLineStyle(5);

    TH1F* ML2;
    TFile *bkg6 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_ML2_300_his.root");
    ML2= (TH1F*) bkg6->Get(samp);
    ML2->SetLineStyle(2);
    ML2->SetLineWidth(3);
    ML2->SetLineColor(kBlack);
/*
    TH1F* ML3;
    TFile *bkg7 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_ML3_10_his.root");
    ML3= (TH1F*) bkg7->Get(samp);
    ML3->SetLineStyle(2);
    ML3->SetLineWidth(3);
    ML3->SetLineColor(kGreen-4);

    TH1F* ML4;
    TFile *bkg8 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_"+scene+"_ML4_10_his.root");
    ML4= (TH1F*) bkg8->Get(samp);
    ML4->SetLineStyle(2);
    ML4->SetLineWidth(3);
    ML4->SetLineColor(kBlue+1);
*/
  /*  
    TH1F* ML4;
    TFile *bkg8 = TFile::Open("/home/cakir/NtuplerAnalyzer/ML4_Signal_NoPU_TDR4.root");
    ML4= (TH1F*) bkg8->Get(samp);
    ML4->SetLineStyle(10);
    ML4->SetLineStyle(kSpring+9);

    TH1F* ML5;
    TFile *bkg9 = TFile::Open("/home/cakir/NtuplerAnalyzer/ML5_Signal_NoPU_TDR4.root");
    ML5= (TH1F*) bkg9->Get(samp);
    ML5->SetLineStyle(4);
    ML5->SetLineStyle(kAzure-8);*/
    //Element_Signal->SetFillColor(kGray);
    //gStyle->SetLineStyleString(11,"400 200");

   /* Double_t eps = 0.005;
    TPad* p1 = new TPad("p1","p1",0.1,0.5,0.9,0.9,0); p1->Draw();
    TPad* p2 = new TPad("p1","p1",0.1,0.1,0.9,0.5+eps,0); p2->Draw();
    p1->SetBottomMargin(0.0);
    p2->SetTopMargin(0.0);
    */
    //TFile* file = new TFile ("stack_"+samp+"_"+scene+".root","RECREATE");
    TCanvas* c1 = new TCanvas("c1","stack_"+samp+"_bckgrnd",800,40,1000,800) ;
    c1->cd(1);
    //c1->SetTopMargin(0.1822542);
    c1->SetLogy();
    //file->Write();
   // p1->cd();
   // p2->cd();

	hs1->Draw();    
	hs1->Add(Element_TopJets);
	hs1->Add(Element_TTbar);    
	hs1->Add(Element_DiBoson);
	hs1->Add(Element_BosonJets);
        
	ML1->Draw("same");	
	ML2->Draw("same");
//	ML3->Draw("same");
  //      ML4->Draw("same");
//	hs1->Add(ML4);
//	hs1->Add(ML5);
    //hs1->GetXaxis()->SetLimits(0, 3000);
    //Aşağıdaki kod y ekseninin minimum ve maksimunu ayarlamımıza yarıyor
    hs1->SetMinimum(0.01);
    hs1->SetMaximum(10000000);
    hs1->GetXaxis()->SetRangeUser(0,2500);
//    hs1->GetXaxis()->SetRangeUser(100,600);
    //hs1->SetTitle("Delphes Simulation 14TeV, 10fb^{-1} "+scene);
    //hs1->SetTitleSize(0.5);
    hs1->GetHistogram()->GetXaxis()->SetTitle(samp); //Number of Events
    hs1->GetHistogram()->GetYaxis()->SetTitle("#Events");//Number of Events
    //Aşağıdaki 2 satır x ve y eksen isimlerinin ortalanmasını sağlar
    //hs1->GetHistogram()->GetYaxis()->CenterTitle();
    //hs1->GetHistogram()->GetXaxis()->CenterTitle();
    hs1->GetHistogram()->GetXaxis()->SetTitleSize(0.05);
    hs1->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
	//TLEgen(,,saga kaydirma,yukari kaydirma)
    TLegend *pl = new TLegend(0.55, 0.7, 0.9, 0.87); //burada (0.7,0.8,0.9,0.9) idi
    //Aşağıdaki satır histogramda sağ üstte çıkan bilgi kutucuğundaki yazıların kalınlığıyla ilgili
    pl-> SetNColumns(2);
    pl->SetTextSize(0.04); //0.03 idi
    pl->SetFillColor(0);
    pl->SetBorderSize(0);
    
   
    //TLegendEntry *ple = pl->AddEntry(samp_scene, samp+" for "+scene,  "lpf");
    /*ple =*/   pl->AddEntry(Element_TopJets, "Single Top","lpf" );
    /*ple =*/   pl->AddEntry(Element_DiBoson, "VV+jets","lpf");
    /*ple=*/    pl->AddEntry(Element_TTbar, "tt+jets",  "lpf");
		pl->AddEntry(Element_BosonJets, "V+jets",  "lpf");
                pl->AddEntry(ML1, "ML1","lpf" );
		pl->AddEntry(ML2, "ML2","lpf" );
//		pl->AddEntry(ML3, "ML3","lpf" );
//		pl->AddEntry(ML4, "ML4","lpf" );
//		pl->AddEntry(ML5, "ML5","lpf" );
    ///*ple=*/pl->AddEntry("Sceneario 140PU");
    pl->SetFillColor(0);
    pl->SetLineColor(0.5);
    pl->Draw("same");
    
    //c1->SaveAs("/home/cakir/Desktop/PlottingTool/StorageHist/stack_"+scene+"_"+samp+".gif");
/*
    c1->SaveAs("/home/cakir/Desktop/PlottingTool/StorageHist_100lumi_tight_"+scene+"/PDFFiles/stack_"+scene+"_"+samp+".pdf");
    c1->SaveAs("/home/cakir/Desktop/PlottingTool/StorageHist_100lumi_tight_"+scene+"/ROOTFiles/stack_"+scene+"_"+samp+".root");
    c1->SaveAs("/home/cakir/Desktop/PlottingTool/StorageHist_100lumi_tight_"+scene+"/PNGFiles/stack_"+scene+"_"+samp+".png");    
*/
    c1->SaveAs("/home/cakir/Desktop/PlottingTool/Plots/stack_"+scene+"_"+samp+"300lumi.pdf");
    c1->SaveAs("/home/cakir/Desktop/PlottingTool/Plots/stack_"+scene+"_"+samp+"300lumi.root");
    c1->SaveAs("/home/cakir/Desktop/PlottingTool/Plots/stack_"+scene+"_"+samp+"300lumi.png"); 
}
