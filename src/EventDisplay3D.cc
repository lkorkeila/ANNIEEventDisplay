#include "EventDisplay3D.hh"
#include "TObject.h"
#include "TString.h"
#include "TFile.h"
#include "TH1.h"

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
#include "TStyle.h"


#include <iostream>
#include <cmath>

//ClassImp(EventDisplay3D)

EventDisplay3D::EventDisplay3D()
{
  // set default time ranges
  _tb[0] = 5.0;
  _tb[1] = 10.0;
  _tb[2] = 15.0;
  _tb[3] = 20.0;
  _tb[4] = 25.0;
  _tb[5] = 30.0;
  _tb[6] = 40.0;
  _tb[7] = 50.0;
         

}

EventDisplay3D::~EventDisplay3D()
{

}

void EventDisplay3D::DrawDetector(){

  TGeoManager *geom = new TGeoManager("DetectorGeometry", "detector geometry");

  // materials
  TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum",0.0,0.0,0.0);
  TGeoMaterial *matWater = new TGeoMaterial("Water",18.0,8.0,1.0);

  // media
  TGeoMedium* Vacuum = new TGeoMedium("Vacuum",1,matVacuum);
  TGeoMedium* Water = new TGeoMedium("Water",2,matWater);

  // top volume
  TGeoVolume *top = geom->MakeBox("Detector", Vacuum, 10000.0, 10000.0, 10000.0);
  geom->SetTopVolume(top);

  //Double_t fCylRadius = 1250.;
  Double_t fCylRadius = 1524.;

  Double_t fCylLength = 3962.;

  TGeoVolume* myCylinder = geom->MakeTube("Cylinder",Water,0.0,fCylRadius,0.5*fCylLength);
  myCylinder->SetLineColor(kCyan);
  myCylinder->SetTransparency(70);  // percentage transparency [0-100]
  myCylinder->SetVisibility(1);     
  top->AddNode( myCylinder, 0, new TGeoTranslation(0, 0, 0));

  // close geometry
  geom->CloseGeometry();

  std::cout<<"Made it this far!"<<std::endl;
	

  // Create Geometry in Event Display
  // ================================

  TGeoNode* node = gGeoManager->GetTopNode();
  TEveGeoTopNode* eveNode = new TEveGeoTopNode(gGeoManager, node);
  eveNode->SetVisLevel(1);
  gEve->AddGlobalElement(eveNode);



  // Draw Display
  // ============
  gEve->Redraw3D(kTRUE);



}

void EventDisplay3D::SetTimeRanges(double Min, double Max){
  // Given input range of timebins, calculate the color for each time bin
  if (Min > Max){
    std::cout << "Minimum time must be smaller than Maximum time"  << std::endl;
  }
  _tb[0] = Min;
  double TimeRange = Max - Min;
  double TimeSegment = TimeRange/7;
  double currentInt = Min;
  for (int i=1;i < 7; i++){
    currentInt+=TimeSegment;
    _tb[i] = currentInt;
  }
  _tb[7] = Max;
  TimeRangeSet = true;
  return;
}

