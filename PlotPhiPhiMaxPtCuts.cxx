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


void PlotPhiPhiMaxPtCuts (float InputStartRange, float InputStopRange) {

TFile *in_file = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_2011_S20r1_VVG.root");
 TTree *my_tupleSignal = (TTree*) in_file->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");
 TChain *my_chainBkG = new TChain("phiphiGammaStrip/DecayTree");

  
  
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


 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_ba_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bb_ntp.root"); 
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bc_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bd_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_be_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bf_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bg_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bh_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bi_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bj_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bk_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bl_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bm_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bn_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bp_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bq_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_br_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bs_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bt_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bu_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bv_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bw_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bx_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_by_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_6_bz_ntp.root");
 
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_ba_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bb_ntp.root"); 
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bc_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bd_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_be_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bf_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bg_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bh_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bj_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bk_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bl_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bm_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bn_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bo_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bp_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bq_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_br_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bs_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bt_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bu_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bv_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bw_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bx_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_by_ntp.root");
 my_chainBkG->AddFile("/../../lhcb/panasas/radiative/TupleProd/Data/2012/RADIATIVE/VVG/S20r0/MagDown/radiativeVVG_R14S20r0_MagDown_3_bz_ntp.root");
   

 //Set Upper and Lower limit for the signal window (5186-5546 MeV for PhiPhi and KstKst(B0s Mass= 5366MeV), 5099-5459MeV for PhiKst(B0 Mass = 5279 MeV))

 float LowerLimit = 5186;
 float UpperLimit = 5546; 

 //Create histogramms
 
 TH1F* hMaxKminusKplusSig=new TH1F("MaxKminusKplus","{Kminus,Kplus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKminusKplusSig->SetFillColor(kBlue-9);

 TH1F* hMaxKminusKplusLBkG=new TH1F("MaxKminusKplus","{Kminus,Kplus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKminusKplusLBkG->SetLineColor(kBlue+1);

 TH1F* hMaxKminusKplusHBkG=new TH1F("MaxKminusKplus","{Kminus,Kplus} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKminusKplusHBkG->SetLineColor(kRed+1);

 TH1F* hMaxKplus0Kminus0Sig=new TH1F("MaxKplus0Kminus0","{Kplus0,Kminus0} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKplus0Kminus0Sig->SetFillColor(kBlue-9);

 TH1F* hMaxKplus0Kminus0LBkG=new TH1F("MaxKplus0Kminus0","{Kplus0,Kminus0} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKplus0Kminus0LBkG->SetLineColor(kBlue+1);

 TH1F* hMaxKplus0Kminus0HBkG=new TH1F("MaxKplus0Kminus0","{Kplus0,Kminus0} Max Pt",
                        100,//Number of bins
                        InputStartRange,//Lower X Boundary
                        InputStopRange);//Upper X Boundary
 hMaxKplus0Kminus0HBkG->SetLineColor(kRed+1);

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

 double Kplus_PT, Kminus_PT, Kminus0_PT, Kplus0_PT, B_MM;
 
 //Select the loaves to be read

 my_tupleSignal->SetBranchAddress("Kplus_PT",&Kplus_PT);
 my_tupleSignal->SetBranchAddress("Kminus_PT",&Kminus_PT);
 my_tupleSignal->SetBranchAddress("Kminus0_PT",&Kminus0_PT);
 my_tupleSignal->SetBranchAddress("Kplus0_PT",&Kplus0_PT);
 my_tupleSignal->SetBranchAddress("B_MM",&B_MM);

 my_chainBkG->SetBranchAddress("Kplus_PT",&Kplus_PT);
 my_chainBkG->SetBranchAddress("Kminus_PT",&Kminus_PT);
 my_chainBkG->SetBranchAddress("Kminus0_PT",&Kminus0_PT);
 my_chainBkG->SetBranchAddress("Kplus0_PT",&Kplus0_PT);
 my_chainBkG->SetBranchAddress("B_MM",&B_MM);
 
 //Fill histogramms

 int entrySig = 0;
 while (my_tupleSignal->GetEntry(entrySig) ){
   
   
   if ((B_MM>LowerLimit)&&(B_MM<UpperLimit)){
     hMaxKminusKplusSig->Fill(max(Kminus_PT,Kplus_PT));
     hMaxKplus0Kminus0Sig->Fill(max(Kplus0_PT,Kminus0_PT));
     hMaxSig->Fill(max(max(Kplus0_PT,Kminus0_PT),max(Kminus_PT,Kplus_PT)));
     hB_MMSig->Fill(B_MM);
   }
   
   ++entrySig ;
   

  }

 int entryBkG = 0;
 while ( my_chainBkG->GetEntry(entryBkG) ) {

   if(B_MM<LowerLimit){
     hMaxKminusKplusLBkG->Fill(max(Kminus_PT,Kplus_PT));
     hMaxKplus0Kminus0LBkG->Fill(max(Kplus0_PT,Kminus0_PT));
     hMaxLBkG->Fill(max(max(Kplus0_PT,Kminus0_PT),max(Kminus_PT,Kplus_PT)));

     hB_MMLBkG->Fill(B_MM);
   }
   
   else if(B_MM>UpperLimit){
     hMaxKminusKplusHBkG->Fill(max(Kminus_PT,Kplus_PT));
     hMaxKplus0Kminus0HBkG->Fill(max(Kplus0_PT,Kminus0_PT));
     hMaxHBkG->Fill(max(max(Kplus0_PT,Kminus0_PT),max(Kminus_PT,Kplus_PT)));
     
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
 // hMaxKminusKplusLBkG->Scale(1/NumEntriesBkG);
 hMaxKminusKplusSig->DrawNormalized();
 // hMaxKminusKplusHBkG->Scale(1/NumEntriesBkG);
 hMaxKminusKplusHBkG->DrawNormalized("same");
 //hMaxKminusKplusSig->Scale(1/NumEntriesSig);
 hMaxKminusKplusLBkG->DrawNormalized("same");
 leg->Draw();
 

 cCanvas->cd(2);
 // hMaxKplus0Kminus0LBkG->Scale(1/NumEntriesBkG);
 hMaxKplus0Kminus0Sig->DrawNormalized();
 //hMaxKplus0Kminus0HBkG->Scale(1/NumEntriesBkG);
 hMaxKplus0Kminus0HBkG->DrawNormalized("same");
 //hMaxKplus0Kminus0Sig->Scale(1/NumEntriesSig);
 hMaxKplus0Kminus0LBkG->DrawNormalized("same");

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
