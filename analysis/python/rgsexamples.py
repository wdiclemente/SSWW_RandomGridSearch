#from array import array
from rgsutil import *
from string import *
from math import *
from ROOT import *

execfile('scales.py')
execfile('systematics.py')

def getBkgFiles(do_13TeV = False):
    files = []
    file_directory = "/disk/userdata00/atlas_data2/wdic/ssWW_upgrade_v13_FCTight/"
    # manually add local files
    files.append("local_v13_FCTight/hist-oldsamples.mc15_14TeV.private.ssWWQCD.root")
    # grid files
    for root, directories, filenames in os.walk(file_directory):
        for filename in filenames:
            filepath = os.path.join(root,filename)
            if not '.root' in filepath: continue
            if '363719' in filepath: continue #old WZ sample
            if '410000' in filepath: continue # for ttbar debugging
            if '410501' in filepath:
                if not do_13TeV and 'mc15_13TeV' in filepath:
                    continue
                elif   do_13TeV and 'mc15_14TeV' in filepath:
                    continue

            if settings.doPolar and (not settings.useCombinedSig):
                if '990031' in filepath and 'LL' in filepath: continue # LL sig
            else:
                if '990031' in filepath: continue # LL and TX
     
            files.append(filepath)

    # w+jets
    file_directory = "/disk/userdata00/atlas_data2/wdic/ssWW_upgrade_v13_wjets_FCTight/"
    for root, directories, filenames in os.walk(file_directory):
        for filename in filenames:
            filepath = os.path.join(root,filename)
            if not '.root' in filepath: continue
            files.append(filepath)

    #print files

    return files

def getBkgFiles_dict():
    files = {}
    file_directory = "/disk/userdata00/atlas_data2/wdic/ssWW_upgrade_v13_FCTight/"

    # manually add local files
    files['123456'] = ["local_v13_FCTight/hist-oldsamples.mc15_14TeV.private.ssWWQCD.root"]

    # grid files
    for root, directories, filenames in os.walk(file_directory):
        for filename in filenames:
            filepath = os.path.join(root,filename)
            if not '.root' in filepath: continue
            run = root.split('.')[3]

            if '363719' in filepath: continue # old WZ sample
            if '410000' in filepath: continue # for ttbar debugging
            if 'mc15_13TeV' in filepath: continue

            if settings.doPolar and (not settings.useCombinedSig):
                if '990031' in filepath and 'LL' in filepath: continue
            else:
                if '990031' in filepath: continue # LL and TX samples

            if run in files:
                files[run].append(filepath)
            else:
                files[run] = [filepath]

    # w+jets
    file_directory = "/disk/userdata00/atlas_data2/wdic/ssWW_upgrade_v13_wjets_FCTight/"
    for root, directories, filenames in os.walk(file_directory):
        for filename in filenames:
            filepath = os.path.join(root,filename)
            if not '.root' in filepath: continue
            run = root.split('.')[3]
            if run in files:
                files[run].append(filepath)
            else:
                files[run] = [filepath]
    #print "Background file dictionary:\n",files
    return files
    

def getSigFiles():
    files = []
    #just one file for now
    if settings.doPolar and (not settings.useCombinedSig):
        files.append("/disk/userdata00/atlas_data2/wdic/ssWW_upgrade_v13_FCTight/user.karolos.ssWWupgrade.990031.LL.v13.TrackCalo.FCTight.00_hist/merged.990031.LL.root")
    else:
        files.append("local_v13_FCTight/hist-oldsamples.mc15_14TeV.private.ssWWEW.root")

    #print "Signal file list:\n",files
    return files

def scaleYAxis(hist_list, scale_factor = 1.4):
    minimum =    0.0
    maximum = -999.0
    for h in hist_list:
        temp_min = h.GetMinimum()
        temp_max = h.GetMaximum()
        if temp_min < minimum:
            minimum = temp_min
        if temp_max > maximum:
            maximum = temp_max
    print "Scaling histograms to (%f,%f)" % (minimum, maximum)
    for h in hist_list:
        h.GetYaxis().SetRangeUser(minimum*scale_factor,
                                  maximum*scale_factor)

def ScaleYAxisMultiple(plot_list, scale_factor=1.4):
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

def getTLineY(x_coord,hist,sig=False):
    ymin = 0 #hist.GetMinimum()
    ymax = hist.GetMaximum()+1000
    line = TLine(x_coord, ymin, x_coord, ymax)
    line.SetLineColor(8)
    if sig:
        line.SetLineColor(2)
    line.SetLineWidth(2)
    line.SetLineStyle(9)
    return line

def getTArrowX(x1, x2, hist):
    y0 = hist.GetMaximum()*1.4
    arrow = TArrow(x1, y0, x2, y0, 0.025, "|>")
    arrow.SetAngle(40)
    arrow.SetLineWidth(2)
    return arrow

