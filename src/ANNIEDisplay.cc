#include "ANNIEDisplay.hh"





#include <iostream>
#include <cmath>

ClassImp(ANNIEDisplay)

ANNIEDisplay::ANNIEDisplay()
{
  TEveManager::Create();

  // create new TStyle
  TStyle *fRootStyle = new  TStyle("My Style", "");

  // set the background color to white
  fRootStyle->SetFillColor(10);
  fRootStyle->SetFrameFillColor(10);
  fRootStyle->SetCanvasColor(10);
  fRootStyle->SetPadColor(10);
  fRootStyle->SetTitleFillColor(0);
  fRootStyle->SetStatColor(10);

  // don't put a colored frame around the plots
  fRootStyle->SetFrameBorderMode(0);
  fRootStyle->SetCanvasBorderMode(0);
  fRootStyle->SetPadBorderMode(0);
  fRootStyle->SetLegendBorderSize(0);

  // use the primary color palette
  fRootStyle->SetPalette(1,0);

  // set the default line color for a histogram to be black
  fRootStyle->SetHistLineColor(kBlack);

  // set the default line color for a fit function to be red
  fRootStyle->SetFuncColor(kRed);

  // make the axis labels black
  fRootStyle->SetLabelColor(kBlack,"xyz");

  // set the default title color to be black
  fRootStyle->SetTitleColor(kBlack);

  // set the margins
  fRootStyle->SetPadBottomMargin(0.18);
  fRootStyle->SetPadTopMargin(0.08);
  fRootStyle->SetPadRightMargin(0.08);
  fRootStyle->SetPadLeftMargin(0.17);

  // set axis label and title text sizes
  fRootStyle->SetLabelFont(42,"xyz");
  fRootStyle->SetLabelSize(0.06,"xyz");
  fRootStyle->SetLabelOffset(0.015,"xyz");
  fRootStyle->SetTitleFont(42,"xyz");
  fRootStyle->SetTitleSize(0.07,"xyz");
  fRootStyle->SetTitleOffset(1.1,"yz");
  fRootStyle->SetTitleOffset(1.0,"x");
  fRootStyle->SetStatFont(42);
  fRootStyle->SetStatFontSize(0.07);
  fRootStyle->SetTitleBorderSize(0);
  fRootStyle->SetStatBorderSize(0);
  fRootStyle->SetTextFont(42);

  // set line widths
  fRootStyle->SetFrameLineWidth(2);
  fRootStyle->SetFuncWidth(2);

  // set the number of divisions to show
  fRootStyle->SetNdivisions(506, "xy");

  // turn off xy grids
  fRootStyle->SetPadGridX(0);
  fRootStyle->SetPadGridY(0);

  // set the tick mark style
  fRootStyle->SetPadTickX(1);
  fRootStyle->SetPadTickY(1);

  // turn off stats
  fRootStyle->SetOptStat(0);

  // marker settings
  fRootStyle->SetMarkerStyle(20);
  fRootStyle->SetMarkerSize(1.2);
  fRootStyle->SetLineWidth(1);

  // done
  fRootStyle->cd();
//  gROOT->ForceStyle();
//  gStyle->ls();

}

ANNIEDisplay::~ANNIEDisplay()
{

}

void ANNIEDisplay::InitializeGUI(){
  ed->DrawDetector();
  this->make_evnav_gui();
}

void ANNIEDisplay::ShowEvent(){
  ed->SetTimeRanges(TimeRangeMin, TimeRangeMax);
  ed->PlotEvent();
  std::cout << "DISPLAYING EVENT " << CurrentEvNum << std::endl;
}

