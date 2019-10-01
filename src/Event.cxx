#include "Event.h"
#include <iostream>

Event::Event(){}

Event::Event(int runNumber, float weight, float lep0pt, float lep1pt, float jet0pt, float jet1pt, float mll, float mjj, float detajj, float centrality) {
  e_runNumber  = runNumber;
  e_weight     = weight;
  e_mjj        = mjj;
  e_mll        = mll;
  e_detajj     = detajj;
  e_centrality = centrality;
  e_lep0pt     = lep0pt;
  e_lep1pt     = lep1pt;
  e_jet0pt     = jet0pt;
  e_jet1pt     = jet1pt;
}

void Event::print() {
  std::cout << "Event" << std::endl;
  std::cout << "  Run Number = " << e_runNumber  << std::endl;
  std::cout << "  Weight     = " << e_weight     << std::endl;
  std::cout << "  Mjj        = " << e_mjj        << std::endl;
  std::cout << "  Mll        = " << e_mll        << std::endl;
  std::cout << "  Detajj     = " << e_detajj     << std::endl;
  std::cout << "  Centrality = " << e_centrality << std::endl;
  std::cout << "  Lep0Pt     = " << e_lep0pt     << std::endl;
  std::cout << "  Lep1Pt     = " << e_lep1pt     << std::endl;
  std::cout << "  Jet0Pt     = " << e_jet0pt     << std::endl;
  std::cout << "  Jet1Pt     = " << e_jet1pt     << std::endl;
}
