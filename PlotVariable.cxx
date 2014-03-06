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

void PlotVariable (int Option,TString NameVariable, float InputStartRange, float InputStopRange) {

  TFile *in_file = NULL ;
  TTree *my_tupleSignal = NULL ;
  TChain *my_chainBkG = NULL ;
  
  //Open files for signal depending on the option (1 for KstKst, 2 for PhiKst, 3 for PhiPhi)

  if (Option == 1){
 in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root"); 
 my_tupleSignal = (TTree*) in_file->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
 my_chainBkG = new TChain("kstkstGammaStrip/DecayTree");

  }

  else if (Option == 2){
 TFile *in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_2011_S20r1_VVG.root"); 
 TTree* my_tupleSignal = (TTree*) in_file->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");
 TChain *my_chainBkG = new TChain("phikstGammaStrip/DecayTree");
  }

  else if (Option == 3){
    //To be modified when MC for PhiPhi
 TFile *in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root"); 
 TTree* my_tupleSignal = (TTree*) in_file->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
 TChain *my_chainBkG = new TChain("phiphiGammaStrip/DecayTree");

  }

  assert ( in_file && my_tupleSignal && my_chainBkG ) ;
  
  
 //Creates TChain to take a sample for data
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aa_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ab_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ac_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ad_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ae_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_af_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ag_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ah_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ai_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aj_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ak_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_al_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_am_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_an_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ao_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ap_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aq_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ar_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_as_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_at_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_au_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_av_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_aw_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ax_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ay_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_az_ntp.root");


 //Set Upper and Lower limit for the signal window (5186-5546 MeV for PhiPhi and KstKst(B0s Mass= 5366MeV), 5099-5459MeV for PhiKst(B0 Mass = 5279 MeV))

 if (Option == 2){   
 float LowerLimit = 5099;
 float UpperLimit = 5459;
 }
 else {
 float LowerLimit = 5186;
 float UpperLimit = 5546;
 }
 
 
 //Print only the number of entries
 gStyle->SetOptStat("");
 float NumEntriesSignal =  my_tupleSignal->GetEntries();
 cout<<"Number of entries for the Signal : "<<NumEntriesSignal<<endl;
 float NumEntriesBkG =  my_chainBkG->GetEntries();
 cout<<"Number of entries for the Background : "<<NumEntriesBkG<<endl;
 
 

 //Create histogramms
 
 TH1F* hB_MINIPCHI2Sig=new TH1F("B_MINIPCHI2","B_MINIPCHI2;;",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hB_MINIPCHI2Sig->SetFillColor(kBlue-6);

 TH1F* hB_MINIPCHI2LBkG=new TH1F("B_MINIPCHI2","B_MINIPCHI2;;",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hB_MINIPCHI2LBkG->SetLineColor(kGreen);

 TH1F* hB_MINIPCHI2HBkG=new TH1F("B_MINIPCHI2","B_MINIPCHI2;;",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hB_MINIPCHI2HBkG->SetLineColor(kRed);

 TH1F* hB_MMSig=new TH1F("B_MM","Mass;Mass (GeV);",
                        100,//Number of bins
                        4000,//Lower X Boundary
                        6500);//Upper X Boundary
 hB_MMSig->SetFillColor(kBlue-6);

 TH1F* hB_MMLBkG=new TH1F("B_MM","Mass;Mass (GeV);",
                        100,//Number of bins
                        4000,//Lower X Boundary
                        6500);//Upper X Boundary
 hB_MMLBkG->SetLineColor(kGreen);

 TH1F* hB_MMHBkG=new TH1F("B_MM","Mass;Mass (GeV);",
                        100,//Number of bins
                        4000,//Lower X Boundary
                        6500);//Upper X Boundary
 hB_MMHBkG->SetLineColor(kRed);

 //Read Trees

 double B_MINIPCHI2, B_MM;
 
 //Select the loaves to be read

 my_tupleSignal->SetBranchAddress("B_MINIPCHI2",&B_MINIPCHI2);
 my_tupleSignal->SetBranchAddress("B_MM",&B_MM);
 my_chainBkG->SetBranchAddress("B_MINIPCHI2",&B_MINIPCHI2);
 my_chainBkG->SetBranchAddress("B_MM",&B_MM);
 
 //Fill histogramms

 for (int irow=0;irow<my_tupleSignal->GetEntries();++irow){
   my_tupleSignal->GetEntry(irow);
   
   if ((B_MM>LowerLimit)&&(B_MM<UpperLimit)){
     hB_MINIPCHI2Sig->Fill(B_MINIPCHI2,1/NumEntriesSignal);
     hB_MMSig->Fill(B_MM,1/NumEntriesSignal);
   }
   

  }

 for (int irow=0;irow<my_chainBkG->GetEntries();++irow){
   my_chainBkG->GetEntry(irow);
   
   if(B_MM<LowerLimit){
     hB_MINIPCHI2LBkG->Fill(B_MINIPCHI2,1/NumEntriesBkG);
     hB_MMLBkG->Fill(B_MM,1/NumEntriesBkG);
   }
   
   else if(B_MM>UpperLimit){
     hB_MINIPCHI2HBkG->Fill(B_MINIPCHI2,1/NumEntriesBkG);
     hB_MMHBkG->Fill(B_MM,1/NumEntriesBkG);
   }  

  }
 
 //Draw histogramms

 TCanvas* cCanvas = new TCanvas("cCanvas","Plots",0,0,1200,650); 
 cCanvas->Divide(2);
 cCanvas->cd(1);
 hB_MINIPCHI2Sig->Draw();
 hB_MINIPCHI2LBkG->Draw("same");
 hB_MINIPCHI2HBkG->Draw("same");
 cCanvas->cd(2);
 hB_MMSig->Draw();
 hB_MMLBkG->Draw("same");
 hB_MMHBkG->Draw("same");
 


}