void ANNIEDisplay::make_evnav_gui(){
  // Create minimal GUI for event navigation.
  TEveBrowser* browser = gEve->GetBrowser();
  browser->StartEmbedding(TRootBrowser::kLeft);

  TGMainFrame* frmMain = new TGMainFrame(gClient->GetRoot(), 1000, 600);
  frmMain->SetWindowName("XX GUI");
  frmMain->SetCleanup(kDeepCleanup);

  TGHorizontalFrame* hf = new TGHorizontalFrame(frmMain);
  {
    TString icondir( Form("%s/icons/", gSystem->Getenv("ROOTSYS")) );
    TGPictureButton* b = 0;
    b = new TGPictureButton(hf, gClient->GetPicture(icondir+"GoBack.gif"));
    hf->AddFrame(b);
    b->Connect("Clicked()", "ANNIEDisplay", this, "BackEvent()");

    b = new TGPictureButton(hf, gClient->GetPicture(icondir+"GoForward.gif"));
    hf->AddFrame(b);
    b->Connect("Clicked()", "ANNIEDisplay", this, "ForwardEvent()");
  }
  // as well as TimeScaleButton
  frmMain->AddFrame(hf);

  frmMain->MapSubwindows();
  frmMain->Resize();
  frmMain->MapWindow();

  browser->StopEmbedding();
  browser->SetTabTitle("Event Control", 0);
}

void ANNIEDisplay::GoToEvent(int evnum){
  if ((evnum > TotalEntries) || (evnum < 0)){
    printf("Invalid entry selection.\n");
    //TODO: have this print to some message log in GUI window
  } else {
    CurrentEvNum = evnum;
    this->LoadNTupleEvent();
    this->ShowEvent();
  }
}

void ANNIEDisplay::ForwardEvent(){
  if (CurrentEvNum < TotalEntries) {
    ++CurrentEvNum;
    this->LoadNTupleEvent();
    this->ShowEvent();
    //TODO: Example re-loads the event here.  Do we really want
    //This class to have the load power though?
  } else {
    printf("Already at last event.\n");
  }
}

void ANNIEDisplay::BackEvent(){
  if (CurrentEvNum > 0) {
    --CurrentEvNum;
    this->LoadNTupleEvent();
    this->ShowEvent();
  } else {
    printf("Already at first event.\n");
  }
}

void ANNIEDisplay::LoadDemoEvent(TString evtname){
  TFile* datafile = new TFile(datafilename);
    TH2D* disphist = (TH2D*) datafile->Get(evtname);
    
  for(int j=0; j<8; j++){
    for(int k=0; k<8; k++){
    
        std::cout<<j<<" "<<k<<std::endl;
      
      double bc = disphist->GetBinContent(j+1,k+1);
      if( (j==0 && k==0) || (j==7 && k==0) || (j==0 && k==7) || (j==7 && k==7)) continue;
        //double bc = 5;
        double xcoor = (-3.5 + ((double)j+0.5)*0.875)*304.8;
        double ycoor = (-3.5 + ((double)k+0.5)*0.875)*304.8;
        double zcoor = -1981.2;
        //Assume the bin content here is time.  Fill in
        //0.0 for the charge info. for now
        if(bc!=0) ed->AddPMTHit(xcoor,ycoor,zcoor, bc,0.0);
    }
  }
}

void ANNIEDisplay::LoadNTupleEvent(){
  ed->ClearPMTHits();
  TChain* evtree = new TChain(datatree);
  evtree->Add(datafilename); 
  std::vector<double> *digitx = 0;
  std::vector<double> *digity = 0;
  std::vector<double> *digitz = 0;
  std::vector<double> *digitt = 0;
  std::vector<double> *digitq = 0;
  std::vector<int> *digittype = 0;

  evtree->SetBranchAddress("digitX",&digitx);
  evtree->SetBranchAddress("digitY",&digity);
  evtree->SetBranchAddress("digitZ",&digitz);
  evtree->SetBranchAddress("digitT",&digitt);
  evtree->SetBranchAddress("digitQ",&digitq);
  evtree->SetBranchAddress("digitType",&digittype);

  evtree->GetEvent(CurrentEvNum);
  //Now, loop through digit types and add PMT hits
  for (int i = 0; i < digittype->size(); i++){
    if ((*digittype)[i]==0){ //is PMT
      double xcoor = digitx->at(i);
      double ycoor = digity->at(i);
      double zcoor = digitz->at(i);
      double time = digitt->at(i);
      double charge = digitq->at(i);
      ed->AddPMTHit(xcoor,ycoor,zcoor, time,charge);
    }
  } 

}
