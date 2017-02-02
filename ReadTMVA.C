//calistirmak icin
//root -l 'ReadTMVA.C("HT","KNN",0.04,"1")'

void ReadTMVA(TString variable,TString method,Float_t cut,TString id)
{
  //convert float to string
  TString Scut=" ";
  Scut=Form("%f",cut);

  // get first 4 char of string
  TString FScut=" ";
  TString SB=" ";
  FScut=Scut(0,4);

  //Open file
  TFile *file =TFile::Open("TMVA.root");
  TestTree->Draw(variable,method+"<"+Scut+" && classID=="+id);
 	 if(id=="1")
 	  {
 	         TFile *f= new TFile(variable+"_"+method+"_"+FScut+"ForBckg.root","CREATE");
 	  }
 	 else if(id=="0")
 	  {
 	 	  TFile *f= new TFile(variable+"_"+method+"_"+FScut+"ForSignal.root","CREATE");
 	  }
  //check htemp!!
  TH1F *h = (TH1F*)c1->GetPrimitive("htemp");
  h->Write();
}
