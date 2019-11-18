from math import sqrt,log
from cutpoint import *

# returns a (sorted) list of all the run ID's in the data file
def get_list_of_runs(tree):
    runs = []
    for leaf in tree.GetListOfLeaves():
        l = leaf.GetName()
        if "count_" in l:
            run = l.split('_')[1]
            runs.append(run)
    return sorted(runs)

# returns a dictionary of the current event
def fill_event(tree):
    event = {}
    for leaf in tree.GetListOfLeaves():
        event[leaf.GetName()] = leaf.GetValue()
    return event

# returns the signal significance with background error term
def signalSignificanceErr(s, b, b_err):
    B0 = 1/2.*(b - b_err**2 + sqrt( (b - b_err**2)**2 + 4*(s + b)*b_err**2))
    Z = 0.0

    if b > 0:
        Z = sqrt(2*((s+b)*log((s+b)/B0) + B0 - s - b) + (b-B0)**2/b_err**2)

    return Z

# returns the signal significance without background error term
def signalSignificance(s, b):
    Z = 0.0

    if b > 0:
        Z = sqrt(abs(2*((s+b)*log((s+b)/b)-s)))
        
    return Z

# returns True if an event passes a cut point
def pass_cut_point(event, cut_point):
    if event.mll < cut_point.mll:
        return False
    if event.mjj < cut_point.mjj:
        return False
    if event.leptons_selected_l0_pt < cut_point.l0pt:
        return False
    if event.leptons_selected_l1_pt < cut_point.l1pt:
        return False
    if event.jets_selected_j0_pt < cut_point.j0pt:
        return False
    if event.jets_selected_j1_pt < cut_point.j1pt:
        return False
    if event.lepjet_centrality < cut_point.cent:
        return False
    return True

# returns a list of the full path to each signal sample
def getSigFiles():
    files = []
    #just one file for now
    files.append("/home/will/Documents/ssww_upgrade_rgs/ssww_local_data/local_v14_20GeV/hist-oldsamples.mc15_14TeV.private.ssWWEW.root")

    return files

# returns a list of the full path to each background sample
def getBkgFiles():
    files = []
    
    # file containing full paths of data samples
    file_list = open("../data/files_20GeV.txt")

    for line in file_list:
        line = line.strip()
        # remove old/debug samples
        if '363719' in line: continue # old WZ sample
        if '410000' in line: continue # old ttbar debug sample
        
        files.append(line)

    return files

# returns a dictionary of the full path to each background sample separated by sample ID (key)
def getBkgFiles_dict():
    files = {}

    # file containing full paths of data samples
    file_list = getBkgFiles()

    for line in file_list:
        line = line.strip() # full path
        sample = line.split('/')[-2] # grid sample name

        # special case
        if "ssWWQCD" in line:
            files['123456'] = line
            continue

        run = sample.split('.')[3] # run number

        # add remaining files to dictionary
        if run in files:
            files[run].append(line)
        else:
            files[run] = [line]

    return files

# returns a dictionary sample ID's sorted by background types (key)
def get_sample_types():
    pass

# returns a dictionary of event weights for each sample ID (key)
def get_event_weights():
    luminosity = 3000
    weights = {}
    with open("weights.csv") as f:
        line = f.readline()
        while line:
            if line[0] == "#":
                line = f.readline()
                continue

            l = line.split(',')
            sid = int(l[0])
            # weight = xsec*kfactor*filter/sumweights * luminosity
            weights[sid] = float(l[1])*float(l[4])*float(l[3])/float(l[2])*luminosity

            line = f.readline()
    return weights