def fill_hists(hist_list, hist_charge, hist_fake, ntuple, bestcuts, is_sig = False):
    do_sig_cuts = False

    for ii, event in enumerate(ntuple):
        if ii%250000 == 0: print "Processing event #",ii
        #if baseCuts(event): continue
        
        if is_sig:
            weight = event.weight_total_no3rdlep
            if settings.doPolar and settings.useCombinedSig:
                weight *= WWEWKscale
            else:
                weight *= scaleDict[999999]
            #weight = event.weight_event*event.weight_trig*WWEWKscale
        else:
            weight = event.weight_total_no3rdlep*scaleDict[event.runNumber]
            #weight = event.weight_event*event.weight_trig*scaleDict[event.runNumber]

        if event.weight_event > 1000:
            print "Skipping (run,event) (%i,%i) with large weight %f" %(event.runNumber, event.eventNumber, event.weight_event)
            continue

        if do_sig_cuts:
            if not event.pass_selection == 10:
                continue

        if not is_sig and event.event_isFlip:
            hist_charge[0].Fill(event.mjj,    weight)
            hist_charge[1].Fill(event.detajj, weight)
            hist_charge[2].Fill(event.lepjet_centrality, weight)
            hist_charge[3].Fill(event.mll,        weight)
            hist_charge[4].Fill(event.leptons_selected_l0_pt, weight)
            hist_charge[5].Fill(event.leptons_selected_l1_pt, weight)
            hist_charge[6].Fill(event.jets_selected_j0_pt,    weight)
            hist_charge[7].Fill(event.jets_selected_j1_pt,    weight)
            if event.pass_selection == 10:
                hist_charge[8].Fill(1,weight)
                hist_charge[8].Fill(1+event.channel,weight)
            if not optimizedCuts(event, bestcuts):
                hist_charge[8].Fill(20,weight)
                hist_charge[8].Fill(20+event.channel,weight)
        elif not is_sig and event.event_isFake:
            hist_fake[0].Fill(event.mjj,    weight)
            hist_fake[1].Fill(event.detajj, weight)
            hist_fake[2].Fill(event.lepjet_centrality, weight)
            hist_fake[3].Fill(event.mll,        weight)
            hist_fake[4].Fill(event.leptons_selected_l0_pt, weight)
            hist_fake[5].Fill(event.leptons_selected_l1_pt, weight)
            hist_fake[6].Fill(event.jets_selected_j0_pt,    weight)
            hist_fake[7].Fill(event.jets_selected_j1_pt,    weight)
            if event.pass_selection == 10:
                hist_fake[8].Fill(1,weight)
                hist_fake[8].Fill(1+event.channel,weight)
            if not optimizedCuts(event, bestcuts):
                hist_fake[8].Fill(20,weight)
                hist_fake[8].Fill(20+event.channel,weight)
        else:
            hist_list[0].Fill(event.mjj,    weight)
            hist_list[1].Fill(event.detajj, weight)
            hist_list[2].Fill(event.lepjet_centrality, weight)
            hist_list[3].Fill(event.mll,        weight)
            hist_list[4].Fill(event.leptons_selected_l0_pt, weight)
            hist_list[5].Fill(event.leptons_selected_l1_pt, weight)
            hist_list[6].Fill(event.jets_selected_j0_pt,    weight)
            hist_list[7].Fill(event.jets_selected_j1_pt,    weight)
            if event.pass_selection == 10:
                hist_list[8].Fill(1,weight)
                hist_list[8].Fill(1+event.channel,weight)
            if not optimizedCuts(event, bestcuts):
                hist_list[8].Fill(20,weight)
                hist_list[8].Fill(20+event.channel,weight)
    return hist_list

def format_hist(hist, num, xaxis_label = ""):
    #colors = [1, 2, 41, 40, 44, 32, 36, 28, 15]
    colors = [1, 3, 9, 6, kYellow-4, kYellow-4, kYellow-4, kOrange+1, 46]
    if num < 9:
        #hist.SetLineColor(colors[num])
        hist.SetLineColor(1)
        hist.SetLineStyle(1)
        hist.SetFillColor(colors[num])
        hist.SetMarkerColor(colors[num])
        hist.SetMarkerStyle(kFullCircle)
    else:
        hist.SetLineColor(13)
        hist.SetMarkerColor(13)
        hist.SetMarkerStyle(2)
    hist.GetYaxis().SetTitle("Events")
    hist.GetXaxis().SetTitle(xaxis_label)

