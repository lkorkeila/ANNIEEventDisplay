R__LOAD_LIBRARY(libEve.so)
R__LOAD_LIBRARY($PWD/../lib/libEventDisplay.so)
#include <vector>

void ThreeDDemo_ROOT6p16(){
  // Load libraries
  // ==============
  ANNIEDisplay* ad = new ANNIEDisplay();
  ad->SelectDataFile("PhaseIITestData.root");
  ad->LoadNTupleEvent();
  ad->InitializeGUI();
  ad->ShowEvent(); 
}

