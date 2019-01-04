{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("../lib/libEventDisplay.so");
  ANNIEDisplay* ad = new ANNIEDisplay();
  ad->Initialize3DDisplay();
  ad->LoadROOTFile("event_plots_R7S0p16.root");
  ad->LoadDemoEvent("dispevt_5");
  ad->InitializeGUI();
  ad->ShowEvent(); 
   
}