def make1DPlots(bestcuts):

    do_normalize = True

    #sig
    ntuples = [Ntuple(getSigFiles(), 't_events')]
    #bkg
    bfiles = getBkgFiles_dict()

    bntuple_wwq = Ntuple(bfiles['123456']
                         , 't_events')
    ntuples.append(bntuple_wwq)

    bntuple_dib = Ntuple(bfiles['364250']+
                         bfiles['364254']+
                         bfiles['364255']+
                         bfiles['364284']+
                         bfiles['363718']
                         , 't_events')
    ntuples.append(bntuple_dib)

    bntuple_tri = Ntuple(bfiles['364242']+
                         bfiles['364243']+
                         bfiles['364244']+
                         bfiles['364245']+
                         bfiles['364246']+
                         bfiles['364336']+
                         bfiles['364337']+
                         bfiles['364338']+
                         bfiles['364339']+
                         bfiles['363507']+
                         bfiles['363508']+
                         bfiles['363509']
                         , 't_events')
    ntuples.append(bntuple_tri)

    bntuple_top = Ntuple(bfiles['410155']+
                         bfiles['410218']+
                         bfiles['410219']+
                         bfiles['410220']+
                         bfiles['410642']+
                         bfiles['410643']+
                         bfiles['410644']+
                         bfiles['410645']+
                         bfiles['410501']
                         , 't_events')
    ntuples.append(bntuple_top)

    bntuple_zjt = Ntuple(bfiles['147806']+
                         bfiles['147807']
                         , 't_events')
    ntuples.append(bntuple_zjt)

    bntuple_wjt = Ntuple(bfiles['363600'] +
                         bfiles['363601'] +
                         bfiles['363602'] +
                         bfiles['363603'] +
                         bfiles['363604'] +
                         bfiles['363605'] +
                         bfiles['363606'] + 
                         bfiles['363607'] +
                         bfiles['363608'] +
                         bfiles['363609'] +
                         bfiles['363610'] + 
                         bfiles['363611'] +
                         bfiles['363612'] +
                         bfiles['363613'] + 
                         bfiles['363614'] +
                         bfiles['363615'] +
                         bfiles['363616'] + 
                         #bfiles['363617'] +
                         bfiles['363618'] + 
                         bfiles['363619'] +
                         bfiles['363620'] +
                         bfiles['363621'] +
                         bfiles['363622'] +
                         bfiles['363623'] + 
                         bfiles['363624'] + 
                         bfiles['363625'] +
                         bfiles['363626'] +
                         bfiles['363627'] +
                         bfiles['363628'] +
                         bfiles['363629'] +
                         bfiles['363630'] +
                         bfiles['363631'] +
                         bfiles['363632'] +
                         bfiles['363633'] +
                         bfiles['363634'] +
                         bfiles['363635'] +
                         bfiles['363636'] +
                         bfiles['363637'] +
                         bfiles['363638'] +
                         bfiles['363639'] +
                         bfiles['363640'] +
                         bfiles['363641'] +
                         bfiles['363642'] +
                         bfiles['363643'] +
                         bfiles['363644'] +
                         bfiles['363645'] +
                         bfiles['363646'] +
                         bfiles['363647'] +
                         bfiles['363648'] +
                         bfiles['363649'] +
                         bfiles['363650'] +
                         bfiles['363651'] +
                         bfiles['363652'] +
                         bfiles['363653'] +
                         bfiles['363654'] +
                         bfiles['363655'] +
                         bfiles['363656'] +
                         bfiles['363657'] +
                         bfiles['363658'] +
                         bfiles['363659'] +
                         bfiles['363660'] +
                         bfiles['363661'] +
                         bfiles['363662'] +
                         bfiles['363663'] +
                         bfiles['363664'] +
                         bfiles['363665'] +
                         bfiles['363666'] +
                         bfiles['363667'] +
                         bfiles['363668'] +
                         bfiles['363669'] +
                         bfiles['363670'] +
                         bfiles['363671']
                         , 't_events')
    ntuples.append(bntuple_wjt)

    # save histos to root file for debugging purposes
    all_hists  = [] #to prevent deletion
    histo_file = TFile("plots/plots.root","RECREATE")
    histo_dir  = histo_file.mkdir("plots")

    samples   = ['wwsig', 'wwqcd', 'diboson', 'triboson', 'top', 'zjets', 'wjets', 'chargeflip', 'fakes']
    plots     = ['mjj', 'detajj', 'centrality', 'mll', 'lep0pt', 'lep1pt', 'jet0pt', 'jet1pt']
    variables = ['mjj', 'detajj', 'lepjet_centrality', 'mll', 'leptons_selected_l0_pt', 'leptons_selected_l1_pt', 'jets_selected_j0_pt', 'jets_selected_j1_pt']
    labels    = ['M_{jj}', '#Delta#eta_{jj}', '#zeta_{lj}','M_{ll}','leading lepton p_{T}', 'subleading lepton p_{T}', 'leading jet p_{T}', 'subleading jet p_{T}']
    old_cuts  = [500, 2.5, 0.0, 20, 25, 25, 30, 30]
    nbins = 20

    mjj_min    = 0.0
    mjj_max    = 1000.0

    detajj_min = 0.0
    detajj_max = 5.0
    
    centra_min = -3.0
    centra_max =  3.0

    mll_min    = 0.0
    mll_max    = 500.0

    lep0pt_min = 0.0
    lep0pt_max = 360.0

    lep1pt_min = 0.0
    lep1pt_max = 360.0

    jet0pt_min = 0.0
    jet0pt_max = 600.0

    jet1pt_min = 0.0
    jet1pt_max = 600.0

    # make charge flip and fake histograms
    h_mjj_c    = mkhist1("mjj_c"   , "m_{jj} [GeV]",     "", nbins, mjj_min,    mjj_max)
    h_detajj_c = mkhist1("detajj_c", "#Delta#eta_{jj}",  "", nbins, detajj_min, detajj_max)
    h_centra_c = mkhist1("centra_c", "Centrality",       "", nbins, centra_min, centra_max)
    h_mll_c    = mkhist1("mll_c"   , "m_{ll} [GeV]",     "", nbins, mll_min,    mll_max)
    h_lep0pt_c = mkhist1("lep0pt_c", "lep0 p_{T} [GeV]", "", 18, lep0pt_min, lep0pt_max)
    h_lep1pt_c = mkhist1("lep1pt_c", "lep1 p_{T} [GeV]", "", 18, lep1pt_min, lep1pt_max)
    h_jet0pt_c = mkhist1("jet0pt_c", "jet0 p_{T} [GeV]", "", 30, jet0pt_min, jet0pt_max)
    h_jet1pt_c = mkhist1("jet1pt_c", "jet1 p_{T} [GeV]", "", 30, jet1pt_min, jet1pt_max)
    h_count_c  = mkhist1("count_c" , "counter"         , "", 100, 0,          100)
    hists_c = [h_mjj_c, h_detajj_c, h_centra_c, h_mll_c, h_lep0pt_c, h_lep1pt_c, h_jet0pt_c, h_jet1pt_c, h_count_c]

    h_mjj_f    = mkhist1("mjj_f"   , "m_{jj} [GeV]",     "", nbins, mjj_min,    mjj_max)
    h_detajj_f = mkhist1("detajj_f", "#Delta#eta_{jj}",  "", nbins, detajj_min, detajj_max)
    h_centra_f = mkhist1("centra_f", "Centrality",       "", nbins, centra_min, centra_max)
    h_mll_f    = mkhist1("mll_f"   , "m_{ll} [GeV]",     "", nbins, mll_min,    mll_max)
    h_lep0pt_f = mkhist1("lep0pt_f", "lep0 p_{T} [GeV]", "", 18, lep0pt_min, lep0pt_max)
    h_lep1pt_f = mkhist1("lep1pt_f", "lep1 p_{T} [GeV]", "", 18, lep1pt_min, lep1pt_max)
    h_jet0pt_f = mkhist1("jet0pt_f", "jet0 p_{T} [GeV]", "", 30, jet0pt_min, jet0pt_max)
    h_jet1pt_f = mkhist1("jet1pt_f", "jet1 p_{T} [GeV]", "", 30, jet1pt_min, jet1pt_max)
    h_count_f  = mkhist1("count_f" , "counter"         , "", 100, 0,          100)
    hists_f = [h_mjj_f, h_detajj_f, h_centra_f, h_mll_f, h_lep0pt_f, h_lep1pt_f, h_jet0pt_f, h_jet1pt_f, h_count_f]

    # Fill lists of histograms for each sample
    for i in range(len(ntuples)):
        print "Filling histograms for",samples[i],"samples"
        h_mjj    = mkhist1("mjj"   +str(i), "m_{jj} [GeV]",     "", nbins, mjj_min,    mjj_max)
        h_detajj = mkhist1("detajj"+str(i), "#Delta#eta_{jj}",  "", nbins, detajj_min, detajj_max)
        h_centra = mkhist1("centra"+str(i), "Centrality",       "", nbins, centra_min, centra_max)
        h_mll    = mkhist1("mll"   +str(i), "m_{ll} [GeV]",     "", nbins, mll_min,    mll_max)
        h_lep0pt = mkhist1("lep0pt"+str(i), "lep0 p_{T} [GeV]", "", 18, lep0pt_min, lep0pt_max)
        h_lep1pt = mkhist1("lep1pt"+str(i), "lep1 p_{T} [GeV]", "", 18, lep1pt_min, lep1pt_max)
        h_jet0pt = mkhist1("jet0pt"+str(i), "jet0 p_{T} [GeV]", "", 30, jet0pt_min, jet0pt_max)
        h_jet1pt = mkhist1("jet1pt"+str(i), "jet1 p_{T} [GeV]", "", 30, jet1pt_min, jet1pt_max)
        h_count  = mkhist1("count" +str(i) , "counter"        , "", 100, 0,          100)
        hists = [h_mjj, h_detajj, h_centra, h_mll, h_lep0pt, h_lep1pt, h_jet0pt, h_jet1pt, h_count]
        all_hists.append(fill_hists(hists, hists_c, hists_f, ntuples[i], bestcuts, i == 0))

    # add filled chargeflip and fake histograms to list
    all_hists.append(hists_c)
    all_hists.append(hists_f)

    # Make a canvas and set its margins
    c1 = TCanvas("c1", "c1", 600, 400)
    c1.SetBottomMargin(0.15)
    c1.SetLeftMargin(0.15)

    # normalize and draw the histograms
    for i in range(len(plots)):
        h_sig = all_hists[0][i]
        format_hist(h_sig, 0, labels[i])
        h_qcd = all_hists[1][i]
        format_hist(h_qcd, 1, labels[i])
        h_dib = all_hists[2][i]
        format_hist(h_dib, 2, labels[i])
        h_tri = all_hists[3][i]
        format_hist(h_tri, 3, labels[i])
        h_top = all_hists[4][i]
        format_hist(h_top, 4, labels[i])
        h_zjt = all_hists[5][i]
        format_hist(h_zjt, 5, labels[i])
        h_wjt = all_hists[6][i]
        format_hist(h_wjt, 6, labels[i])
        h_chf = all_hists[7][i]
        format_hist(h_chf, 7, labels[i])
        h_fak = all_hists[8][i]
        format_hist(h_fak, 8, labels[i])

        error = h_qcd.Clone()
        error.Add(h_dib)
        error.Add(h_tri)
        error.Add(h_top)
        error.Add(h_zjt)
        error.Add(h_wjt)
        error.Add(h_chf)
        error.Add(h_fak)
        format_hist(error, 99)

        if do_normalize:
            # scale bkg histograms to 1/error so when they're stacked the normalization is correct
            scale = error.Integral() if error.Integral() > 0 else 1.
            #h_qcd.Scale(1/scale)
            #h_dib.Scale(1/scale)
            #h_tri.Scale(1/scale)
            #h_top.Scale(1/scale)
            #h_zjt.Scale(1/scale)
            #h_wjt.Scale(1/scale)
            #h_chf.Scale(1/scale)
            #h_fak.Scale(1/scale)
            #error.Scale(1/scale)
            h_sig.Scale(scale/h_sig.Integral() if h_sig.Integral() > 0 else 1.)
            #h_qcd.Scale(scale/h_qcd.Integral() if h_qcd.Integral() > 0 else 1.)

        stack = THStack(plots[i],"stack")
        stack.Add(h_top)
        stack.Add(h_wjt) 
        stack.Add(h_zjt)
        stack.Add(h_tri)
        stack.Add(h_dib)
        stack.Add(h_fak)
        stack.Add(h_chf)
        stack.Add(h_qcd)

        brun = TLegend(.65,.7,.85,.9)
        brun.SetBorderSize(0)
        brun.SetFillColor(0)
        brun.SetTextSize(0.03)
        brun.SetTextFont(42)
        brun.AddEntry(h_sig, "W^{#pm}W^{#pm} (EW)", "pe")
        brun.AddEntry(h_qcd, "W^{#pm}W^{#pm} (QCD)", "f")
        brun.AddEntry(h_chf, "Charge Mis-ID", "f")
        brun.AddEntry(h_fak, "Jets faking electrons", "f")
        brun.AddEntry(h_dib, "Diboson", "f")
        brun.AddEntry(h_tri, "Triboson", "f")
        brun.AddEntry(h_top, "Other non-prompt", "f")
        #brun.AddEntry(h_zjt, "Z+jets", "f")
        #brun.AddEntry(h_wjt, "W+jets", "f")
        #brun.AddEntry(h_top, "top+t#bar{t}", "f")

        if not "detajj" in  variables[i]:
            l_cut = getTLineY(bestcuts[variables[i]], stack, sig=False)
            l_sig = getTLineY(old_cuts[i],            stack, sig=True)
            arrow = getTArrowX(old_cuts[i], bestcuts[variables[i]], h_sig)

        ScaleYAxisMultiple([h_sig,stack])
        stack.Draw("hist")
        stack.GetYaxis().SetTitle("Events")
        stack.GetXaxis().SetTitle(labels[i])
        stack.Draw("hist")
        error.Draw("SAME")
        #h_qcd.Draw("SAME")
        h_sig.Draw("SAME")
        l_cut.Draw()
        l_sig.Draw()
        arrow.Draw()
        brun.Draw()
        c1.SetLogy(0)
        c1.Print("plots/"+plots[i]+".pdf", "Portrait pdf")
        c1.Print("plots/"+plots[i]+".png", "Portrait png")
        #c1.SetLogy(1)
        #c1.Print("plots/"+plots[i]+"_logy.pdf", "Portrait pdf")

    histo_file.Write()
    histo_file.Close()
    return

