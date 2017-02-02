//calistirmak icin
//root -l 'ReadTMVA.C("HT","KNN")'

void ReadTMVAWOCSB(TString variable,TString method)
{

  //Open file
  TFile *file =TFile::Open("TMVA.root");
  TestTree->Draw(variable,method);
  TFile *f= new TFile(variable+"_"+method+".root","CREATE");
  //check htemp!!
  TH1F *h = (TH1F*)c1->GetPrimitive("htemp");
  h->Write();
}
