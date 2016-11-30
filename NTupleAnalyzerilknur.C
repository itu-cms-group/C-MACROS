//  -- previous ECFA version -- _P as paper vesion
//undfined DelphMT2W isoTracksP DelphMT
//         MT2W0                MT2W0
///////////////// naturalSUSY - nS /////////////////////
#include "NtupleTools3.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TFile.h>
#include <TBranch.h>

using namespace std;

void NTupleAnalyzerilknur(TString list, TString outname,bool useW=true){
	gROOT->Reset();
	//gROOT->ProcessLine("#include<vector>");
        bool DELPH = true;// DelphMet

	TObjArray* arr = list.Tokenize(" ");
	int size=arr->GetEntries();
	if(size%2!=0) {
        	cout<<"unbalance file/weight list: "<<list<<endl;
        	exit(0);
	}
	vector<TString> files;
	vector<double> weights;
	for(int i=0;i<size;i+=2){
        	files.push_back( arr->At(i)->GetName() );
        	weights.push_back( atof( arr->At(i+1)->GetName() ) );
	}

//---------Define tree variables-------------------------------
	/*vector<double> ElectronPt;
	vector<double> ElectronEta;
	vector<double> MuonPt;
	vector<double> MuonEta;*/
	vector<double> HT_CUT;
	vector<double> MET_CUT;
	vector<double> MT_CUT;
//	vector<double> LepPT_CUT;
        vector<double> MT2W_CUT;
//	vector<double> JET_Multp;
//------------ML1 içi NoPU---------------------------------------------------
        double xsec1=6.92; //pb
        double Lumi=300000; //fb-1'den pb-1'e çevrilmiş hali 
        double EventSayi1=1000000;
        double ML1_NoPU_weight=(xsec1*Lumi)/EventSayi1;

//------------ML2 içinNoPU------------------------------------------------
        double xsec2=1.14; //pb 
        double EventSayi2=1000000;
        double ML2_NoPU_weight=(xsec2*Lumi)/EventSayi2;

//------------ML3 için-NoPU---------------------------------------------------
        double xsec3=1.82; //pb 
        double EventSayi3=1000000;
        double ML3_NoPU_weight=(xsec3*Lumi)/EventSayi3;

//------------ML4 için-----NOPU-----------------------------------------------
	double xsec4=0.61; //pb
	double EventSayi4=1940000; 
	double ML4_NoPU_weight=(xsec4*Lumi)/EventSayi4;

//-----------------ML2 50PU-----------------------------------------------
        double xsec5=1.19; //pb 
        double EventSayi5=890000;
        double ML2_50PU_weight=(xsec5*Lumi)/EventSayi5;
//-----------------ML1 50PU-----------------------------------------------
        double xsec6=1.19; //pb 
        double EventSayi6=1000000; //890000
        double ML1_50PU_weight=(xsec6*Lumi)/EventSayi6;
//-----------------ML2 140PU-----------------------------------------------
        double xsec7=1.19; //pb 
        double EventSayi7=879858; //890000
        double ML2_140PU_weight=(xsec7*Lumi)/EventSayi7;

//----------------------Normalizing--------------------------------------------
       Double_t norm = 1;
       //h->Scale(norm, "width");


	//Define an outputTree:ilknur
	//TFile *OutFile=new TFile("OutTreeNtupleilknur.root","RECREATE");
	//TBranch *MuPT;
	TTree *TreeS= new TTree("TreeS","Signal Tree");
	TTree *TreeB= new TTree("TreeB","Background Tree");
	/*TreeS->Branch("MuonPt",&MuonPt);
	OutTree->Branch("MuonEta",&MuonEta);
	OutTree->Branch("ElectronPt",&ElectronPt);
	OutTree->Branch("ElectronEta",&ElectronEta);*/
	TreeS->Branch("HT",&HT_CUT);
	TreeS->Branch("MET",&MET_CUT);
	TreeS->Branch("MT",&MT_CUT);
//	TreeS->Branch("LepPT",&LepPT_CUT);
        TreeS->Branch("MT2W",&MT2W_CUT);
//	TreeS->Branch("JET_Multp",&JET_Multp);
	TreeB->Branch("HT",&HT_CUT);
	TreeB->Branch("MET",&MET_CUT);
	TreeB->Branch("MT",&MT_CUT);
//	TreeB->Branch("LepPT",&LepPT_CUT);
	TreeB->Branch("MT2W",&MT2W_CUT);
//	TreeB->Branch("JET_Multp",&JET_Multp);
//---------------------------------------------------------------------------------------------------       
	 //at 1lep 4jets 1b
        TH1F* aDphi      = new TH1F("aDphi","#Delta#phi",100,0,4);
        TH1F* aDelphDphi = new TH1F("aDelphDphi","Delphes #Delta#phi",100,0,4);

        TH1F* aMET       = new TH1F("aMET","MET",100,0,3000);
        TH1F* aDelphMET  = new TH1F("aDelphMET","Delphes MET",100,0,3000);

        TH1F* aMT        = new TH1F("aMT","MT",100,0,2000);
        TH1F* aDelphMT   = new TH1F("aDelphMT","Delphes MT",100,0,500);
        TH1F* aMT2       = new TH1F("aMT2","MT",100,0,2000);
        TH1F* aDelphMT2  = new TH1F("aDelphMT2","Delphes MT",100,0,500);


        TH1F* aMT2W       = new TH1F("aMT2W","MT2W 1,2b only",20,0,600);
        TH1F* aDelphMT2W  = new TH1F("aDelphMT2W","Delphes MT2W 1,2b only",100,0,500);
        TH1F* aMT2W2      = new TH1F("aMT2W2","MT2W 1,2b only",100,0,1000);
        TH1F* aDelphMT2W2 = new TH1F("aDelphMT2W2","Delphes MT2W 1,2b only",100,0,500);

        TH1F* aHT        = new TH1F("aHT","HT40",400,0,4000);
        TH1F* aLepPt     = new TH1F("aLepPt","single lep Pt",200,0,1000);
        TH1F* aLepEta     = new TH1F("aLepEta","single lep Eta",100,-3,3);
        TH1F* a1JetPt    = new TH1F("a1JetPt","highest jet Pt",50,0,2000);
        TH1F* a1bJetPt   = new TH1F("a1bJetPt","highest bjet Pt",50,0,3000);
        TH1F* an1bJetPt   = new TH1F("an1bJetPt","2bd and more highest bjets Pt",100,0,2000);

	TH1F* hMET   = new TH1F("hMET","before DMET<=250 cut",50,0,2500);
	TH1F* hMET_2   = new TH1F("hMET_2","after DMET<=250 cut",50,0,2500);
	TH1F* MET_1   = new TH1F("E_{T}^{miss}_1 [GeV]","MET before cuts",200,0,2000);
	TH1F* MET_2   = new TH1F("E_{T}^{miss}_2 [GeV]","after HT<500 and DMET>250 cut",200,0,2000);
	TH1F* MET_3   = new TH1F("E_{T}^{miss} [GeV] ","PU dependencies for LHC and HL-LHC",200,0,2000);
//	TH1F* MET_hist   = new TH1F("MET_hist","MET after all cuts",200,0,2000);

	TH1F* MT_1   = new TH1F("M_{T}_1 [GeV]","MT before cuts",100,0,2000);
        TH1F* MT_2   = new TH1F("M_{T}_2 [GeV]","after HT<500 and DMET<=250 cut",100,0,2000);
        TH1F* MT_3   = new TH1F("M_{T} [GeV]","PU dependencies for LHC and HL-LHC",100,0,3000);


	TH1F* MT2W_1   = new TH1F("M_{T2}^{W}_1 [GeV]","before cuts",100,0,1000);
        TH1F* MT2W_2   = new TH1F("M_{T2}^{W}_2 [GeV]","after HT<500 and DMET<=250 cut",100,0,1000);
        TH1F* MT2W_3   = new TH1F("M_{T2}^{W} [GeV]","PU dependencies for LHC and HL-LHC",100,200,600);

	TH1F* hMT    = new TH1F("hMT","before MT>200 cut",100,0,2000);
	TH1F* hMT_2    = new TH1F("hMT_2","after MT>200 cut ",100,0,2000);
	TH1F* hMT2Wpre  = new TH1F("hMT2Wpre","MT2W w/o MET,MT req.",100,0,500);
        TH1F* hMT2WDelph_pre  = new TH1F("hMT2WDelph_pre","MT2W w/o MET,MT req. from Delph",100,0,500);
	TH1F* hMT2W  = new TH1F("hMT2W","MT2W",100,0,500);
        TH1F* hMT2W_2  = new TH1F("hMT2W_2","after MT2W>250 cut",100,0,500);
	TH1F* hMETMeff  = new TH1F("hMETMeff","MET/(MET+HT)",100,0,1);
	TH1F* hHT    = new TH1F("hHT","HT40 before HT>500 cut",40,0,5000);
	TH1F* hHT_2   = new TH1F("hHT_2","HT40 after HT>500",50,0,5000);
	TH1F* HT_1    = new TH1F("HT [GeV]_1","BeforeCuts",100,0,7000);
	TH1F* HT_2    = new TH1F("HT [GeV]_2","after DMET>250 cut",100,0,7000);
	TH1F* HT_3    = new TH1F("HT [GeV]","PU dependencies for LHC and HL-LHC",100,0,7000);

	TH1F* hDphi  = new TH1F("hDphi","#Delta#phi",100,0,4);
        TH1F* hDphi_2  = new TH1F("hDphi_2","#Delta#phi<=0.4",100,0,4);
	TH1F* hDelphdphi  = new TH1F("hDelphdphi","#Delta#phi",100,0,4);
        TH1F* hDelphdphi_2  = new TH1F("hDelphdphi_2","#Delta#phi>=0.4",100,0,4);	
	TH1F* hAllHT = new TH1F("hAllHT","before cuts HT40",100,0,5000);
	TH1F* hAllLepPt = new TH1F("hAllLepPt","singlw lep Pt - all",40,0,2000);

        TH1F* hElPt = new TH1F("hElPt","Electron Pt",50,0,3000);
        TH1F* hMuPt = new TH1F("hMuPt","Muon Pt",50,0,3000);
        TH1F* hElEta = new TH1F("hElEta","Electron Eta",100,-2.5,2.5);
        TH1F* hMuEta = new TH1F("hMuEta","Muon Eta",100,-3,3);
	TH1F* aElPt = new TH1F("Electron P_{T} [GeV]","after Quality Cuts",50,0,3000);
        TH1F* aMuPt = new TH1F("Muon P_{T} [GeV]","after Quality Cuts",50,0,3000);
        TH1F* aElEta = new TH1F("#eta_{e^{-}}","after Quality Cuts",100,-2.5,2.5);
        TH1F* aMuEta = new TH1F("#eta_{#mu}","after Quality Cuts",100,-2.5,2.5);
	

        TH1F* allElPt = new TH1F("allElPt","Electron Pt after All Cuts",40,0,1000);
        TH1F* allMuPt = new TH1F("allMuPt","Muon Pt after All Cuts",40,0,1000);
        TH1F* allElEta = new TH1F("allElEta","Electron Eta after All Cuts",100,-2.5,2.5);
        TH1F* allMuEta = new TH1F("allMuEta","Muon Eta after All Cuts",100,-2.5,2.5);


	TH1F* hLepPtJb = new TH1F("Lepton P_{T} [GeV]","PT of lepton",400,0,4000);
	TH1F* hLepPtM = new TH1F("hLepPtM","single lep Pt - jet + MET",100,0,1000);
	TH1F* hLepPtMM = new TH1F("hLepPtMM","single lep Pt - jet + MET +Mt+MT2W",200,0,1000);
	TH1F* hLepEtaJb = new TH1F("#eta_{Lep}","single lep eta - jet req",100,-3.0,3.0);
	TH1F* hLepEtaM = new TH1F("hLepEtaM","single lep eta - jet + MET",100,-4.5,4.5);
	TH1F* hLepEtaMM = new TH1F("hLepEtaMM","single lep eta - jet + MET +Mt+MT2W",100,-4.5,4.5);

	TH1F* LepPtt = new TH1F("P_{T_{Lep}}","after Quality Cuts",100,0,1000);


        TH1F* abasym   = new TH1F("abasym","(bjetsPt-lepPt)/(bjetsPt+lepPt)",100,-1,1);
        TH1F* hbasym   = new TH1F("hbasym","(bjetsPt-lepPt)/(bjetsPt+lepPt)",100,-1,1);
        TH1F* aC      = new TH1F("aC","centrality",100,0,5);
        TH1F* hC      = new TH1F("hC","centrality",100,0,5);
	
	// nS //
	TH1F* atop = new TH1F("atop","topness",100,-21,21);
	TH1F* atop0 = new TH1F("atop0","topness Delph MET",100,-21,21);
	TH1F* htop = new TH1F("htop","topness",100,-21,21);
	TH1F* htop0 = new TH1F("htop0","topness Delph MET",100,-21,21);

	TH1F* htHT    = new TH1F("htHT","topness HT40",100,0,5000);
	TH1F* htDphi  = new TH1F("htDphi","topness #Delta#phi",100,0,4);

	TH1I* hNel = new TH1I("hNel","N good(30) el",10,0,10);
	TH1I* hNel_2 = new TH1I("hNel_2","Single Lepton check",10,0,10);
	TH1I* hNmu = new TH1I("hNmu","N good(30) mu",10,0,10);
	TH1I* hNlep = new TH1I("hNlep","N good(30) mu+el",10,0,10);
        TH1I* hNtj = new TH1I("hNtj","N good(40), before njtes>4",15,0,15);
	TH1I* hNtj_2 = new TH1I("hNtj_2","N jets>3",15,0,15);
	TH1I* hNbjet = new TH1I("hNbjet","N b jets",15,0,15);
        TH1I* hNbjet_2 = new TH1I("hNbjet_2","#bjet after (Nbjet<1||Nbjet>2)",15,0,15);

	EasyChain* tree = new EasyChain("delphTree");
	
	for(unsigned i=0;i<files.size();i++){
       		tree->AddSmartW(files[i],weights[i]);
		cout<<"add: "<<files[i]<<" "<<weights[i]<<endl;
	}

	int Nevents=tree->GetEntries();
	cout<<">>>>>>>>>>>>>>>>>>>>>>> total number of events:\t" << Nevents <<endl;

	// CutFlow variables
	const int CutNumb = 25;
/*
	const char * CutList[CutNumb] = {"Presel","sngl. lep.","tau veto",
					 "nJets >= 3","nJets >= 4","bjets == 1/2",
                                         "MET>500","dphi12 > 0.5",
					 "HT>1000",
                                         "MT>120",
                                         "--MT2W>250",
                                         " HT>1250"," HT>1500"," Meff>0.2"," Meff>0.3",
					 " top=9.5 ",
                                         " basym>-0.2",
                                         " HT>1250"," HT>1500"," Meff>0.2"," Meff>0.3",
                                         "C<3"
                                         " HT>1250"," HT>1500"," Meff>0.2"," Meff>0.3",
                                         };
*/
	const char * CutList[CutNumb] = {"Presel","sngl. lep.","tau veto",
					 "nJets >= 3","nJets >= 4","bjets == 1/2",
                                         "MET>250","dphi12 > 0.5",
					 "HT>500",
                                         "MT>200",
                                         "--MT2W>250",
                                         " MT2W>250","MT2W> 250"
                                         };
	double CFCounter[CutNumb];
	int   iCFCounter[CutNumb];

	for (int i=0;i < CutNumb; i++){
	  CFCounter[i] = 0;
	 iCFCounter[i] = 0;
	}
	TH1D* CutFlow= new TH1D("CutFlow","Cut Flow",CutNumb,0.5,CutNumb+0.5);
	// label bins
        for(int cj = 0; cj < CutNumb; cj++)
              CutFlow->GetXaxis()->SetBinLabel(cj+1,CutList[cj]);
              //double muonpt=1;
	//MuonPt.clear();
	for(int entry=0; entry < Nevents; entry+=1){

		/*MuonPt.clear();
		MuonEta.clear();
		ElectronEta.clear();
		ElectronPt.clear();*/
		HT_CUT.clear();
		MET_CUT.clear();
		MT_CUT.clear();
//		LepPT_CUT.clear();
//		JET_Multp.clear();
		MT2W_CUT.clear();
		progressT();
		double fw = tree->GetEntryW(entry); // the applied with AddSmartW for the current file/dir

		double EvWeight = 1;
		if(useW) EvWeight = tree->Get(EvWeight,"EventWeight");
		EvWeight *= fw * 1000;

//		double HT   = tree->Get(HT,"HT"); 
		double HT   = tree->Get(HT,"HT"); 
		
		hAllHT->Fill(HT,EvWeight);
		
		// 0. CF presel
		 CFCounter[0]+= EvWeight;
		iCFCounter[0]++;
		
		std::vector<TLorentzVector> &Electrons = tree->Get(&Electrons,"Electrons");
		std::vector<TLorentzVector> &Muons = tree->Get(&Muons,"Muons");
		std::vector<int> &ElectronCh = tree->Get(&ElectronCh,"ElectronCh");
		std::vector<int> &MuonCh     = tree->Get(&MuonCh,"MuonCh");

		// 1. Lepton veto
		// etamin in ntupler 2.5, ptmin 10
		Int_t    Nel_tight = 0;
		Int_t    Nmu_tight = 0;
		Int_t    Nel_loose = Electrons.size();
		Int_t    Nmu_loose = Muons.size();
		// 
		TLorentzVector* Lep=0;	
		double lepPt=0;
		double lepEta=0;
		double ElPt=0;
                double ElEta=0;
		double MuPt=0;
                double MuEta=0;
//		double LepPt=0;
		//MuonPt.clear();
		for(Int_t i=0;i<Nmu_loose;++i) {
			if(fabs(Muons[i].Eta())<=2.4&&Muons[i].Pt()>30 ){
				Nmu_tight++;
				lepPt=Muons[0].Pt();
				lepEta=Muons[0].Eta();
			//	MuPt=Muons[0].Pt();
                          //      MuEta=Muons[0].Eta();
				Lep=&Muons[0];
				//cout<<"lepPt:"<<lepPt<<endl;
				/*MuonPt.push_back(lepPt);
				MuonEta.push_back(lepEta);*/
			}
		//cout<<"size of muon pt for icinde"<<MuonPt.size()<<endl;
		}
		/*OutTree->Fill();
		lepPt=0;
		lepEta=0;*/
		//cout<<"size of muon pt"<<MuonPt.size()<<endl;
		for(Int_t i=0;i<Nel_loose;++i) {
			if(fabs(Electrons[i].Eta())<=2.4&&Electrons[i].Pt()>30 ){	
				Nel_tight++;
				lepPt=Electrons[0].Pt();
				lepEta=Electrons[0].Eta();
			//	ElPt=Electrons[0].Pt();
                        //        ElEta=Electrons[0].Eta();
				Lep=&Electrons[0];
				/*ElectronEta.push_back(lepEta);
				ElectronPt.push_back(lepPt);*/
			}
		}
//		LepPt=ElPt+MuPt;
     		HT_1->Fill(HT,EvWeight);
		//Double_t norm=1;
                //Double_t scale=HT_1->GetAxis()->GetBinWidth(1)/(HT_1->GetIntegral());
		//HT_1->Scale(scale);
	//OutTree->Fill();
	//	hNmu->Fill(Nmu_tight,EvWeight);
	//	hNel->Fill(Nel_tight,EvWeight);
		hNlep->Fill(Nel_tight+Nmu_tight,EvWeight);

		// exactly 1 hard lepton, no other loose
		if(Nel_tight+Nmu_tight != 1) continue;
		hNel_2->Fill(Nel_tight+Nmu_tight,EvWeight);
		if(Nel_loose+Nmu_loose > 1) continue;
	//	hNel_2->Fill(Nel_tight,EvWeight);	
		 CFCounter[1]+= EvWeight;
		iCFCounter[1]++;
		//burayı ben komut satırına aldım Ntau'yu daha sonra kullanacağında aç
		/*int Ntaujet   = tree->Get(Ntaujet,"Ntaujet"); 
		if(Ntaujet>0) continue;
		*/ CFCounter[2]+= EvWeight;
		iCFCounter[2]++;

		hAllLepPt->Fill(lepPt,EvWeight);
//		hElPt->Fill(ElPt,EvWeight);
//		hElEta->Fill(ElEta,EvWeight);
//		hMuPt->Fill(MuPt,EvWeight);
//		hMuEta->Fill(MuEta,EvWeight);
		// 2. nJets >= 3,4
		vector<TLorentzVector> &Jets = tree->Get(&Jets,"Jets");
		int Njet_loose = tree->Get(Njet_loose,"Njet");
		int Njet_tight = 0;
		for(int i = 0;i  < Njet_loose; i++)
			if(Jets[i].Pt() > 40) Njet_tight++;

		hNtj->Fill(Njet_tight,EvWeight);
	/*	if(Njet_tight < 3) continue;
		 CFCounter[3]+= EvWeight;
		iCFCounter[3]++;
		

		if(Njet_tight < 4) continue;
		 CFCounter[4]+= EvWeight;
		iCFCounter[4]++;
	*/

		if(Njet_tight<=3) continue;	
		hNtj_2->Fill(Njet_tight,EvWeight);
	//	JET_Multp.push_back(Njet_tight);	
		// 3. Btag cut
		double bjetpt=0;
		int Nbjet = 0;
		bool hardB = false;
		vector<int> &JetB = tree->Get(&JetB,"JetB");		
		for(unsigned i=0;i<Jets.size();i++) {
			if(JetB[i]>0&&Jets[i].Pt() > 40) {
				if(Nbjet==0) {
					a1bJetPt->Fill(Jets[i].Pt());
					bjetpt=Jets[i].Pt();
				}
				else         an1bJetPt->Fill(Jets[i].Pt());
				Nbjet++;
			}
			if(JetB[i]>0&&Jets[i].Pt() > 250) hardB=true;
		}
		hNbjet->Fill(Nbjet,EvWeight);
//		if(Nbjet<1||Nbjet>2) continue;		
		 CFCounter[5]+= EvWeight;
		iCFCounter[5]++;
		hNbjet_2->Fill(Nbjet,EvWeight);
	//	HT_2->Fill(HT,EvWeight);
	//	hNmu->Fill(Nmu_tight,EvWeight);
        //       hNel->Fill(Nel_tight,EvWeight); 
		hLepPtJb->Fill(lepPt,EvWeight);
		hLepEtaJb->Fill(lepEta,EvWeight);
//		aMuPt->Fill(MuPt,EvWeight);
//		aMuEta->Fill(MuEta,EvWeight);
//		aElPt->Fill(ElPt,EvWeight);
//		aElEta->Fill(ElEta,EvWeight);
                // distributions at 1lep4jet1b
                
                double basym = (bjetpt-lepPt)/(bjetpt+lepPt);
                abasym->Fill(basym);
                
                vector<double> &JetMETdPhi = tree->Get(&JetMETdPhi,"JetMETdPhi");
                double dPhi = TMath::Min(JetMETdPhi[0],JetMETdPhi[1]);
                aDphi->Fill(dPhi,EvWeight);

                double DelphMET_Phi  = tree->Get(DelphMET_Phi,"DelphMET_Phi");
                double DelphdPhi = TMath::Min(acos(cos(Jets[0].Phi()-DelphMET_Phi)),acos(cos(Jets[1].Phi()-DelphMET_Phi)));
                aDelphDphi->Fill(DelphdPhi,EvWeight);
		
		// use of DelphMET or MET 
		/*
		double D_MET = 0.0;
		if(DELPH) D_MET  = tree->Get(D_MET,"DelphMET"); 
		else      D_MET  = tree->Get(D_MET,"MET");
		*/
                double MET  = tree->Get(MET,"MET");
		
                aMET->Fill(MET,EvWeight);
                MET_1->Fill(MET,EvWeight);
		double DMET  = tree->Get(DMET,"DelphMET");
                aDelphMET->Fill(DMET,EvWeight);
		//                
                double MT2W  = tree->Get(MT2W,"MT2W");
                aMT2W2->Fill(MT2W,EvWeight);
                if(MT2W>0&&MT2W<499)aMT2W->Fill(MT2W,EvWeight);
		MT2W_1->Fill(MT2W,EvWeight);
		// nS //
		// for naturalSUSY 
		// double DMT2W  = tree->Get(DMT2W,"DelphMT2W");
		// for susyhit 
		double DMT2W  = tree->Get(DMT2W,"MT2W0");
                
		aDelphMT2W2->Fill(DMT2W,EvWeight);
                if(DMT2W>0&&DMT2W<499)aDelphMT2W->Fill(DMT2W,EvWeight);

                double MT  = tree->Get(MT,"MT");
	        aMT2->Fill(MT,EvWeight);
                if(MT!=0)aMT->Fill(MT,EvWeight);
                MT_1->Fill(MT,EvWeight);
		// nS //

		// for naturalSUSY
		//double DMT  = tree->Get(DMT,"DelphMT");
		// for susyhit
		double DMT  = tree->Get(DMT,"MT0");
                aDelphMT2->Fill(DMT,EvWeight);
                if(DMT!=0)aDelphMT->Fill(DMT,EvWeight);
                aHT->Fill(HT,EvWeight);
                aLepPt->Fill(lepPt,EvWeight);
                aLepEta->Fill(lepEta,EvWeight);
                if(Jets[0].Pt()>40.) a1JetPt->Fill(Jets[0].Pt(),EvWeight);

		//burayı da komut satırına aldım ilknur
                //double top   = tree->Get(top,"top");
  /*              double top0  = tree->Get(top0,"top0");

//		if(top!=0)atop->Fill(top,EvWeight);
		if(top0!=0)atop0->Fill(top0,EvWeight);
*/		
		// Centrality
                double MET_Phi  = tree->Get(MET_Phi,"MET_Phi");
		double METx,METy;
		if(DELPH){
		METx = cos(DelphMET_Phi)*DMET;
	        METy = sin(DelphMET_Phi)*DMET;
		}else{
		METx = cos(MET_Phi)*MET;
	        METy = sin(MET_Phi)*MET;
		}
                TLorentzVector a=Jets[0]+(*Lep);
                TLorentzVector b=Jets[1]+(*Lep);
                TLorentzVector c=b;
                b.SetPx(b.Px()+METx);
                b.SetPy(b.Py()+METy);
                double deta1=fabs(a.Eta()-b.Eta());
                a.SetPx(b.Px()+METx);
                a.SetPy(b.Py()+METy);
                double deta2=fabs(a.Eta()-c.Eta());
                double C=TMath::Max(deta1,deta2);
		aC->Fill(C,EvWeight);
		if(DELPH){ if(DMT2W>0)hMT2WDelph_pre->Fill(DMT2W,EvWeight);}
		else if(MT2W>0) hMT2Wpre->Fill(MT2W,EvWeight);
		
		//  MET/Meff
		double Meff = DMET + HT;  //burasi MET+HT idi ben DMET yaptim
		if(DELPH)  Meff = DMET + HT;
		if(DELPH) { if(DMET>0)hMETMeff->Fill(DMET/Meff,EvWeight); } // don't remove the curly bracket!
		else  if(MET>0)hMETMeff->Fill(MET/Meff,EvWeight);
			
		// 4. MET cut
		if(DELPH){
		 hMET->Fill(DMET,EvWeight);
		 if(DMET<=250) continue; //MET<=350 
		}else{
		 hMET->Fill(MET,EvWeight);
		 if(MET<=250) continue; //MET<=350
		}
		 CFCounter[6]+= EvWeight;
		iCFCounter[6]++;
		hMET_2->Fill(DMET,EvWeight);
		HT_2->Fill(HT,EvWeight);

		// 6. dPhi  - had been inverted in first version
		if(DELPH){
		 hDelphdphi->Fill(DelphdPhi,EvWeight);
		 if(DelphdPhi <= 0.4) continue; //buradaki degerler 0.5 idi
		}else{
		 hDphi->Fill(dPhi,EvWeight);
		 if(dPhi <= 0.4) continue; //burdaki deger de 0.5 idi
		}
		hDphi_2->Fill(DelphdPhi,EvWeight);
		hDelphdphi_2->Fill(DelphdPhi,EvWeight);
		 CFCounter[7]+= EvWeight;
		iCFCounter[7]++;
		
		hLepPtM->Fill(lepPt,EvWeight);
		hLepEtaM->Fill(lepEta,EvWeight);

		// 8. HT cut
		
		hHT->Fill(HT,EvWeight);
		if(HT<500) continue; //HT<=800 idi sadece
		 CFCounter[8]+= EvWeight;
		iCFCounter[8]++;
		hHT_2->Fill(HT,EvWeight);
		MET_2->Fill(MET,EvWeight);
		MT_2->Fill(MT,EvWeight);
		MT2W_2->Fill(MT2W,EvWeight);
		// 5. MT cut
		//double MT  = tree->Get(MT,"MT");
		if(DELPH){
		 hMT->Fill(MT,EvWeight);  //bu satir DMT idi MT yaptim
		 if(MT<200) continue;  //DMT<=200 yi MT yaptim asagidaki 3 satiri ben komut satiri yaptim
		}/*else{
		 hMT->Fill(MT,EvWeight);
		 if(MT<=200) continue;
		}*/
		hMT_2->Fill(MT,EvWeight);
		 CFCounter[9]+= EvWeight;
		iCFCounter[9]++;
		
		double flagMT2W=true;
		/*if(DELPH){
		 if(DMT2W>0) hMT2W->Fill(DMT2W,EvWeight); 
	 	 if(DMT2W>170) flagMT2W=false; continue; //DMT2W<250
	 	}else{*/
		 if(MT2W>0) hMT2W->Fill(MT2W,EvWeight);
//MT2W cut'ını UYGULAMIYORUZ	  
//	 	 if(MT2W<250) /*flagMT2W=false;*/ continue; //MT2W<250
//		hNtj_2->Fill(Njet_tight,EvWeight);	 	
		//DONT CHANGE THE ORDER OF 3 LINES AS SEEN IN BELOW
		double LepPt=0;
//		LepPt=MuPt+ElPt;
		HT_3->Fill(HT,EvWeight);
		MET_3->Fill(DMET,EvWeight);
		MT_3->Fill(MT,EvWeight);
		MT2W_3->Fill(MT2W,EvWeight);
		hMT2W_2->Fill(MT2W,EvWeight);
		LepPtt->Fill(LepPt,EvWeight);
		MT_CUT.push_back(MT/*ML2_140PU_weight*/);
		HT_CUT.push_back(HT/*ML2_140PU_weight*/);
		MET_CUT.push_back(DMET/*ML2_140PU_weight*/);
//		LepPT_CUT.push_back(LepPt);
		MT2W_CUT.push_back(MT2W/*ML2_140PU_weight*/);
	//	JET_Multp.push_back(Njet_tight*EvWeight);
		TreeB->Fill();
	 	//if(flagMT2W)    //asagidaki 3 satiri komuta aldim
	 	/*if(DMT2W<250) continue;
		 CFCounter[10]+= EvWeight;
		iCFCounter[10]++;*/    
		hLepPtMM->Fill(lepPt,EvWeight);
		hLepEtaMM->Fill(lepEta,EvWeight);
		
//		allElPt->Fill(ElPt,EvWeight);
//		allElEta->Fill(ElEta,EvWeight);
//		allMuPt->Fill(MuPt,EvWeight);
//		allMuEta->Fill(MuEta,EvWeight);

		//HT_1->Scale(1,"width");
		//TreeB background doldurulacağında aşağıdaki 2 satırın command'i kaldırılır
		//MT2W_CUT.push_back(MT2W*1.45);
		//TreeB->Fill();	
	/*	if(top!=0)htop->Fill(top,EvWeight);
		if(top0!=0)htop0->Fill(top0,EvWeight);
		if(DELPH){
	 	 if(top0<=9.5) continue;
	 	}else{
	 	 if(top<=9.5) continue;
	 	}
		 CFCounter[11]+= EvWeight;
		iCFCounter[11]++;
		if(DMT2W>300){
		 CFCounter[12]+= EvWeight;
		iCFCounter[12]++;
		}
		if(DMT2W>350){
		 CFCounter[13]+= EvWeight;
		iCFCounter[13]++;
		}
               
	 	 if(top0<=12.5) continue;
		 CFCounter[14]+= EvWeight;
		iCFCounter[14]++;
*/
		// 21. topness cut
		
		
		// 22. b lep pt asym
		hbasym->Fill(basym,EvWeight);
	 	 if(basym<=-0.2) continue;
		if(HT>1250){
		 CFCounter[17]+= EvWeight;
		iCFCounter[17]++;
		}
		if(HT>1500){
		 CFCounter[18]+= EvWeight;
		iCFCounter[18]++;
		}
		if(MET/Meff>0.2){
		 CFCounter[19]+= EvWeight;
		iCFCounter[19]++;
		}
		if(MET/Meff>0.3){
		 CFCounter[20]+= EvWeight;
		iCFCounter[20]++;
		}
		
		if(C>=3) continue;
		 CFCounter[21]+= EvWeight;
		iCFCounter[21]++;
		
		if(HT>125){
		 CFCounter[22]+= EvWeight;
		iCFCounter[22]++;
		}
		if(HT>1500){
		 CFCounter[23]+= EvWeight;
		iCFCounter[23]++;
		}
		if(MET/Meff>0.2){
		 CFCounter[24]+= EvWeight;
		iCFCounter[24]++;
		}
		if(MET/Meff>0.3){
		 CFCounter[25]+= EvWeight;
		iCFCounter[25]++;
		}

//TreeS->Fill();	
	}

	// ^loop end^
	
	//OutTree->Fill();
	//cout<<"Nmu_tight :"<<Nmu_tight<<endl;
	double hnmuentries=hNmu->GetEntries();	
	cout<<"hnmuentries :"<<hnmuentries<<endl;

	ofstream tfile;
	if(DELPH)tfile.open("DeepSingle+DelphMET_"+outname+".txt");
	else tfile.open("DeepSingle+MET_"+outname+".txt");
	tfile << "########################################" << endl;
	tfile << "Cut efficiency numbers:" << endl;
	for(int ci = 0; ci < CutNumb; ci++)
	{
		tfile << "After cut " << CutList[ci] <<  "\t\t\t"
		      << CFCounter[ci]  << "\t events left\t"<< iCFCounter[ci] <<" cnt\t"<< endl;
		CutFlow->SetBinContent(1+ci,CFCounter[ci]);
	}

	TFile * outf;
	if(DELPH) outf  = new TFile("DeepSingle+DelphMET_"+outname+"_his.root","RECREATE");
	else  outf  = new TFile("DeepSingle+MET_"+outname+"_his.root","RECREATE");
	
	
	hDphi->Write();
	hDphi_2->Write();
	hDelphdphi->Write();
	hDelphdphi_2->Write();
	hHT->Write();
	hHT_2->Write();
	hAllHT->Write();
	hMETMeff->Write();
	hMET->Write();
	hMET_2->Write();
	hMT->Write();
	hMT_2->Write();
	hMT2W->Write();
	hMT2W_2->Write();
	hNel->Write();
	hNel_2->Write();
	hNmu->Write();
	hNtj->Write();
	hNtj_2->Write();
	hNel->Write();
	hNmu->Write();
	hNlep->Write();
	hNbjet->Write();
	hNbjet_2->Write();
	
	HT_1->Write();	
	HT_2->Write();
	HT_3->Write();

	MT_1->Write();
        MT_2->Write();
        MT_3->Write();

	MET_1->Write();
        MET_2->Write();
        MET_3->Write();

	MT2W_1->Write();
        MT2W_2->Write();
        MT2W_3->Write();

	hElPt->Write();
	hElEta->Write();
	hMuPt->Write();
	hMuEta->Write();
	aElEta->Write();
	aElPt->Write();
	aMuEta->Write();
	aMuPt->Write();

	allMuEta->Write();
	allMuPt->Write();
	allElEta->Write();
	allElPt->Write();

	hAllLepPt->Write();
	hLepPtJb->Write();
	hLepPtM->Write();
	hLepPtMM->Write();
	hLepEtaJb->Write();
	hLepEtaM->Write();
	hLepEtaMM->Write();

	hMT2WDelph_pre->Write();
	hMT2Wpre->Write();

	LepPtt->Write();
        aDphi->Write();
        aDelphDphi->Write();

        aMET->Write();
        aDelphMET->Write();

        aMT->Write();
        aMT2->Write();
        aDelphMT->Write();
        aDelphMT2->Write();

        aMT2W->Write();
        aMT2W2->Write();
        aDelphMT2W->Write();
        aDelphMT2W2->Write();

        aHT->Write();
        aLepPt->Write();
        aLepEta->Write();
        a1JetPt->Write();
        a1bJetPt->Write();
        an1bJetPt->Write();

		atop->Write();      
	atop0->Write();
	htop->Write();
	htop0->Write();
	htHT->Write();
	htDphi->Write();
	abasym->Write();
	hbasym->Write();
	aC->Write();
	hC->Write();
//	for(int i=0;i<check.size();i++){
//		cout<<check[i]<<" "<<CutList[i]<<endl;
//	}

/*Int_t sizeofMuonpt=MuonPt.size();
for(Int_t a=0;a<MuonPt.size();a++){
cout<<"MuonPt[a]"<<MuonPt[a]<<endl;
}
//cout<<"muonpt"<<muonpt<<endl;
cout<<"sizeofMuonpt:"<<sizeofMuonpt<<endl;
//OutTree->Fill();
//OutTree->Print();*/
TreeS->Write();
TreeB->Write();
/*for(Int_t a=0;a<MuonPt.size();a++){
MuPT[a]->Fill();
}*/
//OutFile->Close();
//OutTree->Fill();
}
