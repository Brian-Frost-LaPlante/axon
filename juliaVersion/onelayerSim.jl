λs = 0.065:0.001:0.265

#NUM_SPIKES_EE_i,        ISI_EE_i        = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, earlystop = true);
#NUM_SPIKES_EE_dam_i,    ISI_EE_dam_i    = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, earlystop = true);
#NUM_SPIKES_EE_c,        ISI_EE_c        = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, earlystop = true);
#NUM_SPIKES_EE_dam_c,    ISI_EE_dam_c    = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, earlystop = true);
#
#println("EE done")
#
#NUM_SPIKES_IE_i,        ISI_IE_i        = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, earlystop = true);
#NUM_SPIKES_IE_dam_i,    ISI_IE_dam_i    = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, earlystop = true);
#NUM_SPIKES_IE_c,        ISI_IE_c        = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, earlystop = true);
#NUM_SPIKES_IE_dam_c,    ISI_IE_dam_c    = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, earlystop = true);
#
#println("IE done")
#
#NUM_SPIKES_EE_FB_i,     ISI_EE_FB_i         = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EE_FB_dam_i, ISI_EE_FB_dam_i     = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_EE_FB_c,     ISI_EE_FB_c         = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EE_FB_dam_c, ISI_EE_FB_dam_c     = netSim(λs = λs, celltypes = [0,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);
#
#println("EE FB done")
#
#NUM_SPIKES_EI_FB_i,     ISI_EI_FB_i         = netSim(λs = λs, celltypes = [0,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EI_FB_dam_i, ISI_EI_FB_dam_i     = netSim(λs = λs, celltypes = [0,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_EI_FB_c,     ISI_EI_FB_c         = netSim(λs = λs, celltypes = [0,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EI_FB_dam_c, ISI_EI_FB_dam_c     = netSim(λs = λs, celltypes = [0,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);
#
#println("EI FB done")
#
#NUM_SPIKES_II_FB_i,     ISI_II_FB_i         = netSim(λs = λs, celltypes = [0,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_II_FB_dam_i, ISI_II_FB_dam_i     = netSim(λs = λs, celltypes = [0,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_II_FB_c,     ISI_II_FB_c         = netSim(λs = λs, celltypes = [0,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_II_FB_dam_c, ISI_II_FB_dam_c     = netSim(λs = λs, celltypes = [0,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);
#
#println("II FB done")
#
#NUM_SPIKES_IE_FB_i,     ISI_IE_FB_i         = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_IE_FB_dam_i, ISI_IE_FB_dam_i     = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_IE_FB_c,     ISI_IE_FB_c         = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_IE_FB_dam_c, ISI_IE_FB_dam_c     = netSim(λs = λs, celltypes = [0,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);
#
#println("IE FB done")
#
#NUM_SPIKES_EEE_i,       ISI_EEE_i           = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EEE_dam_i,   ISI_EEE_dam_i       = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
#NUM_SPIKES_EEE_c,       ISI_EEE_c           = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EEE_dam_c,   ISI_EEE_dam_c       = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);
#
#NUM_SPIKES_EEE_FB_i,     ISI_EEE_FB_i       = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EEE_FB_dam_i, ISI_EEE_FB_dam_i   = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_EEE_FB_c,     ISI_EEE_FB_c       = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EEE_FB_dam_c, ISI_EEE_FB_dam_c   = netSim(λs = λs, celltypes = [1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);

#println("EEE done")

#NUM_SPIKES_EEI_i,       ISI_EEI_i           = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EEI_dam_i,   ISI_EEI_dam_i       = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
#NUM_SPIKES_EEI_c,       ISI_EEI_c           = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EEI_dam_c,   ISI_EEI_dam_c       = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);
#
#NUM_SPIKES_EEI_FB_i,     ISI_EEI_FB_i       = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EEI_FB_dam_i, ISI_EEI_FB_dam_i   = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_EEI_FB_c,     ISI_EEI_FB_c       = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EEI_FB_dam_c, ISI_EEI_FB_dam_c   = netSim(λs = λs, celltypes = [1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);

#println("EEI done")
#
#NUM_SPIKES_EIE_i,       ISI_EIE_i           = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EIE_dam_i,   ISI_EIE_dam_i       = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
#NUM_SPIKES_EIE_c,       ISI_EIE_c           = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EIE_dam_c,   ISI_EIE_dam_c       = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);

