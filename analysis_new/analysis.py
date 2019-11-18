#!/usr/bin/python

import os,sys,time
from ROOT import *
from utils import *
from cutpoint import *

#
# CONFIGURABLES TODO
# use error Z
# data file path
# z_improvement
#

### ----------------------------------------------------------------
### ----------------------------------------------------
### PART 1 -- SELECT THE BEST CUT POINT
###       Check each cut point for the one that maximizes significance
### ----------------------------------------------------
### ----------------------------------------------------------------

# ----------------------------------------------------
# open file and get tree
# ----------------------------------------------------
rFile = TFile("../analysis/ssww_50k.root", "READ")
rTree = rFile.Get("RGS")
nEntries = rTree.GetEntries()

# list of all run ID's in the data file
runs = get_list_of_runs(rTree)

# ----------------------------------------------------
# set up default cut point
# ----------------------------------------------------
def_cuts = {}
def_cuts['cutpointindex'] = -1
def_cuts['mll'] = 20
def_cuts['mjj'] = 500
def_cuts['leptons_selected_l0_pt'] = 20
def_cuts['leptons_selected_l1_pt'] = 20
def_cuts['jets_selected_j0_pt'] = 30
def_cuts['jets_selected_j1_pt'] = 30
def_cuts['lepjet_centrality'] = 0
def_cut = CutPoint(def_cuts)

# ----------------------------------------------------
# loop over cut points to select the best one
# ----------------------------------------------------

# initialize variables
best_sig = -1
best_bkg = -1
best_Z   = -1
best_cut = def_cut

start = time.time()

for i in range(nEntries):
    # counter so we know the code is running
    if i%10000 == 0:
        now = time.time()
        print "({:.2f} sec elapsed)\tProcessing cut point {}/{}. . .".format(now-start,i,nEntries)
        
    # fill event info
    rTree.GetEntry(i)
    event = fill_event(rTree) # dictionary

    # count signal events
    sig_num = event['count_999999']
    sig_err = event['error_999999']

    # count background events
    bkg_num = 0
    bkg_err = 0
    for run in runs:
        if run == '999999': continue # signal
        if run == '410000': continue # only used for debugging
        if run == '363719': continue # old sample, no longer used
        bkg_num += event['count_'+run]
        bkg_err += event['error_'+run] # errors are already calculated as the square

    # ----------------------------------------------------
    # calculate signal significance and store the best
    # ----------------------------------------------------
    Z = signalSignificance(sig_num, bkg_num)
    if Z > best_Z:

        # apply some constraints to the optimization, so we don't "over-optimize"
        pass_constraint = True
        if sig_num < 1000: # we want at least 1000 signal events
            pass_constraint = False
        if event['mjj'] < 400 or event['mjj'] > 600: # physically motivated cut; keep it reasonable
            pass_constraint = False

        if not pass_constraint:
            continue

        # we also want to make sure that we don't lose signal for a small increase in Z
        Z_improvement = 0.05
        if sig_num < best_sig:
            Z_diff = abs(Z - best_Z)/best_Z
            if Z_diff < Z_improvement:
                print "Found cut point that reduces signal for gain in Z less than {} ({:.4f}), skipping. . .".format(Z_improvement, Z_diff)
                continue
        
        best_sig = sig_num
        best_bkg = bkg_num
        best_Z   = Z
        best_cut = CutPoint(event)

print "DONE reading {} cut points in {:.2f} sec.".format(nEntries,time.time()-start)
print "--"*20
print "\nCut point #{} selected, Z = {}\n".format(best_cut.get_value('index'),best_Z)
print "  Signal events: {}   Background events: {}".format(best_sig,best_bkg)
print best_cut.to_string()
print "--"*20
rFile.Close()

### ----------------------------------------------------------------
### ----------------------------------------------------
### PART 2 -- EVALUATE THE CUT POINT
###     Count signal and background events before/after optimization
###     Plot the optimization variables showing new and old values
### ----------------------------------------------------
### ----------------------------------------------------------------

# ----------------------------------------------------
# get signal and background files
# ----------------------------------------------------
files_sig = getSigFiles()
files_bkg = getBkgFiles()

# get dictionary of event weights
weights = get_event_weights()

# ----------------------------------------------------
# loop over signal files
# ----------------------------------------------------
sig_num_def = 0
sig_num_opt = 0
start = time.time()

for f in files_sig:
    sFile = TFile(f,"READ")
    sTree = sFile.Get("t_events")
    nEntries = sTree.GetEntries()

    for i in range(nEntries):
        
        if i%25000 == 0:
            now = time.time()
            print "({:.2f} sec elapsed)\tProcessing signal event {}. . .".format(now-start,i)
            
        # fill event info
        sTree.GetEntry(i)
       
        # count events that pass the best cut point
        if pass_cut_point(sTree, best_cut):
            sig_num_opt += sTree.weight_total_no3rdlep*weights[999999]
            
        # count events that pass the default cuts
        if pass_cut_point(sTree, def_cut):
        #if sTree.pass_selection == 10:
            sig_num_def += sTree.weight_total_no3rdlep*weights[999999]


print "DONE reading {} signal events in {:.2f} sec.".format(nEntries,time.time()-start)
            
# ----------------------------------------------------
# loop over background files
# ----------------------------------------------------
bkg_num_def = 0
bkg_num_opt = 0
start = time.time()
count = -1

for f in files_bkg:
    bFile = TFile(f,"READ")
    bTree = bFile.Get("t_events")
    nEntries = bTree.GetEntries()

    for i in range(nEntries):

        count += 1
        if count%100000 == 0:
            now = time.time()
            print "({:.2f} sec elapsed)\tProcessing background event {}. . .".format(now-start,count)

        # fill event info
        bTree.GetEntry(i)

        # count events that pass the best cut point
        if pass_cut_point(bTree, best_cut):
            bkg_num_opt += bTree.weight_total_no3rdlep*weights[bTree.runNumber]
        
        # count events that pass the default cuts
        if pass_cut_point(bTree, def_cut):
        #if bTree.pass_selection == 10:
            bkg_num_def += bTree.weight_total_no3rdlep*weights[bTree.runNumber]
            
print "DONE reading {} background events in {:.2f} sec.".format(count,time.time()-start)

print "Before optimization -- sig: {} bkg: {} Z: {}".format(sig_num_def,bkg_num_def,signalSignificance(sig_num_def,bkg_num_def))
print "After optimization  -- sig: {} bkg: {} Z: {}".format(sig_num_opt,bkg_num_opt,signalSignificance(sig_num_opt,bkg_num_opt))
