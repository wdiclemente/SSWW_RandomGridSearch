import settings

Lumi     = 3000           # 1/fb
dummy    = 100000.0

print "scales.py: doPolar = ",settings.doPolar
print "scales.py: doLoose = ",settings.doLoose

scaleDict = {}

# all cross sections in fb
# format: sample = [ cross_section, sum_weight, filter_efficiency, kfactor ]

# local samples (signal)
WWEWK      = [17.74222134, 3.485460e+05]
WWEWKscale = WWEWK[0]/WWEWK[1] * Lumi # fb 
if not settings.doPolar:
    scaleDict[999999] = WWEWKscale

WWQCD      = [13.90280947, 6.270000e+05]
WWQCDscale = WWQCD[0]/WWQCD[1] * Lumi # fb
scaleDict[123456] = WWQCDscale

# polarization samples
WWLL      = [16.94, 2880000]
WWLLscale = WWLL[0]/WWLL[1] * Lumi # fb 
WWTX      = [16.94, 2880000]
WWTXscale = WWTX[0]/WWTX[1] * Lumi # fb 
if settings.doPolar:
    scaleDict[999999] = WWLLscale
    scaleDict[990031] = WWTXscale

# local sample (wz diboson 363719)
#WZEWK      = [4966.8, 1.502408e+05]
#WZEWKscale = WZEWK[0]/WZEWK[1] * Lumi # fb
#scaleDict[363719] = WZEWKscale

# grid diboson samples
diboson364284      = [53.155, 3462295.75, 1.0]
diboson364284scale = diboson364284[0]/diboson364284[1] * Lumi
scaleDict[364284]  = diboson364284scale

diboson364250      = [1363.900, 412080.03125, 1.0]
diboson364250scale = diboson364250[0]/diboson364250[1] * Lumi
scaleDict[364250]  = diboson364250scale

diboson364254      = [13816.0, 333811.65625, 1.0]
diboson364254scale = diboson364254[0]/diboson364254[1] * Lumi
scaleDict[364254]  = diboson364254scale

diboson364255      = [3634.4, 286894.40625, 1.0]
diboson364255scale = diboson364255[0]/diboson364255[1] * Lumi
scaleDict[364255]  = diboson364255scale

diboson363718      = [4351.2, 26914814.0, 1.0]
diboson363718scale = diboson363718[0]/diboson363718[1] * Lumi
scaleDict[363718]  = diboson363718scale

diboson363719      = [4966.8, 9182654464.0]
diboson363719scale = diboson363719[0]/diboson363719[1] * Lumi # fb
scaleDict[363719]  = diboson363719scale

# grid triboson samples
triboson364242      = [4.246, 2281.84399414, 1.0]
triboson364242scale = triboson364242[0]/triboson364242[1] * Lumi
scaleDict[364242] = triboson364242scale

triboson364243      = [2.055, 698.376525879, 1.0]
triboson364243scale = triboson364243[0]/triboson364243[1] * Lumi
scaleDict[364243] = triboson364243scale

triboson364244      = [4.101, 1381.51013184, 1.0]
triboson364244scale = triboson364244[0]/triboson364244[1] * Lumi
scaleDict[364244] = triboson364244scale

triboson364245      = [0.217, 221.041854858, 1.0]
triboson364245scale = triboson364245[0]/triboson364245[1] * Lumi
scaleDict[364245] = triboson364245scale

triboson364246      = [1.919, 1960.77514648, .44581]
triboson364246scale = triboson364246[0]*triboson364246[2]/triboson364246[1] * Lumi
scaleDict[364246] = triboson364246scale

triboson364336      = [10.847, 7888.02832031, .46163]
triboson364336scale = triboson364336[0]*triboson364336[2]/triboson364336[1] * Lumi
scaleDict[364336] = triboson364336scale

triboson364337      = [6.158, 4680.50439453, .4551]
triboson364337scale = triboson364337[0]*triboson364337[2]/triboson364337[1] * Lumi
scaleDict[364337] = triboson364337scale

triboson364338      = [49.463, 10805.3916016, .32155]
triboson364338scale = triboson364338[0]*triboson364338[2]/triboson364338[1] * Lumi
scaleDict[364338] = triboson364338scale

triboson364339      = [23.395, 3590.63842773, .32049]
triboson364339scale = triboson364339[0]*triboson364339[2]/triboson364339[1] * Lumi
scaleDict[364339] = triboson364339scale

triboson363507      = [19.649, 24848.5585938, .43805]
triboson363507scale = triboson363507[0]*triboson363507[2]/triboson363507[1] * Lumi
scaleDict[363507] = triboson363507scale

triboson363508      = [0.449, 1722.93615723, 1.0]
triboson363508scale = triboson363508[0]/triboson363508[1] * Lumi
scaleDict[363508] = triboson363508scale

triboson363509      = [13.572, 51968.0742188, .22139]
triboson363509scale = triboson363509[0]*triboson363509[2]/triboson363509[1] * Lumi
scaleDict[363509] = triboson363509scale

# grid ttX samples
if settings.doLoose:
    ttx410155      = [631.780, 1171995.0, 1.0] # truth1pp loose
elif settings.do20GeV:
    ttx410155      = [631.780, 1576383.0, 1.0]
else:
    ttx410155      = [631.780, 1548122.125, 1.0] # truth1pp tight
