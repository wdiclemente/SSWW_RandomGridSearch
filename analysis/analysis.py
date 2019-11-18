#!/usr/bin/env python
# ---------------------------------------------------------------------
#  File:        analysis.py
# ---------------------------------------------------------------------
#  Created:     10-Jan-2015 Harrison B. Prosper and Sezen Sekmen
#  Modified:    Will DiClemente for SSWW @HL-LHC Upgrade Study 2018
# ---------------------------------------------------------------------
import os, sys, re
from string import *
from rgsutil import *
from time import sleep
from ROOT import *

import settings
settings.init()

sys.path.append('./python')
from rgsexamples import *

execfile('systematics.py')

# ---------------------------------------------------------------------
def cut(event, full=False):
    # returns True if event FAILS cut
    if not event.leptons_selected_n == 2: return True
    if not event.dilepton_charge    == 1: return True
    
    if full:
        if not event.leptons_selected_l0_pt < 25000.0: return True
        if not event.leptons_selected_l1_pt < 30000.0: return True
        if not event.jets_selected_j0_pt < 30000.0: return True
        if not event.jets_selected_j1_pt < 30000.0: return True
        if not event.mll < 20: return True
        if not event.mjj < 500: return True
        if not event.detajj < 2.4: return True

    return False
# ---------------------------------------------------------------------
def atlas():
    print ". . .Setting up plot style. . ."
    font = 42
    gStyle.SetTextFont(font)
    gStyle.SetLabelFont(font, "x")
    gStyle.SetTitleFont(font, "x")
    gStyle.SetLabelFont(font, "y")
    gStyle.SetTitleFont(font, "y")
    gStyle.SetLabelFont(font, "z")
    gStyle.SetTitleFont(font, "z")
    size = 0.05
    gStyle.SetTextSize(size)
    gStyle.SetLabelSize(size, "x");
    gStyle.SetTitleSize(size, "x");
    gStyle.SetLabelSize(size, "y");
    gStyle.SetTitleSize(size, "y");
    gStyle.SetLabelSize(size, "z");
    gStyle.SetTitleSize(size, "z")

