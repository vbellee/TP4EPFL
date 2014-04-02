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
#include "TAxis.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TNtuple.h"
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

//Optimization with SideOption = 0 for lower cuts and SideOption = 1 for upper cut on the variable
void Optimization2(int Option,TString NameVariable,float StartVar, float EndVar, float LowerBound, float UpperBound, float NumSteps, int SideOption)
{
  

  float LowerLimit = 5186;
  
  float UpperLimit = 5546;
  



  if (Option == 2){
    
    
    LowerLimit = 5099;
    UpperLimit = 5459;
    
    
  }
  
  cout <<"Lower Limit :"<<LowerLimit<<endl;
  

  //Define Mass
  RooRealVar B_MM("B_MM","Mass of the B",4000,6500);

  
  //  RooRealVar SigMass("SigMass","Mass of the B in the windox mass",LowerLimit,UpperLimit);
  


  //Define Sidebands, signal and full background
  B_MM.setRange("FullBkG",4000,6500);
  
  B_MM.setRange("LBkG",4000,LowerLimit);
  
  B_MM.setRange("HBkG",UpperLimit,6500);
  
  B_MM.setRange("Sig",LowerLimit,UpperLimit);
  



  //Create trees
  TFile *in_fileSig = NULL ;
  
  TTree *my_tupleSig = NULL ;
  
  TFile *in_fileBkG = NULL ;
  
  TTree *my_tupleBkG = NULL ;
  

  //Open files for signal depending on the option (1 for KstKst, 2 for PhiKst, 3 for PhiPhi)

  if (Option == 1){
    
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_VVG_Bs2KstKstGamma_PreSel.root");
    
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
    
    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bs2KstKstGamma_PreSel.root");
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
    
  }
  

  else if (Option == 2){
    
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_VVG_Bd2PhiKstGamma_PreSel.root");
    
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");
    
    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bd2PhiKstGamma_PreSel.root");
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phikstGammaStrip/DecayTree","TTree");
    
  }
  

  else if (Option == 3){
    
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_VVG_Bs2PhiPhiGamma_PreSel.root");
    
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");
    
    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bs2PhiPhiGamma_PreSel.root");
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phiphiGammaStrip/DecayTree","TTree");
    
  }
  

  cout<<"Number of events in signal : "<<my_tupleSig->GetEntries()<<endl;
  
  cout<<"Number of events in BkG : "<<my_tupleBkG->GetEntries()<<endl;
  



  //  assert ( in_fileSig && in_fileBkG && my_tupleSig && my_tupleBkG ) ;
  // Does not compile with this assert

  //Define steps
  float Step = (UpperBound-LowerBound)/NumSteps;
  

  


  //Initialize FigureOfMerit, LowerCut, HigherCut, Efficiency, NumEvtsBkG
  float FigMerit = 0;
  
  float Cut = LowerBound;
 
  float Efficiency = 0;
  
  float NumEvtsBkG = 0;
  


  //Now we'll fit the Background with two exponentials
  //First, define the parameters
  RooRealVar tau_1 ("tau_1","tau_1 for HighBkG",-0.001,-0.01,0.0);
  
  RooRealVar tau_2 ("tau_2","tau_2 for LowBkG",-0.001,-0.01,0.0);
  
  // --- Parameters ---
  RooRealVar sigmean("sigmean","Mean value",4200,3000,4500) ;
  
  RooRealVar sigwidth("sigwidth","Width",2000,100,4500) ;
  
 
  // --- Build Gaussian PDF ---
  RooGaussian gauss("gauss","signal PDF",B_MM,sigmean,sigwidth) ;
  

  //  RooRealVar poly_c1("poly_c1", "coefficient of x^1 term", 0,-10,10);
  

  //Define the two PDFs
  RooExponential f1 ("f1","Fit of the High BkG",B_MM,tau_1);
  
  RooExponential f2 ("f2","Fit of the Low BkG",B_MM,tau_2);
  
  //  RooPolynomial bkgd_poly("bkgd_poly", "linear function for background",B_MM, RooArgList(poly_c1));
  

  //Create total PDF (sum of f1 and f2)
  RooRealVar f("f","f",0.,1.) ;
  
  RooAddPdf totalPdf("totalPdf","sum of BkG",RooArgList(f1,gauss),f);
  

  //Create datasets
  RooRealVar Variable(NameVariable.Data(),NameVariable.Data(),StartVar,EndVar);
  
  RooArgSet ntupleSet(B_MM,Variable);
  
  
  //Create Data sets for signal and BkG
  RooDataSet dataSetSig("dataSetSig","Data Set for Signal", my_tupleSig, ntupleSet);
  
  RooDataSet dataSetBkG("dataSetBkG","Data Set for BackGround", my_tupleBkG, ntupleSet);

  cout<<dataSetBkG.sumEntries()<<endl;


  

  char smass[60];
    
  sprintf(smass,"B_MM>%f && B_MM<%f",LowerLimit,UpperLimit);

  TString CutSignal = smass;
  cout <<CutSignal.Data()<<endl;
  
      
  RooDataSet *dataSetSig_Cut = (RooDataSet*)dataSetSig.reduce(RooArgSet(B_MM,Variable),CutSignal.Data());

  cout<<dataSetSig_Cut->sumEntries()<<endl;

  if (dataSetSig_Cut->sumEntries()>200){
  

    //Enter the loop (here we would need to reset everything...)

    for (int ix=0;ix<(NumSteps+1);++ix) {
    


      //Define temporary Left cut
      float tmpCut = LowerBound + ix*Step;
    
      cout << "Temporary cut : "<<tmpCut<<endl;      




    
      //Creates Cuts for BkG

      TString CutString = (NameVariable.Data());
      if (SideOption == 1){      
        CutString.Append("<");
      }
      else if (SideOption ==0){
        CutString.Append(">");
      }
      CutString +=tmpCut;
      cout<<CutString.Data()<<endl;
      


      RooDataSet *dataSetBkG_Cut = (RooDataSet*)dataSetBkG.reduce(RooArgSet(B_MM,Variable),CutString.Data());


      cout<<dataSetBkG_Cut->sumEntries()<<endl;
      /*                                       
      //Fit High BkG
      f1.fitTo(*dataSetBkG_Cut,Range("HBkG"));

      
      
      
      //Fix the parmeter of f1
      tau_1.setConstant();
      */
      //Fit all sidebands with totalPdF
      //totalPdf.fitTo(*dataSetBkG_Cut,Range("HBkG,LBkG"));
    
      gauss.fitTo(*dataSetBkG_Cut,Range("HBkG,LBkG"));
    

      //Compute the integral of the total Pdf
      RooAbsReal* igx = totalPdf.createIntegral(B_MM) ;
      NumEvtsBkG = igx->getVal();
      //Be careful ! Here the efficiency is computed as NumEvts in the massWindow and inside the cuts over the total num of events in the tree (not only in mass window)
      Efficiency = dataSetSig_Cut->sumEntries(CutString.Data())/my_tupleSig->GetEntries();
    
      //Compute TemporaryFigure of merit
      float tmpFigMerit = Efficiency / sqrt(NumEvtsBkG);
    
      //Replace FigOfMerit and Cuts if the tmpFigOfMerit is better than FigOfMerit
      if (tmpFigMerit>FigMerit){
        FigMerit = tmpFigMerit;
        Cut = tmpCut;
        cout<<"Changed figure of merit to :"<<FigMerit<<endl;
        cout<<"Changed Lower Cut to :"<<Cut<<endl;
      
      }
      
      if(ix==0){
        
      // Plot Pdf over data
      RooPlot* frame = B_MM.frame() ;
      dataSetBkG_Cut->plotOn(frame) ;
      gauss.plotOn(frame,Range("LBkG,HBkG"),Normalization( 1.0,RooAbsReal::Relative));
      
      //totalPdf.plotOn(frame) ;


      //      f1.plotOn(frame);
      
      frame->Draw();
      }
      

    
      
                
    
                                     
    
    }
  

    cout<<"Optimized Figure of Merit : "<<FigMerit<<"\n"<<"Cut : "<<Cut<<endl;
    //End of the if loop added to check datasets  
  }

  
}
