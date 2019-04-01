//R__ADD_INCLUDE_PATH(/home/lenak/ANNIE/ANNIEEventDisplay/include/)
//R__ADD_LIBRARY_PATH(/home/lenak/ANNIE/ANNIEEventDisplay/lib/)
//R__LOAD_LIBRARY(libEve.so)
R__LOAD_LIBRARY(/home/lenak/ANNIE/ANNIEEventDisplay/lib/libEventDisplay.so)
#include <vector>

void ThreeDDemo_ROOT6(){
  // Load libraries
  // ==============
  //gSystem->Load("libGeom");
  //gSystem->Load("libEve");
  //gSystem->Load("libMinuit");
  //gSystem->Load("../lib/libEventDisplay.so");
  //gSystem->AddIncludePath("-I/home/lenak/ANNIE/ANNIEEventDisplay/include/");
  //gSystem->AddLinkedLibs("/home/lenak/ANNIE/ANNIEEventDisplay/lib/libEventDisplay.so");
  ANNIEDisplay* ad = new ANNIEDisplay();
  ad->SelectDataFile("PhaseIITestData.root");
  ad->LoadNTupleEvent();
  ad->InitializeGUI();
  ad->ShowEvent(); 
}

