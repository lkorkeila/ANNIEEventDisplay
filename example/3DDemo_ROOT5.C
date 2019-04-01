{
  // Load libraries
  // ==============
  //gSystem->Load("libGeom");
  gSystem->Load("libEve");
  //gSystem->Load("libMinuit");
  gSystem->Load("../lib/libEventDisplay.so");
  gROOT->ProcessLine("#include <vector>");
  ANNIEDisplay* ad = new ANNIEDisplay();
  ad->SelectDataFile("PhaseIITestData.root");
  ad->LoadNTupleEvent();
  ad->InitializeGUI();
  ad->ShowEvent(); 
   
}