def baseCuts(event):
    if not event.leptons_selected_n == 2: return True
    if not event.dilepton_charge    == 1: return True
    return False

def signalCuts(event):
    # using the ntuple's selection variable for now
    if not event.pass_selection == 10:
        return 1
    return 0

def optimizedCuts(event, bestcuts):
    if not event.pass_selection == 10:
        return 1
    if event.leptons_selected_l0_pt < bestcuts['leptons_selected_l0_pt']: return 2
    if not settings.doPolar:
        if event.leptons_selected_l1_pt < bestcuts['leptons_selected_l1_pt']: return 2
    if event.mll < bestcuts['mll']: return 3
    if event.jets_selected_j0_pt < bestcuts['jets_selected_j0_pt']: return 4
    if event.jets_selected_j1_pt < bestcuts['jets_selected_j1_pt']: return 4
    if event.mjj < bestcuts['mjj']: return 5
    if event.lepjet_centrality < bestcuts['lepjet_centrality']: return 6
    return 0

def getSSWWSignalZ(bestcuts):
    # manually set flags for some printout stuff
    no_weight = False
    fake_only = False
    flip_only = False

    # get data ntuples
    sntuple = Ntuple(getSigFiles(), 't_events')
    bntuple = Ntuple(getBkgFiles(settings.do13TeV), 't_events')

    # default cuts
    default_dict = {} # [total, mm, ee, me, em]

    # optimized cuts
    optimize_dict = {}

    debug_counter = 0

    # background
    current_run = -1
    for ii, event in enumerate(bntuple):
        if not event.runNumber == current_run:
        #    print "Beginning run",event.runNumber
            current_run = event.runNumber

        if ii%250000 == 0: print "Checking selection cuts for bkg event #",ii
        if event.weight_event > 1000:
            print "Found event with very large weight %f! Skipping!" %(event.weight_event)
            continue

        # get weight
        weight = event.weight_total_no3rdlep*scaleDict[event.runNumber]
        if no_weight:
            weight = 1

        # tag flip/fake events
        runNum = event.runNumber
        if event.event_isFlip:
            runNum = 111111
        elif event.event_isFake:
            runNum = 222222

        if fake_only and not event.event_isFake:
            continue
        if flip_only and not event.event_isFlip:
            continue

        # get statistical and systematic errors for event
        stat_error2 = weight**2
        #syst_error2 = (sysDict[runNum]*weight)**2

        # check default selection
        result = signalCuts(event)
        if not result:
            if runNum in default_dict:
                default_dict[runNum][0][0] += weight
                default_dict[runNum][0][1] += stat_error2
                #default_dict[runNum][0][2] += syst_error2
            else:
                default_dict[runNum]  = [[weight,stat_error2,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.]]
            default_dict[runNum][event.channel][0] += weight
            default_dict[runNum][event.channel][1] += stat_error2
            #default_dict[runNum][event.channel][2] += syst_error2

        # check optimized selection
        opt_result = optimizedCuts(event, bestcuts)
        if not opt_result:
            if runNum in optimize_dict:
                optimize_dict[runNum][0][0] += weight
                optimize_dict[runNum][0][1] += stat_error2
                #optimize_dict[runNum][0][2] += syst_error2
            else:
                optimize_dict[runNum]  = [[weight,stat_error2,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.]]
            optimize_dict[runNum][event.channel][0] += weight
            optimize_dict[runNum][event.channel][1] += stat_error2
            #optimize_dict[runNum][event.channel][2] += syst_error2

    # signal
    for ii, event in enumerate(sntuple):
        if ii%250000 == 0: print "Checking selection cuts for sig event #",ii
        if event.weight_event > 1000:
            print "Found event with very large weight %f! Skipping!" %(event.weight_event)
            continue

        runNum = 999999
        weight = event.weight_total_no3rdlep
        if settings.doPolar and settings.useCombinedSig:
            weight *= WWEWKscale
        else:
            weight *= scaleDict[runNum]
        stat_error2 = weight**2

        # check default selection
        result = signalCuts(event)
        if not result:
            if runNum in default_dict:
                default_dict[runNum][0][0] += weight
                default_dict[runNum][0][1] += stat_error2
                #default_dict[runNum][0][2] += syst_error2
            else:
                default_dict[runNum]  = [[weight,stat_error2,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.]]
            default_dict[runNum][event.channel][0] += weight
            default_dict[runNum][event.channel][1] += stat_error2
            #default_dict[runNum][event.channel][2] += syst_error2

        # check optimized selection
        opt_result = optimizedCuts(event, bestcuts)
        if not opt_result:
            if runNum in optimize_dict:
                optimize_dict[runNum][0][0] += weight
                optimize_dict[runNum][0][1] += stat_error2
                #optimize_dict[runNum][0][2] += syst_error2
            else:
                optimize_dict[runNum]  = [[weight,stat_error2,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.], [0.,0.,0.]]
            optimize_dict[runNum][event.channel][0] += weight
            optimize_dict[runNum][event.channel][1] += stat_error2
            #optimize_dict[runNum][event.channel][2] += syst_error2

    # calculate systematic errors and store them as syst_err**2 for ease of combining
    for key in default_dict.iterkeys():
        for i in range(0,5):
            default_dict[key][i][2] = (default_dict[key][i][0]*sysDict[key])**2
    for key in optimize_dict.iterkeys():
        for i in range(0,5):
            optimize_dict[key][i][2] = (optimize_dict[key][i][0]*sysDict[key])**2

    # end of loop event counting and error calculations
    # default selection
    def_sig           = default_dict[999999][0][0]
    def_sig_stat_err  = sqrt(abs(default_dict[999999][0][1]))
    def_sig_syst_err  = sqrt(abs(default_dict[999999][0][2]))
    def_sig_total_err = sqrt(abs(def_sig_stat_err**2 + def_sig_syst_err**2))
    def_bkg           = 0.
    def_bkg_stat_err  = 0.
    def_bkg_syst_err  = 0.
    for key,value in default_dict.items():
        if key == 999999: continue
        def_bkg          += value[0][0]
        def_bkg_stat_err += value[0][1]
        def_bkg_syst_err += value[0][2]
    def_bkg_total_err = sqrt(abs(def_bkg_stat_err + def_bkg_syst_err)) # errors are still squared at this point
    def_bkg_stat_err  = sqrt(abs(def_bkg_stat_err))
    def_bkg_syst_err  = sqrt(abs(def_bkg_syst_err))

    # optimized selection
    opt_sig           = optimize_dict[999999][0][0]
    opt_sig_stat_err  = sqrt(abs(optimize_dict[999999][0][1]))
    opt_sig_syst_err  = sqrt(abs(optimize_dict[999999][0][2]))
    opt_sig_total_err = sqrt(abs(opt_sig_stat_err**2 + opt_sig_syst_err**2))
    opt_bkg           = 0.
    opt_bkg_stat_err  = 0.
    opt_bkg_syst_err  = 0.
    for key,value in optimize_dict.items():
        if key == 999999: continue
        opt_bkg          += value[0][0]
        opt_bkg_stat_err += value[0][1]
        opt_bkg_syst_err += value[0][2]
    opt_bkg_total_err = sqrt(abs(opt_bkg_stat_err + opt_bkg_syst_err))
    opt_bkg_stat_err  = sqrt(abs(opt_bkg_stat_err))
    opt_bkg_syst_err  = sqrt(abs(opt_bkg_syst_err))

    # print run summaries
    print "--"*10

    print "Done checking events for signal selection."
    print "\tsig: %10.2f +/- %10.2f (stat) +/- %10.2f (sys)" % (def_sig, def_sig_stat_err, def_sig_syst_err)
    print "\tbkg: %10.2f +/- %10.2f (stat) +/- %10.2f (sys)" % (def_bkg, def_bkg_stat_err, def_bkg_syst_err)

    print "Done checking events for optimized selection."
    print "\tsig: %10.2f +/- %10.2f (stat) +/- %10.2f (sys)" % (opt_sig, opt_sig_stat_err, opt_sig_syst_err)
    print "\tbkg: %10.2f +/- %10.2f (stat) +/- %10.2f (sys)" % (opt_bkg, opt_bkg_stat_err, opt_bkg_syst_err)

    print "Run-by-run -- signal selection"
    print "   run       total         mm         ee         me         em"
    for key,value in sorted(default_dict.items()):
        print "%i\t%10.2f %10.2f %10.2f %10.2f %10.2f" %(key,value[0][0],value[1][0],value[2][0],value[3][0],value[4][0])
    print "Run-by-run -- optimized selection"
    print "   run       total         mm         ee         me         em"
    for key,value in sorted(optimize_dict.items()):
        print "%i\t%10.2f %10.2f %10.2f %10.2f %10.2f" %(key,value[0][0],value[1][0],value[2][0],value[3][0],value[4][0])

    print "--"*10

    # do detailed print outs
    print "Full yield table with errors: Default selection"
    printFullYieldsAndErrors(default_dict)
    print "--"*10
    print "Full yield table with errors: Optimized selection"
    printFullYieldsAndErrors(optimize_dict)
    print "--"*10
    

    # calculate significance before & after optimization
    def_sig = signalSignificanceErr(def_sig, def_bkg, def_bkg_total_err)
    opt_sig = signalSignificanceErr(opt_sig, opt_bkg, opt_bkg_total_err)

    return def_sig, opt_sig

