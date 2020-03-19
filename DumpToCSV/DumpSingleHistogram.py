import pandas as pd
import numpy as np
from ast import literal_eval
import glob

all_files = glob.glob("DF2017*_1D_Complete/ZeroBias_2017*_DataFrame_1D*.csv")
dflist=[]

for filename in all_files:
    print('Adding file %s',filename)
    dfi = pd.read_csv(filename, index_col=None)
#select your histogram here, metype == 6 for 2D histograms and < 6 for 1D
    dfclean = dfi.loc[(dfi['metype'] <= 5) & (dfi['hname'] == 'chargeInner_PXLayer_4'),['fromrun','fromlumi','hname','histo','entries','Xmax','Xmin','Xbins','metype']]
    dflist.append(dfclean)

df = pd.concat(dflist, axis=0, ignore_index=True)


df_tmp= df[['fromrun','fromlumi','hname','entries','Xmax','Xmin','Xbins','metype']].copy()

df_tmp['histo']=df['histo'].apply(literal_eval)#.apply(lambda x: x[1:-1]) #eval the string and cut the first and last value which correspond to Underflow and Overflow

print(df_tmp.head())

fname="ZeroBias_2017UL_DataFrame_ChargeInnerLayer4.txt"
df_tmp.to_csv(fname)
