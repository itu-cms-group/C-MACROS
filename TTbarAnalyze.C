#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TClonesArray.h"
#include "TBranch.h"
//struct JJet{
  //       Int_t njets;
    //     Float_t eta[20];
      //   Float_t pt[12];
  	// };


void TTbarAnalyze ()
{	
  gROOT->Reset();
  //gSystem->Load("/home/ilknur/root/lib/libTree.so");
  gSystem->Load("/home/cakir/Programs/Delphes-3.3.0/libDelphes.so");
  TFile *f=new TFile("/home/cakir/Programs/Delphes-3.3.0/delphes_outttbar.root");
  TTree *TTbarTree=f->Get("Delphes");
  TFile *f2=new TFile("mytree.root","RECREATE");
  TTree *TreeS= new TTree("TreeS","Signal Tree");
  TTree *TreeB= new TTree("TreeB","Background Tree");
  //TTbarTree=GetTree->CloneTree(0);
  ExRootTreeReader *treeReader=new ExRootTreeReader(TTbarTree);
  Float_t Jetpt,JetEta,Muonpt,MuonEta,Electronpt,ElectronEta,Scalarht; 
  Long64_t entries=treeReader->GetEntries();
  TClonesArray *branchMuon= treeReader->UseBranch("Muon");
  TClonesArray *branchElectron= treeReader->UseBranch("Electron");
  TClonesArray *branchJet= treeReader->UseBranch("Jet");
  TClonesArray *branchScalarht= treeReader->UseBranch("ScalarHT");
//Histogram çizdirmek istenirse aşağıdaki yorum satırları koda dönüştürülür
  //TH1F *histJetpt=new TH1F("JetPT","JetP_{T}",50,0.0,100);
  //TH1F *histmuonpt=new TH1F("MuonPT","MuonP_{T}",200,0,400);
  //TH1F *histelectronpt=new TH1F("ElectronPT","ElectronP_{T}",50,0.0,100.0);
  //TH1F *histJetETA=new TH1F("JetETA","Jet_{ETA}",50.0,0.0,20);
  //TH1F *histmuonETA=new TH1F("MuonETA","Muon_{ETA}",50,0,400);
  //TH1F *histelectronETA=new TH1F("ElectronETA","Electron_{ETA}",50,0.0,100.0);
 

   TreeS->Branch("JetEta",&JetEta,"JetEta/F");
   TreeS->Branch("Jetpt",&Jetpt,"Jetpt/F") ; 
   TreeS->Branch("Scalarht",&Scalarht,"Scalarht/F");
   TreeS->Branch("Muonpt",&Muonpt,"Muonpt/F");
   TreeS->Branch("MuonEta",&MuonEta,"MuonEta/F");
   TreeS->Branch("ElectronEta",&ElectronEta,"ElectronEta/F");
   TreeS->Branch("Electronpt",&Electronpt,"Electronpt/F"); 
//TreeBackground için dal oluşturmak
   TreeB->Branch("JetEta",&JetEta,"JetEta/F");
   TreeB->Branch("Jetpt",&Jetpt,"Jetpt/F") ; 
   TreeB->Branch("Scalarht",&Scalarht,"Scalarht/F");
   TreeB->Branch("Muonpt",&Muonpt,"Muonpt/F");
   TreeB->Branch("MuonEta",&MuonEta,"MuonEta/F");
   TreeB->Branch("ElectronEta",&ElectronEta,"ElectronEta/F");
   TreeB->Branch("Electronpt",&Electronpt,"Electronpt/F"); 

for(Int_t i=0;i<entries;++i)
  {
	treeReader->ReadEntry(i);

		for(Int_t a=0;a<branchJet->GetEntries();a++)    	
			{
				Jet *jet=(Jet*)branchJet->At(a);
				if(jet->PT>40.0){
				//Struct yapısı kullanmak istenirse aşağıdakiler koda dönüştürülebilir
				//jet.njets = a;
				//jet.pt[a]= jet->PT;
				//jet.eta[a] = jet->Eta();				
				Jetpt=jet->PT;
				//Histogram çizdirmek için				
				//histJetpt->Fill(jet->PT);
				//Jetpt=histJetpt->Fill(jet->PT);	
				
				}
				
				//histJetpt->Draw();
				if(jet->Eta<3.0 && jet->Eta>-3.0) { //abs bak!!
				//histJetETA->Fill(jet->Eta);
				//jet.eta[a] = jet->Eta;
				JetEta=jet->Eta;				
				//histJetETA->Draw();				
			//	branch1_2->Fill();				
				TreeS->Fill();				
				}			
				TreeS->Fill();
			}
	        	
			for(Int_t a=0;a<branchMuon->GetEntries();++a){
			
				Muon *muon=(Muon*)branchMuon->At(a);
				if(muon->PT>20.0){  
				Muonpt=muon->PT;				
				//histmuonpt->Fill(muon->PT);
				}
				//
				if(muon->Eta<2.1 && muon->Eta>-2.1){	
				//histmuonETA->Fill(muon->Eta);
				MuonEta=muon->Eta;
				}
				TreeS->Fill();
			}
					
			for(Int_t a=0;a<branchElectron->GetEntries();++a) 			
			{
				Electron *electron=(Electron*)branchElectron->At(a);
				if(electron->PT>30.0){ 
				Electronpt=electron->PT;			
				//histelectronpt->Fill(electron->PT);
								
				}
				
				if(electron->Eta<2.5 && electron->Eta>-2.5){
				ElectronEta=electron->Eta;		
				//histelectronETA->Fill(electron->Eta);	
				}
				TreeS->Fill();
			}
			for(Int_t a=0;a<branchScalarht->GetEntries();++a) 			
			{
				ScalarHT *sht=(ScalarHT*)branchScalarht->At(a);
				//if(sht->HT>30.0){ 
				Scalarht=sht->HT;			
				//histelectronpt->Fill(electron->PT);
								
				//}
				
				
				TreeS->Fill();
			}		
  }
for(Int_t i=0;i<entries;++i)
  {
	treeReader->ReadEntry(i);

		for(Int_t a=0;a<branchJet->GetEntries();a++)    	
			{
				Jet *jet=(Jet*)branchJet->At(a);
				if(jet->PT>30.0){
				//Struct yapısı kullanmak istenirse aşağıdakiler koda dönüştürülebilir
				//jet.njets = a;
				//jet.pt[a]= jet->PT;
				//jet.eta[a] = jet->Eta();				
				Jetpt=jet->PT;
				//Histogram çizdirmek için				
				//histJetpt->Fill(jet->PT);
				//Jetpt=histJetpt->Fill(jet->PT);	
				
				}
				
				//histJetpt->Draw();
				if(jet->Eta<4.0 && jet->Eta>-4.0) { //abs bak!!
				//histJetETA->Fill(jet->Eta);
				//jet.eta[a] = jet->Eta;
				JetEta=jet->Eta;				
				//histJetETA->Draw();				
			//	branch1_2->Fill();				
				TreeB->Fill();				
				}			
				TreeB->Fill();
			}
	        	
			for(Int_t a=0;a<branchMuon->GetEntries();++a){
			
				Muon *muon=(Muon*)branchMuon->At(a);
				if(muon->PT>10.0){  
				Muonpt=muon->PT;				
				//histmuonpt->Fill(muon->PT);
				}
				//
				if(muon->Eta<3 && muon->Eta>-3){	
				//histmuonETA->Fill(muon->Eta);
				MuonEta=muon->Eta;
				}
				TreeB->Fill();
			}
					
			for(Int_t a=0;a<branchElectron->GetEntries();++a) 			
			{
				Electron *electron=(Electron*)branchElectron->At(a);
				if(electron->PT>20.0){ 
				Electronpt=electron->PT;			
				//histelectronpt->Fill(electron->PT);
								
				}
				
				if(electron->Eta<3 && electron->Eta>-3){
				ElectronEta=electron->Eta;		
				//histelectronETA->Fill(electron->Eta);	
				}
				TreeB->Fill();
			}
			for(Int_t a=0;a<branchScalarht->GetEntries();++a) 			
			{
				ScalarHT *sht=(ScalarHT*)branchScalarht->At(a);
				//if(sht->HT>30.0){ 
				Scalarht=sht->HT;			
				//histelectronpt->Fill(electron->PT);
								
				//}
				
				
				TreeB->Fill();
			}		
  }
f2->Write();
}
