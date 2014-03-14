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


void PlotKstPhiMinPtCuts (float InputStartRange, float InputStopRange) {

  
  //Open files for signal depending on the option (1 for KstKst, 2 for PhiKst, 3 for PhiPhi)

TFile *in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_2011_S20r1_VVG.root"); 
 TTree *my_tupleSignal = (TTree*) in_file->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");
 TChain *my_chainBkG = new TChain("phikstGammaStrip/DecayTree");
  
  
  
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
 



 //Set Lower and Upper Limit for mass

 float LowerLimit = 5099;
 float UpperLimit = 5459; 
 

 //Create histogramms
 
 TH1F* hMinKminusKplusSig=new TH1F("MinKminusKplus","{Kminus,Kplus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKminusKplusSig->SetFillColor(kBlue-9);

 TH1F* hMinKminusKplusLBkG=new TH1F("MinKminusKplus","{Kminus,Kplus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKminusKplusLBkG->SetLineColor(kBlue+1);

 TH1F* hMinKminusKplusHBkG=new TH1F("MinKminusKplus","{Kminus,Kplus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKminusKplusHBkG->SetLineColor(kRed+1);

 TH1F* hMinKplus0piminusSig=new TH1F("MinKplus0piminus","{Kplus0,piminus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKplus0piminusSig->SetFillColor(kBlue-9);

 TH1F* hMinKplus0piminusLBkG=new TH1F("MinKplus0piminus","{Kplus0,piminus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKplus0piminusLBkG->SetLineColor(kBlue+1);

 TH1F* hMinKplus0piminusHBkG=new TH1F("MinKplus0piminus","{Kplus0,piminus} Min Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMinKplus0piminusHBkG->SetLineColor(kRed+1);

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

 double Kplus_PT, Kminus_PT, piminus_PT, Kplus0_PT, B_MM;
 
 //Select the loaves to be read

 my_tupleSignal->SetBranchAddress("Kplus_PT",&Kplus_PT);
 my_tupleSignal->SetBranchAddress("Kminus_PT",&Kminus_PT);
 my_tupleSignal->SetBranchAddress("piminus_PT",&piminus_PT);
 my_tupleSignal->SetBranchAddress("Kplus0_PT",&Kplus0_PT);
 my_tupleSignal->SetBranchAddress("B_MM",&B_MM);

 my_chainBkG->SetBranchAddress("Kplus_PT",&Kplus_PT);
 my_chainBkG->SetBranchAddress("Kminus_PT",&Kminus_PT);
 my_chainBkG->SetBranchAddress("piminus_PT",&piminus_PT);
 my_chainBkG->SetBranchAddress("Kplus0_PT",&Kplus0_PT);
 my_chainBkG->SetBranchAddress("B_MM",&B_MM);
 
 //Fill histogramms

 int entrySig = 0;
 while (my_tupleSignal->GetEntry(entrySig) ){
   
   
   if ((B_MM>LowerLimit)&&(B_MM<UpperLimit)){
     hMinKminusKplusSig->Fill(min(Kminus_PT,Kplus_PT));
     hMinKplus0piminusSig->Fill(min(Kplus0_PT,piminus_PT));
     hMinSig->Fill(min(min(Kplus0_PT,piminus_PT),min(Kminus_PT,Kplus_PT)));
     hB_MMSig->Fill(B_MM);
   }
   
   ++entrySig ;
   

  }

 int entryBkG = 0;
 while ( my_chainBkG->GetEntry(entryBkG) ) {

   if(B_MM<LowerLimit){
     hMinKminusKplusLBkG->Fill(min(Kminus_PT,Kplus_PT));
     hMinKplus0piminusLBkG->Fill(min(Kplus0_PT,piminus_PT));
     hMinLBkG->Fill(min(min(Kplus0_PT,piminus_PT),min(Kminus_PT,Kplus_PT)));

     hB_MMLBkG->Fill(B_MM);
   }
   
   else if(B_MM>UpperLimit){
     hMinKminusKplusHBkG->Fill(min(Kminus_PT,Kplus_PT));
     hMinKplus0piminusHBkG->Fill(min(Kplus0_PT,piminus_PT));
     hMinHBkG->Fill(min(min(Kplus0_PT,piminus_PT),min(Kminus_PT,Kplus_PT)));
     
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
 // hMinKminusKplusLBkG->Scale(1/NumEntriesBkG);
 hMinKminusKplusSig->DrawNormalized();
 //hMinKminusKplusHBkG->Scale(1/NumEntriesBkG);
 hMinKminusKplusHBkG->DrawNormalized("same");
 //hMinKminusKplusSig->Scale(1/NumEntriesSig);
 hMinKminusKplusLBkG->DrawNormalized("same");
 leg->Draw();


 cCanvas->cd(2);
 // hMinKplus0piminusLBkG->Scale(1/NumEntriesBkG);
 hMinKplus0piminusSig->DrawNormalized();
 //hMinKplus0piminusHBkG->Scale(1/NumEntriesBkG);
 hMinKplus0piminusHBkG->DrawNormalized("same");
 //hMinKplus0piminusSig->Scale(1/NumEntriesSig);
 hMinKplus0piminusLBkG->DrawNormalized("same");

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
