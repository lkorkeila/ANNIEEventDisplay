#ifndef ANNIEDISPLAY_HH
#define ANNIEDISPLAY_HH

#include "EventDisplay3D.hh"

#include "TObject.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TGButton.h"
#include "TGClient.h"
#include "TString.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"

#include <string>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>

#include "TGeometry.h"
#include "TGeoManager.h"
#include "TGeoMaterial.h"
#include "TGeoMatrix.h"

#include "TEveManager.h"
#include "TEveEventManager.h"
#include "TEveBrowser.h"
#include "TEveViewer.h"
#include "TEveGeoNode.h"
#include "TEvePointSet.h"
#include "TEveStraightLineSet.h"
#include "TEveArrow.h"
#include "TEveText.h"

class ANNIEDisplay : public TObject {

 public: 

  ANNIEDisplay();

  ~ANNIEDisplay();
  void GoToEvent(int EvtNumber);
  void SelectDataFile(TString thedata){datafilename = thedata;}
  void SelectTree(TString thetree){datatree = thetree;}
  void LoadDemoEvent(TString evtname);
  void LoadNTupleEvent();
  void InitializeGUI();
  void ShowEvent();
  // Event navigation GUI methods
  void ForwardEvent();
  void BackEvent();
  // Will want another text box that sets time ranges for color scale

 private:
  void Initialize3DDisplay(){ed = new EventDisplay3D();} 
  TString datafilename;
  TString datatree = "phaseII";
  void OpenNavigationPanel();
  double TimeRangeMin = -30.0;
  double TimeRangeMax = 30.0;
  int CurrentEvNum = 0;
  int TotalEntries = 9999;
  void LoadEvent();
  //Event display GUI element
  EventDisplay3D* ed;

  ClassDef(ANNIEDisplay,0)

};

#endif
