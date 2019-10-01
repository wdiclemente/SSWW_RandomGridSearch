#ifndef CutPoint_h
#define CutPoint_h

#include "Event.h"

class CutPoint {
 public:
  CutPoint();
  CutPoint(int index, Event &event);
  CutPoint(int index, float lep0pt, float lep1pt, float jet0pt, float jet1pt, float mll, float mjj, float detajj, float centrality);
  ~CutPoint();

  int c_index;

  float c_mjj;
  float c_mll;
  float c_detajj;
  float c_centrality;
  float c_lep0pt;
  float c_lep1pt;
  float c_jet0pt;
  float c_jet1pt;

  float getIndex()     { return c_index; };
  float getMjj()       { return c_mjj; };
  float getMll()       { return c_mll; };
  float getDetajj()    { return c_detajj; };
  float getCentrality(){ return c_centrality; };
  float getLep0pt()    { return c_lep0pt; };
  float getLep1pt()    { return c_lep1pt; };
  float getJet0pt()    { return c_jet0pt; };
  float getJet1pt()    { return c_jet1pt; };

  void setIndex     (int   i){ c_index      = i; };
  void setMjj       (float v){ c_mjj        = v; };
  void getMll       (float v){ c_mll        = v; };
  void getDetajj    (float v){ c_detajj     = v; };
  void getCentrality(float v){ c_centrality = v; };
  void getLep0pt    (float v){ c_lep0pt     = v; };
  void getLep1pt    (float v){ c_lep1pt     = v; };
  void getJet0pt    (float v){ c_jet0pt     = v; };
  void getJet1pt    (float v){ c_jet1pt     = v; };

  void print();

};

#endif