#NUM_SPIKES_EIE_FB_i,     ISI_EIE_FB_i       = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EIE_FB_dam_i, ISI_EIE_FB_dam_i   = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_EIE_FB_c,     ISI_EIE_FB_c       = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EIE_FB_dam_c, ISI_EIE_FB_dam_c   = netSim(λs = λs, celltypes = [1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);
#
#println("EIE done")
#
#NUM_SPIKES_EII_i,       ISI_EII_i           = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EII_dam_i,   ISI_EII_dam_i       = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
#NUM_SPIKES_EII_c,       ISI_EII_c           = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
#NUM_SPIKES_EII_dam_c,   ISI_EII_dam_c       = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);
#
#NUM_SPIKES_EII_FB_i,     ISI_EII_FB_i       = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EII_FB_dam_i, ISI_EII_FB_dam_i   = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
#NUM_SPIKES_EII_FB_c,     ISI_EII_FB_c       = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
#NUM_SPIKES_EII_FB_dam_c, ISI_EII_FB_dam_c   = netSim(λs = λs, celltypes = [1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);
#
#println("EII done")
#
NUM_SPIKES_IEE_i,       ISI_IEE_i           = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_IEE_dam_i,   ISI_IEE_dam_i       = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
NUM_SPIKES_IEE_c,       ISI_IEE_c           = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_IEE_dam_c,   ISI_IEE_dam_c       = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);

NUM_SPIKES_IEE_FB_i,     ISI_IEE_FB_i       = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_IEE_FB_dam_i, ISI_IEE_FB_dam_i   = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
NUM_SPIKES_IEE_FB_c,     ISI_IEE_FB_c       = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_IEE_FB_dam_c, ISI_IEE_FB_dam_c   = netSim(λs = λs, celltypes = [-1,1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);

println("IEE done")

NUM_SPIKES_IEI_i,       ISI_IEI_i           = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_IEI_dam_i,   ISI_IEI_dam_i       = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
NUM_SPIKES_IEI_c,       ISI_IEI_c           = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_IEI_dam_c,   ISI_IEI_dam_c       = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);

NUM_SPIKES_IEI_FB_i,     ISI_IEI_FB_i       = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_IEI_FB_dam_i, ISI_IEI_FB_dam_i   = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
NUM_SPIKES_IEI_FB_c,     ISI_IEI_FB_c       = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_IEI_FB_dam_c, ISI_IEI_FB_dam_c   = netSim(λs = λs, celltypes = [-1,1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);

println("IEI done")

NUM_SPIKES_IIE_i,       ISI_IIE_i           = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_IIE_dam_i,   ISI_IIE_dam_i       = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
NUM_SPIKES_IIE_c,       ISI_IIE_c           = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_IIE_dam_c,   ISI_IIE_dam_c       = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);

NUM_SPIKES_IIE_FB_i,     ISI_IIE_FB_i       = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_IIE_FB_dam_i, ISI_IIE_FB_dam_i   = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
NUM_SPIKES_IIE_FB_c,     ISI_IIE_FB_c       = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_IIE_FB_dam_c, ISI_IIE_FB_dam_c   = netSim(λs = λs, celltypes = [-1,-1,1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);

println("IIE done")

NUM_SPIKES_III_i,       ISI_III_i           = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_III_dam_i,   ISI_III_dam_i       = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = false, earlystop = true);
NUM_SPIKES_III_c,       ISI_III_c           = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = false, earlystop = true);
NUM_SPIKES_III_dam_c,   ISI_III_dam_c       = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = false, earlystop = true);

NUM_SPIKES_III_FB_i,     ISI_III_FB_i       = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_III_FB_dam_i, ISI_III_FB_dam_i   = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = false, damaged = true, fb = true, earlystop = true);
NUM_SPIKES_III_FB_c,     ISI_III_FB_c       = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = false, fb = true, earlystop = true);
NUM_SPIKES_III_FB_dam_c, ISI_III_FB_dam_c   = netSim(λs = λs, celltypes = [-1,-1,-1], NUM_REALIZATIONS = 10000, coherent = true, damaged = true, fb = true, earlystop = true);

println("Job's Done!")
