def init():
    global doPolar
    doPolar = False

    # Set useCS = True if you want to run everything optimizing on the
    #   polarization samples but use the combined signal sample for the 
    #   event yields/plots
    global useCombinedSig
    useCS = False
    useCombinedSig = (doPolar and useCS)
    
    global doLoose
    doLoose = False

    global do20GeV
    do20GeV = True

    global doZwithErr
    doZwithErr = False
