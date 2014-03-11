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
using namespace std;


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
 in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_2011_S20r1_VVG.root"); 
 my_tupleSignal = (TTree*) in_file->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");
 my_chainBkG = new TChain("phikstGammaStrip/DecayTree");
  }

  else if (Option == 3){
    //To be modified when MC for PhiPhi
 in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_2011_S20r1_VVG.root");
 my_tupleSignal = (TTree*) in_file->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");
 my_chainBkG = new TChain("phiphiGammaStrip/DecayTree");

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

 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aa_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ab_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ac_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ad_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ae_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_af_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ag_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ah_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ai_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aj_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ak_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_al_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_am_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_an_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ao_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ap_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aq_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ar_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_as_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_at_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_au_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_av_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aw_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ax_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ay_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_az_ntp.root");

 //Add files to the sample for PhiPhi because low statistics

 if (Option == 3){

 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aa_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ab_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ac_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ad_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ae_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_af_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ag_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ah_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ai_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aj_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ak_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_al_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_am_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_an_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ao_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ap_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aq_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ar_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_as_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_at_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_au_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_av_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aw_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ax_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ay_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_az_ntp.root");
   
   
 }
 


 //Set Upper and Lower limit for the signal window (5186-5546 MeV for PhiPhi and KstKst(B0s Mass= 5366MeV), 5099-5459MeV for PhiKst(B0 Mass = 5279 MeV))

 float LowerLimit = 5186;
 float UpperLimit = 5546;

 if (Option == 2){   
 float LowerLimit = 5099;
 float UpperLimit = 5459;
 } 
 
 //Create Title for the histogramms of the considered variable
 TString TitleHisto = TString (NameVariable.Data()) + ";;";
 

 //Create histogramms
 
 TH1F* hVariableSig=new TH1F(NameVariable.Data(),TitleHisto.Data(),
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hVariableSig->SetFillColor(kBlue-9);

 TH1F* hVariableLBkG=new TH1F(NameVariable.Data(),TitleHisto.Data(),
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hVariableLBkG->SetLineColor(kBlue+1);

 TH1F* hVariableHBkG=new TH1F(NameVariable.Data(),TitleHisto.Data(),
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hVariableHBkG->SetLineColor(kRed+1);

 TH1F* hB_MMSig=new TH1F("B_MM","Mass;Mass (GeV);",
                        100,//Number of bins
                        4000,//Lower X Boundary
                        6500);//Upper X Boundary
 hB_MMSig->SetFillColor(kBlue-9);

 TH1F* hB_MMLBkG=new TH1F("B_MM","Mass;Mass (GeV);",
                        100,//Number of bins
                        4000,//Lower X Boundary
                        6500);//Upper X Boundary
 hB_MMLBkG->SetLineColor(kBlue+1);

 TH1F* hB_MMHBkG=new TH1F("B_MM","Mass;Mass (GeV);",
                        100,//Number of bins
                        4000,//Lower X Boundary
                        6500);//Upper X Boundary
 hB_MMHBkG->SetLineColor(kRed+1);

 //Read Trees

 double TemporaryVariable, B_MM;
 
 //Select the loaves to be read

 my_tupleSignal->SetBranchAddress(NameVariable.Data(),&TemporaryVariable);
 my_tupleSignal->SetBranchAddress("B_MM",&B_MM);
 my_chainBkG->SetBranchAddress(NameVariable.Data(),&TemporaryVariable);
 my_chainBkG->SetBranchAddress("B_MM",&B_MM);
 
 //Fill histogramms

 int entrySig = 0;
 while (my_tupleSignal->GetEntry(entrySig) ){
   
   
   if ((B_MM>LowerLimit)&&(B_MM<UpperLimit)){
     hVariableSig->Fill(TemporaryVariable);
     hB_MMSig->Fill(B_MM);
   }
   
   ++entrySig ;
   

  }

 int entryBkG = 0;
 while ( my_chainBkG->GetEntry(entryBkG) ) {

   if(B_MM<LowerLimit){
     hVariableLBkG->Fill(TemporaryVariable);
     hB_MMLBkG->Fill(B_MM);
   }
   
   else if(B_MM>UpperLimit){
     hVariableHBkG->Fill(TemporaryVariable);
     hB_MMHBkG->Fill(B_MM);
   }  
   

   ++entryBkG ;
   
 }

  
 //Define scale factors and print entries

 float NumEntriesSig = entrySig ;
 float NumEntriesBkG = entryBkG ; 
 
 cout<<"Number of entries for the Signal : "<<entrySig<<endl;
 cout<<"Number of entries for the BkG : "<<entryBkG<<endl;


 TLegend *leg = new TLegend(0.6,0.7,0.89,0.89); 
 leg->AddEntry(hVariableSig,"Signal","f"); 
 leg->AddEntry(hVariableLBkG,"Low BkG","l");
 leg->AddEntry(hVariableHBkG,"High BkG","l");
 

 gStyle->SetOptStat(0);
 
 
 //Draw histogramms


 TCanvas* cCanvas = new TCanvas("cCanvas","Plots",0,0,1200,650);
 // cCanvas->Divide(2);

 cCanvas->cd(1);
 // hVariableLBkG->Scale(1/NumEntriesBkG);
 hVariableSig->DrawNormalized();
 // hVariableHBkG->Scale(1/NumEntriesBkG);
 hVariableHBkG->DrawNormalized("same");
 // hVariableSig->Scale(1/NumEntriesSig);
 hVariableLBkG->DrawNormalized("same");
 leg->Draw();
 
 /*
 cCanvas->cd(2);
 //hB_MMSig->Scale(1/NumEntriesSig);
 hB_MMSig->DrawNormalized();
 //hB_MMLBkG->Scale(1/NumEntriesBkG);
 hB_MMLBkG->DrawNormalized("same");
 //hB_MMHBkG->Scale(1/NumEntriesBkG);
 hB_MMHBkG->DrawNormalized("same");
 */



}