void EventDisplay3D::PlotEvent(){
  if(!TimeRangeSet){
    std::cout << "Please set time range before plotting an event" << std::endl;
  }

  // Containers for Hits
  // ===================
  Int_t markerStyle = 4;   
  //Double_t markerSize = 0.25;
  Double_t markerSize = 3.0;


  Int_t colourCode1 = kBlue+1;
  Int_t colourCode2 = kCyan+1;
  Int_t colourCode3 = kGreen;
  Int_t colourCode4 = kYellow;
  Int_t colourCode5 = kOrange;
  Int_t colourCode6 = kOrange+7;
  Int_t colourCode7 = kRed;
  Int_t colourCode8 = kRed;
  Int_t colourCode9 = kRed;
 

  TEvePointSet* fHitList1 = new TEvePointSet(); 
  fHitList1->SetMarkerColor(colourCode1);
  fHitList1->SetMarkerSize(markerSize);
  fHitList1->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList1);

  TEvePointSet* fHitList2 = new TEvePointSet(); 
  fHitList2->SetMarkerColor(colourCode2);
  fHitList2->SetMarkerSize(markerSize);
  fHitList2->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList2);

  TEvePointSet* fHitList3 = new TEvePointSet();  
  fHitList3->SetMarkerColor(colourCode3);
  fHitList3->SetMarkerSize(markerSize);
  fHitList3->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList3);

  TEvePointSet* fHitList4 = new TEvePointSet();  
  fHitList4->SetMarkerColor(colourCode4);
  fHitList4->SetMarkerSize(markerSize);
  fHitList4->SetMarkerStyle(markerStyle);  
  gEve->AddElement(fHitList4);

  TEvePointSet* fHitList5 = new TEvePointSet();  
  fHitList5->SetMarkerColor(colourCode5);
  fHitList5->SetMarkerSize(markerSize);
  fHitList5->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList5);

  TEvePointSet* fHitList6 = new TEvePointSet();  
  fHitList6->SetMarkerColor(colourCode6);
  fHitList6->SetMarkerSize(markerSize);
  fHitList6->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList6);

  TEvePointSet* fHitList7 = new TEvePointSet();  
  fHitList7->SetMarkerColor(colourCode7);
  fHitList7->SetMarkerSize(markerSize);
  fHitList7->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList7);

  TEvePointSet* fHitList8 = new TEvePointSet(); 
  fHitList8->SetMarkerColor(colourCode8);
  fHitList8->SetMarkerSize(markerSize);
  fHitList8->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList8);

  TEvePointSet* fHitList9 = new TEvePointSet();
  fHitList9->SetMarkerColor(colourCode9);
  fHitList9->SetMarkerSize(markerSize);
  fHitList9->SetMarkerStyle(markerStyle);
  gEve->AddElement(fHitList9);


  // Loop over digits
  // ================
  for(int i=0; i < PMTT.size(); i++){
    
    double t = PMTT[i];
     
    double x = PMTX[i];
    double y = PMTY[i];
    double z = PMTZ[i];

    Int_t listNumber = 0;

    if( t<_tb[0] )               listNumber = 1;
    if( t>=_tb[0] && t<_tb[1] )  listNumber = 2;
    if( t>=_tb[1] && t<_tb[2] )  listNumber = 3;
    if( t>=_tb[2] && t<_tb[3] )  listNumber = 4;
    if( t>=_tb[3] && t<_tb[4] )  listNumber = 5;
    if( t>=_tb[4] && t<_tb[5] )  listNumber = 6;
    if( t>=_tb[5] && t<_tb[6] )  listNumber = 7;
    if( t>=_tb[6] && t<_tb[7] )  listNumber = 8;
    if( t>=_tb[7] )              listNumber = 9;



    switch( listNumber ){
      case 1: fHitList1->SetNextPoint(x,y,z); break;
      case 2: fHitList2->SetNextPoint(x,y,z); break;
      case 3: fHitList3->SetNextPoint(x,y,z); break;
      case 4: fHitList4->SetNextPoint(x,y,z); break;
      case 5: fHitList5->SetNextPoint(x,y,z); break;
      case 6: fHitList6->SetNextPoint(x,y,z); break;
      case 7: fHitList7->SetNextPoint(x,y,z); break;
      case 8: fHitList8->SetNextPoint(x,y,z); break;
      case 9: fHitList9->SetNextPoint(x,y,z); break;
      default: break;
    }
  }
  
  // Re-draw Event Display
  // =====================
  gEve->Redraw3D();

  return;
}

void EventDisplay3D::AddPMTHit(double x, double y, double z, double t, double q){
  PMTX.push_back(x);
  PMTY.push_back(y);
  PMTZ.push_back(z);
  PMTT.push_back(t);
  PMTQ.push_back(q);
}

void EventDisplay3D::AddLAPPDHit(double x, double y, double z, double t, double q){
  LAPPDX.push_back(x);
  LAPPDY.push_back(y);
  LAPPDZ.push_back(z);
  LAPPDT.push_back(t);
  LAPPDQ.push_back(q);
}

void EventDisplay3D::ClearPMTHits(){
  PMTX.clear();
  PMTY.clear();
  PMTZ.clear();
  PMTT.clear();
  PMTQ.clear();
}

void EventDisplay3D::ClearLAPPDHits(){
  LAPPDX.clear();
  LAPPDY.clear();
  LAPPDZ.clear();
  LAPPDT.clear();
  LAPPDQ.clear();
}
