//{
//#include "TStyle.h"

#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TPad.h"    
#include "TAttFill.h" 
#include "TAttPad.h"
#include "TAttLine.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TAttText.h"
#include "TLatex.h"


//to compile root -l ‘ratioPlot.C(“hHT”)’
void ratiPlot(TString samp)
{
    gROOT->Reset();
    //gROOT->Reset();
    gROOT->SetStyle("Plain");
    gStyle->SetOptStat(kFALSE);
//    gStyle->SetCanvasPreferGL(1);
    //aşağıdaki satırda "t" yazmazsam algılamıyor alttaki satır başlıktaki yazının boyutu
    gStyle->SetOptTitle(0);
    gStyle->SetTitleSize(0.04,"t"); //0.33
    gStyle->SetTitleBorderSize(0); //başlığın etrafındaki çerçeve kalınlığı
    gStyle->SetTitleX(0.08); //graph title X location
    gStyle->SetTitleY(0.97); //graph title Y location 
    gStyle->SetPadBorderMode(0);
    gStyle->SetFrameBorderMode(0);
    //gStyle->SetLineStyleString(5,"400 200");
    //gStyle->SetLineStyleString(5,"20 12 4 12");
   ////
    cout << "******start drawing********** for "+samp<<endl;   
    	
    TH1F* Element_50PU;
    TFile *bkg1 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_140PU_DiBoson_100_his.root");
    Element_50PU= (TH1F*) bkg1->Get(samp); 
      Element_50PU->SetLineStyle(3);
	Element_50PU->SetTitle("deneem");
      Element_50PU->SetLineWidth(1);
      Element_50PU->SetLineColor(kRed);
      Element_50PU->SetFillColor(kRed);
    Element_50PU->SetMinimum(0.01);
	
    TH1F* Element_NoPU;
    TFile *bkg2 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_140PU_BosonJets_100_his.root");
    Element_NoPU= (TH1F*) bkg2->Get(samp);
	Element_50PU->SetTitle("deneem");
    Element_NoPU->SetLineStyle(3);
    Element_NoPU->SetLineWidth(1);
    Element_NoPU->SetFillColor(kWhite+10);
    Element_NoPU->SetMinimum(0.01);

    TH1F* Element_140PU;
    TFile *bkg3 = TFile::Open("/home/cakir/NtuplerAnalyzer/DeepSingle+DelphMET_140PU_TopJets_100_his.root");
    Element_140PU= (TH1F*) bkg3->Get(samp);
	Element_50PU->SetTitle("deneem");
    Element_140PU->SetLineStyle(3);
    Element_140PU->SetLineWidth(1);
   Element_140PU->SetFillColor(kGreen);
   Element_140PU->SetLineColor(kGreen);
    Element_140PU->SetMinimum(0.01);

	
      TCanvas* c1 = new TCanvas("c1","Latex",600,700);
//95
  TPaveText *pt = new TPaveText(75,140.59743,1000,400);
   pt->AddText("PU dependecies for LHC and HL-LHC");
   pt->SetTextSize(0.05);
   pt->SetBorderSize(0);
   pt->SetFillColor(0);	

     TText *th1 = new TText(-200,5,"# Events"); 
 th1->SetTextAlign(11); th1->SetTextSize(0.05);


	
 
	th1->SetTextAngle(90);
	TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
	pad1->SetLogy();
	pad1->SetBottomMargin(0.04);
//	pad1->SetMinimum(0.01);
 	pad1->Draw();
	
	pad1->cd();

	Element_140PU->Draw();
	Element_50PU->Draw("same");
	Element_NoPU->DrawCopy("same");
	Element_140PU->GetXaxis()->SetRangeUser(0,1500);
        pt->Draw();//histogram çizdirmeden önceye koyarsam bu satırı histogram->draw() deyince bunu çizdirmiyor
	th1->Draw();
	c1->cd(); //go back t main canvas before defining pad2


TPaveText *pt2 = new TPaveText(1100,-0.25,4500,-0.4);
   pt2->AddText("M_{T}  GeV");
   pt2->SetTextSize(0.12);
   pt2->SetBorderSize(0);
   pt2->SetFillColor(0);


	TPad *pad2 = new TPad("pad2","pad2",0,0.05,1,0.3);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.2);
	pad2->SetGridx();
	pad2->Draw();

	pad2->cd();
	c1->Update();//update işlemi zorunlu
//TLine x1,y1,x2,y2
	 TLine *l=new TLine(0.0,1.0,1500.0,1.0);
         l->SetLineColor(kBlue);
	l->SetLineStyle(7);
 	
	TH1F *Clone_50PU = (TH1F*)Element_50PU->Clone("Clone_50PU");
	TH1F *Clone_140PU = (TH1F*)Element_140PU->Clone("Clone_140PU");
	TH1F *Clone_NoPU = (TH1F*)Element_NoPU->Clone("Clone_NoPU");
	TH1F *Clone_NoPU2 = (TH1F*)Element_NoPU->Clone("Clone_NoPU2");
	Clone_NoPU->SetLineColor(kRed);
	Clone_NoPU->SetLineWidth(3);
	Clone_NoPU2->SetLineColor(kGreen);
	Clone_NoPU2->SetLineWidth(3);

	Clone_NoPU->Divide(Element_50PU);
	Clone_NoPU2->Divide(Element_140PU);
        Element_NoPU->Divide(Element_NoPU);
        Element_NoPU->SetStats(0);
        Element_NoPU->SetMarkerStyle(1);
	Element_NoPU->SetLineStyle(1);
   	
        Element_NoPU->Draw("e2");
        Clone_NoPU->Draw("same");
        Clone_NoPU2->Draw("same");
	    l->Draw(); 
        pt2->Draw();
	Element_NoPU->GetXaxis()->SetRangeUser(0,1500);	
	Element_NoPU->GetYaxis()->SetLabelSize(0.065);
        Element_NoPU->GetXaxis()->SetLabelSize(0.065);
  	Element_NoPU->GetXaxis()->SetLabelOffset(0.02);
	

    TLegend *pl = new TLegend(0.7, 0.65, 0.9, 0.8); 

    pl->SetTextSize(0.055); //0.03 idi
    pl->SetFillColor(0);
    pl->SetBorderSize(0);
    pl->AddEntry(Element_140PU, "140PU","lpf" );
    pl->AddEntry(Element_50PU, "50PU","lpf");
    pl->AddEntry(Element_NoPU, "NoPU",  "lpf");
    pl->SetFillColor(0);
    pl->SetLineColor(0.5);
    pad1->cd();
    pl->Draw("same");

    TLegend *pl2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    pl2->SetTextSize(0.08); //0.03 idi
    pl2->SetFillColor(0);
    pl2->SetBorderSize(0);
    pl2->AddEntry(Clone_NoPU2, "NoPU/140PU","lpf");
    pl2->AddEntry(Clone_NoPU, "NoPU/50PU","lpf");
    pad2->cd();
    pl2->Draw("same");

}


