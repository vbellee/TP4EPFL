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


void PlotKstKstMaxPtCuts (float InputStartRange, float InputStopRange) {

  
  //Open files for signal depending on the option (1 for KstKst, 2 for PhiKst, 3 for PhiPhi)

TFile *in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root"); 
 TTree *my_tupleSignal = (TTree*) in_file->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree");
 TChain *my_chainBkG = new TChain("kstkstGammaStrip/DecayTree");
  
  
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

 float LowerLimit = 5186;
 float UpperLimit = 5546;

 
 

 //Create histogramms
 
 TH1F* hMaxKminuspiplusSig=new TH1F("MaxKminuspiplus","{Kminus,piplus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKminuspiplusSig->SetFillColor(kBlue-9);

 TH1F* hMaxKminuspiplusLBkG=new TH1F("MaxKminuspiplus","{Kminus,piplus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKminuspiplusLBkG->SetLineColor(kBlue+1);

 TH1F* hMaxKminuspiplusHBkG=new TH1F("MaxKminuspiplus","{Kminus,piplus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKminuspiplusHBkG->SetLineColor(kRed+1);

 TH1F* hMaxKpluspiminusSig=new TH1F("MaxKpluspiminus","{Kplus,piminus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKpluspiminusSig->SetFillColor(kBlue-9);

 TH1F* hMaxKpluspiminusLBkG=new TH1F("MaxKpluspiminus","{Kplus,piminus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKpluspiminusLBkG->SetLineColor(kBlue+1);

 TH1F* hMaxKpluspiminusHBkG=new TH1F("MaxKpluspiminus","{Kplus,piminus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKpluspiminusHBkG->SetLineColor(kRed+1);

 TH1F* hMaxSig=new TH1F("Max","Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxSig->SetFillColor(kBlue-9);

 TH1F* hMaxLBkG=new TH1F("Max","Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxLBkG->SetLineColor(kBlue+1);

 TH1F* hMaxHBkG=new TH1F("Max","Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxHBkG->SetLineColor(kRed+1);

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

 double piplus_PT, Kminus_PT, piminus_PT, Kplus_PT, B_MM;
 
 //Select the loaves to be read

 my_tupleSignal->SetBranchAddress("piplus_PT",&piplus_PT);
 my_tupleSignal->SetBranchAddress("Kminus_PT",&Kminus_PT);
 my_tupleSignal->SetBranchAddress("piminus_PT",&piminus_PT);
 my_tupleSignal->SetBranchAddress("Kplus_PT",&Kplus_PT);
 my_tupleSignal->SetBranchAddress("B_MM",&B_MM);

 my_chainBkG->SetBranchAddress("piplus_PT",&piplus_PT);
 my_chainBkG->SetBranchAddress("Kminus_PT",&Kminus_PT);
 my_chainBkG->SetBranchAddress("piminus_PT",&piminus_PT);
 my_chainBkG->SetBranchAddress("Kplus_PT",&Kplus_PT);
 my_chainBkG->SetBranchAddress("B_MM",&B_MM);
 
 //Fill histogramms

 int entrySig = 0;
 while (my_tupleSignal->GetEntry(entrySig) ){
   
   
   if ((B_MM>LowerLimit)&&(B_MM<UpperLimit)){
     hMaxKminuspiplusSig->Fill(max(Kminus_PT,piplus_PT));
     hMaxKpluspiminusSig->Fill(max(Kplus_PT,piminus_PT));
     hMaxSig->Fill(max(max(Kplus_PT,piminus_PT),max(Kminus_PT,piplus_PT)));
     hB_MMSig->Fill(B_MM);
   }
   
   ++entrySig ;
   

  }

 int entryBkG = 0;
 while ( my_chainBkG->GetEntry(entryBkG) ) {

   if(B_MM<LowerLimit){
     hMaxKminuspiplusLBkG->Fill(max(Kminus_PT,piplus_PT));
     hMaxKpluspiminusLBkG->Fill(max(Kplus_PT,piminus_PT));
     hMaxLBkG->Fill(max(max(Kplus_PT,piminus_PT),max(Kminus_PT,piplus_PT)));

     hB_MMLBkG->Fill(B_MM);
   }
   
   else if(B_MM>UpperLimit){
     hMaxKminuspiplusHBkG->Fill(max(Kminus_PT,piplus_PT));
     hMaxKpluspiminusHBkG->Fill(max(Kplus_PT,piminus_PT));
     hMaxHBkG->Fill(max(max(Kplus_PT,piminus_PT),max(Kminus_PT,piplus_PT)));
     
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
 leg->AddEntry(hB_MMSig,"Signal","f"); 
 leg->AddEntry(hB_MMLBkG,"Low BkG","l");
 leg->AddEntry(hB_MMHBkG,"High BkG","l");
 
 

 gStyle->SetOptStat(0);
 
 
 
 //Draw histogramms


 TCanvas* cCanvas = new TCanvas("cCanvas","Plots",0,0,1200,700);
 cCanvas->Divide(2,2);

 cCanvas->cd(1);
 //hMaxKminuspiplusLBkG->Scale(1/NumEntriesBkG);
 hMaxKminuspiplusSig->DrawNormalized();
 //hMaxKminuspiplusHBkG->Scale(1/NumEntriesBkG);
 hMaxKminuspiplusHBkG->DrawNormalized("same");
 //hMaxKminuspiplusSig->Scale(1/NumEntriesSig);
 hMaxKminuspiplusLBkG->DrawNormalized("same");
 leg->Draw();
 

 cCanvas->cd(2);
 // hMaxKpluspiminusLBkG->Scale(1/NumEntriesBkG);
 hMaxKpluspiminusSig->DrawNormalized();
 //hMaxKpluspiminusHBkG->Scale(1/NumEntriesBkG);
 hMaxKpluspiminusHBkG->DrawNormalized("same");
 //hMaxKpluspiminusSig->Scale(1/NumEntriesSig);
 hMaxKpluspiminusLBkG->DrawNormalized("same");

 cCanvas->cd(3);
 // hMaxLBkG->Scale(1/NumEntriesBkG);
 hMaxSig->DrawNormalized();
 //hMaxHBkG->Scale(1/NumEntriesBkG);
 hMaxHBkG->DrawNormalized("same");
 //hMaxSig->Scale(1/NumEntriesSig);
 hMaxLBkG->DrawNormalized("same");


 cCanvas->cd(4);
 hB_MMSig->Scale(1/NumEntriesSig);
 hB_MMSig->Draw();
 hB_MMLBkG->Scale(1/NumEntriesBkG);
 hB_MMLBkG->Draw("same");
 hB_MMHBkG->Scale(1/NumEntriesBkG);
 hB_MMHBkG->Draw("same");
 



}
