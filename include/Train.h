//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 26 10:38:15 2018 by ROOT version 6.04/16
// from TTree t_events/Output tree for events
// found on file: ../ssWW/RandomGridSearch/ssww/local_v13_FCTight/hist-oldsamples.mc15_14TeV.private.ssWWEW.root
//////////////////////////////////////////////////////////

#ifndef Train_h
#define Train_h

// root includes
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

// local object includes
#include "Event.h"
#include "CutPoint.h"

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <ctime>

class Train {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Functions
  void SetupCrossSections(std::string path);
  void SetupOutput();
  void FinalizeOutput();
  void FillTree(std::map<int,std::pair<double,double> > seen_map, std::map<int,std::pair<double,double> > pass_map);
  void FillTotals(std::map<int,std::pair<double,double> > totals);
  
  int  ReadSignal();
  int  ReadBackground();
  void DoTrain(int nCutPoints);
  
  bool passCut(Event &e, CutPoint &cp);
  
  int numSigEvents(){ return m_SigEvents.size(); };
  int numBkgEvents(){ return m_BkgEvents.size(); };
  int numCutPoints(){ return m_CutPoints.size(); };
  
  // Member Variables
  float m_Lumi = 3000.;
  std::map<int, float> m_xsecDict;
  
  static const int m_SelectionCut = 6;
  
  std::vector<CutPoint*> m_CutPoints;
  std::vector<Event*>    m_SigEvents;
  std::vector<Event*>    m_BkgEvents;
  std::vector<Event*>    m_Events;
  
  // Declaration of leaf types
  Int_t           eventNumber;
  Int_t           runNumber;
  Int_t           pass_selection;
  Float_t         weight_total_no3rdlep;
  Int_t           event_isFlip;
  Int_t           event_isFake;
  Float_t         detajj;
  Float_t         mjj;
  Float_t         mll;
  Float_t         leptons_selected_l0_pt;
  Float_t         leptons_selected_l1_pt;
  Float_t         lepjet_centrality;
  Float_t         jets_selected_j0_pt;
  Float_t         jets_selected_j1_pt;
  
  // List of branches
  TBranch        *b_eventNumber;   //!
  TBranch        *b_runNumber;   //!
  TBranch        *b_pass_selection;   //!
  TBranch        *b_weight_total_no3rdlep;   //!
  TBranch        *b_event_isFlip;   //!
  TBranch        *b_event_isFake;   //!
  TBranch        *b_detajj;   //!
  TBranch        *b_mjj;   //!
  TBranch        *b_mll;   //!
  TBranch        *b_leptons_selected_l0_pt;   //!
  TBranch        *b_leptons_selected_l1_pt;   //!
  TBranch        *b_lepjet_centrality;   //!
  TBranch        *b_jets_selected_j0_pt;   //!
  TBranch        *b_jets_selected_j1_pt;   //!
  
  Train(TTree *tree=0);
  virtual ~Train();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  //virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  // output tree variables
  TFile *outputFile; //!
  TTree *t_out; //!
  
  TH1F  *t_total; //!
  
  int cp_index; //!
  
  double o_mll; //!
  double o_mjj; //!
  double o_centrality; //!
  double o_lep0pt; //!
  double o_lep1pt; //!
  double o_jet0pt; //!
  double o_jet1pt; //!
  
  // these store the event output variables and are overwritten on a per-event basis 
  std::vector<int> m_run_numbers;
  std::map<int,double> m_count_map;
  std::map<int,double> m_error_map;
  std::map<int,double> m_fraction_map;

};

#endif

#ifdef Train_cxx
Train::Train(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/will/Documents/ssww_upgrade_rgs/ssww_local_data/local_v14_20GeV/hist-oldsamples.mc15_14TeV.private.ssWWEW.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/will/Documents/ssww_upgrade_rgs/ssww_local_data/local_v14_20GeV/hist-oldsamples.mc15_14TeV.private.ssWWEW.root");
      }
      f->GetObject("t_events",tree);

   }
   Init(tree);
}

Train::~Train()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Train::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Train::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Train::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set object pointer
 
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
  fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
  fChain->SetBranchAddress("pass_selection", &pass_selection, &b_pass_selection);
  fChain->SetBranchAddress("weight_total_no3rdlep", &weight_total_no3rdlep, &b_weight_total_no3rdlep);
  fChain->SetBranchAddress("event_isFlip", &event_isFlip, &b_event_isFlip);
  fChain->SetBranchAddress("event_isFake", &event_isFake, &b_event_isFake);
  fChain->SetBranchAddress("detajj", &detajj, &b_detajj);
  fChain->SetBranchAddress("mjj", &mjj, &b_mjj);
  fChain->SetBranchAddress("mll", &mll, &b_mll);
  fChain->SetBranchAddress("leptons_selected_l0_pt", &leptons_selected_l0_pt, &b_leptons_selected_l0_pt);
  fChain->SetBranchAddress("leptons_selected_l1_pt", &leptons_selected_l1_pt, &b_leptons_selected_l1_pt);
  fChain->SetBranchAddress("lepjet_centrality", &lepjet_centrality, &b_lepjet_centrality);
  fChain->SetBranchAddress("jets_selected_j0_pt", &jets_selected_j0_pt, &b_jets_selected_j0_pt);
  fChain->SetBranchAddress("jets_selected_j1_pt", &jets_selected_j1_pt, &b_jets_selected_j1_pt);
  Notify();
}

Bool_t Train::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Train::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Train::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Train_cxx
