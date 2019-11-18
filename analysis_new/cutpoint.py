class CutPoint:

    def __init__(self,event):
        self.index = int(event['cutpointindex'])
        self.mll   = event['mll']
        self.mjj   = event['mjj']
        self.l0pt  = event['leptons_selected_l0_pt']
        self.l1pt  = event['leptons_selected_l1_pt']
        self.j0pt  = event['jets_selected_j0_pt']
        self.j1pt  = event['jets_selected_j1_pt']
        self.cent  = event['lepjet_centrality']

        self.values = [self.index,
                       self.mll,
                       self.mjj,
                       self.l0pt,
                       self.l1pt,
                       self.j0pt,
                       self.j1pt,
                       self.cent]
        
    lookup = { 'index'      : 0,
               'mll'        : 1,
               'mjj'        : 2,
               'l0pt'       : 3,
               'l1pt'       : 4,
               'j0pt'       : 5,
               'j1pt'       : 6,
               'centrality' : 7 }
        
    def get_value(self,name):
        if name in self.lookup:
            return self.values[self.lookup[name]]
        else:
            print "Requested variable {} not valid!".format(name)

    def to_string(self):
        out = "---- Cut point {} ----\n".format(self.index)
        for k,v in self.lookup.iteritems():
            if v == 0: continue
            out += "\t{} = {:.2f}\n".format(k,self.values[v])
        return out
