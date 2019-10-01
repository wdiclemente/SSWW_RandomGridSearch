#ifndef Event_h
#define Event_h

class Event {
 public:
  Event();
  Event(int runNumber, float weight, float lep0pt, float lep1pt, float jet0pt, float jet1pt, float mll, float mjj, float detajj, float centrality);
  ~Event();

  int   e_runNumber;
  float e_weight;

  float e_mjj;
  float e_mll;
  float e_detajj;
  float e_centrality;
  float e_lep0pt;
  float e_lep1pt;
  float e_jet0pt;
  float e_jet1pt;

  int   getRunNumber() { return e_runNumber; };
  float getWeight()    { return e_weight; };
  float getMjj()       { return e_mjj; };
  float getMll()       { return e_mll; };
  float getDetajj()    { return e_detajj; };
  float getCentrality(){ return e_centrality; };
  float getLep0pt()    { return e_lep0pt; };
  float getLep1pt()    { return e_lep1pt; };
  float getJet0pt()    { return e_jet0pt; };
  float getJet1pt()    { return e_jet1pt; };

  void setRunNumber (int   i){ e_runNumber  = i; };
  void setWeight    (float v){ e_weight     = v; };
  void setMjj       (float v){ e_mjj        = v; };
  void getMll       (float v){ e_mll        = v; };
  void getDetajj    (float v){ e_detajj     = v; };
  void getCentrality(float v){ e_centrality = v; };
  void getLep0pt    (float v){ e_lep0pt     = v; };
  void getLep1pt    (float v){ e_lep1pt     = v; };
  void getJet0pt    (float v){ e_jet0pt     = v; };
  void getJet1pt    (float v){ e_jet1pt     = v; };

  void print();

};

#endif
