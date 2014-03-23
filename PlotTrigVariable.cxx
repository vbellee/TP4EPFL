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

using namespace std;

TChain* FillChain(TChain* TmpChain,int Opt);

void PlotTrigVariable (int Option,TString NameVariable, float InputStartRange, float InputStopRange, int LogOption = 0) {

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
  my_chainBkG = FillChain(my_chainBkG,Option); 


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
  bool B_L0PhotonDecision_TOS, B_L0ElectronDecision_TOS,B_L0HadronDecision_TOS,B_Hlt1TrackAllL0Decision_TOS,B_Hlt1TrackPhotonDecision_TOS,B_Hlt2RadiativeTopoTrackDecision_TOS,B_Hlt2RadiativeTopoPhotonDecision_TOS,B_Hlt2RadiativeTopoTrackTOSDecision_TOS,B_Hlt2RadiativeTopoPhotonL0Decision_TOS,B_Hlt2IncPhiDecision_TOS;
 
  //Select the loaves to be read

  my_tupleSignal->SetBranchAddress(NameVariable.Data(),&TemporaryVariable);
  my_tupleSignal->SetBranchAddress("B_MM",&B_MM);
  my_tupleSignal->SetBranchAddress("B_L0PhotonDecision_TOS",&B_L0PhotonDecision_TOS);
  my_tupleSignal->SetBranchAddress("B_L0ElectronDecision_TOS",&B_L0ElectronDecision_TOS);
  my_tupleSignal->SetBranchAddress("B_L0HadronDecision_TOS",&B_L0HadronDecision_TOS);
  my_tupleSignal->SetBranchAddress("B_Hlt1TrackAllL0Decision_TOS",&B_Hlt1TrackAllL0Decision_TOS);
  my_tupleSignal->SetBranchAddress("B_Hlt1TrackPhotonDecision_TOS",&B_Hlt1TrackPhotonDecision_TOS);
  my_tupleSignal->SetBranchAddress("B_Hlt2RadiativeTopoTrackDecision_TOS",&B_Hlt2RadiativeTopoTrackDecision_TOS);
  my_tupleSignal->SetBranchAddress("B_Hlt2RadiativeTopoPhotonDecision_TOS",&B_Hlt2RadiativeTopoPhotonDecision_TOS);
  my_tupleSignal->SetBranchAddress("B_Hlt2RadiativeTopoTrackTOSDecision_TOS",&B_Hlt2RadiativeTopoTrackTOSDecision_TOS);
  my_tupleSignal->SetBranchAddress("B_Hlt2RadiativeTopoPhotonL0Decision_TOS",&B_Hlt2RadiativeTopoPhotonL0Decision_TOS);
  my_tupleSignal->SetBranchAddress("B_Hlt2IncPhiDecision_TOS",&B_Hlt2IncPhiDecision_TOS);
  my_chainBkG->SetBranchAddress(NameVariable.Data(),&TemporaryVariable);
  my_chainBkG->SetBranchAddress("B_MM",&B_MM);
 
  //Fill histogramms

  int entrySig = 0;
  while (my_tupleSignal->GetEntry(entrySig) ){
   
   
    if ((B_MM>LowerLimit)&&(B_MM<UpperLimit)){

      if ((Option==1)&&
          //L0
          (B_L0PhotonDecision_TOS ||
           B_L0ElectronDecision_TOS ||
           B_L0HadronDecision_TOS)&&
          //Hlt1
          (B_Hlt1TrackAllL0Decision_TOS ||
           B_Hlt1TrackPhotonDecision_TOS)&&
          //Hlt2
          (B_Hlt2RadiativeTopoTrackDecision_TOS ||
           B_Hlt2RadiativeTopoPhotonDecision_TOS ||
           B_Hlt2RadiativeTopoTrackTOSDecision_TOS ||
           B_Hlt2RadiativeTopoPhotonL0Decision_TOS)){       

        hVariableSig->Fill(TemporaryVariable);
        hB_MMSig->Fill(B_MM);
      }

      else if (((Option==2)||(Option==3))&&
               //L0
               (B_L0PhotonDecision_TOS ||
                B_L0ElectronDecision_TOS ||
                B_L0HadronDecision_TOS)&&
               //Hlt1
               (B_Hlt1TrackAllL0Decision_TOS ||
                B_Hlt1TrackPhotonDecision_TOS)&&
               //Hlt2
               (B_Hlt2RadiativeTopoTrackDecision_TOS ||
                B_Hlt2RadiativeTopoPhotonDecision_TOS ||
                B_Hlt2RadiativeTopoTrackTOSDecision_TOS ||
                B_Hlt2RadiativeTopoPhotonL0Decision_TOS ||
                B_Hlt2IncPhiDecision_TOS)){

        hVariableSig->Fill(TemporaryVariable);
        hB_MMSig->Fill(B_MM);


      }
     

     
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



  THStack *hs = new THStack ("hs",TitleHisto.Data());
  float NormSig ;
  NormSig = 1/(hVariableSig->Integral());
  hVariableSig->Scale(NormSig);
  hs->Add(hVariableSig);

  float NormLBkG;
 
  NormLBkG = 1/(hVariableLBkG->Integral());
  hVariableLBkG->Scale(NormLBkG);
  hs->Add(hVariableLBkG);

  float NormHBkG;
 
  NormHBkG = 1/(hVariableHBkG->Integral());
  hVariableHBkG->Scale(NormHBkG);
  hs->Add(hVariableHBkG);


  hs->Print();

  TCanvas* cCanvas = new TCanvas("cCanvas","Plots",0,0,1200,650);
  // cCanvas->Divide(2);
  
  cCanvas->cd(1);
  if (LogOption==1){   
    gPad->SetLogy();
  }
  
  hs->Draw("nostack");
  //hVariableSig->DrawNormalized("same");
  //hVariableLBkG->DrawNormalized("same");
  

  // hVariableLBkG->Scale(1/NumEntriesBkG);
  // hVariableSig->DrawNormalized();
  // hVariableHBkG->Scale(1/NumEntriesBkG);
  //hVariableHBkG->DrawNormalized("same");
  // hVariableSig->Scale(1/NumEntriesSig);
  //hVariableLBkG->DrawNormalized("same");
  leg->Draw("same");
 
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

 if (Opt!=1){
   

 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aa_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ab_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ac_ntp.root");
 // TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ad_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ae_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_af_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ag_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ah_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ai_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ak_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_al_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_am_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_an_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ao_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ap_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ar_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_as_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_at_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_au_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_av_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_aw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ax_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ay_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_az_ntp.root");

 //Add files to the sample for PhiPhi because low statistics

 if (Opt == 3){

 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aa_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ab_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ac_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ad_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ae_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_af_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ag_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ah_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ai_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ak_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_al_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_am_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_an_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ao_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ap_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ar_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_as_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_at_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_au_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_av_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_aw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ax_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ay_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_az_ntp.root");


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ba_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bc_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_be_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bf_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bi_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_br_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bu_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_by_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bz_ntp.root");
 
 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ba_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_be_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bf_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bo_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_br_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bu_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_by_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bz_ntp.root");
 


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_aa_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ab_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ac_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ad_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ae_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_af_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ag_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ah_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_aj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ak_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_al_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_am_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_an_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ao_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ap_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_aq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ar_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_as_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_at_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_au_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_av_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_aw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ax_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ay_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_az_ntp.root");



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_da_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_db_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_de_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_df_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_do_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ds_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_du_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dy_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_dz_ntp.root");
 

 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ba_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_be_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bf_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bo_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_br_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bu_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_by_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_bz_ntp.root");
  
  

 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ca_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ce_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cf_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ch_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cy_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_cz_ntp.root");


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_aa_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ab_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ac_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ad_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ae_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_af_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ag_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ah_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_aj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ak_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_al_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_am_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_an_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ao_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ap_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_aq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ar_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_as_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_at_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_au_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_av_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_aw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ax_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ay_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_az_ntp.root");



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ba_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_be_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bf_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bo_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_br_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bu_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_by_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_bz_ntp.root");



 



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_eb_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ec_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ed_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ee_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ef_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_eg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_eh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ej_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_el_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_em_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_eo_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ep_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_eq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_er_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_es_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_et_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ev_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ew_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ex_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ey_ntp.root");



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ca_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ch_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ck_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_co_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ct_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cu_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_cy_ntp.root");


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_da_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_de_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_df_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_do_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ds_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_du_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dy_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_dz_ntp.root");


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_eb_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ec_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ed_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ee_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ef_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_eg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_eh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ej_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_el_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_em_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_eo_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ep_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_eq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_er_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_es_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_et_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ev_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ew_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ex_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ey_ntp.root");



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ca_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ch_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ck_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ct_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_cy_ntp.root");


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_da_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_de_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_df_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_do_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_ds_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_du_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dy_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_2_dz_ntp.root");



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_eb_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ec_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ed_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ee_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ef_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_eg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_eh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ej_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_el_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_em_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_eo_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ep_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_eq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_er_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_es_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_et_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ev_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ew_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ex_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ey_ntp.root");



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ca_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ck_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_co_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ct_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cu_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_cy_ntp.root");
 


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_da_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_de_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_df_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_do_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_ds_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_du_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dy_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_4_dz_ntp.root");




 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_eb_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ec_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ed_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ee_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ef_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_eg_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_eh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ej_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_el_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_em_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_eo_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ep_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_eq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_es_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_et_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ev_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ew_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ex_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ey_ntp.root");



 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ca_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cb_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cc_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ck_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cn_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_co_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cp_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cs_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ct_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cu_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cx_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_cy_ntp.root");
 


 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_da_ntp.root"); 
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dd_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_de_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_df_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dh_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dj_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dk_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dl_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dm_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_do_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dq_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dr_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_ds_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dt_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_du_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dv_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dw_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dx_ntp.root");
 TmpChain->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_5_dy_ntp.root");

 

 
 }
 }



  return TmpChain;
  
}
