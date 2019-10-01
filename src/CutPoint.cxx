#include "CutPoint.h"
#include <iostream>

CutPoint::CutPoint(){
  c_index      = -1;
  c_mjj        = -1.;
  c_mll        = -1.;
  c_detajj     = -1.;
  c_centrality = -1.;
  c_lep0pt     = -1.;
  c_lep1pt     = -1.;
  c_jet0pt     = -1.;
  c_jet1pt     = -1.;
}

CutPoint::CutPoint(int index, Event &event){
  c_index      = index;
  c_mjj        = event.getMjj();
  c_mll        = event.getMll();
  c_detajj     = event.getDetajj();
  c_centrality = event.getCentrality();
  c_lep0pt     = event.getLep0pt();
  c_lep1pt     = event.getLep1pt();
  c_jet0pt     = event.getJet0pt();
  c_jet1pt     = event.getJet1pt();
}

CutPoint::CutPoint(int index, float lep0pt, float lep1pt, float jet0pt, float jet1pt, float mll, float mjj, float detajj, float centrality) {
  c_index      = index;
  c_mjj        = mjj;
  c_mll        = mll;
  c_detajj     = detajj;
  c_centrality = centrality;
  c_lep0pt     = lep0pt;
  c_lep1pt     = lep1pt;
  c_jet0pt     = jet0pt;
  c_jet1pt     = jet1pt;
}

void CutPoint::print(){
  std::cout << "Cut point #"     << c_index      << std::endl;
  std::cout << "  Mjj        = " << c_mjj        << std::endl;
  std::cout << "  Mll        = " << c_mll        << std::endl;
  std::cout << "  Detajj     = " << c_detajj     << std::endl;
  std::cout << "  Centrality = " << c_centrality << std::endl;
  std::cout << "  Lep0Pt     = " << c_lep0pt     << std::endl;
  std::cout << "  Lep1Pt     = " << c_lep1pt     << std::endl;
  std::cout << "  Jet0Pt     = " << c_jet0pt     << std::endl;
  std::cout << "  Jet1Pt     = " << c_jet1pt     << std::endl;
}
