//calistirmak icin
//root -l 'ReadTMVA.C("HT","KNN","1")'

void ReadTMVAWOCut(TString variable,TString method,TString id)
{

  //Open file
  TFile *file =TFile::Open("TMVA.root");
  TestTree->Draw(variable,method+" && classID=="+id);
         if(id=="1")
          {
                 TFile *f= new TFile(variable+"_"+method+"_ForBckg.root","CREATE");
          }
         else if(id=="0")
          {
                  TFile *f= new TFile(variable+"_"+method+"_ForSignal.root","CREATE");
          }
  //check htemp!!
  TH1F *h = (TH1F*)c1->GetPrimitive("htemp");
  h->Write();
}
