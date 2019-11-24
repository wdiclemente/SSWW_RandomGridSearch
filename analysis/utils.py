from ROOT import *
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

# returns two lists of 1D histograms for each of the optimization variables
#  the first list is for signal and the second is for background
#  these are hard-coded for now, and the order MUST be the same here and in fill_histograms()
def create_histograms():
    h_sig = []
    h_bkg = []
    plot_vars = ['mll', 'mjj', 'lepjet_centrality',
                 'leptons_selected_l0_pt',
                 'leptons_selected_l1_pt',
                 'jets_selected_j0_pt',
                 'jets_selected_j1_pt']

    h_sig.append(TH1F("sig_mll","m_{ll}",20,0,500))
    h_bkg.append(TH1F("bkg_mll","m_{ll}",20,0,500))

    h_sig.append(TH1F("sig_mjj","m_{jj}",20,0,1500))
    h_bkg.append(TH1F("bkg_mjj","m_{jj}",20,0,1500))

    h_sig.append(TH1F("sig_centrality","centrality",20,-3,3))
    h_bkg.append(TH1F("bkg_centrality","centrality",20,-3,3))

    h_sig.append(TH1F("sig_l0pt","l_{0} p_{T}",18,0,360))
    h_bkg.append(TH1F("bkg_l0pt","l_{0} p_{T}",18,0,360))

    h_sig.append(TH1F("sig_l1pt","l_{1} p_{T}",18,0,360))
    h_bkg.append(TH1F("bkg_l1pt","l_{1} p_{T}",18,0,360))

    h_sig.append(TH1F("sig_j0pt","j_{0} p_{T}",18,0,600))
    h_bkg.append(TH1F("bkg_j0pt","j_{0} p_{T}",18,0,600))

    h_sig.append(TH1F("sig_j1pt","j_{1} p_{T}",18,0,600))
    h_bkg.append(TH1F("bkg_j1pt","j_{1} p_{T}",18,0,600))

    return h_sig, h_bkg

# fills the histograms for the given event
#  order MUST be the same as in create_histograms
def fill_histograms(event, weight, histograms):

    histograms[0].Fill(event.mll,                    weight)
    histograms[1].Fill(event.mjj,                    weight)
    histograms[2].Fill(event.lepjet_centrality,      weight)
    histograms[3].Fill(event.leptons_selected_l0_pt, weight)
    histograms[4].Fill(event.leptons_selected_l1_pt, weight)
    histograms[5].Fill(event.jets_selected_j0_pt,    weight)
    histograms[6].Fill(event.jets_selected_j1_pt,    weight)

    return

# set global plot style
def plot_style():
    style = TStyle("style","style")

    icol = 0 #white
    style.SetFrameBorderMode(icol)
    style.SetFrameFillColor(icol)
    style.SetCanvasBorderMode(icol)
    style.SetCanvasColor(icol)
    style.SetPadBorderMode(icol)
    style.SetPadColor(icol)
    style.SetStatColor(icol)

    style.SetPaperSize(20,26)

    style.SetPadTopMargin(0.05)
    style.SetPadRightMargin(0.05)
    style.SetPadBottomMargin(0.16)
    style.SetPadLeftMargin(0.16)

    style.SetTitleXOffset(1.4)
    style.SetTitleYOffset(1.4)

    font = 42
    tsize = 0.05
    style.SetTextFont(font)

    style.SetTextSize(tsize)
    style.SetLabelFont(font,"x")
    style.SetTitleFont(font,"x")
    style.SetLabelFont(font,"y")
    style.SetTitleFont(font,"y")
    style.SetLabelFont(font,"z")
    style.SetTitleFont(font,"z")
    
    style.SetLabelSize(tsize,"x")
    style.SetTitleSize(tsize,"x")
    style.SetLabelSize(tsize,"y")
    style.SetTitleSize(tsize,"y")
    style.SetLabelSize(tsize,"z")
    style.SetTitleSize(tsize,"z")
    
    style.SetMarkerStyle(20)
    style.SetMarkerSize(1.2)
    style.SetHistLineWidth(2)
    style.SetLineStyleString(2,"[12 12]")

    style.SetEndErrorSize(0.)

    style.SetOptTitle(0)
    style.SetOptStat(0)
    style.SetOptFit(0)

    style.SetPadTickX(1)
    style.SetPadTickY(1)

    # apply the style
    style.cd()

# applies formatting to histogram
def format_hist(hist, is_signal, normalize, xaxis_label = ""):
    colors = [kBlack,kBlue-9]
    hist.GetYaxis().SetTitle("Events")
    hist.GetXaxis().SetTitle(xaxis_label)
    
    if not is_signal:
        hist.SetLineColor(kBlack)
        hist.SetLineStyle(1)
        hist.SetFillStyle(1001)
        hist.SetFillColor(colors[1])

    else:
        hist.SetLineColor(colors[0])
        hist.SetMarkerColor(colors[0])
        hist.SetMarkerStyle(kFullCircle)

    if normalize:
        h_int = hist.Integral()
        if not h_int == 0:
            hist.Scale(1/h_int)
        
    return

# scales axes for list of histograms so they all fit on the same view
def scale_y_axis(plot_list, scale_factor=1.4):
    maximum = -1
    for plot in plot_list:
        temp = plot.GetMaximum()
        if temp > maximum:
            maximum = temp

    for plot in plot_list:
        plot.SetMinimum(0)
        plot.SetMaximum(maximum*scale_factor)
        plot.SetMinimum(.001)
    return

# makes a vertical line at the given x_coord
def getTLineY(x_coord,hist,opt=False):
    ymin = 0 #hist.GetMinimum()
    ymax = hist.GetMaximum()
    line = TLine(x_coord, ymin, x_coord, ymax)
    if opt:
        line.SetLineColor(8)
    else:
        line.SetLineColor(2)
    line.SetLineWidth(2)
    line.SetLineStyle(9)
    return line

# makes a horizontal arrow from x1 to x2
def getTArrowX(x1, x2, hist):
    y0 = hist.GetMaximum()*0.8
    arrow = TArrow(x1, y0, x2, y0, 0.025, "|>")
    arrow.SetAngle(40)
    arrow.SetLineWidth(2)
    return arrow
