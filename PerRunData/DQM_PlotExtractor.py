#!/usr/bin/env python
from __future__ import print_function
from ROOT import gDirectory, TDirectory,TFile, TH1, TH1F, TIter, TKey

import sys
import numpy
import uproot
import argparse
import pandas as pand

parser = argparse.ArgumentParser(description="Display in text format a single ME out of a DQM (legacy or DQMIO) file. " + " there is more than on copy, of one ME, all are shown.")
parser.add_argument('filename', help='Name of local root file. For remote files, use edmCopyUtil first: `edmCopyUtil root://cms-xrd-global.cern.ch/<FILEPATH> .`')
args = parser.parse_args()

f = uproot.open(args.filename)
things = f.keys()

runnum= args.filename[args.filename.find('__')-6:args.filename.find('__')]
#print(runnum)

pd= args.filename[args.filename.find('__')+len('__'):args.filename.find('__',args.filename.find('__')+1)]
#print(pd)

plotList=[]
print("Filling List ...")
if 'DQMData;1' in things:
    basedir = f['DQMData']
    print(basedir.keys())
    for run in basedir.keys():
        if not run.startswith("Run "): continue
        rundir = basedir[run]
        for lumi in rundir.keys():            
            if (lumi.find("HLT")>=0 or lumi.find("AlCaReco")>=0 or lumi.find("Debug")>=0 or lumi.find("Alca")>=0 or lumi.find("EventInfo")>=0 or lumi.find("Castor")>=0 or lumi.find("FED")>=0 or lumi.find("DQM")>=0 or lumi.find("MessageLogger")>=0 or lumi.find("Info")>=0 or lumi.find("EcalCalibration")>=0 or lumi.find("EcalPreshower")>=0 or lumi.find("RecoTauV")>=0 or lumi.find("DT")>=0 or lumi.find("Physics")>=0): continue
            plotdir=rundir[lumi]
            for plot in plotdir.allkeys():
                if (str(plot).startswith("<") or str(plot).find("EventInfo")>=0): continue
                fullpath="DQMData/"+ run[:-2] + "/" + lumi[:-2] + "/" + plot
                plotList.append(fullpath)
                
print("Done! ... extracting values now")

#loop on the plotList and extract interesting values "PD, run, fullpath, plot title, mean, rms, skewness and Kurtosis" uproot was failing in opening some of the plots
df=pand.DataFrame(columns=['run','pd','path','title','entries','mean','rms','skewness', 'kurtosis'])

f = TFile.Open(args.filename,"r")
count=0

for entry in plotList:
        obj = f.Get(entry)
        if not obj: continue
        if not obj.InheritsFrom('TH1'): continue
        dim=obj.GetDimension()
        if (dim==1):
                myrow={'run':runnum,'pd':pd, 'path': entry, 'title':obj.GetTitle(), 'entries':obj.GetEntries(), 'mean':obj.GetMean(), 'rms':obj.GetRMS(), 'skewness':obj.GetSkewness(), 'kurtosis':obj.GetKurtosis()}
                df=df.append(myrow, ignore_index=True)
                #print(df.shape)
        elif (dim==2):
                myrow={'run':runnum,'pd':pd, 'path': entry, 'title':obj.GetTitle(), 'entries':obj.GetEntries(), 'mean':obj.GetMean(), 'rms':obj.GetRMS(), 'skewness':obj.GetMean(2), 'kurtosis':obj.GetRMS(2)}
                df=df.append(myrow, ignore_index=True)

f.Close()

outname=pd+"_"+runnum+"_UL2017.csv"
df.to_csv(outname)
print(df.head())
print(args.filename)
