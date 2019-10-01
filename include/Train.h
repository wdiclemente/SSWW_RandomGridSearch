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
   static const float m_Lumi = 3000.;
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

   double count_999999; //!
   double error_999999; //!
   double fraction_999999; //!
   double count_111111; //!
   double error_111111; //!
   double fraction_111111; //!
   double count_222222; //!
   double error_222222; //!
   double fraction_222222; //!
   double count_990031; //!
   double error_990031; //!
   double fraction_990031; //!
   double count_123456; //!
   double error_123456; //!
   double fraction_123456; //!
   double count_364284; //!
   double error_364284; //!
   double fraction_364284; //!
   double count_364250; //!
   double error_364250; //!
   double fraction_364250; //!
   double count_364254; //!
   double error_364254; //!
   double fraction_364254; //!
   double count_364255; //!
   double error_364255; //!
   double fraction_364255; //!
   double count_363718; //!
   double error_363718; //!
   double fraction_363718; //!
   double count_363719; //!
   double error_363719; //!
   double fraction_363719; //!
   double count_364242; //!
   double error_364242; //!
   double fraction_364242; //!
   double count_364243; //!
   double error_364243; //!
   double fraction_364243; //!
   double count_364244; //!
   double error_364244; //!
   double fraction_364244; //!
   double count_364245; //!
   double error_364245; //!
   double fraction_364245; //!
   double count_364246; //!
   double error_364246; //!
   double fraction_364246; //!
   double count_364336; //!
   double error_364336; //!
   double fraction_364336; //!
   double count_364337; //!
   double error_364337; //!
   double fraction_364337; //!
   double count_364338; //!
   double error_364338; //!
   double fraction_364338; //!
   double count_364339; //!
   double error_364339; //!
   double fraction_364339; //!
   double count_363507; //!
   double error_363507; //!
   double fraction_363507; //!
   double count_363508; //!
   double error_363508; //!
   double fraction_363508; //!
   double count_363509; //!
   double error_363509; //!
   double fraction_363509; //!
   double count_410155; //!
   double error_410155; //!
   double fraction_410155; //!
   double count_410218; //!
   double error_410218; //!
   double fraction_410218; //!
   double count_410219; //!
   double error_410219; //!
   double fraction_410219; //!
   double count_410220; //!
   double error_410220; //!
   double fraction_410220; //!
   double count_410642; //!
   double error_410642; //!
   double fraction_410642; //!
   double count_410643; //!
   double error_410643; //!
   double fraction_410643; //!
   double count_410644; //!
   double error_410644; //!
   double fraction_410644; //!
   double count_410645; //!
   double error_410645; //!
   double fraction_410645; //!
   double count_410501; //!
   double error_410501; //!
   double fraction_410501; //!
   double count_147806; //!
   double error_147806; //!
   double fraction_147806; //!
   double count_147807; //!
   double error_147807; //!
   double fraction_147807; //!
   double count_363600; //!
   double error_363600; //!
   double fraction_363600; //!
   double count_363601; //!
   double error_363601; //!
   double fraction_363601; //!
   double count_363602; //!
   double error_363602; //!
   double fraction_363602; //!
   double count_363603; //!
   double error_363603; //!
   double fraction_363603; //!
   double count_363604; //!
   double error_363604; //!
   double fraction_363604; //!
   double count_363605; //!
   double error_363605; //!
   double fraction_363605; //!
   double count_363606; //!
   double error_363606; //!
   double fraction_363606; //!
   double count_363607; //!
   double error_363607; //!
   double fraction_363607; //!
   double count_363608; //!
   double error_363608; //!
   double fraction_363608; //!
   double count_363609; //!
   double error_363609; //!
   double fraction_363609; //!
   double count_363610; //!
   double error_363610; //!
   double fraction_363610; //!
   double count_363611; //!
   double error_363611; //!
   double fraction_363611; //!
   double count_363612; //!
   double error_363612; //!
   double fraction_363612; //!
   double count_363613; //!
   double error_363613; //!
   double fraction_363613; //!
   double count_363614; //!
   double error_363614; //!
   double fraction_363614; //!
   double count_363615; //!
   double error_363615; //!
   double fraction_363615; //!
   double count_363616; //!
   double error_363616; //!
   double fraction_363616; //!
   double count_363617; //!
   double error_363617; //!
   double fraction_363617; //!
   double count_363618; //!
   double error_363618; //!
   double fraction_363618; //!
   double count_363619; //!
   double error_363619; //!
   double fraction_363619; //!
   double count_363620; //!
   double error_363620; //!
   double fraction_363620; //!
   double count_363621; //!
   double error_363621; //!
   double fraction_363621; //!
   double count_363622; //!
   double error_363622; //!
   double fraction_363622; //!
   double count_363623; //!
   double error_363623; //!
   double fraction_363623; //!
   double count_363624; //!
   double error_363624; //!
   double fraction_363624; //!
   double count_363625; //!
   double error_363625; //!
   double fraction_363625; //!
   double count_363626; //!
   double error_363626; //!
   double fraction_363626; //!
   double count_363627; //!
   double error_363627; //!
   double fraction_363627; //!
   double count_363628; //!
   double error_363628; //!
   double fraction_363628; //!
   double count_363629; //!
   double error_363629; //!
   double fraction_363629; //!
   double count_363630; //!
   double error_363630; //!
   double fraction_363630; //!
   double count_363631; //!
   double error_363631; //!
   double fraction_363631; //!
   double count_363632; //!
   double error_363632; //!
   double fraction_363632; //!
   double count_363633; //!
   double error_363633; //!
   double fraction_363633; //!
   double count_363634; //!
   double error_363634; //!
   double fraction_363634; //!
   double count_363635; //!
   double error_363635; //!
   double fraction_363635; //!
   double count_363636; //!
   double error_363636; //!
   double fraction_363636; //!
   double count_363637; //!
   double error_363637; //!
   double fraction_363637; //!
   double count_363638; //!
   double error_363638; //!
   double fraction_363638; //!
   double count_363639; //!
   double error_363639; //!
   double fraction_363639; //!
   double count_363640; //!
   double error_363640; //!
   double fraction_363640; //!
   double count_363641; //!
   double error_363641; //!
   double fraction_363641; //!
   double count_363642; //!
   double error_363642; //!
   double fraction_363642; //!
   double count_363643; //!
   double error_363643; //!
   double fraction_363643; //!
   double count_363644; //!
   double error_363644; //!
   double fraction_363644; //!
   double count_363645; //!
   double error_363645; //!
   double fraction_363645; //!
   double count_363646; //!
   double error_363646; //!
   double fraction_363646; //!
   double count_363647; //!
   double error_363647; //!
   double fraction_363647; //!
   double count_363648; //!
   double error_363648; //!
   double fraction_363648; //!
   double count_363649; //!
   double error_363649; //!
   double fraction_363649; //!
   double count_363650; //!
   double error_363650; //!
   double fraction_363650; //!
   double count_363651; //!
   double error_363651; //!
   double fraction_363651; //!
   double count_363652; //!
   double error_363652; //!
   double fraction_363652; //!
   double count_363653; //!
   double error_363653; //!
   double fraction_363653; //!
   double count_363654; //!
   double error_363654; //!
   double fraction_363654; //!
   double count_363655; //!
   double error_363655; //!
   double fraction_363655; //!
   double count_363656; //!
   double error_363656; //!
   double fraction_363656; //!
   double count_363657; //!
   double error_363657; //!
   double fraction_363657; //!
   double count_363658; //!
   double error_363658; //!
   double fraction_363658; //!
   double count_363659; //!
   double error_363659; //!
   double fraction_363659; //!
   double count_363660; //!
   double error_363660; //!
   double fraction_363660; //!
   double count_363661; //!
   double error_363661; //!
   double fraction_363661; //!
   double count_363662; //!
   double error_363662; //!
   double fraction_363662; //!
   double count_363663; //!
   double error_363663; //!
   double fraction_363663; //!
   double count_363664; //!
   double error_363664; //!
   double fraction_363664; //!
   double count_363665; //!
   double error_363665; //!
   double fraction_363665; //!
   double count_363666; //!
   double error_363666; //!
   double fraction_363666; //!
   double count_363667; //!
   double error_363667; //!
   double fraction_363667; //!
   double count_363668; //!
   double error_363668; //!
   double fraction_363668; //!
   double count_363669; //!
   double error_363669; //!
   double fraction_363669; //!
   double count_363670; //!
   double error_363670; //!
   double fraction_363670; //!
   double count_363671; //!
   double error_363671; //!
   double fraction_363671; //! 

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
