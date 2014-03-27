/*

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooFit.h"

#include "RooRealVar.h"
#include "RooAbsData.h"
//#include "RooDataSet.h"
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
*/

using namespace RooFit;

void Optimization2(int Option,TString NameVariable, float LeftLowerBound, float LeftUpperBound, float LeftNumSteps, float RightLowerBound, float RightUpperBound, float RightNumSteps)
{
  
  float LowerLimit = 5186;
  float UpperLimit = 5546;
  
  

  if (Option == 2){
    
    float LowerLimit = 5099;    
    float UpperLimit = 5459;
    
  }
    

  //Define Mass 
  RooRealVar Mass("Mass","Mass of the B",4000,6500);
  RooRealVar SigMass("Mass","Mass of the B",LowerLimit,UpperLimit);
    
  
  //Define Sidebands, signal and full background
  Mass.setRange("FullBkG",4000,6500);
  Mass.setRange("LBkG",4000,LowerLimit);
  Mass.setRange("HBkG",UpperLimit,6500);
  Mass.setRange("Sig",LowerLimit,UpperLimit);
    


  //Create trees
  TFile *in_fileSig = NULL ; 
  TTree *my_tupleSig = NULL ;
  TFile *in_fileBkG = NULL ;
  TTree *my_tupleBkG = NULL ;
    
  //Open files for signal depending on the option (1 for KstKst, 2 for PhiKst, 3 for PhiPhi)
  
  if (Option == 1){
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root");    
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root");
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
  }  
  
  else if (Option == 2){
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_2011_S20r1_VVG.root");
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");
    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bd2PhiKstGamma_PreSel.root");
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phikstGammaStrip/DecayTree","TTree");
  }

  else if (Option == 3){
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_2011_S20r1_VVG.root");
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");
    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/Data/CombinedOffline/RADIATIVE/VVG/S20rX/Bs2PhiPhiGamma_PreSel.root");
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phiphiGammaStrip/DecayTree","TTree");
  }

  cout<<"Number of events in signal : "<<my_tupleSig->GetEntries()<<endl;
  cout<<"Number of events in BkG : "<<my_tupleBkG->GetEntries()<<endl;

    

  //  assert ( in_fileSig && in_fileBkG && my_tupleSig && my_tupleBkG ) ;
  // Does not compile with this assert  
  
  //Define steps
  float LeftStep = (LeftUpperBound-LeftLowerBound)/LeftNumSteps;
  float RightStep = (RightUpperBound-RightLowerBound)/RightNumSteps;
  

  //Initialize FigureOfMerit, LowerCut, HigherCut, Efficiency, NumEvtsBkG
  float FigMerit = 0;  
  float LowerCut = LeftLowerBound;  
  float UpperCut = RightUpperBound;  
  float Efficiency = 0;  
  float NumEvtsBkG = 0;
  

        
  //Enter the loop (here we would need to reset everything...)

  for (int ix=0;ix<(LeftNumSteps+1);++ix) {
    

    //Define temporary Left cut
    float tmpLowerCut = LeftLowerBound + ix*LeftStep;
    cout << "Temporary lower cut : "<<tmpLowerCut<<endl;
    

    
    for (int iy=0;iy<(RightNumSteps+1);++iy) {
      

      //Define temporary Right cut
      float tmpUpperCut = RightLowerBound + iy*RightStep;
    cout << "Temporary upper cut : "<<tmpUpperCut<<endl;


      
      //Define temporary chosen interval for the variable
      RooRealVar Variable("Variable",NameVariable.Data(),tmpLowerCut,tmpUpperCut);
      RooArgSet ntupleSetSig (SigMass,Variable);
      RooArgSet ntupleSetBkG (Mass,Variable);

            
      //Create Data sets for signal and BkG
      RooDataSet dataSetSig("dataSetSig","Data Set for Signal", my_tupleSig, ntupleSetSig);
      RooDataSet dataSetBkG("dataSetBkG","Data Set for BackGround", my_tupleBkG, ntupleSetBkG);

      //Now we'll fit the Background with two exponentials
      //First, define the parameters
      RooRealVar tau_1 ("tau_1","tau_1 for HighBkG",-1.0,-10.0,0.0);
      RooRealVar tau_2 ("tau_2","tau_2 for LowBkG",-1.0,-10.0,0.0);
      
      //Define the two PDFs
      RooExponential f1 ("f1","Fit of the High BkG",Mass,tau_1,RooConst(1));
      RooExponential f2 ("f2","Fit of the Low BkG",Mass,tau_2,RooConst(1));

      //Create total PDF (sum of f1 and f2)
      RooRealVar f("f","f",0.,1.) ;
      RooAddPdf totalPdf("totalPdf","sum of BkG",RooArgList(f1,f2),f);

      //Fit High BkG
      f1.fitTo(dataSetBkG,Range("HBkG"));

      /*
      //Fix the parmeter of f1
      tau_1.setConstant();
      
      //Fit all sidebands with totalPdF
      totalPdf.fitTo(dataSetBkG,Range("HBkG,LBkG"));

      //Compute the integral of the total Pdf
      RooAbsReal* igx = totalPdf.createIntegral(Mass) ;
      NumEvtsBkG = igx->getVal();
      //Be careful ! Here the efficiency is computed as NumEvts in the massWindow and inside the cuts over the total num of events in the tree (not only in mass window)
      Efficiency = dataSetSig.sumEntries()/my_tupleSig->GetEntries();
      
      //Compute TemporaryFigure of merit
      float tmpFigMerit = Efficiency / sqrt(NumEvtsBkG);
      
      //Replace FigOfMerit and Cuts if the tmpFigOfMerit is better than FigOfMerit
      if (tmpFigMerit>FigMerit){        
        FigMerit = tmpFigMerit;
        LowerCut = tmpLowerCut;
        UpperCut = tmpUpperCut;
        cout<<"Changed figure of merit to :"<<FigMerit<<endl;
        cout<<"Changed Lower Cut to :"<<LowerCut<<endl;
        cout<<"Changed Upper Cut to :"<<UpperCut<<endl;
        
      }
      
      
      
      
      
      
      */

    }
    
  }
  
    cout<<"Optimized Figure of Merit : "<<FigMerit<<"\n"<<"LowerCut : "<<LowerCut<<"\n"<<"UpperCut : "<<UpperCut<<endl;
      

}