def writeSSWWResults(filename, varfilename, ntuple, variables,
                     bestrow, bestZ, totals, outerhull=None):
    
    cutdir  = {}
    cutdirs = []
    for t in getCutDirections(varfilename):
        token = t[0]
        if token == '\\':
            continue
        else:
            cutdirs.append(t)
            cutdir[token] = t[1]
            
    ntuple.read(bestrow)

    # get dictionary of best cuts
    bestcuts = {}
    for name, count in variables:    
        if name[0:5] in ['count', 'fract', 'cutpo']: continue
        var = ntuple(name)
        bestcuts[name] = var
    #print bestcuts
    
    out = open(filename, 'w')

    print 
    record = "Yields before optimization"
    out.write('%s\n' % record); print record
    
    # signal
    record = "\tsignal:        %10.3f +/- %-10.1f" % (totals[0][0], totals[0][1])
    out.write('%s\n' % record); print record

    # background
    bkg_tot = 0
    bkg_err = 0
    for tot in totals[1:]:
        bkg_tot += tot[0]
        bkg_err += tot[1]**2
    bkg_err = bkg_err**(0.5)

    #print totals

    record = "\tbackground:    %10.3f +/- %-10.1f" % (bkg_tot,  bkg_err)
    out.write('%s\n' % record); print record    

    # significance
    s  = totals[0][0]
    b  = bkg_tot
    be = bkg_err
    if settings.doZwithErr:
        Z = signalSignificanceErr(s, b, be)
    else:
        Z = signalSignificance(s, b)

    sel_Z, opt_Z = getSSWWSignalZ(bestcuts)

    record = "\nZ values"
    out.write('%s\n' % record); print record
    
    #record = "  before optimization, no cuts:  %10.3f" % Z
    #out.write('%s\n' % record); print record

    record = "  before optimization, default cuts: %10.3f" % sel_Z
    out.write('%s\n' % record); print record

    #record = "  after optimization:   %10.3f" % bestZ
    #out.write('%s\n' % record); print record    

    record = "  after optimization, new cuts:      %10.3f" % opt_Z
    out.write('%s\n' % record); print record

    # best cuts
    record = "Best cuts"
    out.write('\n%s\n' % record); print; print record

    #bestcuts = {}
    for name, count in variables:    
        if settings.doPolar and "lepton_selected_l1_pt" in name: continue
        if name[0:5] in ['count', 'fract', 'error', 'cutpo']: continue
        var = ntuple(name)

        if type(var) == type(0.0):
            rec = '%3s %6.2f' % (cutdir[name], var)
            record = "\t%-10s\t%10s" % (name, rec)
            out.write('%s\n' % record); print record
        else:
            record = "\t%-10s\t%10.2f\t%10.2f" % (name,
                                                    min(var[0], var[1]),
                                                    max(var[0], var[1]))
            out.write('%s\n' % record); print record            
    print
    out.write('\n')

    # post-optimization yields
    record = "Yields after optimization (and relative efficiencies)"
    out.write('%s\n' % record); print record    

    sig_wwewk     = 0
    bkg_wwqcd     = 0
    bkg_diboson   = 0
    bkg_triboson  = 0
    bkg_top       = 0
    bkg_fake      = 0
    bkg_flip      = 0
    bkg_zjets     = 0
    bkg_wjets     = 0

    for name, count in variables:        
        if not (name[0:5] in ['count', 'fract']): continue
        var = ntuple(name)
        record = "\t%-15s %10.3f" % (name, var)
        out.write('%s\n' % record); print record                    
        if name[0:5] == "fract":
            print
            out.write('\n')
        elif name[0:5] == "count":
            if   "wwewk" in name:
                sig_wwewk += var
            elif "wwqcd" in name:
                bkg_wwqcd += var
            elif "diboson" in name or "wzewk" in name:
                bkg_diboson += var
            elif "triboson" in name:
                bkg_triboson += var
            elif "top" in name:
                bkg_top += var
            elif "fake" in name:
                bkg_fake += var
            elif "flip" in name:
                bkg_flip += var
            elif "zjets" in name:
                bkg_zjets += var
            elif "wjets" in name:
                bkg_wjets += var

    record = "Yields after optimization (by background type) -- this is broken after the switch to my own training code (naming convention changed etc etc)"
    out.write('%s\n' % record); print record
    record = "\t ww sig:   %10.3f" % (sig_wwewk)
    out.write('%s\n' % record); print record
    record = "--"*20
    out.write('%s\n' % record); print record
    record = "\t ww qcd:   %10.3f" % (bkg_wwqcd)
    out.write('%s\n' % record);print record
    record = "\t diboson:  %10.3f" % (bkg_diboson)
    out.write('%s\n' % record);print record
    record = "\t triboson: %10.3f" % (bkg_triboson)
    out.write('%s\n' % record);print record
    record = "\t top:      %10.3f" % (bkg_top)
    out.write('%s\n' % record);print record
    record = "\t fake:     %10.3f" % (bkg_fake)
    out.write('%s\n' % record);print record
    record = "\t ch flip:  %10.3f" % (bkg_flip)
    out.write('%s\n' % record);print record
    record = "\t zjets:    %10.3f" % (bkg_zjets)
    out.write('%s\n' % record);print record
    record = "\t wjets:    %10.3f" % (bkg_wjets)
    out.write('%s\n' % record);print record
    record = "--"*20
    out.write('%s\n' % record); print record
    record = "\tTotal bkg: %10.3f" % (bkg_wwqcd+bkg_diboson+bkg_triboson+bkg_top+bkg_fake+bkg_flip+bkg_zjets+bkg_wjets)
    out.write('%s\n' % record); print record

    out.close()
    return bestcuts
