#define Train_cxx
#include "Train.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <algorithm>

// comparator for pointers to Event
bool sortByRun(Event *l, Event *r) { return l->getRunNumber() < r->getRunNumber(); };

void Train::DoTrain(int nCutPoints) {

  // make sure we have enough cut points
  if(nCutPoints < 0) {
    std::cout << "DoTrain: nCutPoints is less than 0. Using all available cut points!" << std::endl;
    nCutPoints = m_CutPoints.size();
  }
  else if(m_CutPoints.size() < nCutPoints) {
    std::cout << "DoTrain: Requested more cut points than are available! Using all available cut points." << std::endl;
    nCutPoints = m_CutPoints.size();
  }
  std::cout << "DoTrain: Running over " << nCutPoints << " cut points." << std::endl;

  // create maps [ run number, [total events, square of stat error] ]
  std::map<int,std::pair<double, double> > pass_map; // pass the cut point
  std::map<int,std::pair<double, double> > seen_map; // all events

  // initialize timer
  std::clock_t cl_start    = std::clock();

  // sort the vector of events by run number
  std::cout << "Sorting vector of events by run number" << std::endl;
  std::sort(m_Events.begin(), m_Events.end(),sortByRun);
  std::cout << "Done sorting vector in " << ((std::clock() - cl_start) / (double)CLOCKS_PER_SEC) << "s" << std::endl;

  // update timer before cut point loop
  cl_start = std::clock();
  double cl_previous = cl_start;

  // loop over cut points
  for(unsigned int i=0; i<nCutPoints; i++) {
    if(i%1000 == 0) {
      double cl_duration = (std::clock() - cl_start)   / (double)CLOCKS_PER_SEC;
      double cl_split    = (std::clock() - cl_previous)/ (double)CLOCKS_PER_SEC;
      std::cout << "Checking cut point " << i << "/" << nCutPoints 
		<< "\tElapsed time: " << cl_duration 
		<< "s\tSplit: " << cl_split << "s" << std::endl;
      cl_previous = std::clock();
    }

    pass_map.clear();
    seen_map.clear();
    //m_run_numbers.clear(); // i don't know why this line is here

    // set up run number markers
    int currRun = -1;
    int prevRun = (*m_Events.begin())->getRunNumber();
    // set up weight and error totals
    double runWeight_seen = 0.0;
    double runError2_seen = 0.0;
    double runWeight_pass = 0.0;
    double runError2_pass = 0.0;

    for(std::vector<Event*>::iterator e=m_Events.begin(); e != m_Events.end(); ++e) {
      // pointer to event
      Event *ev = (*e);

      // store relevant numbers (saves a tiny bit of time)
      int runNumber = ev->getRunNumber();
      double weight = ev->getWeight();
      currRun = runNumber;

      // if we've moved on to a new run
      if(currRun != prevRun) {
	// add previous run's info to map
	seen_map[prevRun] = std::make_pair(runWeight_seen, runError2_seen);
	pass_map[prevRun] = std::make_pair(runWeight_pass, runError2_pass);
	// reset event counts
	runWeight_seen = 0.0;
	runError2_seen = 0.0;
	runWeight_pass = 0.0;
	runError2_pass = 0.0;
	// update previous run
	prevRun = currRun;
      }

      // things we do every event
      runWeight_seen = runWeight_seen + weight;
      runError2_seen = runError2_seen + weight*weight;
      if(passCut(*ev, *(m_CutPoints.at(i)))) {
	runWeight_pass = runWeight_pass + weight;
	runError2_pass = runError2_pass + weight*weight;
      }

    }
    // since we finished with the last event nothing will trigger storing the run info
    //  --> need to do it manually
    seen_map[prevRun] = std::make_pair(runWeight_seen, runError2_seen);
    pass_map[prevRun] = std::make_pair(runWeight_pass, runError2_pass);

    // fill output tree for this cut point
    cp_index     = m_CutPoints.at(i)->getIndex();
    o_mll        = m_CutPoints.at(i)->getMll();
    o_mjj        = m_CutPoints.at(i)->getMjj();
    o_centrality = m_CutPoints.at(i)->getCentrality();
    o_lep0pt     = m_CutPoints.at(i)->getLep0pt();
    o_lep1pt     = m_CutPoints.at(i)->getLep1pt();
    o_jet0pt     = m_CutPoints.at(i)->getJet0pt();
    o_jet1pt     = m_CutPoints.at(i)->getJet1pt();
    FillTree(seen_map, pass_map);
    t_out->Fill();

  } // cut point loop

  FillTotals(seen_map);

  return;
}

