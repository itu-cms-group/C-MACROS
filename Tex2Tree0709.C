// Read data (CERN staff) from an ascii file and create a root file wiith a Tree.
// see also a variant in staff.C
// Author: Rene Brun
   
TFile *Tex2Tree0709(Int_t get=0, Int_t print=1) {

   string      SONumber1;
   int 	SONumber2;
    string 	PostName1;
    string 	PostName2;
   int          SentYear;
   int 		SentMonth;
   int          SentDay;
   int          GetYear;
   int 		GetMonth;
   int          GetDay;
   float	Average;
   string       SentTime;
   string 	GetTime;
   int          SenderZip;
   int          RecipientZip;
   string       ItemDescription;
   float         ItemWeight;
   int           UnitsShipped;
   float          AverageUnitPrice;
   //The input file cern.dat is a copy of the CERN staff data base
   //from 1988
   TString filename = "shippingData_Months_07to09.root";
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("Tex2Tree0709.C","");
   dir.ReplaceAll("/./","/");
//   FILE *fp = fopen(Form("%smonth8.txt",dir.Data()),"r");
   ifstream fp;
   string name=Form("%sshippingData_Months_07to09.txt",dir.Data());
   cout<<"name="<<name<<endl;
   fp.open(name.c_str());
   TFile *hfile = 0;
   if (get) {
      // if the argument get =1 return the file "cernstaff.root"
      // if the file does not exist, it is created
      if (!gSystem->AccessPathName(dir+"shippingData_Months_07to09.root",kFileExists)) {
         hfile = TFile::Open(dir+"shippingData_Months_07to09.root"); //in $ROOTSYS/tutorials/tree
         if (hfile) return hfile;
      }
      //otherwise try $PWD/cernstaff.root
      if (!gSystem->AccessPathName("shippingData_Months_07to09.root",kFileExists)) {
         hfile = TFile::Open("shippingData_Months_07to09.root"); //in current dir
         if (hfile) return hfile;
      }
   }
   //no cernstaff.root file found. Must generate it !
   //generate cernstaff.root in $ROOTSYS/tutorials/tree if we have write access
   if (!gSystem->AccessPathName(dir,kWritePermission)) {
      filename = dir+"shippingData_Months_07to09.root";
   } else if (!gSystem->AccessPathName(".",kWritePermission)) {
      //otherwise generate cernstaff.root in the current directory
   } else {
      printf("you must run the script in a directory with write access\n");
      return 0;
   }
   hfile = TFile::Open(filename,"RECREATE");
   TTree *tree = new TTree("Tex2Tree0709","");
   tree->Branch("SONumber1",&SONumber1,"SONumber/S");
   tree->Branch("PostName1",&PostName1,"PostName1/S");
   tree->Branch("PostName2",&PostName1,"PostName2/S");
   tree->Branch("SenderZip",&SenderZip,"SenderZip/I");
   tree->Branch("RecipientZip",&RecipientZip,"RecipientZip/I");
   tree->Branch("ItemDescription",& ItemDescription,"ItemDescription/S");
   tree->Branch("Average",&Average,"Average/F");
   tree->Branch("SONumber2",&SONumber2,"SONumber2/I");
   tree->Branch("SentDay",&SentDay,"SentDay/I");
   tree->Branch("SentMonth",&SentMonth,"SentMonth/I");
   tree->Branch("SentYear",&SentYear,"SentYear/I");
   tree->Branch("SentTime",&SentTime,"SentTime/S");
   tree->Branch("GetDay",&GetDay,"GetDay/I");
   tree->Branch("GetMonth",&GetMonth,"GetMonth/I");
   tree->Branch("GetYear",&GetYear,"GetYear/I");
   tree->Branch("GetTime",&GetTime,"GetTime/S");
   char line[110];

      int count=0;
   while(!fp.eof()) {
fp>>SONumber1>>PostName1>>PostName2>>SenderZip>>RecipientZip>>ItemDescription>>Average>>SONumber2>>SentMonth>>SentDay>>SentYear>>SentTime>>GetMonth>>GetDay>>GetYear>>GetTime;
cout<<SONumber1<<"-----" <<PostName1<<"---------"<<PostName2<<"---------"<<SenderZip<<"---------"<<RecipientZip<<"---------"<<ItemDescription<<"---------"<<Average<<"---------"<<SONumber2<<"---------"<<SentDay<<"---------"<<SentMonth<<"---------"<<SentYear<<"------"<<SentTime<<"--------"<<GetDay<<"------"<<GetMonth<<"-----"<<GetYear<<"----------"<<GetTime<<"---------"<<endl;
     tree->Fill();
   } 

   
   
   //----------------------------
   if (print) tree->Print();
   tree->Write();

   fclose(fp);
   delete hfile;
   if (get) {
      //we come here when the script is executed outside $ROOTSYS/tutorials/tree
      hfile = TFile::Open(filename);
      return hfile;
   }
   return 0;
}
