Some tools to read data straight from DQMIO files.

The code needs PyROOT to read ROOT data. It works with Python3 and Python2 
(limited), and a CMSSW environment can be used to have all tools available.

This code can be used on SWAN, using data from EOS, or on Minsky using data 
copied there. Alternatively, DQMIO data could be read straight from the GRID,
but we have not really explored that option yet.

Running things on Minsky is a lot faster.

You should be able to use command like this:
```
NAME=mschneid; PORT=$(( 10000 + ( RANDOM % 10000 ) )); ssh -o ProxyCommand="ssh -W %h:%p $NAME@ibmminsky-head" $NAME@ibmminsky-2 -L $PORT:localhost:$PORT /nfs/public/mschneid/cmssw-jupyter.sh $PORT
```

to set up a notebook server on one of the compute nodes and build a ssh tunnel there. This is for inside CERN, outside it needs another layer of tunneling.

The script used here (`/nfs/public/mschneid/cmssw-jupyter.sh`) looks like this:
```
#!/bin/bash
PORT=$1
source /cvmfs/cms.cern.ch/cmsset_default.sh
SCRAM_ARCH=slc7_ppc64le_gcc820
# cmssw env created with `cmsrel`; needs to be updated every ~2 weeks.
cd /nfs/public/mschneid/CMSSW_11_1_X_2020-02-18-2300
eval `scramv1 runtime -sh`
mkdir -p /nfs/public/$USER
cd /nfs/public/$USER
jupyter-notebook --port $PORT
```

We don't have Python3 IBs for powerpc, so on Minsky you need to use Python2 for now.