int Train::ReadSignal() {
  if (fChain == 0) return 0;
  
  // reset vectors
  m_CutPoints.clear();
  m_SigEvents.clear();
  
  // counters
  int nEvents = 0;
  int cutPointIndex = 0;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if(jentry % 10000 == 0) std::cout << "Processing signal event #" << jentry << std::endl;
    
    nEvents++;

    // event selection
    if(pass_selection < m_SelectionCut) continue;
    
    // update run number if we're using polarization samples
    int newRunNumber = 999999;
    if(runNumber == 990031) newRunNumber = 666666;

    // get weight
    float weight = weight_total_no3rdlep;
    float norm   = m_xsecDict[newRunNumber];
    if(norm > 0) weight = weight * norm;

    Event *e = new Event(999999,
			 weight,
			 leptons_selected_l0_pt,
			 leptons_selected_l1_pt,
			 jets_selected_j0_pt,
			 jets_selected_j1_pt,
			 mll,
			 mjj,
			 detajj,
			 lepjet_centrality);
    m_SigEvents.push_back(e);
    m_Events   .push_back(e);
    
    CutPoint *c = new CutPoint(cutPointIndex,*e);
    cutPointIndex++;
    m_CutPoints.push_back(c);

    // add the run number to the run number vector (only if it's not already there)
    if(std::find(m_run_numbers.begin(), m_run_numbers.end(), 999999) == m_run_numbers.end()) {
      m_run_numbers.push_back(999999);
    }
    
  }

  return nEvents;
}

int Train::ReadBackground() {
  if (fChain == 0) return 0;
  
  // reset vectors
  m_BkgEvents.clear();
  
  // counters
  int nEvents = 0;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if(jentry % 100000 == 0) std::cout << "Processing background event #" << jentry << std::endl;
    
    nEvents++;

    // event selection
    if(pass_selection < m_SelectionCut) continue;
    
    // get weight
    float weight = weight_total_no3rdlep;
    float norm   = m_xsecDict[runNumber];
    if(norm > 0) weight = weight * norm;

    // update run number for flip/fake
    int newRunNumber = runNumber;
    if     (event_isFlip) newRunNumber = 111111;
    else if(event_isFake) newRunNumber = 222222;

    Event *e = new Event(newRunNumber, 
			 weight,
			 leptons_selected_l0_pt,
			 leptons_selected_l1_pt,
			 jets_selected_j0_pt,
			 jets_selected_j1_pt,
			 mll,
			 mjj,
			 detajj,
			 lepjet_centrality);
    m_BkgEvents.push_back(e);
    m_Events   .push_back(e);

    // add the run number to the run number vector (only if it's not already there)
    if(std::find(m_run_numbers.begin(), m_run_numbers.end(), newRunNumber) == m_run_numbers.end()) {
      m_run_numbers.push_back(newRunNumber);
    }
    
  }

  return nEvents;
}

bool Train::passCut(Event &e, CutPoint &cp) {
  if(e.getMjj()    < cp.getMjj()) return false;
  if(e.getMll()    < cp.getMll()) return false;
  //if(e.getDetajj() < cp.getDetajj()) return false;
  if(e.getCentrality() < cp.getCentrality()) return false;
  if(e.getLep0pt() < cp.getLep0pt()) return false;
  //if(e.getLep1pt() < cp.getLep1pt()) return false;
  if(e.getJet0pt() < cp.getJet0pt()) return false;
  if(e.getJet1pt() < cp.getJet1pt()) return false;
  return true;
}

void Train::SetupCrossSections(std::string filepath) {
  // reads input file and constructs map of normalization factors for event weighting
  std::ifstream inFile(filepath.c_str());

  if(!inFile) {
    std::cerr << "FATAL SetupCrossSections: Unable to open cross section input file!" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string line;

  while(std::getline(inFile, line)) {
    std::istringstream iss(line);

    int run;
    float xsec, kfac, feff, sumw;

    if(!(iss >> run >> xsec >> kfac >> feff >> sumw)) continue;
    if(run == 0) continue;

    float weight = xsec*kfac*feff/sumw * m_Lumi;

    if(!m_xsecDict.count(run)) {
      m_xsecDict[run] = weight;
    }
    else {
      std::cout << "SetupCrossSections: Weight for run " << run << " already in map!" << std::endl;
    }
    
  }
  
}
