import sqlite3
import sys
import pandas as pd
import json


run=True
count=0
spill=100000

while (run):
    con = sqlite3.connect("SQLiteTables2017/ZeroBias__Run2017B-09Aug2019_UL2017-v1__1D.sqlite")	
    #query="SELECT metype,fromrun,fromlumi,value FROM monitorelements LIMIT 100000 OFFSET "+ str(count*100000)
    query="SELECT metype,fromrun,fromlumi,value FROM monitorelements WHERE (rowid >=" + str(count*spill+1) + " AND rowid <" + str((count+1)*spill+1) + ")"
    print(query)
    
    df=pd.read_sql_query(query, con)
        
    if(df.empty):
        print('Empty DF, Finish!') 
        run=False
        break
    
    df_final= df[['fromrun','fromlumi','metype']]

    df1 = pd.DataFrame.from_dict([x for x in df['value'].apply(json.loads)])
    dfx = pd.DataFrame.from_dict([x for x in df1['fXaxis']])
    dfy = pd.DataFrame.from_dict([x for x in df1['fYaxis']])

    df_final[['hname','histo', 'entries']]=df1[['fName','fArray','fEntries']].copy() 

    df_final[['Xmax','Xmin','Xbins']]=dfx[['fXmax','fXmin','fNbins']].copy()
    df_final[['Ymax','Ymin','Ybins']]=dfy[['fXmax','fXmin','fNbins']].copy()

    df_final.index=pd.MultiIndex.from_frame(df_final[['fromrun','fromlumi','hname']])
    count=count+1 

    fname="ZeroBias_2017B_DataFrame_1D_" + str(count) + ".csv"

    print(fname)
    
    df_final.to_csv(fname)

    print('DONE!')
