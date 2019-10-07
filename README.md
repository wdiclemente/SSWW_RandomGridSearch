# SSWW Signal Optimization
This repository houses the code that I used to optimize the signal event selection for same-sign WW scattering (SSWW) using a Random Grid Search (RGS) algorithm. 
For more information on the algorithm, see [this paper by P.C. Bhat, et al.](https://arxiv.org/abs/1706.09907).

This was used in an ATLAS study on the prospects for measuring SSWW production at the planned High-Luminosity LHC (HL-LHC).
The analysis publication is available [here](http://cds.cern.ch/record/2652447), and it is also included in the joint ATLAS and CMS [Report on the Physics at the HL-LHC and Perspectives for the HE-LHC](https://arxiv.org/abs/1902.10229).

This framework is written in `python2` and `C++`, and has dependencies on CERN's [Root data analysis framework](https://root.cern.ch/) which is the standard toolkit for LHC physics research and the [RGS package](https://github.com/hbprosper/RGS) provided by the authors of the paper linked above.

## Code overview
The RGS algorithm is broken into two components: `train` and `analysis`.
The `train` component is the primary focus of this repository, and it has been re-written from the ground up in `C++` as I needed additional features (such as prserving statistical uncertainties) that are not included in the authors' package.
The output format is consistent with the original framework; however, additional variables for the errors need to be handled in the next step.

As such, the `analysis` stage of the code has also been modified from the original version to accomodate this.
The RGS package is required for this step, and it is provided as a submodule.
The scripts that have been added or changed to run with my version of the code are provided in this repository.

## Running the training code
The training code is contained in the `include` and `src` directories, and can be compiled using `make`.
Once again, ROOT is required, and linking the libraries can be rather finicky, and may depend on the local install.
If trouble arises, some solutions I found particularly useful can be found [here](https://stackoverflow.com/a/2481326) and [here](https://root-forum.cern.ch/t/linking-root-libraries-to-a-makefile-install/12233).

The code requires several inputs, which will be detailed below.
**Please note that I am unable to provide the data samples used for the analysis as they are internal to the collaboration**.  As such the paths specified in the repository will not work and would need to be updated to your own samples.

1. Input signal file in `src/Main.cxx`: `sig_chain->AddFile("/path/to/signal/file.root");`
2. Input background file(s) in `src/Main.cxx`.  The first file is input manually much like the signal: `bkg_chain->AddFile("/path/to/bkg/file.root");`
Alternatively, background files may be read in from a text file containing the full file path per sample per line.  The default file is located in `data/files_20GeV.txt`.
3. Cross section and normalizations are read in from `data/xsec_20GeV.txt`.
4. The number of cut points (see RGS paper) can be requested as a command line argument during running.  If no number is specified, the code will default to 10,000 cut points: `./train <number of cut points>`

## Choosing the best cut point
The python script responsible for running the analysis that chooses the best cut point is a modified version of the one provided by the RGS package, and it is located in the `analysis` subdirectory of this repository.

Essentially, the code chooses the cut point that maximizes signal significance given a set of 3 criteria (restrictions on how much certain variables are able to fluctuate from their default values, as well as a requirement that if the number of signal events is reduced, the significance must increase by enough to justify this signal loss).

Running the actual analysis code will likely not be possible without a lot of effort to replace required files with my changes as well as setting up proper paths and data dependencies.  As a result, they are included here more as a reference/archive rather than as a working example.