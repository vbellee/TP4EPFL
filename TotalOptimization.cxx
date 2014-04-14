#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooFit.h"

#include "RooRealVar.h"
#include "RooAbsData.h"
#include "RooAbsReal.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
//#include "TArrayF.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <algorithm>
#include "TString.h"
#include "TChain.h"
#include "TTree.h"
#include "TCanvas.h"
#include <iostream>
#include "TStyle.h"
#include "TLegend.h"
#include "THStack.h"
#include "RooExponential.h"
#include "TF1.h"


using namespace RooFit;



using namespace std;

void Optimization2(RooDataSet*dataSetSig,RooDataSet*dataSetBkG,int Option,TString NameVariable,float StartVar,
 float EndVar, float LowerBound, float UpperBound, float NumSteps,
 int SideOption);


void TotalOptimization(float num)
{




  for (int io=3;io<4;++io) {


  float LowerLimit = 5186;  
  float UpperLimit = 5546;
  if (io == 2){
    LowerLimit = 5099;
    UpperLimit = 5459;
  }

  //Create trees
  TFile *in_fileSig = NULL ;
  
  
  TTree *my_tupleSig = NULL ;
  
  
  TFile *in_fileBkG = NULL ;
  
  
  TTree *my_tupleBkG = NULL ;
  


  //Open files for signal depending on the option (1 for KstKst, 2 for PhiKst, 3 for PhiPhi)

  if (io == 1){
    
    
    in_fileSig = TFile::Open("/panfs/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_VVG_Bs2KstKstGamma_PreSel.root");
    
    
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
    
    
    in_fileBkG = TFile::Open("/panfs/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bs2KstKstGamma_PreSel.root");
    
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("kstkstGammaStrip/DecayTree","TTree");
    
    
  }
  
  
  else if (io == 2){
    
    
    in_fileSig = TFile::Open("/panfs/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_VVG_Bd2PhiKstGamma_PreSel.root");
    
    
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");
    
    
    in_fileBkG = TFile::Open("/panfs/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bd2PhiKstGamma_PreSel.root");
    
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phikstGammaStrip/DecayTree","TTree");
    
    
  }
  
  
  else if (io == 3){
    
    
    in_fileSig = TFile::Open("/panfs/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_VVG_Bs2PhiPhiGamma_PreSel.root");
    
    
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");
    
    
    in_fileBkG = TFile::Open("/panfs/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bs2PhiPhiGamma_PreSel.root");
    
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phiphiGammaStrip/DecayTree","TTree");
    
    
  }
  
  

  cout<<"Number of events in signal : "<<my_tupleSig->GetEntries()<<endl;
  
  
  cout<<"Number of events in BkG : "<<my_tupleBkG->GetEntries()<<endl;


  RooRealVar B_MM("B_MM","Mass of the B",4400,6500);
  RooRealVar B_DIRA_OWNPV("B_DIRA_OWNPV","DIRA",0.9999,1);
  RooRealVar B_ENDVERTEX_CHI2("B_ENDVERTEX_CHI2","ENDV",0,16);
  RooRealVar B_FDCHI2_OWNPV("B_FDCHI2_OWNPV","FD",200,170000);
  RooRealVar B_MINIPCHI2("B_MINIPCHI2","MINIP",0,16);
  RooRealVar B_PT("B_PT","PT",0,50000);
  RooRealVar B_SmallestDeltaChi2OneTrack("B_SmallestDeltaChi2OneTrack","SmallestDelta",0,10000);
  RooRealVar gamma_CaloHypo_isPhoton("gamma_CaloHypo_isPhoton","isPhot",0.5,1);
  RooRealVar gamma_PT("gamma_PT","gammaPT",3000,30000);
  RooArgSet ComplntupleSet(B_MM,B_DIRA_OWNPV,B_ENDVERTEX_CHI2,B_FDCHI2_OWNPV,B_MINIPCHI2,B_PT,B_SmallestDeltaChi2OneTrack,gamma_CaloHypo_isPhoton,gamma_PT);



  //Create Data sets for signal and BkG
  RooDataSet *dataSetSig = new RooDataSet("dataSetSig","Data Set for Signal", my_tupleSig, ComplntupleSet);
  
  

  RooDataSet *dataSetBkG = new RooDataSet("dataSetBkG","Data Set for BackGround", my_tupleBkG, ComplntupleSet);
  
  

  cout<<dataSetBkG->sumEntries()<<endl;
  
  
  





  //Optimization2(dataSetSig,dataSetBkG,io,"B_DIRA_OWNPV",0.9999,1,0.9999,0.99998,num,0);
                Optimization2(dataSetSig,dataSetBkG,io,"B_ENDVERTEX_CHI2",0,16,4,16,num,1);
        //Optimization2(dataSetSig,dataSetBkG,io,"B_FDCHI2_OWNPV",200,170000,200,1000,num,0);
        //Optimization2(dataSetSig,dataSetBkG,io,"B_MINIPCHI2",0,16,2,16,num,1);
        //Optimization2(dataSetSig,dataSetBkG,io,"B_PT",0,50000,0,16000,num,0);
        //Optimization2(dataSetSig,dataSetBkG,io,"B_SmallestDeltaChi2OneTrack",0,10000,0,200,num,0);
        //Optimization2(dataSetSig,dataSetBkG,io,"gamma_CaloHypo_isPhoton",0.5,1,0.5,0.95,num,0);
        //Optimization2(dataSetSig,dataSetBkG,io,"gamma_PT",3000,30000,3000,5000,num,0);
    

  }
  


}

