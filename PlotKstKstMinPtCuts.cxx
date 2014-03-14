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


void PlotKstKstMinPtCuts (float InputStartRange, float InputStopRange) {

  
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
 
 TH1F* hMinKminuspiplusSig=new TH1F("MinKminuspiplus","{Kminus,piplus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKminuspiplusSig->SetFillColor(kBlue-9);

 TH1F* hMinKminuspiplusLBkG=new TH1F("MinKminuspiplus","{Kminus,piplus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKminuspiplusLBkG->SetLineColor(kBlue+1);

 TH1F* hMinKminuspiplusHBkG=new TH1F("MinKminuspiplus","{Kminus,piplus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKminuspiplusHBkG->SetLineColor(kRed+1);

 TH1F* hMinKpluspiminusSig=new TH1F("MinKpluspiminus","{Kplus,piminus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKpluspiminusSig->SetFillColor(kBlue-9);

 TH1F* hMinKpluspiminusLBkG=new TH1F("MinKpluspiminus","{Kplus,piminus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKpluspiminusLBkG->SetLineColor(kBlue+1);

 TH1F* hMinKpluspiminusHBkG=new TH1F("MinKpluspiminus","{Kplus,piminus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKpluspiminusHBkG->SetLineColor(kRed+1);

 TH1F* hMinSig=new TH1F("Min","Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinSig->SetFillColor(kBlue-9);

 TH1F* hMinLBkG=new TH1F("Min","Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinLBkG->SetLineColor(kBlue+1);

 TH1F* hMinHBkG=new TH1F("Min","Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinHBkG->SetLineColor(kRed+1);

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
     hMinKminuspiplusSig->Fill(min(Kminus_PT,piplus_PT));
     hMinKpluspiminusSig->Fill(min(Kplus_PT,piminus_PT));
     hMinSig->Fill(min(min(Kplus_PT,piminus_PT),min(Kminus_PT,piplus_PT)));
     hB_MMSig->Fill(B_MM);
   }
   
   ++entrySig ;
   

  }

 int entryBkG = 0;
 while ( my_chainBkG->GetEntry(entryBkG) ) {

   if(B_MM<LowerLimit){
     hMinKminuspiplusLBkG->Fill(min(Kminus_PT,piplus_PT));
     hMinKpluspiminusLBkG->Fill(min(Kplus_PT,piminus_PT));
     hMinLBkG->Fill(min(min(Kplus_PT,piminus_PT),min(Kminus_PT,piplus_PT)));

     hB_MMLBkG->Fill(B_MM);
   }
   
   else if(B_MM>UpperLimit){
     hMinKminuspiplusHBkG->Fill(min(Kminus_PT,piplus_PT));
     hMinKpluspiminusHBkG->Fill(min(Kplus_PT,piminus_PT));
     hMinHBkG->Fill(min(min(Kplus_PT,piminus_PT),min(Kminus_PT,piplus_PT)));
     
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
 //hMinKminuspiplusLBkG->Scale(1/NumEntriesBkG);
 hMinKminuspiplusSig->DrawNormalized();
 //hMinKminuspiplusHBkG->Scale(1/NumEntriesBkG);
 hMinKminuspiplusHBkG->DrawNormalized("same");
 //hMinKminuspiplusSig->Scale(1/NumEntriesSig);
 hMinKminuspiplusLBkG->DrawNormalized("same");
 leg->Draw();
 

 cCanvas->cd(2);
 // hMinKpluspiminusLBkG->Scale(1/NumEntriesBkG);
 hMinKpluspiminusSig->DrawNormalized();
 //hMinKpluspiminusHBkG->Scale(1/NumEntriesBkG);
 hMinKpluspiminusHBkG->DrawNormalized("same");
 //hMinKpluspiminusSig->Scale(1/NumEntriesSig);
 hMinKpluspiminusLBkG->DrawNormalized("same");

 cCanvas->cd(3);
 // hMinLBkG->Scale(1/NumEntriesBkG);
 hMinSig->DrawNormalized();
 //hMinHBkG->Scale(1/NumEntriesBkG);
 hMinHBkG->DrawNormalized("same");
 //hMinSig->Scale(1/NumEntriesSig);
 hMinLBkG->DrawNormalized("same");


 cCanvas->cd(4);
 hB_MMSig->Scale(1/NumEntriesSig);
 hB_MMSig->Draw();
 hB_MMLBkG->Scale(1/NumEntriesBkG);
 hB_MMLBkG->Draw("same");
 hB_MMHBkG->Scale(1/NumEntriesBkG);
 hB_MMHBkG->Draw("same");
 



}