def main():
    gROOT.SetBatch()
    atlas()

    getBkgFiles_dict()
    
    NAME = 'ssww'
    
    resultsfilename = "%s_50k.root" % NAME

    treename = "RGS"
    print "\n\topen RGS file: %s"  % resultsfilename
    ntuple = Ntuple(resultsfilename, treename)
    
    variables = ntuple.variables()
    #for name, count in variables:
    #    print "\t\t%-30s\t%5d" % (name, count)        
    print "\tnumber of cut-points: ", ntuple.size()
  
    # -------------------------------------------------------------
    # Plot results of RGS, that is, the fraction of events that
    # pass a given cut-point.
    #  1. Loop over cut points and compute a significance measure
    #     for each cut-point.
    #  2. Find cut-point with highest significance.
    # -------------------------------------------------------------
    # Set up a standard Root graphics style (see histutil.py in the
    # python directory).
    setStyle()

    #cmass, hs, hb = fillMjjMll(baseCuts)
    
    # Create a 2-D histogram for ROC plot
    msize = 0.30  # marker size for points in ROC plot
    
    xbins =   50  # number of bins in x (background)
    xmin  =  0.0  # lower bound of x
    xmax  =  0.1  # upper bound of y

    ybins =   50
    ymin  =  0.0
    ymax  =  0.3

    color = kBlue+1
    hist  = mkhist2("hroc",
                    "#font[12]{#epsilon_{B}}",
                    "#font[12]{#epsilon_{S}}",
                    xbins, xmin, xmax,
                    ybins, ymin, ymax,
                    color=color)
    hist.SetMinimum(0)
    hist.SetMarkerSize(msize)

    print "Significance test: s = 100, b = 16, err = 4\n\t",signalSignificanceErr(100,16,4)
    print "Significance test: s = 207, b = 13289, err = 2119\n\t",signalSignificanceErr(207,13289,2119)
    print "Significance test: s = 160, b = 5118, err = 247\n\t",signalSignificanceErr(160,5118,247)

    # loop over all cut-points, compute a significance measure Z
    # for each cut-point, and find the cut-point with the highest
    # significance and the associated cuts.
    print "\tfilling ROC plot..."	
    bestZ   = -1    # best Z value
    bestRow = -1    # row with best cut-point
    bestSig = -1
    bestBkg = -1

    totals = ntuple.totals()

    tot_sig = totals[0][0]
    tot_bkg = 0
    for tot in totals[1:]:
        tot_bkg += tot[0]

    for row, cuts in enumerate(ntuple):
        # central values
        c_wwsig    = cuts.count_999999 #name of variable in RGS .root file
        c_wwtx     = 0
        if settings.doPolar:
            c_wwtx = cuts.count_990031
        c_wwbkg    = cuts.count_123456
        c_diboson  = cuts.count_364250 + cuts.count_364254 + cuts.count_364255 + cuts.count_364284 + cuts.count_363718
        c_triboson = cuts.count_364242 + cuts.count_364243 + cuts.count_364244 + cuts.count_364245 + cuts.count_364246 + cuts.count_364336 + cuts.count_364337 + cuts.count_364339 + cuts.count_363507 + cuts.count_363508 + cuts.count_363509 + cuts.count_364338
        c_top      = cuts.count_410155 + cuts.count_410219 + cuts.count_410220 + cuts.count_410218 + cuts.count_410642 + cuts.count_410643 + cuts.count_410644 + cuts.count_410645 + cuts.count_410501
        c_fake     = cuts.count_222222
        c_flip     = cuts.count_111111
        c_zjets    = cuts.count_147806 + cuts.count_147807
        #c_wjets    = cuts.count_363600 + cuts.count_363601 + cuts.count_363602 + cuts.count_363603 + cuts.count_363604 + cuts.count_363605 + cuts.count_363606 + cuts.count_363607 + cuts.count_363608 + cuts.count_363609 + cuts.count_363610 + cuts.count_363611 + cuts.count_363612 + cuts.count_363613 + cuts.count_363614 + cuts.count_363615 + cuts.count_363616 + cuts.count_363617 + cuts.count_363618 + cuts.count_363619 + cuts.count_363620 + cuts.count_363621 + cuts.count_363622 + cuts.count_363623 + cuts.count_363624 + cuts.count_363625 + cuts.count_363626 + cuts.count_363627 + cuts.count_363628 + cuts.count_363629 + cuts.count_363630 + cuts.count_363631 + cuts.count_363632 + cuts.count_363633 + cuts.count_363634 + cuts.count_363635 + cuts.count_363636 + cuts.count_363637 + cuts.count_363638 + cuts.count_363639 + cuts.count_363640 + cuts.count_363641 + cuts.count_363642 + cuts.count_363643 + cuts.count_363644 + cuts.count_363645 + cuts.count_363646 + cuts.count_363647 + cuts.count_363648 + cuts.count_363649 + cuts.count_363650 + cuts.count_363651 + cuts.count_363652 + cuts.count_363653 + cuts.count_363654 + cuts.count_363655 + cuts.count_363656 + cuts.count_363657 + cuts.count_363658 + cuts.count_363659 + cuts.count_363660 + cuts.count_363661 + cuts.count_363662 + cuts.count_363663 + cuts.count_363664 + cuts.count_363665 + cuts.count_363666 + cuts.count_363667 + cuts.count_363668 + cuts.count_363669 + cuts.count_363670 + cuts.count_363671
        c_wjets    = cuts.count_363606 + cuts.count_363609 + cuts.count_363612 + cuts.count_363613 + cuts.count_363615 + cuts.count_363616 + cuts.count_363617 + cuts.count_363618 + cuts.count_363619 + cuts.count_363620 + cuts.count_363621 + cuts.count_363622 + cuts.count_363623 + cuts.count_363630 + cuts.count_363631 + cuts.count_363632 + cuts.count_363633 + cuts.count_363634 + cuts.count_363635 + cuts.count_363636 + cuts.count_363637 + cuts.count_363638 + cuts.count_363639 + cuts.count_363640 + cuts.count_363641 + cuts.count_363642 + cuts.count_363643 + cuts.count_363644 + cuts.count_363645 + cuts.count_363646 + cuts.count_363647 + cuts.count_363654 + cuts.count_363660 + cuts.count_363662 + cuts.count_363663 + cuts.count_363666
        s  = c_wwsig
        b  = c_wwtx+c_wwbkg+c_diboson+c_triboson+c_top+c_fake+c_flip+c_zjets+c_wjets

        # stat errors -- note these are stored as the square of the stat error
        stat_wwbkg    = cuts.error_123456
        stat_wwtx     = 0
        if settings.doPolar:
            stat_wwtx = cuts.error_990031
        stat_diboson  = cuts.error_364250 + cuts.error_364254 + cuts.error_364255 + cuts.error_364284 + cuts.error_363718
        stat_triboson = cuts.error_364242 + cuts.error_364243 + cuts.error_364244 + cuts.error_364245 + cuts.error_364246 + cuts.error_364336 + cuts.error_364337 + cuts.error_364339 + cuts.error_363507 + cuts.error_363508 + cuts.error_363509 + cuts.error_364338
        stat_top      = cuts.error_410155 + cuts.error_410219 + cuts.error_410220 + cuts.error_410218 + cuts.error_410642 + cuts.error_410643 + cuts.error_410644 + cuts.error_410645 + cuts.error_410501
        stat_fake     = cuts.error_222222
        stat_flip     = cuts.error_111111
        stat_zjets    = cuts.error_147806 + cuts.error_147807
        #stat_wjets    = cuts.error_363600 + cuts.error_363601 + cuts.error_363602 + cuts.error_363603 + cuts.error_363604 + cuts.error_363605 + cuts.error_363606 + cuts.error_363607 + cuts.error_363608 + cuts.error_363609 + cuts.error_363610 + cuts.error_363611 + cuts.error_363612 + cuts.error_363613 + cuts.error_363614 + cuts.error_363615 + cuts.error_363616 + cuts.error_363617 + cuts.error_363618 + cuts.error_363619 + cuts.error_363620 + cuts.error_363621 + cuts.error_363622 + cuts.error_363623 + cuts.error_363624 + cuts.error_363625 + cuts.error_363626 + cuts.error_363627 + cuts.error_363628 + cuts.error_363629 + cuts.error_363630 + cuts.error_363631 + cuts.error_363632 + cuts.error_363633 + cuts.error_363634 + cuts.error_363635 + cuts.error_363636 + cuts.error_363637 + cuts.error_363638 + cuts.error_363639 + cuts.error_363640 + cuts.error_363641 + cuts.error_363642 + cuts.error_363643 + cuts.error_363644 + cuts.error_363645 + cuts.error_363646 + cuts.error_363647 + cuts.error_363648 + cuts.error_363649 + cuts.error_363650 + cuts.error_363651 + cuts.error_363652 + cuts.error_363653 + cuts.error_363654 + cuts.error_363655 + cuts.error_363656 + cuts.error_363657 + cuts.error_363658 + cuts.error_363659 + cuts.error_363660 + cuts.error_363661 + cuts.error_363662 + cuts.error_363663 + cuts.error_363664 + cuts.error_363665 + cuts.error_363666 + cuts.error_363667 + cuts.error_363668 + cuts.error_363669 + cuts.error_363670 + cuts.error_363671
        stat_wjets = 0

        # systematic errors
        syst_wwbkg    = (c_wwbkg    * sys_wwqcd)**2
        syst_diboson  = (c_diboson  * sys_dibos)**2
        syst_triboson = (c_triboson * sys_tribo)**2
        syst_top      = (c_top      * sys_top  )**2
        syst_flip     = (c_flip     * sys_flip )**2
        syst_fake     = (c_fake     * sys_fake )**2

        # total errors
        be =  stat_wwtx+stat_wwbkg+stat_diboson+stat_triboson+stat_top+stat_fake+stat_flip+stat_zjets+stat_wjets
        be += (syst_wwbkg+syst_diboson+syst_triboson+syst_top+syst_fake+syst_flip)
        be = sqrt(be)

        fs = s / tot_sig
        fb = b / tot_bkg
                
        #  Plot fs vs fb
        hist.Fill(fb, fs)
        	
        # Compute measure of significance
        #   Z  = sign(LR) * sqrt(2*|LR|)
        # where LR = log(Poisson(s+b|s+b)/Poisson(s+b|b))
        if settings.doZwithErr:
            Z = signalSignificanceErr(s, b, be)
        else:
            Z = signalSignificance(s,b)

        if Z > bestZ:
            # apply constraints on the best cut points
            ntuple.read(row)
            pass_constraint = True
            if not settings.doPolar and c_wwsig < 1000: 
                pass_constraint = False
            for name, count in variables:
                if name == 'mjj':
                    var = ntuple(name)
                    if var < 400 or var > 600: 
                        pass_constraint = False
            if not pass_constraint: continue
            
            # check to make sure that if we reduce signal, we're actually getting a substantial improvement in Z
            Z_improvement = 0.05 # 5%
            if c_wwsig < bestSig:
                Zdiff = abs(Z-bestZ)/bestZ
                print "Old Z: %f\nNew Z: %f\nDiffZ: %f" %(bestZ, Z, Zdiff)
                print "Old N: %f\nNew N: %f" %(bestSig, c_wwsig)
                if Zdiff < Z_improvement: 
                    print "Cut point reduces signal for minimal gain in Z -- skipping. . ."
                    continue
                print "--"*20

            # if cut point passes our constraints, keep it
            bestZ   = Z
            bestRow = row
            bestSig = s
            bestBkg = b

    # -------------------------------------------------------------            
    # Write out best cut
    # -------------------------------------------------------------
    print bestZ
    print bestRow
    print bestSig
    print bestBkg
    
    bestcuts = writeSSWWResults('r_%s.txt' % NAME,
                                '%s.cuts'  % NAME,
                                ntuple, variables,
                                bestRow, bestZ,
                                totals)
    
    # -------------------------------------------------------------
    # Save plots
    # -------------------------------------------------------------
    print "\t== plot ROC ==="	
    hist_best = mkhist2("hroc_best",
                    "#font[12]{#epsilon_{B}}",
                    "#font[12]{#epsilon_{S}}",
                    xbins, xmin, xmax,
                    ybins, ymin, ymax,
                    color=kMagenta+1)
    hist_best.SetMarkerStyle(kFullTriangleUp)
    hist_best.SetMarkerSize(1)
    hist_best.Fill(bestBkg/tot_bkg, bestSig/tot_sig)
    print bestBkg/tot_bkg,bestSig/tot_sig
    croc = TCanvas("h_%s_ROC" % NAME,
                   "ROC", 520, 10, 400, 400)
    croc.cd()
    hist.Draw()
    #croc.Update()
    hist_best.Draw("SAME")
    croc.Update()
    croc.SaveAs(".pdf")        
    gSystem.ProcessEvents()    


    # ---------------------------------------------------------------------
    # My plots
    # ---------------------------------------------------------------------
    make1DPlots(bestcuts)

# ---------------------------------------------------------------------
try:
    main()
except KeyboardInterrupt:
    print "bye!"


