#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TClonesArray.h"
#include "TBranch.h"
void ADDHisto()
{
//gROOT->Reset(); do not use Reset in a named macro
 
//TCanvas *c1 = new TCanvas("c1", "Adding histograms", 10,10, 800, 800);
TFile *f = new TFile("new.root","recreate");
TFile *f0 = new TFile("/home/cakir/TMVA-v4.2.0/test/TMVA.root","READ");
TFile *f1 = new TFile("/home/cakir/TMVA-v4.2.0/test/300lumi_ML1_50pu.root","READ");
TTree* f0T= (TTree*)f1->Get("TreeS");
TTree* f1T= (TTree*)f1->Get("TreeB");
f0T->Project("METS","MET");
f1T->Project("METB","MET");
TH1F *METS=(TH1F*)gROOT->FindObject("METS");
TH1F *METB=(TH1F*)gROOT->FindObject("METB");
//TH1F* METS_Combine = METS.Clone("METS_Combine");
//METS_Combine->Add(METB);
//METS_Combine->Draw();
//METS_Combine->Write();
METB->Add(METS);
METB->Draw();
f->Write();
}
