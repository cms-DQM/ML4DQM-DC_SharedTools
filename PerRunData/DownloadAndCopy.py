#DQM_V0001_R000302492__HTMHT__Run2017D-09Aug2019_UL2017-v1__DQMIO.root

import sys
import os

start="__"
end="__Run"
count=0
#filename=$1

with open("listZB2018Clean.txt", 'r') as f:
    for line in f:
        #create GUI name
        s=line.rstrip()
        pd= s[s.find(start)+len(start):s.rfind(end)]

        dir= s[s.find("_R")+2:s.find("_R")+9]
        dir=dir+"xx"

        guiPath="https://cmsweb.cern.ch/dqm/offline/data/browse/ROOT/OfflineData/Run2018/"+pd+"/"+dir+"/"+s
        eosPath="/eos/cms/store/group/comm_dqm/DQMGUI_data/Run2018/"+pd+"/R"+dir+"/"+s

        comm="curl -E /tmp/x509up_u23273 -o " + eosPath + " " + guiPath
        os.system(comm)
        count +=1
        print("AAAAAAAAAAAAAAAAAAAA")
        print(s)
        print(count)
        
        
