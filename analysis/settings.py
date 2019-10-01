def init():
    global doPolar
    doPolar = True

    # Set useCS = True if you want to run everything optimizing on the
    #   polarization samples but use the combined signal sample for the 
    #   event yields/plots
    global useCombinedSig
    useCS = True 
    useCombinedSig = (doPolar and useCS)

    global do13TeV
    do13TeV = False
    
    global doLoose
    doLoose = False

    global do20GeV
    do20GeV = False

    global doZwithErr
    doZwithErr = False
