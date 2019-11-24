# SSWW Signal Optimization
This repository houses the code that I used to optimize the signal event selection for same-sign WW scattering (SSWW) using a Random Grid Search (RGS) algorithm. 
For more information on the algorithm, see [this paper by P.C. Bhat, et al.](https://arxiv.org/abs/1706.09907).

This was used in an ATLAS study on the prospects for measuring SSWW production at the planned High-Luminosity LHC (HL-LHC).
The analysis publication is available [here](http://cds.cern.ch/record/2652447), and it is also included in the joint ATLAS and CMS [Report on the Physics at the HL-LHC and Perspectives for the HE-LHC](https://arxiv.org/abs/1902.10229).

This framework is written in `python2` and `C++`, and it has a dependency on CERN's [Root data analysis framework](https://root.cern.ch/), which is the standard toolkit for LHC physics research.
The authors of the paper above provide a framework for RGS analyses in their [RGS package](https://github.com/hbprosper/RGS).
This package is required for running the "old" analysis code (located in `analysis_paper`), but a new version of the analysis is included in the `analysis` directory that is independent of the package.

## Code overview
The RGS algorithm is broken into two components: `train` and `analysis`.
The `train` component is the primary focus of this repository, and it has been re-written from the ground up in `C++` as I needed additional features (such as prserving statistical uncertainties) that are not included in the authors' package.
The output format is consistent with the original framework; however, additional variables for the errors need to be handled in the next step.

This repository contains two versions of the `analysis` step.
The first is the version used in the ATLAS paper, and it is a modified version of the code provided in the RGS package mentioned in the previous section (it is provided as a submodule in this repository).
It can be found in the `analysis_paper` directory; however, many of the original RGS scripts have been modified (the modified versions are included in the directory), and running this code locally may be tricky.

The second version is independent of the RGS package and be found in the `analysis` directory.
It does not have as many features as the paper version; however, it still runs a complete analysis and produces plots of the optimized variables separated by signal and background
This version will continue to be updated to include all of the features of the paper analysis code.
For now it is an excellent starting point to run an example of the RGS method.

## Running the training code
The training code is contained in the `include` and `src` directories, and can be compiled using `make`.
Once again, ROOT is required, and linking the libraries can be rather finicky, and may depend on the local install.
If trouble arises, some solutions I found particularly useful can be found [here](https://stackoverflow.com/a/2481326) and [here](https://root-forum.cern.ch/t/linking-root-libraries-to-a-makefile-install/12233).

The code requires several inputs, which will be detailed below.
**Please note that I am unable to provide the data samples used for the analysis as they are internal to the collaboration**.  As such the paths specified in the repository will not work and would need to be updated to your own samples.

1. Input signal file in `src/Main.cxx`: `sig_chain->AddFile("/path/to/signal/file.root");`
2. Input background file(s) in `src/Main.cxx` are read in from a text file containing the full file path per sample per line.  The default file is located in `data/files_20GeV.txt`.
3. Cross section and normalizations are read in from `data/xsec_20GeV.txt`.
4. The number of cut points (see RGS paper) can be requested as a command line argument during running.  If no number is specified, the code will default to 10,000 cut points: `./train <number of cut points>`  For all available cut points, use `-1`.

The `train` code will run over the signal and background samples and calculate the number of events that pass each cut point.
This is all stored in the output file `ssww.root`, which contains a ROOT TTree `RGS` with the values of the optimization variables as well as counts of the events passing the cut point separated by sample.
This output `.root` file is the input to the `analysis` code.

## Choosing the best cut point
`analysis/analysis.py` is a python script responsible for choosing the best cut point.
It reads in the output of the `train` code as well as the same set of signal and background samples (using the same text file of file paths).
Event weights are calculated using values stored in the `weights.csv` file.

The code chooses the cut point that maximizes signal significance.
The implementation in this code also applies three constraints that must be satisfied by the chosen cut point:

1. A minimum number of signal events that must survive the optimization.
2. A restriction on how far a chosen variable (`mjj` in this case) is allowed to deviate from its default value.
3. As requirement that if the number of signal events is reduced, the significance must increase by more than 5% (to avoid large reductions in signal statistics for a minimal increase in significance).

Once the best cut point is selected, the code prints out the optimized cuts, and then it loops over the signal and background files in order to calculate the signal significance before and after optimization.
It also makes plots of the optimization variables showing both the old and new cut values.