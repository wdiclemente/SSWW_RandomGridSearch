#include "Train.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cctype>

int main(int argc, char *argv[]){
  
  TChain *sig_chain = new TChain("t_events");
  TChain *bkg_chain = new TChain("t_events");

  sig_chain->AddFile("/home/will/Documents/ssww_upgrade_rgs/ssww_local_data/local_v14_20GeV/hist-oldsamples.mc15_14TeV.private.ssWWEW.root");

  // build background chain from text file
  std::vector<std::string> bkg_files;
  std::string filename;
  std::ifstream inFile("/home/will/Documents/ssww_upgrade_rgs/will_train/data/files_20GeV.txt");
  if(!inFile) {
    std::cerr << "FATAL Main: Unable to open list of background files!" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  while(getline(inFile,filename)) bkg_files.push_back(filename);

  bkg_chain->AddFile("/home/will/Documents/ssww_upgrade_rgs/ssww_local_data/local_v14_20GeV/hist-oldsamples.mc15_14TeV.private.ssWWQCD.root");
  for(std::vector<std::string>::const_iterator i=bkg_files.begin();i != bkg_files.end();++i){
    bkg_chain->AddFile(i->c_str());
  }

  Train *t = new Train();

  // initialize bits of the analysis
  std::string xsec_file = "/home/will/Documents/ssww_upgrade_rgs/will_train/data/xsec_20GeV.txt";
  t->SetupCrossSections(xsec_file);
  t->SetupOutput();

  // read signal
  t->Init(sig_chain);
  int totSig = t->ReadSignal();

  // read background
  t->Init(bkg_chain);
  int totBkg = t->ReadBackground();

  std::cout << "---------- Run Summary ----------" << std::endl;
  std::cout << "Total sig events seen: " << totSig            << std::endl;
  std::cout << "Selected sig events:   " << t->numSigEvents() << std::endl;
  std::cout << "Number of cut points:  " << t->numCutPoints() << std::endl;
  std::cout << "Total bkg events seen: " << totBkg            << std::endl;
  std::cout << "Selected bkg events:   " << t->numBkgEvents() << std::endl;
  std::cout << "---------------------------------" << std::endl;

  // train the optimization
  int defaultCutPoint = 10000;
  if(argc < 2) {
    std::cout << "INFO Main: Number of cut points not specified at command line, using default." << std::endl;
    t->DoTrain(defaultCutPoint);
  }
  else {
    char *end;
    int numCutPoints = strtol(argv[1], &end, 10);
    
    if(*end != '\0') {
      std::cout << "WARNING Main: Command line input for number of cut points is not an integer, using default." << std::endl;
      t->DoTrain(defaultCutPoint);
    }
    else {
      t->DoTrain(numCutPoints);
    }

  }
  // finalize
  t->FinalizeOutput();

  return 0;
}
