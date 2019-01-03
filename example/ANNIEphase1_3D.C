{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("../lib/libEventDisplay.so");

  #include "TRandom3.h"
  #include <iomanip>
  #include "../include/EventDisplay3D.hh"

  TRandom3 numberp(42484);


  // Path to WCSim ROOT file
  // =======================
  TString filename("event_plots_R7S0p16.root");
  TString evtname("dispevt_5");
//  TString filename("SmearedEventTree.root");
//  TString treename("SmearedEventTree");

  int ievent=33;

  // Load Data
  // =========

  vector<vector<double> > theHits;

  TFile* mtf = new TFile(filename);
  TH2D* disphist = (TH2D*) mtf->Get(evtname);
  EventDisplay3D* ed = new EventDisplay3D();
    
  for(int j=0; j<8; j++){
      for(int k=0; k<8; k++){
      
          cout<<j<<" "<<k<<endl;
          
          double bc = disphist->GetBinContent(j+1,k+1);
          if( (j==0 && k==0) || (j==7 && k==0) || (j==0 && k==7) || (j==7 && k==7))
          //double bc = 5;
          double zcoor=-1981.2;
          double xcoor = (-3.5 + ((double)j+0.5)*0.875)*304.8;
          double ycoor = (-3.5 + ((double)k+0.5)*0.875)*304.8;
          //Assume the bin content here is time.  Fill in
          //0.0 for the charge info. for now
          if(bc!=0) ed->AddPMTHit(xcoor,ycoor,zcoor,bc,0.0);
      }
  }

	
  ed->DrawDetector();

  //Specify time range to have color-code spread across 
  ed->SetTimeRanges(-30.0,30.0);

  ed->PlotEvent();

  //TCanvas* timedist = new TCanvas();
  //timehist->Draw();

}

