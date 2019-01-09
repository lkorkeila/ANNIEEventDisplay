#include "EventDisplay3D.hh"

ClassImp(EventDisplay3D)

EventDisplay3D::EventDisplay3D()
{
  //Initialize some times so the timebins are not empty
  this->SetTimeRanges(-30.0, 30.0); 

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
  Double_t fCylRadius = 152.4;

  Double_t fCylLength = 396.2;

  TGeoVolume* myCylinder = geom->MakeTube("Cylinder",Water,0.0,fCylRadius,0.5*fCylLength);
  myCylinder->SetLineColor(kCyan);
  myCylinder->SetTransparency(70);  // percentage transparency [0-100]
  myCylinder->SetVisibility(1);
  TGeoRotation* cylinderrot = new TGeoRotation();
  cylinderrot->RotateX(90.0);
  top->AddNode( myCylinder, 0, new TGeoCombiTrans(0.,0.0,0.,cylinderrot));

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

  // Delete the Current Event (and deletes the elements in it
  TEveEventManager * currentEvent = gEve->GetCurrentEvent();
  delete currentEvent;

  // Containers for Hits
  // ===================
  Int_t markerStyle = 4;   
  //Double_t PMTmarkerSize = 0.25;
  Double_t PMTmarkerSize = 3.0;
  Double_t LAPPDmarkerSize = 1.0;


  Int_t colourCode1 = kBlue+1;
  Int_t colourCode2 = kCyan+1;
  Int_t colourCode3 = kGreen;
  Int_t colourCode4 = kYellow;
  Int_t colourCode5 = kOrange;
  Int_t colourCode6 = kOrange+7;
  Int_t colourCode7 = kRed;
  Int_t colourCode8 = kRed;
  Int_t colourCode9 = kRed;

  gEve->AddEvent(new TEveEventManager("PMT Hit Times (ns)","ANNIE Events")); 

  TEvePointSet* fPMTHitList1 = new TEvePointSet(); 
  fPMTHitList1->SetMarkerColor(colourCode1);
  fPMTHitList1->SetMarkerSize(PMTmarkerSize);
  fPMTHitList1->SetMarkerStyle(markerStyle);
  fPMTHitList1->SetElementName(this->GetTimeRange(1));
  gEve->AddElement(fPMTHitList1);

  TEvePointSet* fPMTHitList2 = new TEvePointSet(); 
  fPMTHitList2->SetMarkerColor(colourCode2);
  fPMTHitList2->SetMarkerSize(PMTmarkerSize);
  fPMTHitList2->SetMarkerStyle(markerStyle);
  fPMTHitList2->SetElementName(this->GetTimeRange(2));
  gEve->AddElement(fPMTHitList2);

  TEvePointSet* fPMTHitList3 = new TEvePointSet();  
  fPMTHitList3->SetMarkerColor(colourCode3);
  fPMTHitList3->SetMarkerSize(PMTmarkerSize);
  fPMTHitList3->SetMarkerStyle(markerStyle);
  fPMTHitList3->SetElementName(this->GetTimeRange(3));
  gEve->AddElement(fPMTHitList3);

  TEvePointSet* fPMTHitList4 = new TEvePointSet();  
  fPMTHitList4->SetMarkerColor(colourCode4);
  fPMTHitList4->SetMarkerSize(PMTmarkerSize);
  fPMTHitList4->SetMarkerStyle(markerStyle);
  fPMTHitList4->SetElementName(this->GetTimeRange(4));
  gEve->AddElement(fPMTHitList4);

  TEvePointSet* fPMTHitList5 = new TEvePointSet();  
  fPMTHitList5->SetMarkerColor(colourCode5);
  fPMTHitList5->SetMarkerSize(PMTmarkerSize);
  fPMTHitList5->SetMarkerStyle(markerStyle);
  fPMTHitList5->SetElementName(this->GetTimeRange(5));
  gEve->AddElement(fPMTHitList5);

  TEvePointSet* fPMTHitList6 = new TEvePointSet();  
  fPMTHitList6->SetMarkerColor(colourCode6);
  fPMTHitList6->SetMarkerSize(PMTmarkerSize);
  fPMTHitList6->SetMarkerStyle(markerStyle);
  fPMTHitList6->SetElementName(this->GetTimeRange(6));
  gEve->AddElement(fPMTHitList6);

  TEvePointSet* fPMTHitList7 = new TEvePointSet();  
  fPMTHitList7->SetMarkerColor(colourCode7);
  fPMTHitList7->SetMarkerSize(PMTmarkerSize);
  fPMTHitList7->SetMarkerStyle(markerStyle);
  fPMTHitList7->SetElementName(this->GetTimeRange(7));
  gEve->AddElement(fPMTHitList7);

  TEvePointSet* fPMTHitList8 = new TEvePointSet(); 
  fPMTHitList8->SetMarkerColor(colourCode8);
  fPMTHitList8->SetMarkerSize(PMTmarkerSize);
  fPMTHitList8->SetMarkerStyle(markerStyle);
  fPMTHitList8->SetElementName(this->GetTimeRange(8));
  gEve->AddElement(fPMTHitList8);

  TEvePointSet* fPMTHitList9 = new TEvePointSet();
  fPMTHitList9->SetMarkerColor(colourCode9);
  fPMTHitList9->SetMarkerSize(PMTmarkerSize);
  fPMTHitList9->SetMarkerStyle(markerStyle);
  fPMTHitList9->SetElementName(this->GetTimeRange(9));
  gEve->AddElement(fPMTHitList9);

  gEve->AddEvent(new TEveEventManager("LAPPD Hit Times (ns)","ANNIE Events")); 

  TEvePointSet* fLAPPDHitList1 = new TEvePointSet(); 
  fLAPPDHitList1->SetMarkerColor(colourCode1);
  fLAPPDHitList1->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList1->SetMarkerStyle(markerStyle);
  fLAPPDHitList1->SetElementName(this->GetTimeRange(1));
  gEve->AddElement(fLAPPDHitList1);

  TEvePointSet* fLAPPDHitList2 = new TEvePointSet(); 
  fLAPPDHitList2->SetMarkerColor(colourCode2);
  fLAPPDHitList2->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList2->SetMarkerStyle(markerStyle);
  fLAPPDHitList2->SetElementName(this->GetTimeRange(2));
  gEve->AddElement(fLAPPDHitList2);

  TEvePointSet* fLAPPDHitList3 = new TEvePointSet();  
  fLAPPDHitList3->SetMarkerColor(colourCode3);
  fLAPPDHitList3->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList3->SetMarkerStyle(markerStyle);
  fLAPPDHitList3->SetElementName(this->GetTimeRange(3));
  gEve->AddElement(fLAPPDHitList3);

  TEvePointSet* fLAPPDHitList4 = new TEvePointSet();  
  fLAPPDHitList4->SetMarkerColor(colourCode4);
  fLAPPDHitList4->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList4->SetMarkerStyle(markerStyle);
  fLAPPDHitList4->SetElementName(this->GetTimeRange(4));
  gEve->AddElement(fLAPPDHitList4);

  TEvePointSet* fLAPPDHitList5 = new TEvePointSet();  
  fLAPPDHitList5->SetMarkerColor(colourCode5);
  fLAPPDHitList5->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList5->SetMarkerStyle(markerStyle);
  fLAPPDHitList5->SetElementName(this->GetTimeRange(5));
  gEve->AddElement(fLAPPDHitList5);

  TEvePointSet* fLAPPDHitList6 = new TEvePointSet();  
  fLAPPDHitList6->SetMarkerColor(colourCode6);
  fLAPPDHitList6->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList6->SetMarkerStyle(markerStyle);
  fLAPPDHitList6->SetElementName(this->GetTimeRange(6));
  gEve->AddElement(fLAPPDHitList6);

  TEvePointSet* fLAPPDHitList7 = new TEvePointSet();  
  fLAPPDHitList7->SetMarkerColor(colourCode7);
  fLAPPDHitList7->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList7->SetMarkerStyle(markerStyle);
  fLAPPDHitList7->SetElementName(this->GetTimeRange(7));
  gEve->AddElement(fLAPPDHitList7);

  TEvePointSet* fLAPPDHitList8 = new TEvePointSet(); 
  fLAPPDHitList8->SetMarkerColor(colourCode8);
  fLAPPDHitList8->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList8->SetMarkerStyle(markerStyle);
  fLAPPDHitList8->SetElementName(this->GetTimeRange(8));
  gEve->AddElement(fLAPPDHitList8);

  TEvePointSet* fLAPPDHitList9 = new TEvePointSet();
  fLAPPDHitList9->SetMarkerColor(colourCode9);
  fLAPPDHitList9->SetMarkerSize(LAPPDmarkerSize);
  fLAPPDHitList9->SetMarkerStyle(markerStyle);
  fLAPPDHitList9->SetElementName(this->GetTimeRange(9));
  gEve->AddElement(fLAPPDHitList9);



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
      case 1: fPMTHitList1->SetNextPoint(x,y,z); break;
      case 2: fPMTHitList2->SetNextPoint(x,y,z); break;
      case 3: fPMTHitList3->SetNextPoint(x,y,z); break;
      case 4: fPMTHitList4->SetNextPoint(x,y,z); break;
      case 5: fPMTHitList5->SetNextPoint(x,y,z); break;
      case 6: fPMTHitList6->SetNextPoint(x,y,z); break;
      case 7: fPMTHitList7->SetNextPoint(x,y,z); break;
      case 8: fPMTHitList8->SetNextPoint(x,y,z); break;
      case 9: fPMTHitList9->SetNextPoint(x,y,z); break;
      default: break;
    }
  }

  // Loop over LAPPD Hits 
  // ================
  for(int i=0; i < LAPPDT.size(); i++){
    
    double t = LAPPDT[i];
    double x = LAPPDX[i];
    double y = LAPPDY[i];
    double z = LAPPDZ[i];

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
      case 1: fLAPPDHitList1->SetNextPoint(x,y,z); break;
      case 2: fLAPPDHitList2->SetNextPoint(x,y,z); break;
      case 3: fLAPPDHitList3->SetNextPoint(x,y,z); break;
      case 4: fLAPPDHitList4->SetNextPoint(x,y,z); break;
      case 5: fLAPPDHitList5->SetNextPoint(x,y,z); break;
      case 6: fLAPPDHitList6->SetNextPoint(x,y,z); break;
      case 7: fLAPPDHitList7->SetNextPoint(x,y,z); break;
      case 8: fLAPPDHitList8->SetNextPoint(x,y,z); break;
      case 9: fLAPPDHitList9->SetNextPoint(x,y,z); break;
      default: break;
    }
  }

  // Re-draw Event Display
  // =====================
  gEve->Redraw3D();

  return;
}

const char * EventDisplay3D::GetTimeRange(int PointSet){
  std::ostringstream strs; 
  if (PointSet < 1 || PointSet > 9){
    std::cout << "Problem labeling point set; outside defined indices" << std::endl;
    strs << "nope";
  } else if (PointSet == 1){
    strs << "< " << _tb[0];
  } else if (PointSet == 9){
    strs << "> " << _tb[7];
  } else { 
    strs << _tb[PointSet - 1] << " to " << _tb[PointSet];
  }
  std::string TimeRange = strs.str();
  return TimeRange.c_str();
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
