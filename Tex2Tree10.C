// Read data (CERN staff) from an ascii file and create a root file wiith a Tree.
// see also a variant in staff.C
// Author: Rene Brun
   
TFile *Tex2Tree10(Int_t get=0, Int_t print=1) {
/*
   Int_t        SONumber;
   Int_t          ShippingDate_Year;
   Int_t 	ShippingDate_Month;
   Int_t        ShippingDate_Day;
   Int_t           ShippingTime_hour;
   Int_t 	ShippingTime_Minute;
   Int_t        ShippingTime_Sceonds;
   Int_t           SenderZip;
   Int_t           RecipientZip;
   Char_t          ItemDescription[70];
   float         ItemWeight;
   int           UnitsShipped;
   float          AverageUnitPrice;
*/

   int          SONumber;
   int          ShippingDate_Year;
   int	 	ShippingDate_Month;
   int          ShippingDate_Day;
   int       Shipping_Hour;
   int       Shipping_Minutes;
   int       Shipping_Seconds;
   int          SenderZip;
   int          RecipientZip;
   string       ItemDescription;
   float        ItemWeight;
   int          UnitsShipped;
   float         AverageUnitPrice;
   //The input file cern.dat is a copy of the CERN staff data base
   //from 1988
   TString filename = "month10.root";
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("Tex2Tree10.C","");
   dir.ReplaceAll("/./","/");
//   FILE *fp = fopen(Form("%smonth10.txt",dir.Data()),"r");
   ifstream fp;
   string name=Form("%smonth10_v3.txt",dir.Data());
   cout<<"name="<<name<<endl;
   fp.open(name.c_str());
   TFile *hfile = 0;
   if (get) {
      // if the argument get =1 return the file "cernstaff.root"
      // if the file does not exist, it is created
      if (!gSystem->AccessPathName(dir+"month10.root",kFileExists)) {
         hfile = TFile::Open(dir+"month10.root"); //in $ROOTSYS/tutorials/tree
         if (hfile) return hfile;
      }
      //otherwise try $PWD/cernstaff.root
      if (!gSystem->AccessPathName("month10.root",kFileExists)) {
         hfile = TFile::Open("month10.root"); //in current dir
         if (hfile) return hfile;
      }
   }
   //no cernstaff.root file found. Must generate it !
   //generate cernstaff.root in $ROOTSYS/tutorials/tree if we have write access
   if (!gSystem->AccessPathName(dir,kWritePermission)) {
      filename = dir+"month10.root";
   } else if (!gSystem->AccessPathName(".",kWritePermission)) {
      //otherwise generate cernstaff.root in the current directory
   } else {
      printf("you must run the script in a directory with write access\n");
      return 0;
   }
   hfile = TFile::Open(filename,"RECREATE");
   TTree *tree = new TTree("Tex2Tree10","");
   tree->Branch("SONumber",&SONumber,"SONumber/I");
   tree->Branch("ShippingDate_Year",&ShippingDate_Year,"ShippingDate_Year/I");
   tree->Branch("ShippingDate_Month",&ShippingDate_Month,"ShippingDate_Month/I");
   tree->Branch("ShippingDate_Day",&ShippingDate_Day,"ShippingDate_Day/I");
   tree->Branch("Shipping_Hour",&Shipping_Hour,"Shipping_Hour/I");
   tree->Branch("Shipping_Minutes",&Shipping_Minutes,"Shipping_Minutes/I");
   tree->Branch("Shipping_Seconds",&Shipping_Seconds,"Shipping_Seconds/I");
   tree->Branch("SenderZip",&SenderZip,"SenderZip/I");
   tree->Branch("RecipientZip",&RecipientZip,"RecipientZip/I");
   tree->Branch("ItemDescription",& ItemDescription,"ItemDescription/S");
   tree->Branch("ItemWeight",& ItemWeight,"ItemWeight/F");
   tree->Branch("UnitsShipped",&UnitsShipped,"UnitsShipped/I");
   tree->Branch("AverageUnitPrice",&AverageUnitPrice,"AverageUnitPrice/F");
   char line[110_3];
   /*

   while (fgets(&line,110_3,fp)) {
      sscanf(&line[0],"%d %d %d %d %d %d %d ",&SONumber,&ShippingDate_Month,&ShippingDate_Day,&ShippingDate_Year,&ShippingTime_hour,&ShippingTime_Minute,&ShippingTime_Sceonds);
      sscanf(&line[28],"%s %s %s %f %d %f",SenderZip,RecipientZip,ItemDescription,&ItemWeight,&UnitsShipped,&AverageUnitPrice);
     // count++;
   //   if( count<10_3)cout<<"-------------------------"<<SenderZip<<"--------------"<<ItemDescription[count]<<endl;
//	sscanf(&line[56],"%f %d %f",&ItemWeight,&UnitsShipped,&AverageUnitPrice);
      tree->Fill();//29 56
   }
   */
   //---------------------------
      int count=0;
   while(!fp.eof()) {

fp>>SONumber>>ShippingDate_Month>>ShippingDate_Day>>ShippingDate_Year>>Shipping_Hour>>Shipping_Minutes>>Shipping_Seconds>>SenderZip>>RecipientZip>>ItemDescription>>ItemWeight>>UnitsShipped>>AverageUnitPrice;
cout <<SONumber<<"-----" <<ShippingDate_Month<<"---------"<<ShippingDate_Day<<"---------"<<ShippingDate_Year<<"---------"<<Shipping_Hour<<"---------"<<Shipping_Minutes<<"---------"<<Shipping_Seconds<<"---------"<<SenderZip<<"---------"<<RecipientZip<<"---------"<<ItemDescription<<"---------"<<ItemWeight<<"---------"<<UnitsShipped<<"---------"<<AverageUnitPrice<<endl;
     tree->Fill();
   } 

  fp.close(); 
   
   
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
