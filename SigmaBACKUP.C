#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TClonesArray.h"
#include "TBranch.h"
//#include "TLorentzVector.h"
#include <vector>
#include "TSystem.h"
#include "TMath.h"
#include "TCanvas.h"
#include <fstream>
#include <iostream>
#include <string>
#include "TChain.h"
#include "TString.h"
#include <iostream>
#include "TLeaf.h"
#include "TTreeFormula.h"
#include "TLeafElement.h"
//asagidaki fonksiyon degerlerinin onune yildiz koyma SAKINNN!!!
void SigmaBACKUP(TString analysis,double value)
{
  gROOT->SetStyle("Plain");
//  gSystem->Load("/usr/local/bin/root-5.34.34/lib/libvectorDict.so");
  gSystem->Load("/home/cakir/Programs/Delphes-3.3.0/libDelphes.so");
  gSystem->Load("/usr/local/bin/root-5.34.34/lib/libPhysics.so");
//-----------Convert value to string----------------------------
	TString de=" ";
	TString da=" ";
//----------converting part to string-----------------------
	de=Form("%f",value);
//---------taking the first 3 characters of de string--------
	da=de(0,3);
	  TFile *f2=new TFile(analysis+"_"+da+".root","RECREATE");
	 TTree *TreeSigma= new TTree("TreeSigma","deneme Tree");  //sonra isimleri degistir
//----------------------------Define branch of created trees--------------------------------------------
	double val=0;
	double MET=0;
	double MT=0;
        double MT2W=0;
	double HT=0;
	vector <double> *analysis_v;
	vector <double> *MET_v;
	vector <double> *MT_v;
	vector <double> *HT_v;
	vector <double> *MT2W_v;
	TreeSigma->Branch(analysis,&analysis_v);
	TreeSigma->Branch("MET",&MET_v);
	TreeSigma->Branch("MT",&MT_v);
	TreeSigma->Branch("HT",&HT_v);
        TreeSigma->Branch("MT2W",&MT2W_v);
//----------------------------------------------------------------------------------------------------------
//---------------------take the values for brach x for entry n from Existing root file------------------------
       TFile *f=new TFile("TMVA.root");//bunu script olarak ça?~_r pyhton script tüm root dosyaların üzerinden dummy
       TTree *Tree1=(TTree*)f->Get("TrainTree");
       ExRootTreeReader *treeReader=new ExRootTreeReader(Tree1);
       Long64_t entries=treeReader->GetEntries();
       	TLeaf *leaf=Tree1->GetLeaf(analysis);
	TLeaf *MET_L=Tree1->GetLeaf("MET");
	TLeaf *MT_L=Tree1->GetLeaf("MT");
        TLeaf *MT2W_L=Tree1->GetLeaf("MT2W");
	TLeaf *HT_L=Tree1->GetLeaf("HT");
	for(int i=0;i<entries;i++){
		leaf->GetBranch()->GetEntry(i);
		val=leaf->GetValue();
		MET_L->GetBranch()->GetEntry(i);
       		MET=MET_L->GetValue();
		MT_L->GetBranch()->GetEntry(i);
        	MT=MT_L->GetValue();
       		MT2W_L->GetBranch()->GetEntry(i);
       		MT2W=MT2W_L->GetValue();
		HT_L->GetBranch()->GetEntry(i);
        	HT=HT_L->GetValue();
		if(val<value){
			analysis_v->push_back(val);
			MET_v->push_back(MET); 
			MT2W_v->push_back(MT2W);
			MT_v->push_back(MT);
		 	HT_v->push_back(HT); 
		 }
	}
       TreeSigma->Fill();
//	TreeSigma->Draw("BDT_v");
	f2->Write();

}