# ---------------------------------------------------------------------
def drawSSWWLegend(stitle="WW EWK",
                  btitle="WW QCD",
                  left=True,
                  postfix=''):                       
    lgoffset1 = 0.595
    lgoffset2 = 0.583
    if left:
        lgoffset1 = 0.23
        lgoffset2 = 0.21
        
    # Title
    t = TLatex(lgoffset1, 0.85, "ssWW Upgrade test RGS")
    t.SetTextSize(0.045)
    t.SetTextFont(42)
    t.SetNDC()
    t.Draw("same")
    SetOwnership(t, 0)    

    # Make the histogram legend    
    hs_d = TH1D('hs_d%s' % postfix, '', 4,0,4)
    hs_d.SetMarkerStyle(20)
    hs_d.SetMarkerColor(kMagenta+1)
    hs_d.SetMarkerSize(0.8)
    SetOwnership(hs_d, 0)
    
    hb_d = TH1D('hb_d%s' % postfix, '', 4,0,4)
    hb_d.SetMarkerStyle(20)    
    hb_d.SetMarkerColor(kAzure+1)
    hb_d.SetMarkerSize(0.8)    
    SetOwnership(hb_d, 0)
    
    l = TLegend(lgoffset2, 0.67, 0.90, 0.82)
    l.SetBorderSize(0)
    l.SetFillStyle(0000)
    l.SetTextSize(0.045)
    l.SetTextFont(42)
    l.AddEntry(hs_d, stitle, 'p')
    l.AddEntry(hb_d, btitle, 'p')
    l.Draw("same")
    SetOwnership(l, 0)