ttx410155scale = ttx410155[0]/ttx410155[1] * Lumi
scaleDict[410155] = ttx410155scale

if settings.doLoose:
    ttx410218      = [44.382, 27079.7109375, 1.0] # truth1pp loose
elif settings.do20GeV:
    ttx410218      = [44.382, 35020.8515625, 1.0]
else:
    ttx410218      = [44.382, 39294.3203125, 1.0] # truth1pp tight
ttx410218scale = ttx410218[0]/ttx410218[1] * Lumi
scaleDict[410218] = ttx410218scale

if settings.doLoose:
    ttx410219      = [44.391, 21745.90625, 1.0] # truth1pp loose
elif settings.do20GeV:
    ttx410219      = [44.391, 36137.734375, 1.0]
else:
    ttx410219      = [44.391, 39732.140625, 1.0] # truth1pp tight
ttx410219scale = ttx410219[0]/ttx410219[1] * Lumi
scaleDict[410219] = ttx410219scale

if settings.doLoose:
    ttx410220      = [43.970, 25910.5957031, 1.0] # truth1pp loose
elif settings.do20GeV:
    ttx410220      = [43.970, 33608.2929688, 1.0]
else:
    ttx410220      = [43.970, 38254.2109375, 1.0] # truth1pp tight
ttx410220scale = ttx410220[0]/ttx410220[1] * Lumi
scaleDict[410220] = ttx410220scale

# grid charge flip/fakes: single top
if settings.doLoose:
    chfake410642      = [41915.0, 77535968.0, 1.0, 3.6922] # truth1pp loose
elif settings.do20GeV:
    chfake410642      = [41915.0, 102195248.0, 1.0, 3.6922]
else:
    chfake410642      = [41915.0, 104354120.0, 1.0, 3.6922] # truth1pp tight
chfake410642scale = chfake410642[0]*chfake410642[3]/chfake410642[1] * Lumi
scaleDict[410642] = chfake410642scale

if settings.doLoose:
    chfake410643      = [25544.0, 47139332.0, 1.0, 3.6517] # truth1pp loose
elif settings.do20GeV:
    chfake410643      = [25544.0, 62263868.0, 1.0, 3.6517]
else:
    chfake410643      = [25544.0, 63543376.0, 1.0, 3.6517] # truth1pp tight
chfake410643scale = chfake410643[0]*chfake410643[3]/chfake410643[1] * Lumi
scaleDict[410643] = chfake410643scale

if settings.doLoose:
    chfake410644      = [2222.6,  3951885.25, 1.0, 3.1399] # truth1pp loose
elif settings.do20GeV:
    chfake410644      = [2222.6,  5272512.5, 1.0, 3.1399]
else:
    chfake410644      = [2222.6, 5497038.0, 1.0, 3.1399] # truth1pp tight
chfake410644scale = chfake410644[0]*chfake410644[3]/chfake410644[1] * Lumi
scaleDict[410644] = chfake410644scale

if settings.doLoose:
    chfake410645      = [1407.7, 2533252.5, 1.0, 3.1392] # truth1pp loose
elif settings.do20GeV:
    chfake410645      = [1407.7, 3298587.0, 1.0, 3.1392]
else:
    chfake410645      = [1407.7, 3481784.25, 1.0, 3.1392] # truth1pp tight
chfake410645scale = chfake410645[0]*chfake410645[3]/chfake410645[1] * Lumi
scaleDict[410645] = chfake410645scale

# grid charge flip/fakes: ttbar
if settings.doLoose:
    chfake410501      = [863860.0, 12695142400.0, .54383, 1.0] # truth1pp loose
elif settings.do20GeV:
    chfake410501      = [863860.0, 16773300224.0, .54383, 1.0]
else:
    chfake410501      = [863860.0, 17153086464.0, .54383, 1.0] # truth1pp tight
chfake410501scale = chfake410501[0]*chfake410501[2]*chfake410501[3]/chfake410501[1] * Lumi
scaleDict[410501] = chfake410501scale

chfake410000      = [824510.0, 298200032.0, .54383, 1.0] # old ttbar sample for cross check
chfake410000scale = chfake410000[0]*chfake410000[2]*chfake410000[3]/chfake410000[1] * Lumi
scaleDict[410000] = chfake410000scale

# grid Z+jets
zjets147806       = [2057.0e3, 5000000.0, 1.0] 
zjets147806scale  = zjets147806[0]/zjets147806[1] * Lumi
scaleDict[147806] = zjets147806scale

zjets147807       = [2058.0e3, 400000.0, 1.0]
zjets147807scale  = zjets147807[0]/zjets147807[1] * Lumi
scaleDict[147807] = zjets147807scale

#w+jets samples
wjetfile = open("../data/xsec_wjets.txt",'r')
for line in wjetfile:
    if line.startswith('#'): continue
    line = line.split()
    if len(line) < 6: continue
    run  = int(line[0])
    xsec = float(line[1])
    kfac = float(line[2])
    feff = float(line[3])
    sumw = float(line[5])
    scaleDict[run] = xsec*kfac*feff/sumw * Lumi


#print "Scale factors for samples: "
#print "WWEWK signal:",WWEWKscale
#for key,value in sorted(scaleDict.items()):
#    print key,":",value
