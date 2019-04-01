R__ADD_INCLUDE_PATH(/home/onetrueteal/Programs/ANNIE/ANNIEEventDisplay/include/)
R__ADD_LIBRARY_PATH(/home/onetrueteal/Programs/ANNIE/ANNIEEventDisplay/lib/)
R__LOAD_LIBRARY(libEve.so)
R__LOAD_LIBRARY(libEventDisplay.so)
#include <vector>

void ThreeDDemo_ROOT6(){
  // Load libraries
  // ==============
  ANNIEDisplay* ad = new ANNIEDisplay();
  ad->SelectDataFile("PhaseIITestData.root");
  ad->LoadNTupleEvent();
  ad->InitializeGUI();
  ad->ShowEvent(); 
}

