#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TClonesArray.h"
#include "TBranch.h"

void AnalyzeTree ()
{
  gROOT->Reset();
  gSystem->Load("/home/ilknur/Delphes-3.3.0/libDelphes.so");
  TFile *f=new TFile("/home/ilknur/hepmcout41.root");
  TTree *intree=f->Get("Delphes");
  //TFile *f2=new TFile("mytree.root","RECREATE");
  TTree *tree= new TTree("mytree","test tree");
  
  
  ExRootTreeReader *treeReader=new ExRootTreeReader(intree);
  Long64_t entries=treeReader->GetEntries();
  TClonesArray *branchMuon= treeReader->UseBranch("Muon");
  TClonesArray *branchElectron= treeReader->UseBranch("Electron");
  TClonesArray *branchJet= treeReader->UseBranch("Jet");

  TH1F *histJetpt=new TH1F("JetPT","JetP_{T}",50,0.0,100);
  TH1F *histmuonpt=new TH1F("MuonPT","MuonP_{T}",200,0,400);
  TH1F *histelectronpt=new TH1F("ElectronPT","ElectronP_{T}",50,0.0,100.0);
  TH1F *histJetETA=new TH1F("JetETA","Jet_{ETA}",50.0,0.0,20);
  TH1F *histmuonETA=new TH1F("MuonETA","Muon_{ETA}",50,0,400);
  TH1F *histelectronETA=new TH1F("ElectronETA","Electron_{ETA}",50,0.0,100.0);

  for(Int_t i=0;i<entries;++i)
  {
	treeReader->ReadEntry(i);
	        
		//	for(Int_t a=0;a<branchMuon->GetEntries();++a){
		//	
		//		Muon *muon=(Muon*)branchMuon->At(a);
		//		if(muon->PT>20.0){  
		//		histmuonpt->Fill(muon->PT);}
				//if(muon->Eta<2.1){	
		//		histmuonETA->Fill(muon->Eta);}
		//			}
		//	}
		//	histmuonETA->Draw();	
		//	histmuonpt->Draw();			
		//	for(Int_t a=0;a<branchElectron->GetEntries();++a) 			
		//	{
		//		Electron *electron=(Electron*)branchElectron->At(a);
		//		if(electron->PT>30.0){ 			
		//		histelectronpt->Fill(electron->PT);}
		//		if(electron->Eta<2.5){		
		//		histelectronETA->Fill(electron->Eta);	}
		//		//histelectronpt->Draw();
		//		//histelectronETA->Draw();
		//		}
		//	}
		
			for(Int_t a=0;a<branchJet->GetEntries();++a)    	
			{
				Jet *jet=(Jet*)branchJet->At(0);
				if(jet->PT>40.0 ){				
				histJetpt->Fill(jet->PT);
				//histJetpt->Draw();
				TBranch *branch=tree->Branch("Jets","TH1F",&histJetpt);
				}
				if(jet->Eta<3.0){
				histJetETA->Fill(jet->Eta);					
				//histJetETA->Draw();				
				}
				
			}			
		
  }

}