//Optimization with SideOption = 0 for lower cuts and SideOption = 1 for upper cut on the variable
void Optimization2(RooDataSet*dataSetSig,RooDataSet*dataSetBkG,int Option,TString NameVariable,float StartVar, float EndVar, float LowerBound, float UpperBound, float NumSteps, int SideOption)
{
  
  
  float LowerLimit = 5186;  
  float UpperLimit = 5546;
  float SizeBin = (UpperBound-LowerBound)/NumSteps ;
  
  

  if (Option == 2){
    
    
    LowerLimit = 5099;
    
    
    UpperLimit = 5459;
    
    
  }
  
  

  cout <<"Lower Limit :"<<LowerLimit<<endl;
  
  
  //Define Mass
  RooRealVar B_MM("B_MM","Mass of the B",4400,6500);
  
  
  // RooRealVar SigMass("SigMass","Mass of the B in the windox mass",LowerLimit,UpperLimit);

  //Define Sidebands, signal and full background
  B_MM.setRange("FullBkG",4400,6500);
  
  
  B_MM.setRange("LBkG",4400,LowerLimit);
  
  
  B_MM.setRange("HBkG",UpperLimit,6500);
  
  
  B_MM.setRange("Sig",LowerLimit,UpperLimit);
  
  

  


  
  


  //Initialize Cut
  TString TextCut ;
  TString TextCut2 ;
  
  

  //Define steps
  float Step = (UpperBound-LowerBound)/NumSteps;
  

  //Number of events in the signal MC
  float NSig = 1 ;
  
  TString DecayName ;
  
  
  
  if (Option == 1){
    
    
    NSig = 2041489;
    
    DecayName = ("KstKstG");
    
    
  }
  

  else if (Option == 2){
    
    
    NSig = 506496;
    
    DecayName = ("PhiKstG");
    
    
  }
  

  else if (Option == 3){
    
    
    NSig = 507997;
    
    DecayName = ("PhiPhiG");
    
    
  }
  


  //Initialize FigureOfMerit, LowerCut, HigherCut, Efficiency, NumEvtsBkG
  float FigMerit = 0;
  float FigMerit2 = 0;//Fit only high bkg
  
  
  float Cut = LowerBound;
  float Cut2 = LowerBound;
  
  
  float Efficiency = 0;
  
  
  float NumEvtsBkG = 0;
  float NumEvtsBkG2 = 0;//Fit only high BkG

  //To be removed (test for the total integral)
  
  float NumEvtsBkGBis = 0;
  

  //Now we'll fit the Background with two exponentials
  //First, define the parameters
  RooRealVar tau_1 ("tau_1","tau_1 for HighBkG",-0.001,-0.01,0.0);
  
  
  RooRealVar tau_2 ("tau_2","tau_2 for LowBkG",-0.001,-0.01,0.0);
  
  

  // --- Parameters ---
  RooRealVar sigmean("sigmean","Mean value",4200,3000,4500) ;
  
  
  RooRealVar sigwidth("sigwidth","Width",2000,100,4500) ;
  
  

  // --- Build Gaussian PDF ---
  RooGaussian gauss("gauss","signal PDF",B_MM,sigmean,sigwidth) ;
  
  
  // RooRealVar poly_c1("poly_c1", "coefficient of x^1 term", 0,-10,10);

  //Define the two PDFs
  RooExponential f1 ("f1","Fit of the High BkG",B_MM,tau_1);
  
  //The one which will fit only HBkG
  RooExponential f2 ("f2","Fit of the High BkG only",B_MM,tau_2);
  
  

  // RooPolynomial bkgd_poly("bkgd_poly", "linear function for background",B_MM, RooArgList(poly_c1));

  //Create total PDF (sum of f1 and f2)
  RooRealVar f("f","f",0.,1.) ;
  
  
  
  RooAddPdf totalPdf("totalPdf","sum of BkG",RooArgList(f1,gauss),f);
  
  

  //Create datasets
  RooRealVar Variable(NameVariable.Data(),NameVariable.Data(),StartVar,EndVar);
  
  

  RooArgSet ntupleSet(B_MM,Variable);


  //Reduce DataSets  
  

  char smass[60];
  
  
  char sbkg[60];
  char shbkg[60];
  
  

  sprintf(smass,"B_MM>%f && B_MM<%f",LowerLimit,UpperLimit);
  
  sprintf(shbkg,"B_MM>%f",UpperLimit);
  
  
  sprintf(sbkg,"B_MM<%f || B_MM>%f",LowerLimit,UpperLimit);
  
  

  TString CutSignal = smass;
  
  
  cout <<CutSignal.Data()<<endl;
  
  
  TString CutBkg = sbkg;
  
  TString CutHBkG = shbkg;
  
  
  cout <<CutBkg.Data()<<endl;
  

  RooDataSet *dataSetSig_Cut = (RooDataSet*)dataSetSig->reduce(ntupleSet,CutSignal.Data());
  
  
  RooDataSet *dataSetBkg_Cut = (RooDataSet*)dataSetBkG->reduce(ntupleSet,CutBkg.Data());
  
  
  
  

  cout<<dataSetSig_Cut->sumEntries()<<endl;
  


  

  //Prints only the number of entries
  gStyle->SetOptStat("");
  
  

  int NumBins = NumSteps + 1;
  
  

  //Creates Arrays for tmpCuts,tmpFigureOfMerits, and errors
  Float_t tmpCuts[NumBins];
  
  Float_t tmpFoMs[NumBins];
  Float_t tmpFoMs2[NumBins];
  
  Float_t tmpCutsErrors[NumBins];
  
  Float_t tmpFoMsErrors[NumBins];
  Float_t tmpFoMsErrors2[NumBins];
  

  //Creates part of the title for graph
  TString SideCut ;
  
  
  if (SideOption==0){
    
    SideCut = ("Lower cut on ");
    
  }
  
  else if (SideOption==1){
    
    SideCut = ("Upper cut on ");
    
  }
  
  
  



  //Enter the loop (here we would need to reset everything...)

  for (int ix=0;ix<(NumSteps+1);++ix) {
    
      



    //Define temporary Left cut
    float tmpCut = LowerBound + ix*Step;
    
      

    cout << "Temporary cut : "<<tmpCut<<endl;
    
    //Creates Cuts for BkG and Fills Side of cut

    TString CutString = (NameVariable.Data());
    
      
      
    if (SideOption == 1){
      
        
      CutString.Append("<");
      
      
    }
    
      
    else if (SideOption ==0){
      
        
      CutString.Append(">");
      
      
    }
    
      
    CutString +=tmpCut;
    
      
    cout<<CutString.Data()<<endl;
    
      



    RooDataSet *dataSetBkG_Cut_Sel = (RooDataSet*) dataSetBkg_Cut->reduce(RooArgSet(B_MM,Variable),CutString.Data());
    RooDataSet *dataSetHBkG_Cut_Sel = (RooDataSet*) dataSetBkG_Cut_Sel->reduce(RooArgSet(B_MM,Variable),CutHBkG.Data());
      

    cout<<"Number of events in the data set of background (without the window mass) : "<<dataSetBkG_Cut_Sel->sumEntries()<<endl;
    cout<<"Number of events in the data set of background (only High Background) : "<<dataSetHBkG_Cut_Sel->sumEntries()<<endl;
    
      
      
    //Fit High BkG
    f1.fitTo(*dataSetBkG_Cut_Sel,Range("HBkG"));
    f2.fitTo(*dataSetBkG_Cut_Sel,Range("HBkG"));
 

    RooAbsReal* igxf1 = f1.createIntegral(B_MM) ;
    
      
    float NumEvtsf1 = igxf1->getVal();
    
    cout<<"Number of events for f1"<<NumEvtsf1<<endl;
    

    //Fix the parmeter of f1
        tau_1.setConstant();
    
          
    //Fit all sidebands with totalPdF
    totalPdf.fitTo(*dataSetBkG_Cut_Sel,Range("HBkG,LBkG"));
    

    // gauss.fitTo(*dataSetBkG_Cut_Sel, Range("HBkG,LBkG"));
      

    
//Compute the integral outside the mass window
    RooAbsReal* igxOut = totalPdf.createIntegral(B_MM,Range("HBkG,LBkG")) ;
    //Compute the integral in the mass window 
    RooAbsReal* igx = totalPdf.createIntegral(B_MM,Range("Sig")) ;
    
      
    NumEvtsBkG = (igx->getVal()/igxOut->getVal())*dataSetBkG_Cut_Sel->sumEntries();

    cout<<"Number of events in the background inside the mass window : "<<NumEvtsBkG<<endl;



//Compute the integral outside the mass window (for high BkG only)
    RooAbsReal* igxOut2 = f2.createIntegral(B_MM,Range("HBkG")) ;
    //Compute the integral in the mass window (for high BkG only)
    RooAbsReal* igx2 = f2.createIntegral(B_MM,Range("Sig")) ;
    
      
    NumEvtsBkG2 = (igx2->getVal()/igxOut2->getVal())*dataSetHBkG_Cut_Sel->sumEntries();

    cout<<"Number of events in the background inside the mass window : "<<NumEvtsBkG2<<endl;
    


      
    //Be careful ! Here the efficiency is computed as NumEvts in the massWindow and inside the cuts over the total num of events in the tree (not only in mass window)

    float NumSelectedSignal = dataSetSig_Cut->sumEntries(CutString.Data());
    
      

    Efficiency = NumSelectedSignal/NSig;
    
      
    cout<<"Number of Selected events in Signal after cut : "<<NumSelectedSignal<<endl;
    
      
    //Compute TemporaryFigure of merit for a search at 5 sigma
    float tmpFigMerit = Efficiency / (5/2+sqrt(NumEvtsBkG));
    float tmpFigMerit2 = Efficiency / (5/2+sqrt(NumEvtsBkG2));
    
    float tmpFigMeritError = tmpFigMerit*sqrt(1/NumSelectedSignal
                                              +1/(4*(5/2+sqrt(NumEvtsBkG))*(5/2+sqrt(NumEvtsBkG))));
    float tmpFigMeritError2 = tmpFigMerit2*sqrt(1/NumSelectedSignal
                                              +1/(4*(5/2+sqrt(NumEvtsBkG2))*(5/2+sqrt(NumEvtsBkG2))));
    
      
      
    //Fill hFoG with the temporary figure of merit
    //     gFoM->SetPoint(ix,tmpCut,tmpFigMerit,SizeBin,tmpFigMeritError);
      
    //Fill arrays
    tmpCuts[ix]=tmpCut;
    
    tmpFoMs[ix]=tmpFigMerit;
    tmpFoMs2[ix]=tmpFigMerit2;
    
    tmpCutsErrors[ix]=SizeBin/2;
    
    tmpFoMsErrors[ix]=tmpFigMeritError;
    tmpFoMsErrors2[ix]=tmpFigMeritError2;
    



    //Replace FigOfMerit and Cuts if the tmpFigOfMerit is better than FigOfMerit
    if (tmpFigMerit>FigMerit){
      
        
      FigMerit = tmpFigMerit;
      
        
      Cut = tmpCut;
      
        
      cout<<"Changed figure of merit to :"<<FigMerit<<endl;
      
        
      cout<<"Changed Lower Cut to :"<<Cut<<endl;
      
        
      TextCut = CutString;
      
        
      
    }

    //Same for the fit of High BkG
    if (tmpFigMerit2>FigMerit2){
      
        
      FigMerit2 = tmpFigMerit2;
      
        
      Cut2 = tmpCut;
      
        
      cout<<"Changed figure of merit (high bkg) to :"<<FigMerit2<<endl;
      
        
      cout<<"Changed Lower Cut (high bkg) to :"<<Cut2<<endl;
      
        
      TextCut2 = CutString;
      
        
      
    }




    
      
    // Plotting
    TCanvas *canvas = new TCanvas() ;
    
      
    // Plot Pdf over data
    RooPlot* frame = B_MM.frame() ;
    
      
    dataSetBkG_Cut_Sel->plotOn(frame) ;
    
      
    int nBkg = dataSetBkG_Cut_Sel->sumEntries() ;
    
      
    totalPdf.plotOn(frame, Range("LBkG,HBkG"), Normalization(nBkg, RooAbsReal::NumEvent));
    totalPdf.plotOn(frame, Range("LBkG,HBkG"),Normalization(nBkg, RooAbsReal::NumEvent),Components(f1),LineStyle(kDashed),LineColor(kMagenta));
    totalPdf.plotOn(frame, Range("LBkG,HBkG"),Normalization(nBkg, RooAbsReal::NumEvent),Components(gauss),LineStyle(kDashed),LineColor(kGreen));
    
      

    frame->Draw();
    

      
    canvas->SaveAs(TString("../Optimization/")+DecayName+TString("_")+CutString+TString(".eps")) ;
    
      
    delete canvas ;
    
      
    delete frame ;
    
      
    delete igx ;
    
      
    

    ////////////////////////////////////////////////////////////////////////////////////////
    //  Plot of the fit for high BkG only
    ////////////////////////////////////////////////////////////////////////////////////////

    // Plotting
    TCanvas *canvas2 = new TCanvas() ;
    
      
    // Plot Pdf over data
    RooPlot* frame2 = B_MM.frame() ;
    
      
    dataSetBkG_Cut_Sel->plotOn(frame2) ;
    
      
    int nHBkg = dataSetHBkG_Cut_Sel->sumEntries() ;
    int nHSBkg =(igx2->getVal()+igxOut2->getVal())/igxOut2->getVal()*dataSetHBkG_Cut_Sel->sumEntries();
    
      
    f2.plotOn(frame2, Range("Sig,HBkG"), Normalization(nHSBkg, RooAbsReal::NumEvent),LineColor(kMagenta));
    
    
    
      

    frame2->Draw();
    

      
    canvas2->SaveAs(TString("../Optimization/")+DecayName+TString("_")+CutString+TString("_2.eps")) ;
    
      
    delete canvas2 ;
    
      
    delete frame2 ;
    
      
    delete igx2 ;
    
      
    delete dataSetHBkG_Cut_Sel ;
    
    delete dataSetBkG_Cut_Sel ;
    

    
  }
  
    


  cout<<"Optimized Figure of Merit : "<<FigMerit<<"\n"<<"Cut : "<<Cut<<endl;
 cout<<"Optimized Figure of Merit : "<<FigMerit2<<"\n"<<"Cut : "<<Cut2<<endl;
  

  //Plot the histogram of figures of merit
  TCanvas *cFoM = new TCanvas() ;
  
    
  cFoM->SetGrid();
  
    
    

  for (int i=0;i<NumBins;i++) {
    
    tmpFoMs[i] *= 1/FigMerit;
    

    //---------BE-CAREFUL------------Errors on FoM reduced artificially !!!
    tmpFoMsErrors[i] *= 1/(10*FigMerit);
    
  }
  
    
  //Creates the histogramm for Fig of Merit
  TGraphErrors* gFoM = new TGraphErrors(NumBins,tmpCuts,tmpFoMs,tmpCutsErrors,tmpFoMsErrors);
  
  gFoM->SetLineColor(kBlue-5);
  
  
  gFoM->SetLineWidth(1);
  
  
  gFoM->SetMarkerColor(kBlue+3);
  
  
  gFoM->SetMarkerStyle(33);
  

  gFoM->SetMarkerSize(2);
  
  
  gFoM->SetTitle("");
  



  gFoM->GetXaxis()->SetTitle(SideCut+NameVariable);
  

  gFoM->GetXaxis()->SetTitleOffset(1.3);
  

  gFoM->GetXaxis()->CenterTitle();
  
  
  gFoM->GetYaxis()->SetTitle("Punzi F.O.M. [A.U.]");
  

  gFoM->GetYaxis()->SetTitleOffset(1.3);
  
  
  gFoM->GetYaxis()->CenterTitle();
  

  gFoM->Draw("ALP");
  
      
      
  cFoM->SaveAs(TString("../Optimization/")+DecayName+TString("_FoM_")+NameVariable+TString(".eps")) ;
  

  ///////////////////////////////////////////////////////////////////////////
  /////////////// Same plot for High BkG only ///////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

//Plot the histogram of figures of merit
  TCanvas *cFoM2 = new TCanvas() ;
  
    
  cFoM2->SetGrid();
  
    
    

  for (int i=0;i<NumBins;i++) {
    
    tmpFoMs2[i] *= 1/FigMerit2;
    

    //---------BE-CAREFUL------------Errors on FoM reduced artificially !!!
    tmpFoMsErrors2[i] *= 1/(10*FigMerit2);
    
  }
  
    
  //Creates the histogramm for Fig of Merit
  TGraphErrors* gFoM2 = new TGraphErrors(NumBins,tmpCuts,tmpFoMs2,tmpCutsErrors,tmpFoMsErrors2);
  
  gFoM2->SetLineColor(kBlue-5);
  
  
  gFoM2->SetLineWidth(1);
  
  
  gFoM2->SetMarkerColor(kBlue+3);
  
  
  gFoM2->SetMarkerStyle(33);
  

  gFoM2->SetMarkerSize(2);
  
  
  gFoM2->SetTitle("");
  



  gFoM2->GetXaxis()->SetTitle(SideCut+NameVariable);
  

  gFoM2->GetXaxis()->SetTitleOffset(1.3);
  

  gFoM2->GetXaxis()->CenterTitle();
  
  
  gFoM2->GetYaxis()->SetTitle("Punzi F.O.M. [A.U.]");
  

  gFoM2->GetYaxis()->SetTitleOffset(1.3);
  
  
  gFoM2->GetYaxis()->CenterTitle();
  

  gFoM2->Draw("ALP");
  
      
      
  cFoM2->SaveAs(TString("../Optimization/")+DecayName+TString("_FoM_")+NameVariable+TString("_2.eps")) ;

  

  
}
