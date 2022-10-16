#include "TFile.h"
#include "TTree.h"
#include <iostream> 
#include "Pythia8/Pythia.h"

using namespace Pythia8;
using namespace std;

//pp COLLISIONS FOR LHC

int main() {
	
	// Generator.
  Pythia pythia;
  Settings& settings  = pythia.settings;
  
	// Decrease the output.
	pythia.readString("Stat:reset = on");
  pythia.readString("Init:showMultipartonInteractions = off");
  pythia.readString("Init:showChangedSettings = off");
  pythia.readString("Init:showChangedParticleData = off");
  pythia.readString("Next:numberCount = 0");
  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");
  pythia.readString("Stat:reset = on");
  
	TFile *eventdata = new TFile("eventdata.root","recreate");
  TTree *T = new TTree("events", "4-Momentum of all Charged Final State Particles");
  std::vector<Float_t> px,py,pz,e,pt,phi,eta,rap;
  std::vector<Int_t> eventid;
  T->Branch("eventid", "std::vector<Int_t>",  &eventid);
  T->Branch("px", "std::vector<Float_t>",  &px);
  T->Branch("py", "std::vector<Float_t>",  &py);
  T->Branch("pz", "std::vector<Float_t>",  &pz);
  T->Branch("e", "std::vector<Float_t>",  &e);
  T->Branch("pt", "std::vector<Float_t>",  &pt);		//transverse momentum
  T->Branch("phi", "std::vector<Float_t>",  &phi);	//azimuth angle
  T->Branch("eta", "std::vector<Float_t>",  &eta);	//pseudorapidity
  T->Branch("rap", "std::vector<Float_t>",  &rap);	//rapidity
  
  //pp collisions
  pythia.readString("Beams:idA = 2212");
  pythia.readString("Beams:idB = 2212");
  //Set Beam Energies :
  pythia.readString("Beams:eA  = 7000.");
  pythia.readString("Beams:eB  = 7000.");
  pythia.readString("Beams:eCM = 14000.");
  //Process Selection 
  //pythia.readString("SoftQCD:all = on");
  pythia.readString("HardQCD:all = on");
  
  pythia.readString("PhaseSpace:Q2Min = 125.0");
  //pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.init();
  
  int nEvents = 10000;
  
  //Counter
  int ev=0, c=0;
  
  for (int iEvent = 0; iEvent < nEvents; ++iEvent) {
  
  	//Clear out for next event
  	eventid.clear(); px.clear(); py.clear(); pz.clear(); e.clear();
    pt.clear(); phi.clear(); eta.clear(); rap.clear();
    
    if (!pythia.next()) continue;
    
    ev++;
    eventid.push_back(ev);
    
    if (iEvent == 0) {
      pythia.process.list();
      pythia.event.list();
    }
      
    for (int i = 0; i < pythia.event.size(); ++i){
    	//Storing Charged Final State Particles
      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()){
				px.push_back(pythia.event[i].px());
        py.push_back(pythia.event[i].py());
        pz.push_back(pythia.event[i].pz());
        e.push_back(pythia.event[i].e());
        pt.push_back(pythia.event[i].pT());
        phi.push_back(pythia.event[i].phi());
        eta.push_back(pythia.event[i].eta());
        rap.push_back(pythia.event[i].y());
        c++;
      }
    }
  	T->Fill();
  }
	
  pythia.stat();
  cout << "\nTotal Selected Events : " << ev << endl;
  cout << "Total Event Constituents : " << c << endl;
  
  eventdata->Write();
  eventdata->Close();
  delete eventdata;
}
    
      
      
      	
      	