# ------------------------------------------------------------------------
def signalSignificanceErr(s, b, b_err):
    B0 = 1/2.*(b - b_err**2 + sqrt( (b - b_err**2)**2 + 4*(s + b)*b_err**2))
    Z = 0.0
    if b == 0:
        Z = 0.0
    else:
        Z = sqrt(2*((s+b)*log((s+b)/B0) + B0 - s - b) + (b-B0)**2/b_err**2)
    #print "s: %f, b: %f, b_err: %f" %(s,b,b_err)
    #print "oldZ: %f\tnewZ: %f" %(signalSignificance(s,b),Z)
    return Z

# ------------------------------------------------------------------------
def printFullYieldsAndErrors(dictionary):
    channels = ["Combined channels", "mm channel", "ee channel", "me channel", "em channel"]
    for i,channel in enumerate(channels):
        print "--",channel,"--"
        print "   run      events       stat        sys"
        stat = sqrt(dictionary[999999][i][1])
        syst = sqrt(abs(dictionary[999999][i][2]))
        print "%i\t%10.2f %10.2f %10.2f" % (999999, dictionary[999999][i][0],stat,syst)
        for key,value in sorted(dictionary.items()):
            if key == 999999: continue
            stat = sqrt(dictionary[key][i][1])
            syst = sqrt(abs(dictionary[key][i][2]))
            print "%i\t%10.2f %10.2f %10.2f" % (key, dictionary[key][i][0],stat,syst)
        
