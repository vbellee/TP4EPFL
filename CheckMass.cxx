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
#include "TGraphErrors.h"
//#include "TArrayF.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TNtuple.h"
#include "TCanvas.h"
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

void CheckMass(int MCOption,int TreeOption)
{
  //Creates variables
  RooRealVar B_MM("B_MM","Mass of the B",4400,6500);
  RooRealVar B_M03("B_M03","Reconstructed Mass of particles 0 and 3",0,4500);
  RooRealVar B_M04("B_M04","Reconstructed Mass of particles 0 and 4",0,4500);
  RooRealVar B_M13("B_M13","Reconstructed Mass of particles 1 and 3",0,4500);
  RooRealVar B_M14("B_M14","Reconstructed Mass of particles 1 and 4",0,4500);
  RooRealVar B_BKGCAT("B_BKGCAT","bkgCat",0,100);
  
  
  //Reads trees
  //Create trees
  TFile *in_fileSig = NULL ;
  TTree *my_tupleSig = NULL ;

  //Create Names
  TString MCName;
  TString TreeName;
  

  

  if (MCOption==1){
    
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC2012sim6b/2012/Bs2KstKstGamma/VVG/S20r0/Bs2KstKstGamma_2012_S20r0_VVG.root");
    MCName = "MCKstKst";
    
  }
  
  else if (MCOption==2){
    
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bd2PhiKstGamma/VVG/S20r1/Bd2PhiKstGamma_2011_S20r1_VVG.root");
    MCName = "MCPhiKst";

  }
  
  else if (MCOption==3){
    
    in_fileSig = TFile::Open("/../../lhcb/panasas/radiative/TupleProd/MC11a/2011/Bs2PhiPhiGamma/VVG/S20r1/Bs2PhiPhiGamma_2011_S20r1_VVG.root");
    MCName = "MCPhiPhi";
    
  }
  

 
  
  //Creates ArgSet
  RooArgSet ntupleSet(B_MM,B_M03,B_M04,B_M13,B_M14,B_BKGCAT);
  


  //Define Cut->Reconstruction
  TString TrueCut ="B_BKGCAT<30";
  TString FalseCut ="(B_BKGCAT>=30)&&(B_BKGCAT<31)";

  if (MCOption==1){

    TrueCut = "(B_BKGCAT>=30)&&(B_BKGCAT<31)";
    FalseCut = "(B_BKGCAT>=40)&&(B_BKGCAT<41)";
    
    
  }
  

  //Define Cuts on reconstructed mass for non matched pairs
  TString Cut;
  

  if (TreeOption==1){
    //KstKst

    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("kstkstGammaMCStrip/DecayTree","TTree"); 
    
    Cut = "(B_M03<875||B_M03>925)&&(B_M04<1010||B_M04>1030)&&(B_M14<875||B_M14>925)";

    TreeName = "kstkstTree";
    
  }
  
  else if (TreeOption==2){
    //KstPhi

    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phikstGammaMCStrip/DecayTree","TTree");

    Cut = "(B_M03<1010||B_M03>1030)&&(B_M04<875||B_M04>925)&&(B_M13<1010||B_M13>1030)&&(B_M14<875||B_M14>925)";

    TreeName = "phikstTree";
    
  }

  else if (TreeOption==3){
    //PhiPhi  
  
    my_tupleSig = (TTree*) in_fileSig->GetObjectChecked("phiphiGammaMCStrip/DecayTree","TTree");

    Cut = "(B_M03<1010||B_M03>1030)&&(B_M04<1010||B_M04>1030)&&(B_M13<1010||B_M13>1030)&&(B_M14<1010||B_M14>1030)";
    
    TreeName = "phiphiTree";
    
  }
  

  //Create full data set
  RooDataSet *dataSetSig = new RooDataSet("dataSetSig","Data Set for Signal", my_tupleSig, ntupleSet);
  RooDataSet *dataSetSig_Cut = (RooDataSet*)dataSetSig->reduce(ntupleSet,Cut.Data());



  //Reduce the data set to true events
  RooDataSet *dataSetSig_True = (RooDataSet*)dataSetSig->reduce(ntupleSet,TrueCut.Data());
  RooDataSet *dataSetSig_False = (RooDataSet*)dataSetSig->reduce(ntupleSet,FalseCut.Data());
   


  //Reduce dataset
  RooDataSet *dataSetSig_TCut = (RooDataSet*)dataSetSig_True->reduce(ntupleSet,Cut.Data());
  RooDataSet *dataSetSig_FCut = (RooDataSet*)dataSetSig_False->reduce(ntupleSet,Cut.Data());
  
  
  cout<<"Number of events in MC : "<<dataSetSig->sumEntries()<<endl;
  cout<<"Number of events after mass veto in MC : "<<dataSetSig_Cut->sumEntries()<<endl;
  cout<<"Total percentage of rejection : "<<(dataSetSig->sumEntries()-dataSetSig_Cut->sumEntries())*100/dataSetSig->sumEntries()<<"%"<<endl;
  

  cout<<"Number of true events : "<<dataSetSig_True->sumEntries()<<endl;
  //  cout<<"Percentage of true events : "<<100*dataSetSig_True->sumEntries()/dataSetSig->sumEntries()<<"%"<<endl;
  cout<<"Number of True events after mass veto : "<<dataSetSig_TCut->sumEntries()<<endl;
  //cout<<"Number of events with B_BKGCAT=30 : "<<dataSetSig_False->sumEntries()<<endl;  
  cout<<"Efficiency (true events after cut/true events) : "<<dataSetSig_TCut->sumEntries()/dataSetSig_True->sumEntries()<<endl;
  cout<<"Percentage of rejection of true events : "<<(dataSetSig_True->sumEntries()-dataSetSig_TCut->sumEntries())*100/dataSetSig_True->sumEntries()<<"%"<<endl;
  cout<<"Percentage of rejection of false events : "<<(dataSetSig_False->sumEntries()-dataSetSig_FCut->sumEntries())*100/dataSetSig_False->sumEntries()<<"%"<<endl;
  


  cout<<"Number of BkG events rejected : "<<(dataSetSig_False->sumEntries())-(dataSetSig_FCut->sumEntries())<<endl;
  
  


  //Plot MC before and after reduction
  
  RooPlot* frame = B_MM.frame(Title(" ")) ;
  
  RooPlot* framebis = B_MM.frame(Title(" ")) ;
  RooPlot* frame03 = B_M03.frame(Title(" ")) ;
  RooPlot* frame04 = B_M04.frame(Title(" ")) ;
  RooPlot* frame13 = B_M13.frame(Title(" ")) ;
  RooPlot* frame14 = B_M14.frame(Title(" ")) ;




  //Create canvas
  
  if (MCOption==TreeOption){
    

    TCanvas* c1 = new TCanvas("c1","c1",1300,700) ;
  
    c1->Divide(2,3) ;
    c1->cd(1) ;
  
    dataSetSig_True->plotOn(frame,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_TCut->plotOn(frame,MarkerColor(kBlue),LineColor(kBlue));

    frame->Draw();
  

  
    c1->cd(2) ;
  
    dataSetSig_True->plotOn(frame03,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_TCut->plotOn(frame03,MarkerColor(kOrange),LineColor(kOrange));
    dataSetSig_False->plotOn(frame03,MarkerColor(kGreen),LineColor(kGreen)) ;
    dataSetSig_FCut->plotOn(frame03,MarkerColor(kBlue),LineColor(kBlue));

  
    frame03->Draw();

    c1->cd(3) ;
  
    dataSetSig_True->plotOn(frame04,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_TCut->plotOn(frame04,MarkerColor(kBlue),LineColor(kBlue));
  
  
    frame04->Draw();

    c1->cd(4) ;
  
    dataSetSig_True->plotOn(frame13,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_TCut->plotOn(frame13,MarkerColor(kBlue),LineColor(kBlue));

  
    frame13->Draw();

    c1->cd(5) ;
    
    dataSetSig_True->plotOn(frame14,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_TCut->plotOn(frame14,MarkerColor(kBlue),LineColor(kBlue));

  
    frame14->Draw();

    c1->cd(6) ;


    dataSetSig->plotOn(framebis,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_Cut->plotOn(framebis,MarkerColor(kBlue),LineColor(kBlue));

    framebis->Draw();
  }
  
  else {
    


    TCanvas* c2 = new TCanvas("c2","c2",1300,700) ;

    dataSetSig->plotOn(frame,Name("all"),MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_Cut->plotOn(frame,Name("cutevts"),MarkerColor(kBlue),LineColor(kBlue));
    
    frame->Draw();

    TLegend *leg2 = new TLegend(0.65,0.73,0.86,0.87);
    leg2->SetFillColor(kWhite);
    leg2->SetLineColor(kWhite);
    leg2->AddEntry("all","All events", "LP");  
    leg2->AddEntry("cutevts","Events after Veto on Mass","LP");
    leg2->Draw();
  
    c2->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_MM")+TString(".eps")) ;
    c2->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_MM")+TString(".root")) ;
  
  

    TCanvas* c3 = new TCanvas("c3","c3",1300,700) ;

    dataSetSig->plotOn(frame03,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_Cut->plotOn(frame03,MarkerColor(kBlue),LineColor(kBlue));
  
    frame03->Draw();
    leg2->Draw();
  
    c3->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M03")+TString(".eps")) ;
    c3->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M03")+TString(".root")) ;


    TCanvas* c4 = new TCanvas("c4","c4",1300,700) ;
    
    dataSetSig->plotOn(frame04,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_Cut->plotOn(frame04,MarkerColor(kBlue),LineColor(kBlue));

    frame04->Draw();
    leg2->Draw();

    c4->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M04")+TString(".eps")) ;
    c4->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M04")+TString(".root")) ;
    
    
    TCanvas* c5 = new TCanvas("c5","c5",1300,700) ;
    
    dataSetSig->plotOn(frame13,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_Cut->plotOn(frame13,MarkerColor(kBlue),LineColor(kBlue));
    
    frame13->Draw();
    leg2->Draw();
    
    c5->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M13")+TString(".eps")) ;
    c5->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M13")+TString(".root")) ;
    
    
    TCanvas* c6 = new TCanvas("c6","c6",1300,700) ;
    
    dataSetSig->plotOn(frame14,MarkerColor(kRed),LineColor(kRed)) ;
    dataSetSig_Cut->plotOn(frame14,MarkerColor(kBlue),LineColor(kBlue));
    
    frame14->Draw();
    leg2->Draw();
    
    c6->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M14")+TString(".eps")) ;
    c6->SaveAs(TString("../MassVeto/")+MCName+TString("_")+TreeName+TString("_B_M14")+TString(".root")) ;
  }
  
  
}
