#include "Train.h"
#include <utility>
#include <cmath>

void Train::FillTree(std::map<int, std::pair<double, double> > seen_map, std::map<int, std::pair<double, double> > pass_map) {
  // map is structured as:
  //   - key          = run number
  //   - value.first  = events passing criteria
  //   - value.second = error squared

  float temp_seen = 0;

  // loop over all the runs and store the event info in the maps
  //   the values in the maps get written out to the tree
  for(std::vector<int>::iterator run = m_run_numbers.begin(); run != m_run_numbers.end(); ++run) {
    temp_seen = 0;
    m_count_map[*run] = pass_map[*run].first;
    m_error_map[*run] = pass_map[*run].second;
    temp_seen = seen_map[*run].first;
    m_fraction_map[*run] = (temp_seen != 0 ? pass_map[*run].first/temp_seen : 0.0);
  }

}

void Train::SetupOutput() {
  // create the output file and tree
  outputFile = new TFile("ssww.root", "RECREATE");
  t_out = new TTree("RGS", "RGS output");

  // fill the event maps with dummy values
  for(std::vector<int>::iterator run = m_run_numbers.begin(); run != m_run_numbers.end(); ++run) {
    m_count_map[*run] = -999.99;
    m_error_map[*run] = -999.99;
    m_fraction_map[*run] = -999.99;
  }

  // link all the output branches with their values
  t_out->Branch("mll",                    &o_mll);
  t_out->Branch("mjj",                    &o_mjj);
  t_out->Branch("lepjet_centrality",      &o_centrality);
  t_out->Branch("leptons_selected_l0_pt", &o_lep0pt);
  t_out->Branch("leptons_selected_l1_pt", &o_lep1pt);
  t_out->Branch("jets_selected_j0_pt",    &o_jet0pt);
  t_out->Branch("jets_selected_j1_pt",    &o_jet1pt);

  t_out->Branch("cutpointindex", &cp_index);

  // loop over the run numbers to create the branches for each run
  for(std::vector<int>::iterator run = m_run_numbers.begin(); run != m_run_numbers.end(); ++run) {
    t_out->Branch(("count_"+std::to_string(*run)).c_str(), 
		  &m_count_map[*run]);
    t_out->Branch(("error_"+std::to_string(*run)).c_str(), 
		  &m_error_map[*run]);
    t_out->Branch(("fraction_"+std::to_string(*run)).c_str(), 
		  &m_fraction_map[*run]);
  }

  t_total = new TH1F("total", "total", 120,0,120);

}

void Train::FillTotals(std::map<int, std::pair<double, double> > totals) {
  int bin = 1;

  // for the next step, the first entry in the totals histogram must be the signal,
  //   so this one is hard-coded
  if(totals.count(999999)) {
    t_total->SetBinContent(bin, totals[999999].first);
    t_total->SetBinError  (bin, sqrt(totals[999999].second));
  }
  bin++;

  // loop over the rest of the runs
  for(std::vector<int>::iterator run = m_run_numbers.begin(); run != m_run_numbers.end(); ++run) {
    if(*run == 999999) continue;

    t_total->SetBinContent(bin, totals[*run].first);
    t_total->SetBinError  (bin, sqrt(totals[*run].second));

    bin++;
  }

}

void Train::FinalizeOutput() {
  t_out->Write();
  t_total->Write();
  outputFile->Close();
}
