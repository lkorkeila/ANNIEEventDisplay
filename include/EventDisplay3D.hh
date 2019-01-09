#ifndef EVENTDISPLAY3D_HH
#define EVENTDISPLAY3D_HH

#include "TObject.h"
#include "TObject.h"
#include "TString.h"
#include "TFile.h"
#include "TH1.h"

#include <string>
#include <iostream>
#include <cmath>
#include <map>

#include "TGeometry.h"
#include "TGeoManager.h"
#include "TGeoMaterial.h"
#include "TGeoMatrix.h"

#include "TEveManager.h"
#include "TEveEventManager.h"
#include "TEveViewer.h"
#include "TEveGeoNode.h"
#include "TEvePointSet.h"
#include "TEveStraightLineSet.h"
#include "TEveArrow.h"
#include "TEveText.h"


class EventDisplay3D : public TObject {

 public: 

  EventDisplay3D();

  ~EventDisplay3D();

  void PlotEvent();

  void AddPMTHit(double x, double y, double z, double t, double q);
  void AddLAPPDHit(double x, double y, double z, double t, double q);
  void ClearPMTHits();
  void ClearLAPPDHits();

  void DrawDetector();

  void SetTimeRanges(double min, double max);
  bool TimeRangeSet;

 private: 
  std::vector<double> PMTX;
  std::vector<double> PMTY;
  std::vector<double> PMTZ;
  std::vector<double> PMTT;
  std::vector<double> PMTQ;
  
  std::vector<double> LAPPDX;
  std::vector<double> LAPPDY;
  std::vector<double> LAPPDZ;
  std::vector<double> LAPPDT;
  std::vector<double> LAPPDQ;

 
  double _tb[8];
  TGeoManager *geom;	
  TGeoMaterial *matVacuum;
  TGeoMaterial *matWater;
  TGeoMedium* Vacuum;
  TGeoMedium* Water;     

  TGeoVolume *top; 

  ClassDef(EventDisplay3D,0)

};

#endif
