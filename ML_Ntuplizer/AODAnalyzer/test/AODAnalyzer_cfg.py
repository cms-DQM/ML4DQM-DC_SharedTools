import FWCore.ParameterSet.Config as cms

process = cms.Process("MLANALYSIS")

process.source = cms.Source("PoolSource",
                    fileNames = cms.untracked.vstring(
        "file:/afs/cern.ch/work/f/fiori/testAOD.root"
        ),
                            secondaryFileNames = cms.untracked.vstring(),
#                   lumisToProcess = cms.untracked.VLuminosityBlockRange('258158:1-258158:1786'),

)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '103X_dataRun2_v6'

process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.Geometry.GeometryRecoDB_cff')

process.MyAnalysis =cms.EDAnalyzer("AODAnalyzer",

                       gTrackTag               = cms.untracked.InputTag("generalTracks"),
                       globTrackTag            = cms.untracked.InputTag("globalMuons"),
                       PFJetTag                = cms.untracked.InputTag("ak4PFJets"), #ak4PFJets
                       PFJet4CHSTag            = cms.untracked.InputTag("ak4PFJetsCHS"),
                       PFJet8CHSTag            = cms.untracked.InputTag("ak8PFJetsCHS"),
                       PFJetEITag              = cms.untracked.InputTag("pfJetsEI"),
                       PFJet8CHSSoftDropTag    = cms.untracked.InputTag("ak8PFJetsCHSSoftDrop","SubJets"),
                       PFJetTopCHSTag          = cms.untracked.InputTag("cmsTopTagPFJetsCHS","caTopSubJets"),

                       PFChMETTag              = cms.untracked.InputTag("pfChMet"),
                       PFMETTag                = cms.untracked.InputTag("pfMet"),

                       CaloJetTag              = cms.untracked.InputTag("ak4CaloJets"),

                       CaloMETTag              = cms.untracked.InputTag("caloMet"),  #calometTag
                       CaloMETBETag            = cms.untracked.InputTag("caloMetBE"),
                       CaloMETBEFOTag          = cms.untracked.InputTag("caloMetBEFO"),
                       CaloMETMTag             = cms.untracked.InputTag("caloMetM"),

                       vtx                     = cms.untracked.InputTag("offlinePrimaryVertices"),
                       bits                    = cms.untracked.InputTag("TriggerResults","","HLT"),  #should be fine
                       #prescales               = cms.untracked.InputTag("patTrigger"), # TriggerResults//PROBABLY get from https://github.com/cms-sw/cmssw/blob/master/DataFormats/PatCandidates/interface/TriggerEvent.h  ... ask about how
                       # triggerResultsTag       = cms.untracked.InputTag("TriggerResults","","HLT"),

                       SuperClusterTag         = cms.untracked.InputTag("particleFlowEGamma"),
                       SuperClusterhfEMTag     = cms.untracked.InputTag("hfEMClusters"),
                       SuperCluster5x5Tag      = cms.untracked.InputTag("correctedMulti5x5SuperClustersWithPreshower"),

                       CaloClusterTag          = cms.untracked.InputTag("particleFlowEGamma","EBEEClusters"),  #ESClusters also possible instead of EBEEClusters
                       CaloCluster5x5Tag       = cms.untracked.InputTag("multi5x5SuperClusters","multi5x5EndcapBasicClusters"),    #CHANGING HEFM TO MULTI5X5  HFEM was empty!

                       PhotonTag               = cms.untracked.InputTag("photons"),
                       gedPhotonTag            = cms.untracked.InputTag("gedPhotons"),

                       MuonTag                 = cms.untracked.InputTag("muons"),
                       #MuonCosmTag             = cms.untracked.InputTag("muonsFromCosmics"),
                       #MuonCosmLegTag          = cms.untracked.InputTag("muonsFromCosmics1Leg"),

                       GsfElectronTag          = cms.untracked.InputTag("gedGsfElectrons"),
                       #GsfElectronUncleanedTag = cms.untracked.InputTag("uncleanedOnlyGsfElectrons"),

                       EBRecHitSourceTag       = cms.untracked.InputTag("reducedEcalRecHitsEB"),
                       EERecHitSourceTag       = cms.untracked.InputTag("reducedEcalRecHitsEE"),
                       ESRecHitSourceTag       = cms.untracked.InputTag("reducedEcalRecHitsES"),

                       HBHERecHitTag           = cms.untracked.InputTag("reducedHcalRecHits","hbhereco"),
                       HFRecHitTag             = cms.untracked.InputTag("reducedHcalRecHits","hfreco"),
                       HORecHitTag             = cms.untracked.InputTag("reducedHcalRecHits","horeco"),

                       PreshowerClusterXTag    = cms.untracked.InputTag("multi5x5SuperClustersWithPreshower","preshowerXClusters"),  
                       PreshowerClusterYTag    = cms.untracked.InputTag("multi5x5SuperClustersWithPreshower","preshowerYClusters"),
                       
                       # CastorTowerTag          = cms.untracked.InputTag("CastorTowerReco"),  #add LeafCandidate variables
        
                       # maxJetEta               = cms.untracked.double(5.0),   #is this ok? --REMOVE BOUNDARIES
                       # minJetPt                = cms.untracked.double(10.0),  #is this ok?

                       # maxSCEta                = cms.untracked.double(3.0),   # IS THIS OK?
                       # minSCEn                 = cms.untracked.double(8.0),  # IS THIS OK?
                       #lumifile etc were used in the previous version
                       #lumiFile                = cms.untracked.string(basePath+'run_ls_lumi_2016.txt'),
                       #subsystems              = cms.untracked.vstring(subsystemList),
                       #qualityFiles            = cms.untracked.vstring(fileList),
                       quantiles               = cms.untracked.vdouble(0.1,0.3,0.5,0.7,0.9)

                        )


process.mypath  = cms.Path(process.MyAnalysis)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("AODTree.root"),
                                   closeFileFast = cms.untracked.bool(False),
                                   )
 
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))
process.options =  cms.untracked.PSet(
                   #allowUnscheduled = cms.untracked.bool(True),
                   wantSummary = cms.untracked.bool(True),
                   #SkipEvent = cms.untracked.vstring('ProductNotFound'), #!! only for testing
                   )

process.MessageLogger = cms.Service("MessageLogger",
   destinations   = cms.untracked.vstring('cerr'),
   cerr           = cms.untracked.PSet(
       threshold      = cms.untracked.string('ERROR'),
   ),
    debugModules  = cms.untracked.vstring('*')
)
