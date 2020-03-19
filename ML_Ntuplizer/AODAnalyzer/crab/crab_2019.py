
from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = False
config.General.workArea = 'DoubleMuon2018D_Prompt-v2'
config.General.requestName = ''

config.section_('JobType')
config.JobType.psetName = '/afs/cern.ch/work/f/fiori/2019ML4DC/CMSSW_10_6_0/src/AODAnalyzer/AODAnalyzer/test/AODAnalyzer_cfg.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['AODTree.root']
#config.JobType.maxJobRuntimeMin = 2750 #45 h


config.section_('Data')
config.Data.inputDataset = '/DoubleMuon/Run2018D-PromptReco-v2/AOD'
config.Data.unitsPerJob = 500 #without '' since it must be an int
config.Data.splitting = 'LumiBased'
config.Data.publication = False
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/user/fiori/MLData_2019/' #/dijet/Dijet13TeV/deguio/ML-DQM/'
config.Data.ignoreLocality = False

config.section_('User')

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist = ['T2_DE_RWTH']


#/ZeroBias/Run2018D-PromptReco-v2/AOD ok  the v1 is not relevant, not a single run is in Golden JSON
#/ZeroBias/Run2018C-PromptReco-v3/AOD ok
#/ZeroBias/Run2018C-PromptReco-v2/AOD ok
#/ZeroBias/Run2018C-PromptReco-v1/AOD ok
#/ZeroBias/Run2018B-PromptReco-v2/AOD ok
#/ZeroBias/Run2018A-PromptReco-v2/AOD ok
#/ZeroBias/Run2018A-PromptReco-v1/AOD ok

