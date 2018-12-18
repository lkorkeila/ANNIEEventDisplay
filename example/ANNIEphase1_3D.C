{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("../lib/EventDisplay.so");

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
  vector<vector<double> > theGens;

  TFile* mtf = new TFile(filename);
  TH2D* disphist = (TH2D*) mtf->Get(evtname);
    
    
  for(int j=0; j<8; j++){
      for(int k=0; k<8; k++){
      
          cout<<j<<" "<<k<<endl;
          
          double bc = disphist->GetBinContent(j+1,k+1);
          if( (j==0 && k==0) || (j==7 && k==0) || (j==0 && k==7) || (j==7 && k==7))
          //double bc = 5;
          double zcoor=-1981.2;
          double xcoor = (-3.5 + ((double)j+0.5)*0.875)*304.8;
          double ycoor = (-3.5 + ((double)k+0.5)*0.875)*304.8;
          vector<double> ahit;
          ahit.push_back(xcoor);
          ahit.push_back(ycoor);
          ahit.push_back(zcoor);
          ahit.push_back(bc);
          ahit.push_back(400);
          ahit.push_back(bc);

          vector<double> ghit;
          ghit.push_back(0);
          ghit.push_back(0);
          ghit.push_back(0);
          ghit.push_back(0);

          if(bc!=0) theHits.push_back(ahit);
          theGens.push_back(ghit);
      }
  }

	
  EventDisplay3D* ed = new EventDisplay3D();
  ed->AddHits(theHits);
  //ed->DoGen(theGens);
  ed->DrawDetector();
 
  ed->SetTimeRanges(0,0.2);
  ed->SetTimeRanges(1,0.4);
  ed->SetTimeRanges(2,0.6);
  ed->SetTimeRanges(3,0.8);
  ed->SetTimeRanges(4,1.0);
  ed->SetTimeRanges(5,1.5);
  ed->SetTimeRanges(6,2);
  ed->SetTimeRanges(7,2.5);


  ed->PlotEvent();

  //TCanvas* timedist = new TCanvas();
  //timehist->Draw();

}

