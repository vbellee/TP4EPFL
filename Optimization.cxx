#include "TInterpreter.h"
#include "TSystem.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <algorithm>
#include "TString.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include <iostream>
#include "TStyle.h"
#include "TLegend.h"
#include "THStack.h"
#include "RooExponential.h"
#include "RooRealVar.h"
#include "TF1.h"

using namespace std;

TChain* FillChain(TChain* TmpChain,int Opt);


void Optimization (int Option,TString NameVariable, float LeftLowerBound, float LeftUpperBound, float LeftNumSteps, float RightLowerBound, float RightUpperBound, float RightNumSteps) 

{
  TFile *in_fileSignal = NULL ;
  
  TTree *my_tupleSignal = NULL ;
  
  //  TFile *in_fileBkG = NULL ;
  
  //TTree *my_tupleBkG = NULL ;

  //To be removed  
    TChain *my_tupleBkG = NULL ;
  
  
  //Open files for signal depending on the option (1 for KstKst, 2 for PhiKst, 3 for PhiPhi)

  if (Option == 1){
    
    in_fileSignal = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root");
    
    my_tupleSignal = (TTree*) in_fileSignal->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
    
    //        in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root");
    
    //    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
        my_tupleBkG = new TChain("kstkstGammaStrip/DecayTree");
    
    
  }
  
  /*
  else if (Option == 2){
    
    in_fileSignal = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_2011_S20r1_VVG.root");
    
    my_tupleSignal = (TTree*) in_fileSignal->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");

    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_2011_S20r1_VVG.root");
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");
    
    
  }
  

  else if (Option == 3){

    in_fileSignal = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_2011_S20r1_VVG.root");
    
    my_tupleSignal = (TTree*) in_fileSignal->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");

    in_fileBkG = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_2011_S20r1_VVG.root");
    
    my_tupleBkG = (TTree*) in_fileBkG->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");
    
    
    
  }
  */  

  //    assert ( in_fileSignal && in_fileBkG && my_tupleSignal && my_tupleBkG ) ;
    assert ( in_fileSignal && my_tupleSignal && my_tupleBkG ) ;
  

  //Creates TChain to take a sample for data
    my_tupleBkG = FillChain(my_tupleBkG,Option);
   


  //Set Upper and Lower limit for the signal window (5186-5546 MeV for PhiPhi and KstKst(B0s Mass= 5366MeV), 5099-5459MeV for PhiKst(B0 Mass = 5279 MeV))

  float LowerLimit = 5186;
  float UpperLimit = 5546;
  

  if (Option == 2){
    float LowerLimit = 5099;    
    float UpperLimit = 5459;    
  }
   

  
  //Create the Histogramms
  //Create Title for the histogramms of the considered variable
  TString TitleHisto = TString (NameVariable.Data()) + ";;";
  
 

  //Create histogramms
 
  TH1F* hB_MMSig=new TH1F("B_MM","Mass;Mass (GeV);",
                          100,//Number of bins
                          4000,//Lower X Boundary
                          6500);  //Upper X Boundary
  hB_MMSig->SetFillColor(kBlue-9);
  

  TH1F* hB_MMBkG=new TH1F("B_MM","Mass;Mass (GeV);",
                           100,//Number of bins
                           4000,//Lower X Boundary
                           6500);//Upper X Boundary
  hB_MMBkG->SetLineColor(kBlue+1);

  //Select loaves to be read
  double TemporaryVariable, B_MM;
  
 
  //Select the loaves to be read

  my_tupleSignal->SetBranchAddress(NameVariable.Data(),&TemporaryVariable);  
  my_tupleSignal->SetBranchAddress("B_MM",&B_MM);  
  my_tupleBkG->SetBranchAddress(NameVariable.Data(),&TemporaryVariable);
  my_tupleBkG->SetBranchAddress("B_MM",&B_MM);
  
 


  //Define steps
  float LeftStep = (LeftUpperBound-LeftLowerBound)/LeftNumSteps;
  float RightStep = (RightUpperBound-RightLowerBound)/RightNumSteps;

  //Initialize FigureOfMerit, LowerCut and HigherCut
  float FigMerit = 0;
  float LowerCut = LeftLowerBound;
  float UpperCut = RightUpperBound;
  float Efficiency = 0;
  float NumEvtsBkG = 0;
  

  //Enter the loop

  for (int ix=0;ix<(LeftNumSteps+1);++ix) {

    //Define temporary Left cut
    float tmpLowerCut = LeftLowerBound + ix*LeftStep;
    
    cout<<"Temporary Lower Cut"<<tmpLowerCut<<endl;
    

    for (int iy=0;iy<(RightNumSteps+1);++iy) {

      //Define temporary Right cut 
      float tmpUpperCut = RightLowerBound + iy*RightStep;

      cout<<"Temporary Upper Cut"<<tmpUpperCut<<endl;
      hB_MMSig->Reset();
      hB_MMBkG->Reset();
      
      
      //Fill Cut Signal histogramm
      int entrySig = 0;
      while (my_tupleSignal->GetEntry(entrySig) ){
        if ((TemporaryVariable>tmpLowerCut)&&(TemporaryVariable<tmpUpperCut)){ 
          hB_MMSig->Fill(B_MM);
        }
        ++entrySig ;
      }
      
      //Fill Cut BkG histogramm
      int entryBkG = 0;      
      while (my_tupleBkG->GetEntry(entryBkG) ){
        if (((B_MM<LowerLimit)||(B_MM>UpperLimit))&&(TemporaryVariable>tmpLowerCut)&&(TemporaryVariable<tmpUpperCut)){
          hB_MMBkG->Fill(B_MM); 
        }
        ++entryBkG ;
      }

      //Compute Efficiency (for Signal Events)
      Efficiency = 0 ;
      cout<<"Efficiency before computing integral"<<Efficiency<<endl;
      
      Efficiency = (hB_MMSig->Integral())/entrySig ;
      cout<<"Efficiency after computing integral"<<Efficiency<<endl;
      

      //Compute Number of events in the Background (here we'll have to fit the BkG)
      //Create Fitting Functions
      TF1* gHBkG = new TF1 ("gHBkG","expo",4000,6500);
      TF1* gLBkG = new TF1 ("gLBkG","expo",4000,6500);
      hB_MMBkG->Fit("gHBkG","","",UpperLimit,6500);
      hB_MMBkG->Fit("gLBkG","","",4000,LowerLimit);
      //      TF1 *gHBkGClone = (TF1*)gHBkG->Clone("gHBkG");
      //      TF1 *gLBkGClone = (TF1*)gLBkG->Clone("gLBkG");

      TF1* gBkG = new TF1("gBkG","(gHBkG+gLBkG+abs(gHBkG-gLBkG))/2",4000,6500);
      


      
      // float NumHBkG = gHBkG->Integral(LowerLimit,6500);
      // float NumLBkG = gLBkG->Integral(4000,UpperLimit);
      cout<<"NumOfEvents before computing the integral :"<<NumEvtsBkG<<endl;
      
      float NumEvtsBkG = gBkG->Integral(4000,6500) ;
      cout<<"Number of events in the BkG :"<<NumEvtsBkG<<endl;
    

      //Compute TemporaryFigure of merit
      float tmpFigMerit = Efficiency / sqrt(NumEvtsBkG);
      cout<<"Temporary Figure of Merit"<<tmpFigMerit<<endl;
      
      
      //Replace FigOfMerit and Cuts if the tmpFigOfMerit is better than FigOfMerit
      if (tmpFigMerit>FigMerit){
        FigMerit = tmpFigMerit;
        LowerCut = tmpLowerCut;
        UpperCut = tmpUpperCut;
        cout<<"Changed figure of merit to :"<<FigMerit<<endl;
        cout<<"Changed Lower Cut to :"<<LowerCut<<endl;
        cout<<"Changed Upper Cut to :"<<UpperCut<<endl;
    

      }
      
      
    }
  }
  

  cout<<"Optimized Figure of Merit : "<<FigMerit<<"\n"<<"LowerCut : "<<LowerCut<<"\n"<<"UpperCut : "<<UpperCut<<endl;
  


  
}


TChain* FillChain(TChain* TmpChain,int Opt)
{
  

  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dz_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aa_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ab_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ac_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ad_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ae_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_af_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ag_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ah_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ai_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aj_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ak_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_al_ntp.root");
  
  // TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_am_ntp.root");
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_an_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ao_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ap_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aq_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ar_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_as_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_at_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_au_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_av_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aw_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ax_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ay_ntp.root");
  
  TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_az_ntp.root");

  return TmpChain;
  
  
}

