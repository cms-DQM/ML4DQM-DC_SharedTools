#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Scalers/interface/LumiScalers.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSetNew.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "Geometry/HcalTowerAlgo/interface/HcalGeometry.h"

//PTComparator for sorting by pt
#include "CommonTools/Utils/interface/PtComparator.h"
#include "Validation/EventGenerator/interface/HepMCValidationHelper.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "DataFormats/Candidate/interface/LeafCandidate.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/JetCollection.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Provenance/interface/ParameterSetID.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/HLTGlobalStatus.h"

#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h" //added because of SuperCluster (collection)
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h" 
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"  
#include "DataFormats/METReco/interface/PFMETFwd.h" 

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETFwd.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"
#include "DataFormats/HcalRecHit/interface/HFRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "DataFormats/EgammaReco/interface/PreshowerCluster.h"
#include "DataFormats/EgammaReco/interface/PreshowerClusterFwd.h"

#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include <numeric>
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/Event.h"

#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include "TTree.h"
//#include "Python.h"

class AODAnalyzer : public edm::EDAnalyzer {
  
public:
  AODAnalyzer(const edm::ParameterSet& cfg);
  virtual ~AODAnalyzer();
  
  virtual void analyze (const edm::Event& event, const edm::EventSetup & eventSetup);
  virtual void beginJob();
  virtual void endJob();
  virtual void beginRun(const edm::Run & run,    const edm::EventSetup & eventSetup);
  virtual void endRun  (const edm::Run & run,    const edm::EventSetup & eventSetup) {};
  virtual void beginLuminosityBlock  (const edm::LuminosityBlock& lumi, const edm::EventSetup& eventSetup);
  virtual void endLuminosityBlock    (const edm::LuminosityBlock& lumi, const edm::EventSetup& eventSetup);
  
private:
  
  void fillPUandLumiEvt(float &, float&);
  
  template<typename jetCollection>
  void fillJets(const edm::Handle<jetCollection> &, std::string );

  template<typename PFJet4CHSCollection>
  void fill4CHSJets(const edm::Handle<PFJet4CHSCollection> &, std::string );

  template<typename TrackCollection>
  void fillgTracks(const edm::Handle<TrackCollection> &, std::string );

  template<typename TrackCollection>
  void fillglobTracks(const edm::Handle<TrackCollection> &, std::string );

  template<typename PFJet8CHSCollection>
  void fill8CHSJets(const edm::Handle<PFJet8CHSCollection> &, std::string );

  template<typename PFJetEICollection>
  void fillEIJets(const edm::Handle<PFJetEICollection> &, std::string );

  template<typename PFJet8CHSSoftDropCollection>
  void fill8CHSoftDropJets(const edm::Handle<PFJet8CHSSoftDropCollection> &, std::string );

  template<typename PFJetTopCHSCollection>
  void fillTopCHSJets(const edm::Handle<PFJetTopCHSCollection> &, std::string );

  template<typename PFChMETCollection>
  void fillPFChMets(const edm::Handle<PFChMETCollection> &);

  template<typename PFMETCollection>
  void fillPFMets(const edm::Handle<PFMETCollection> &);

  template<typename CaloJetCollection> 
  void fillCaloJets(const edm::Handle<CaloJetCollection> &);

  template<typename CaloMETCollection>
  void fillCaloMETs(const edm::Handle<CaloMETCollection> &);

  template<typename CaloMETBECollection>
  void fillCaloMETBEs(const edm::Handle<CaloMETBECollection> &);

  template<typename CaloMETBEFOCollection>
  void fillCaloMETBEFOs(const edm::Handle<CaloMETBEFOCollection> &);

  template<typename CaloMETMCollection>
  void fillCaloMETMs(const edm::Handle<CaloMETMCollection> &);

  template<typename SuperClusterCollection> 
  void fillSC(const edm::Handle<SuperClusterCollection> &); 

  template<typename SuperClusterhfEMCollection> 
  void fillSChfEM(const edm::Handle<SuperClusterhfEMCollection> &); 

  template<typename SuperCluster5x5Collection> 
  void fillSC5x5(const edm::Handle<SuperCluster5x5Collection> &); 

  template<typename CaloCluster5x5Collection>
  void fillCC5x5(const edm::Handle<CaloCluster5x5Collection> &); 

  template<typename CaloClusterCollection>
  void fillCC(const edm::Handle<CaloClusterCollection> &); 

  template<typename PhotonCollection>
  void fillPhotons(const edm::Handle<PhotonCollection> &);

  template<typename PhotongedCollection>
  void fillgedPhotons(const edm::Handle<PhotongedCollection> &);

  template<typename MuonCollection>
  void fillMuons(const edm::Handle<MuonCollection> &);

  template<typename GsfElectronCollection>
  void fillGsf(const edm::Handle<GsfElectronCollection> &);
  
  template<typename EBEcalRecHitCollection>
  void fillEBrecHit(const edm::Handle<EBEcalRecHitCollection> &);

  template<typename EEEcalRecHitCollection>
  void fillEErecHit(const edm::Handle<EEEcalRecHitCollection> &);
 
  template<typename ESEcalRecHitCollection>
  void fillESrecHit(const edm::Handle<ESEcalRecHitCollection> &);

  template<typename HBHERecHitCollection>
  void fillHBHErecHit(const edm::Handle<HBHERecHitCollection> &);

  template<typename HFRecHitCollection>
  void fillHFrecHit(const edm::Handle<HFRecHitCollection> &);

  template<typename PreshowerClusterCollection>
  void fillPreshowerCluster(const edm::Handle<PreshowerClusterCollection> &);

  template<typename PreshowerClusterCollectionY>
  void fillPreshowerClusterY(const edm::Handle<PreshowerClusterCollectionY> &);

  void initialize();
  template<typename T>

  void computeQuantiles(std::vector<T>*, std::vector<T>*, std::vector<double>, bool &); 
  template<typename T>

  void computeMeanAndRms(std::vector<T>*, std::vector<T>*);

  /// file service and tree
  edm::Service<TFileService> outfile_;
  HLTConfigProvider hltConfigProvider_;

  TTree* outTree_;
  int    runId_;
  int    lumiId_;
  float  lumi_;
  int    isSig_;

  //vtx position
  std::vector<float>* pVtxNtr_;
  std::vector<float>* pVtxChi2_;

  std::vector<float>* qpVtxNtr_;
  std::vector<float>* qpVtxChi2_;

  std::vector<float>* pVtxX_;
  std::vector<float>* pVtxY_;
  std::vector<float>* pVtxZ_;

  std::vector<float>* qpVtxX_;
  std::vector<float>* qpVtxY_;
  std::vector<float>* qpVtxZ_;

  //general Tracks variables
  std::vector<float>* gTkPt_;
  std::vector<float>* gTkEta_;
  std::vector<float>* gTkPhi_;
  std::vector<float>* gTkN_;
  std::vector<float>* gTkChi2_;
  std::vector<float>* gTkNHits_;
  std::vector<float>* gTkNLay_;

  std::vector<float>* qgTkPt_;
  std::vector<float>* qgTkEta_;
  std::vector<float>* qgTkPhi_;
  std::vector<float>* qgTkN_;
  std::vector<float>* qgTkChi2_;
  std::vector<float>* qgTkNHits_;
  std::vector<float>* qgTkNLay_;

 //global muons Tracks variables
  std::vector<float>* globTkPt_;
  std::vector<float>* globTkEta_;
  std::vector<float>* globTkPhi_;
  std::vector<float>* globTkN_;
  std::vector<float>* globTkChi2_;
  std::vector<float>* globTkNHits_;

  std::vector<float>* qglobTkPt_;
  std::vector<float>* qglobTkEta_;
  std::vector<float>* qglobTkPhi_;
  std::vector<float>* qglobTkN_;
  std::vector<float>* qglobTkChi2_;
  std::vector<float>* qglobTkNHits_;

  //lumi and pu per event
  std::vector<float>* PUEvt_;
  std::vector<float>* lumiEvt_;

  //PFJet variables
  std::vector<float>* PFJetN_;
  std::vector<float>* PFJetPt_;
  std::vector<float>* PFJetEta_;
  std::vector<float>* PFJetPhi_;

  //PF4CHS variables
  std::vector<float>* PFJet4CHSPt_;
  std::vector<float>* PFJet4CHSEta_;
  std::vector<float>* PFJet4CHSPhi_;

  //PF8CHS variables
  std::vector<float>* PFJet8CHSPt_;
  std::vector<float>* PFJet8CHSEta_;
  std::vector<float>* PFJet8CHSPhi_;

  //PFJetEI variables
  std::vector<float>* PFJetEIPt_;
  std::vector<float>* PFJetEIEta_;
  std::vector<float>* PFJetEIPhi_;

  //8CHSSoftDrop variables
  std::vector<float>* PFJet8CHSSDPt_;
  std::vector<float>* PFJet8CHSSDEta_;
  std::vector<float>* PFJet8CHSSDPhi_;

  //TopCHS variables
  std::vector<float>* PFJetTopCHSPt_;
  std::vector<float>* PFJetTopCHSEta_;
  std::vector<float>* PFJetTopCHSPhi_;

  //PFChMet variables (met has no Eta)
  std::vector<float>* PFChMetPt_;
  std::vector<float>* PFChMetPhi_;
  std::vector<float>* PFMetPt_;
  std::vector<float>* PFMetPhi_;
  std::vector<float>* nVtx_;

  //CaloJet variables
  std::vector<float>* CalJetN_;
  std::vector<float>* CalJetPt_;
  std::vector<float>* CalJetEta_;
  std::vector<float>* CalJetPhi_;
  std::vector<float>* CalJetEn_;

  //CaloJet sorted variables
  std::vector<float>* CalJet0Pt_;
  std::vector<float>* CalJet1Pt_;
  std::vector<float>* CalJet2Pt_;
  std::vector<float>* CalJet3Pt_;
  std::vector<float>* CalJet4Pt_;
  std::vector<float>* CalJet5Pt_;

  std::vector<float>* CalJet0Eta_;
  std::vector<float>* CalJet1Eta_;
  std::vector<float>* CalJet2Eta_;
  std::vector<float>* CalJet3Eta_;
  std::vector<float>* CalJet4Eta_;
  std::vector<float>* CalJet5Eta_;

  std::vector<float>* CalJet0Phi_;
  std::vector<float>* CalJet1Phi_;
  std::vector<float>* CalJet2Phi_;
  std::vector<float>* CalJet3Phi_;
  std::vector<float>* CalJet4Phi_;
  std::vector<float>* CalJet5Phi_;

  std::vector<float>* CalJet0En_;
  std::vector<float>* CalJet1En_;
  std::vector<float>* CalJet2En_;
  std::vector<float>* CalJet3En_;
  std::vector<float>* CalJet4En_;
  std::vector<float>* CalJet5En_;

  //CaloMet variables
  std::vector<float>* CalMETPt_;
  std::vector<float>* CalMETPhi_;
  std::vector<float>* CalMETEn_;

  //CaloMet variables BE
  std::vector<float>* CalMETBEPt_;
  std::vector<float>* CalMETBEPhi_;
  std::vector<float>* CalMETBEEn_;

    //CaloMet variables  BEFO
  std::vector<float>* CalMETBEFOPt_;
  std::vector<float>* CalMETBEFOPhi_;
  std::vector<float>* CalMETBEFOEn_;

    //CaloMet variables  M
  std::vector<float>* CalMETMPt_;
  std::vector<float>* CalMETMPhi_;
  std::vector<float>* CalMETMEn_;

  // SuperCluster variables
  std::vector<float>* SCN_;
  std::vector<float>* SCEn_;
  std::vector<float>* SCEta_;
  std::vector<float>* SCPhi_;
  std::vector<float>* SCEtaWidth_;
  std::vector<float>* SCPhiWidth_;
  std::vector<float>* SCEnhfEM_;
  std::vector<float>* SCEtahfEM_;
  std::vector<float>* SCPhihfEM_;
  std::vector<float>* SCEn5x5_;
  std::vector<float>* SCEta5x5_;
  std::vector<float>* SCPhi5x5_;
  std::vector<float>* SCEtaWidth5x5_;
  std::vector<float>* SCPhiWidth5x5_; 

  //caloclusters variables
  std::vector<float>* CCN_;
  std::vector<float>* CCEn_;
  std::vector<float>* CCEta_;
  std::vector<float>* CCPhi_;

  //calocluster hfem variables
  std::vector<float>* CCEn5x5_;
  std::vector<float>* CCEta5x5_;
  std::vector<float>* CCPhi5x5_;

  //photon variables
  std::vector<float>* PhoN_;
  std::vector<float>* PhoPt_;
  std::vector<float>* PhoEta_;
  std::vector<float>* PhoPhi_;
  std::vector<float>* PhoEn_;
  std::vector<float>* Phoe1x5_;
  std::vector<float>* Phoe2x5_;
  std::vector<float>* Phoe3x3_;
  std::vector<float>* Phoe5x5_;
  std::vector<float>* Phomaxenxtal_;
  std::vector<float>* Phosigmaeta_;
  std::vector<float>* PhosigmaIeta_;
  std::vector<float>* Phor1x5_;
  std::vector<float>* Phor2x5_;
  std::vector<float>* Phor9_;

  //ged photon variables
  std::vector<float>* gedPhoPt_;
  std::vector<float>* gedPhoEta_;
  std::vector<float>* gedPhoPhi_;
  // CURRENTLY FILLING ENERGY() AND NOT CORRECTED ENERGY
  std::vector<float>* gedPhoEn_;
  // CURRENTLY FILLING ENERGY() AND NOT CORRECTED ENERGY

  std::vector<float>* gedPhoe1x5_;
  std::vector<float>* gedPhoe2x5_;
  std::vector<float>* gedPhoe3x3_;
  std::vector<float>* gedPhoe5x5_;
  std::vector<float>* gedPhomaxenxtal_;
  std::vector<float>* gedPhosigmaeta_;
  std::vector<float>* gedPhosigmaIeta_;
  std::vector<float>* gedPhor1x5_;
  std::vector<float>* gedPhor2x5_;
  std::vector<float>* gedPhor9_;

  // Muon variables
  std::vector<float>* MuN_;
  std::vector<float>* MuPt_;
  std::vector<float>* MuEta_;
  std::vector<float>* MuPhi_;
  std::vector<float>* MuEn_;
  std::vector<float>* MuCh_;
  std::vector<float>* MuNCh_;
  std::vector<float>* MuChi2_;

  // GSF variables
  std::vector<float>* GsfN_;
  std::vector<float>* GsfPt_;
  std::vector<float>* GsfPhi_;
  std::vector<float>* GsfEta_;

  std::vector<float>* SigmaIEta_;
  std::vector<float>* SigmaIPhi_;
  std::vector<float>* r9_;
  std::vector<float>* HadOEm_;
  std::vector<float>* drSumPt_;
  std::vector<float>* drSumEt_;
  std::vector<float>* eSCOP_;
  std::vector<float>* ecEn_;

  //EB rechit, EE rechit and ES rechit variables
  std::vector<float>* EBenergy_;   
  std::vector<float>* EBtime_;
  std::vector<float>* EBchi2_;  
  std::vector<float>* EBiEta_;
  std::vector<float>* EBiPhi_;   

  std::vector<float>* EEenergy_;
  std::vector<float>* EEtime_;
  std::vector<float>* EEchi2_;
  std::vector<float>* EEix_;
  std::vector<float>* EEiy_; 

  std::vector<float>* ESenergy_;
  std::vector<float>* EStime_;
  std::vector<float>* ESix_;
  std::vector<float>* ESiy_; 
  std::vector<float>* HBHEenergy_;
  std::vector<float>* HBHEtime_;
  std::vector<float>* HBHEauxe_;
  std::vector<float>* HBHEieta_;
  std::vector<float>* HBHEiphi_;

  std::vector<float>* HFenergy_;
  std::vector<float>* HFtime_;
  std::vector<float>* HFieta_;
  std::vector<float>* HFiphi_;

  //preshower variables
  std::vector<float>* PreShEn_;
  std::vector<float>* PreShEta_;
  std::vector<float>* PreShPhi_;
  std::vector<float>* PreShYEn_;
  std::vector<float>* PreShYEta_;
  std::vector<float>* PreShYPhi_;

  std::vector<float>* qPUEvt_;
  std::vector<float>* qlumiEvt_;

  std::vector<float>* qPFJetN_;
  std::vector<float>* qPFJetPt_;
  std::vector<float>* qPFJetEta_;
  std::vector<float>* qPFJetPhi_;

  std::vector<float>* qPFJet4CHSPt_;
  std::vector<float>* qPFJet4CHSEta_;
  std::vector<float>* qPFJet4CHSPhi_;

  std::vector<float>* qPFJet8CHSPt_;
  std::vector<float>* qPFJet8CHSEta_;
  std::vector<float>* qPFJet8CHSPhi_;

  std::vector<float>* qPFJetEIPt_;
  std::vector<float>* qPFJetEIEta_;
  std::vector<float>* qPFJetEIPhi_;

  std::vector<float>* qPFJet8CHSSDPt_;
  std::vector<float>* qPFJet8CHSSDEta_;
  std::vector<float>* qPFJet8CHSSDPhi_;

  std::vector<float>* qPFJetTopCHSPt_;
  std::vector<float>* qPFJetTopCHSEta_;
  std::vector<float>* qPFJetTopCHSPhi_;

  std::vector<float>* qPFChMetPt_;
  std::vector<float>* qPFChMetPhi_;
  std::vector<float>* qPFMetPt_;
  std::vector<float>* qPFMetPhi_;
  std::vector<float>* qNVtx_;

  std::vector<float>* qCalJetN_;
  std::vector<float>* qCalJetPt_;
  std::vector<float>* qCalJetEta_;
  std::vector<float>* qCalJetPhi_;
  std::vector<float>* qCalJetEn_;

  std::vector<float>* qCalMETPt_;
  std::vector<float>* qCalMETPhi_;
  std::vector<float>* qCalMETEn_;


  std::vector<float>* qCalMETBEPt_;
  std::vector<float>* qCalMETBEPhi_;
  std::vector<float>* qCalMETBEEn_;


  std::vector<float>* qCalMETBEFOPt_;
  std::vector<float>* qCalMETBEFOPhi_;
  std::vector<float>* qCalMETBEFOEn_;


  std::vector<float>* qCalMETMPt_;
  std::vector<float>* qCalMETMPhi_;
  std::vector<float>* qCalMETMEn_;

  std::vector<float>* qSCN_;
  std::vector<float>* qSCEn_;
  std::vector<float>* qSCEta_;
  std::vector<float>* qSCPhi_;
  std::vector<float>* qSCEtaWidth_;
  std::vector<float>* qSCPhiWidth_;  
  std::vector<float>* qSCEnhfEM_;
  std::vector<float>* qSCEtahfEM_;
  std::vector<float>* qSCPhihfEM_;
  std::vector<float>* qSCEn5x5_;
  std::vector<float>* qSCEta5x5_;
  std::vector<float>* qSCPhi5x5_;
  std::vector<float>* qSCEtaWidth5x5_;
  std::vector<float>* qSCPhiWidth5x5_;    

  std::vector<float>* qCCN_;
  std::vector<float>* qCCEn_;
  std::vector<float>* qCCEta_;
  std::vector<float>* qCCPhi_;
  std::vector<float>* qCCEn5x5_;
  std::vector<float>* qCCEta5x5_;
  std::vector<float>* qCCPhi5x5_;

  std::vector<float>* qPhoN_;
  std::vector<float>* qPhoPt_;
  std::vector<float>* qPhoEta_;
  std::vector<float>* qPhoPhi_;
  std::vector<float>* qPhoEn_;

  std::vector<float>* qPhoe1x5_;
  std::vector<float>* qPhoe2x5_;
  std::vector<float>* qPhoe3x3_;
  std::vector<float>* qPhoe5x5_;
  std::vector<float>* qPhomaxenxtal_;
  std::vector<float>* qPhosigmaeta_;
  std::vector<float>* qPhosigmaIeta_;
  std::vector<float>* qPhor1x5_;
  std::vector<float>* qPhor2x5_;
  std::vector<float>* qPhor9_;

  std::vector<float>* qgedPhoPt_;
  std::vector<float>* qgedPhoEta_;
  std::vector<float>* qgedPhoPhi_;
  std::vector<float>* qgedPhoEn_;

  std::vector<float>* qgedPhoe1x5_;
  std::vector<float>* qgedPhoe2x5_;
  std::vector<float>* qgedPhoe3x3_;
  std::vector<float>* qgedPhoe5x5_;
  std::vector<float>* qgedPhomaxenxtal_;
  std::vector<float>* qgedPhosigmaeta_;
  std::vector<float>* qgedPhosigmaIeta_;
  std::vector<float>* qgedPhor1x5_;
  std::vector<float>* qgedPhor2x5_;
  std::vector<float>* qgedPhor9_;

  std::vector<float>* qMuN_;
  std::vector<float>* qMuPt_;
  std::vector<float>* qMuEta_;
  std::vector<float>* qMuPhi_;
  std::vector<float>* qMuEn_;
  std::vector<float>* qMuCh_;
  std::vector<float>* qMuNCh_;
  std::vector<float>* qMuChi2_;

  std::vector<float>* qGsfN_;

  std::vector<float>* qGsfPt_;
  std::vector<float>* qGsfPhi_;
  std::vector<float>* qGsfEta_;

  std::vector<float>* qSigmaIEta_;
  std::vector<float>* qSigmaIPhi_;
  std::vector<float>* qr9_;
  std::vector<float>* qHadOEm_;
  std::vector<float>* qdrSumPt_;
  std::vector<float>* qdrSumEt_;
  std::vector<float>* qeSCOP_;
  std::vector<float>* qecEn_;

  std::vector<float>* qEBenergy_;   
  std::vector<float>* qEBtime_;
  std::vector<float>* qEBchi2_;  
  std::vector<float>* qEBiEta_;
  std::vector<float>* qEBiPhi_;   

  std::vector<float>* qEEenergy_;
  std::vector<float>* qEEtime_;
  std::vector<float>* qEEchi2_;
  std::vector<float>* qEEix_;
  std::vector<float>* qEEiy_; 
   
  std::vector<float>* qESenergy_;
  std::vector<float>* qEStime_;
  std::vector<float>* qESix_;
  std::vector<float>* qESiy_; 

  std::vector<float>* qHBHEenergy_;
  std::vector<float>* qHBHEtime_;
  std::vector<float>* qHBHEauxe_;
  std::vector<float>* qHBHEieta_;
  std::vector<float>* qHBHEiphi_;

  std::vector<float>* qHFenergy_;
  std::vector<float>* qHFtime_;
  std::vector<float>* qHFieta_;
  std::vector<float>* qHFiphi_;

  std::vector<float>* qPreShEn_;
  std::vector<float>* qPreShEta_;
  std::vector<float>* qPreShPhi_;
  std::vector<float>* qPreShYEn_;
  std::vector<float>* qPreShYEta_;
  std::vector<float>* qPreShYPhi_;

  std::vector<float>*   pathRates_;
  std::vector<std::string>*   pathNames_;
  std::map<std::string,int> rateMap;

  edm::EDGetTokenT<LumiScalersCollection> lScalers_;

  edm::EDGetTokenT<reco::TrackCollection>  gTkToken_; //generalTracks
  edm::EDGetTokenT<reco::TrackCollection>  globTkToken_; //global muons tracks
  edm::EDGetTokenT<reco::PFJetCollection> PFJetToken_;
  edm::EDGetTokenT<reco::PFJetCollection> PFJet4CHSToken_;
  edm::EDGetTokenT<reco::PFJetCollection> PFJet8CHSToken_;
  edm::EDGetTokenT<reco::PFJetCollection> PFJetEIToken_;
  edm::EDGetTokenT<reco::PFJetCollection> PFJet8CHSSoftDropToken_;
  edm::EDGetTokenT<reco::PFJetCollection> PFJetTopCHSToken_;
  edm::EDGetTokenT<reco::PFMETCollection> PFChMETToken_;
  edm::EDGetTokenT<reco::PFMETCollection> PFMETToken_;

  edm::EDGetTokenT<reco::CaloJetCollection> CaloJetToken_;
  edm::EDGetTokenT<reco::CaloMETCollection> CaloMETToken_;      
  edm::EDGetTokenT<reco::CaloMETCollection> CaloMETBEToken_;
  edm::EDGetTokenT<reco::CaloMETCollection> CaloMETBEFOToken_;
  edm::EDGetTokenT<reco::CaloMETCollection> CaloMETMToken_;
  edm::EDGetTokenT<reco::VertexCollection>  vtxToken_;

  edm::EDGetTokenT<edm::TriggerResults>     triggerBits_;

  edm::EDGetTokenT<reco::SuperClusterCollection>   SuperClusterToken_;  
  edm::EDGetTokenT<reco::SuperClusterCollection>    SuperClusterhfEMToken_;
  edm::EDGetTokenT<reco::SuperClusterCollection>   SuperCluster5x5Token_;  

  edm::EDGetTokenT<reco::CaloClusterCollection>   CaloClusterToken_;  
  edm::EDGetTokenT<reco::CaloClusterCollection>   CaloCluster5x5Token_;

  edm::EDGetTokenT<reco::PhotonCollection> PhotonToken_;  
  edm::EDGetTokenT<reco::PhotonCollection> gedPhotonToken_;
  edm::EDGetTokenT<reco::MuonCollection>   MuonToken_;

  edm::EDGetTokenT<reco::GsfElectronCollection> GsfElectronToken_;
  edm::EDGetTokenT<reco::GsfElectronCollection> GsfElectronUncleanedToken_;

  edm::EDGetTokenT<EcalRecHitCollection> ebRHSrcToken_;
  edm::EDGetTokenT<EcalRecHitCollection> eeRHSrcToken_;
  edm::EDGetTokenT<EcalRecHitCollection> esRHSrcToken_;

  edm::EDGetTokenT<HBHERecHitCollection> hbheRHcToken_;
  edm::EDGetTokenT<HFRecHitCollection>   hfRHcToken_;
 
  edm::EDGetTokenT<reco::PreshowerClusterCollection> preshowerXToken_;
  edm::EDGetTokenT<reco::PreshowerClusterCollection> preshowerYToken_;
 
  int LSeventCounter;
  float PU_;
 
  std::string lumiFile_;
  std::map<int,std::map<int,float> > lumiMap;

  std::vector<double> quantiles_;

  std::vector<std::string> subsystemNames_;
  std::vector<bool>* subsystemQuality_;

  std::vector<std::string> qualityFiles_;

  typedef std::map<int, std::vector<std::pair<int, int> > > jsonMapType;
  jsonMapType myJsonMap;
  std::map<std::string,jsonMapType> qualityMaps;
};

AODAnalyzer::AODAnalyzer(const edm::ParameterSet& cfg):

  lScalers_                 (consumes<LumiScalersCollection>(edm::InputTag("scalersRawToDigi"))),

  gTkToken_                 (consumes<reco::TrackCollection>(cfg.getUntrackedParameter<edm::InputTag>("gTrackTag"))),
  globTkToken_              (consumes<reco::TrackCollection>(cfg.getUntrackedParameter<edm::InputTag>("globTrackTag"))),
  PFJetToken_               (consumes<reco::PFJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFJetTag"))),  
  PFJet4CHSToken_           (consumes<reco::PFJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFJet4CHSTag"))),
  PFJet8CHSToken_           (consumes<reco::PFJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFJet8CHSTag"))),
  PFJetEIToken_             (consumes<reco::PFJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFJetEITag"))),
  PFJet8CHSSoftDropToken_   (consumes<reco::PFJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFJet8CHSSoftDropTag"))),
  PFJetTopCHSToken_         (consumes<reco::PFJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFJetTopCHSTag"))),
  PFChMETToken_             (consumes<reco::PFMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFChMETTag"))),
  PFMETToken_               (consumes<reco::PFMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("PFMETTag"))),
  CaloJetToken_             (consumes<reco::CaloJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("CaloJetTag"))),
  CaloMETToken_             (consumes<reco::CaloMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("CaloMETTag"))),  
  CaloMETBEToken_           (consumes<reco::CaloMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("CaloMETBETag"))),  
  CaloMETBEFOToken_         (consumes<reco::CaloMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("CaloMETBEFOTag"))),  
  CaloMETMToken_            (consumes<reco::CaloMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("CaloMETMTag"))), 
 
  vtxToken_                 (consumes<reco::VertexCollection>(cfg.getUntrackedParameter<edm::InputTag>("vtx"))),
  triggerBits_              (consumes<edm::TriggerResults>(cfg.getUntrackedParameter<edm::InputTag>("bits"))),
  SuperClusterToken_        (consumes<reco::SuperClusterCollection>(cfg.getUntrackedParameter<edm::InputTag>("SuperClusterTag"))),
  SuperClusterhfEMToken_    (consumes<reco::SuperClusterCollection>(cfg.getUntrackedParameter<edm::InputTag>("SuperClusterhfEMTag"))),
  SuperCluster5x5Token_     (consumes<reco::SuperClusterCollection>(cfg.getUntrackedParameter<edm::InputTag>("SuperCluster5x5Tag"))),
  CaloClusterToken_         (consumes<reco::CaloClusterCollection>(cfg.getUntrackedParameter<edm::InputTag>("CaloClusterTag"))),
  CaloCluster5x5Token_      (consumes<reco::CaloClusterCollection>(cfg.getUntrackedParameter<edm::InputTag>("CaloCluster5x5Tag"))),
  PhotonToken_              (consumes<reco::PhotonCollection>(cfg.getUntrackedParameter<edm::InputTag>("PhotonTag"))),
  gedPhotonToken_           (consumes<reco::PhotonCollection>(cfg.getUntrackedParameter<edm::InputTag>("gedPhotonTag"))),
  MuonToken_                (consumes<reco::MuonCollection>(cfg.getUntrackedParameter<edm::InputTag>("MuonTag"))),

  GsfElectronToken_         (consumes<reco::GsfElectronCollection>(cfg.getUntrackedParameter<edm::InputTag>("GsfElectronTag"))),

  ebRHSrcToken_             (consumes<EcalRecHitCollection>(cfg.getUntrackedParameter<edm::InputTag>("EBRecHitSourceTag"))),  
  eeRHSrcToken_             (consumes<EcalRecHitCollection>(cfg.getUntrackedParameter<edm::InputTag>("EERecHitSourceTag"))),
  esRHSrcToken_             (consumes<EcalRecHitCollection>(cfg.getUntrackedParameter<edm::InputTag>("ESRecHitSourceTag"))),

  hbheRHcToken_             (consumes<HBHERecHitCollection>(cfg.getUntrackedParameter<edm::InputTag>("HBHERecHitTag"))),
  hfRHcToken_               (consumes<HFRecHitCollection>(cfg.getUntrackedParameter<edm::InputTag>("HFRecHitTag"))),
  preshowerXToken_          (consumes<reco::PreshowerClusterCollection>(cfg.getUntrackedParameter<edm::InputTag>("PreshowerClusterXTag"))),
  preshowerYToken_          (consumes<reco::PreshowerClusterCollection>(cfg.getUntrackedParameter<edm::InputTag>("PreshowerClusterYTag"))),
 
  quantiles_                (cfg.getUntrackedParameter<std::vector<double> >("quantiles"))


{}

void AODAnalyzer::initialize()
{

  LSeventCounter = 0;

  lumiId_ = -1;
  runId_ = -1;
  isSig_ = -1;

  pVtxNtr_->clear();
  pVtxChi2_->clear();

  qpVtxNtr_->clear();
  qpVtxChi2_->clear();

  pVtxX_->clear();
  pVtxY_->clear();
  pVtxZ_->clear();

  qpVtxX_->clear();
  qpVtxY_->clear();
  qpVtxZ_->clear();

  gTkPt_->clear();
  gTkEta_->clear();
  gTkPhi_->clear();
  gTkN_->clear();
  gTkChi2_->clear();
  gTkNHits_->clear();
  gTkNLay_->clear();

  qgTkPt_->clear();
  qgTkEta_->clear();
  qgTkPhi_->clear();
  qgTkN_->clear();
  qgTkChi2_->clear();
  qgTkNHits_->clear();
  qgTkNLay_->clear();

  globTkPt_->clear();
  globTkEta_->clear();
  globTkPhi_->clear();
  globTkN_->clear();
  globTkChi2_->clear();
  globTkNHits_->clear();

  qglobTkPt_->clear();
  qglobTkEta_->clear();
  qglobTkPhi_->clear();
  qglobTkN_->clear();
  qglobTkChi2_->clear();
  qglobTkNHits_->clear();

  PUEvt_->clear();
  lumiEvt_->clear();

  PFJetN_->clear();
  PFJetPt_->clear();
  PFJetEta_->clear();
  PFJetPhi_->clear();

  PFJet4CHSPt_->clear();
  PFJet4CHSEta_->clear();
  PFJet4CHSPhi_->clear();

  PFJet8CHSPt_->clear();
  PFJet8CHSEta_->clear();
  PFJet8CHSPhi_->clear();
  
  PFJetEIPt_->clear();
  PFJetEIEta_->clear();
  PFJetEIPhi_->clear();

  PFJet8CHSSDPt_->clear();
  PFJet8CHSSDEta_->clear();
  PFJet8CHSSDPhi_->clear();

  PFJetTopCHSPt_->clear();
  PFJetTopCHSEta_->clear();
  PFJetTopCHSPhi_->clear();       

  PFChMetPt_->clear();
  PFChMetPhi_->clear();
  PFMetPt_->clear();
  PFMetPhi_->clear();
  nVtx_->clear();

  CalJetN_->clear();
  CalJetPt_->clear();
  CalJetEta_->clear();
  CalJetPhi_->clear();
  CalJetEn_->clear();

  CalMETPt_->clear();
  CalMETPhi_->clear();
  CalMETEn_->clear();

  CalMETBEPt_->clear();
  CalMETBEPhi_->clear();
  CalMETBEEn_->clear();

  CalMETBEFOPt_->clear();
  CalMETBEFOPhi_->clear();
  CalMETBEFOEn_->clear();

  CalMETMPt_->clear();
  CalMETMPhi_->clear();
  CalMETMEn_->clear();

  SCN_ ->clear();
  SCEn_ ->clear();
  SCEta_->clear();
  SCPhi_->clear();
  SCEtaWidth_->clear();
  SCPhiWidth_->clear();  
  SCEnhfEM_ ->clear();
  SCEtahfEM_->clear();
  SCPhihfEM_->clear();
  SCEn5x5_ ->clear();
  SCEta5x5_->clear();
  SCPhi5x5_->clear();
  SCEtaWidth5x5_->clear();
  SCPhiWidth5x5_->clear();  
  
  CCN_ ->clear();
  CCEn_ ->clear();
  CCEta_->clear();
  CCPhi_->clear();
  CCEn5x5_ ->clear();
  CCEta5x5_->clear();
  CCPhi5x5_->clear();

  PhoN_->clear();
  PhoPt_->clear();
  PhoEta_->clear();
  PhoPhi_->clear();
  PhoEn_->clear();

  Phoe1x5_->clear();
  Phoe2x5_->clear();
  Phoe3x3_->clear();
  Phoe5x5_->clear();
  Phomaxenxtal_->clear();
  Phosigmaeta_->clear();
  PhosigmaIeta_->clear();
  Phor1x5_->clear();
  Phor2x5_->clear();
  Phor9_->clear();

  gedPhoPt_->clear();
  gedPhoEta_->clear();
  gedPhoPhi_->clear();
  gedPhoEn_->clear();

  gedPhoe1x5_->clear();
  gedPhoe2x5_->clear();
  gedPhoe3x3_->clear();
  gedPhoe5x5_->clear();
  gedPhomaxenxtal_->clear();
  gedPhosigmaeta_->clear();
  gedPhosigmaIeta_->clear();
  gedPhor1x5_->clear();
  gedPhor2x5_->clear();
  gedPhor9_->clear();

  MuN_->clear();
  MuPt_->clear();
  MuEta_->clear();
  MuPhi_->clear();
  MuEn_->clear();
  MuCh_->clear();
  MuNCh_->clear();
  MuChi2_->clear();

  GsfN_->clear();

  GsfPt_->clear();
  GsfPhi_->clear();
  GsfEta_->clear();

  SigmaIEta_->clear();
  SigmaIPhi_->clear();
  r9_->clear();
  HadOEm_->clear();
  drSumPt_->clear();
  drSumEt_->clear();
  eSCOP_->clear();
  ecEn_->clear();
  
  EBenergy_->clear();
  EBtime_->clear();
  EBchi2_->clear();
  EBiEta_->clear();
  EBiPhi_->clear();

  EEenergy_->clear();
  EEtime_->clear();
  EEchi2_->clear();
  EEix_->clear();
  EEiy_->clear();

  ESenergy_->clear();
  EStime_->clear();
  ESix_->clear();
  ESiy_->clear();

  HBHEenergy_->clear();
  HBHEtime_->clear();
  HBHEauxe_->clear();
  HBHEieta_->clear();
  HBHEiphi_->clear();

  HFenergy_->clear();
  HFtime_->clear();
  HFieta_->clear();
  HFiphi_->clear();

   
  PreShEn_->clear();
  PreShEta_->clear();
  PreShPhi_->clear();
  PreShYEn_->clear();
  PreShYEta_->clear();
  PreShYPhi_->clear();
  
  qPUEvt_->clear();
  qlumiEvt_->clear();

  qPFJetN_->clear();
  qPFJetPt_->clear();
  qPFJetEta_->clear();
  qPFJetPhi_->clear();

  qPFJet4CHSPt_->clear();
  qPFJet4CHSEta_->clear();
  qPFJet4CHSPhi_->clear();

  qPFJet8CHSPt_->clear();
  qPFJet8CHSEta_->clear();
  qPFJet8CHSPhi_->clear();
  
  qPFJetEIPt_->clear();
  qPFJetEIEta_->clear();
  qPFJetEIPhi_->clear();
  
  qPFJet8CHSSDPt_->clear();
  qPFJet8CHSSDEta_->clear();
  qPFJet8CHSSDPhi_->clear();

  qPFJetTopCHSPt_->clear();
  qPFJetTopCHSEta_->clear();
  qPFJetTopCHSPhi_->clear(); 

  qPFChMetPt_->clear();
  qPFChMetPhi_->clear();
  qPFMetPt_->clear();
  qPFMetPhi_->clear();
  qNVtx_->clear();

  qCalJetN_->clear();
  qCalJetPt_->clear();
  qCalJetEta_->clear();
  qCalJetPhi_->clear();
  qCalJetEn_->clear();
  qCalMETPt_->clear();
  qCalMETPhi_->clear();
  qCalMETEn_->clear();
  qCalMETBEPt_->clear();
  qCalMETBEPhi_->clear();
  qCalMETBEEn_->clear();
  qCalMETBEFOPt_->clear();
  qCalMETBEFOPhi_->clear();
  qCalMETBEFOEn_->clear();
  qCalMETMPt_->clear();
  qCalMETMPhi_->clear();
  qCalMETMEn_->clear();

  qSCN_ ->clear();
  qSCEn_ ->clear();
  qSCEta_->clear();
  qSCPhi_->clear();
  qSCEtaWidth_->clear();
  qSCPhiWidth_->clear();  
  qSCEnhfEM_ ->clear();
  qSCEtahfEM_->clear();
  qSCPhihfEM_->clear();
  qSCEn5x5_ ->clear();
  qSCEta5x5_->clear();
  qSCPhi5x5_->clear();
  qSCEtaWidth5x5_->clear();
  qSCPhiWidth5x5_->clear();  

  qCCEn_ ->clear();
  qCCEn_ ->clear();
  qCCEta_->clear();
  qCCPhi_->clear();
  qCCEn5x5_ ->clear();
  qCCEta5x5_->clear();
  qCCPhi5x5_->clear();

  qPhoN_->clear();
  qPhoPt_->clear();
  qPhoEta_->clear();
  qPhoPhi_->clear();
  qPhoEn_->clear();

  qPhoe1x5_->clear();
  qPhoe2x5_->clear();
  qPhoe3x3_->clear();
  qPhoe5x5_->clear();
  qPhomaxenxtal_->clear();
  qPhosigmaeta_->clear();
  qPhosigmaIeta_->clear();
  qPhor1x5_->clear();
  qPhor2x5_->clear();
  qPhor9_->clear();

  qgedPhoPt_->clear();
  qgedPhoEta_->clear();
  qgedPhoPhi_->clear();
  qgedPhoEn_->clear();

  qgedPhoe1x5_->clear();
  qgedPhoe2x5_->clear();
  qgedPhoe3x3_->clear();
  qgedPhoe5x5_->clear();
  qgedPhomaxenxtal_->clear();
  qgedPhosigmaeta_->clear();
  qgedPhosigmaIeta_->clear();
  qgedPhor1x5_->clear();
  qgedPhor2x5_->clear();
  qgedPhor9_->clear();

  qMuN_->clear();
  qMuPt_->clear();
  qMuEta_->clear();
  qMuPhi_->clear();
  qMuEn_->clear();
  qMuCh_->clear();
  qMuNCh_->clear();
  qMuChi2_->clear();
  
  qGsfN_->clear();

  qGsfPt_->clear();
  qGsfPhi_->clear();
  qGsfEta_->clear();

  qSigmaIEta_->clear();
  qSigmaIPhi_->clear();  
  qr9_->clear();
  qHadOEm_->clear();
  qdrSumPt_->clear();
  qdrSumEt_->clear();
  qeSCOP_->clear();
  qecEn_->clear();

  qEBenergy_->clear();
  qEBtime_->clear();
  qEBchi2_->clear();
  qEBiEta_->clear();
  qEBiPhi_->clear();

  qEEenergy_->clear();
  qEEtime_->clear();
  qEEchi2_->clear();
  qEEix_->clear();
  qEEiy_->clear();

  qESenergy_->clear();
  qEStime_->clear();
  qESix_->clear();
  qESiy_->clear();

  qHBHEenergy_->clear();
  qHBHEtime_->clear();
  qHBHEauxe_->clear();
  qHBHEieta_->clear();
  qHBHEiphi_->clear();

  qHFenergy_->clear();
  qHFtime_->clear();
  qHFieta_->clear();
  qHFiphi_->clear();

  qPreShEn_->clear();
  qPreShEta_->clear();
  qPreShPhi_->clear();
  qPreShYEn_->clear();
  qPreShYEta_->clear();
  qPreShYPhi_->clear();

  pathRates_->clear();
  pathNames_->clear();
  
  rateMap.clear();

  subsystemQuality_->clear();
}

void AODAnalyzer::fillPUandLumiEvt(float &pu, float&lumi){

  PUEvt_->push_back(pu);
  lumiEvt_->push_back(lumi);

}


template<typename jetCollection>
void AODAnalyzer::fillJets(const edm::Handle<jetCollection> & jets, std::string type)
{
 
  typename jetCollection::const_iterator i = jets->begin();

  PFJetN_->push_back(jets->size());

  for(;i != jets->end(); i++){
	
	if(type.compare(std::string("PF")) == 0)
	  {
	    PFJetPt_->push_back(i->pt());
	    PFJetEta_->push_back(i->eta());
	    PFJetPhi_->push_back(i->phi()); 
     	  }
	 

  }
  
  return;
}

template<typename TrackCollection>
void AODAnalyzer::fillglobTracks(const edm::Handle<TrackCollection> & globTracks, std::string type)
{

  typename TrackCollection::const_iterator i = globTracks->begin();
  
  globTkN_->push_back(globTracks->size());
  
  for(;i != globTracks->end(); i++){

    globTkPt_->push_back(i->pt());
    globTkEta_->push_back(i->eta());
    globTkPhi_->push_back(i->phi());
    globTkNHits_->push_back(i->hitPattern().numberOfValidTrackerHits());
    globTkChi2_->push_back(i->normalizedChi2());
  }

  return;
}


template<typename TrackCollection>
void AODAnalyzer::fillgTracks(const edm::Handle<TrackCollection> & gTracks, std::string type)
{

  typename TrackCollection::const_iterator i = gTracks->begin();
  
  gTkN_->push_back(gTracks->size());
  
  for(;i != gTracks->end(); i++){

    gTkPt_->push_back(i->pt());
    gTkEta_->push_back(i->eta());
    gTkPhi_->push_back(i->phi());
    gTkChi2_->push_back(i->normalizedChi2());
    gTkNHits_->push_back(i->hitPattern().numberOfValidTrackerHits());
    gTkNLay_->push_back(i->hitPattern().trackerLayersWithMeasurement());
  }

  return;
}

template<typename PFJet4CHSCollection>
void AODAnalyzer::fill4CHSJets(const edm::Handle<PFJet4CHSCollection> & jets4CHS, std::string type)
{
  // Selected jets
  typename PFJet4CHSCollection::const_iterator i = jets4CHS->begin();
  for(;i != jets4CHS->end(); i++){
   
  if(type.compare(std::string("PF")) == 0)
    {
      PFJet4CHSPt_->push_back(i->pt());
      PFJet4CHSEta_->push_back(i->eta());
      PFJet4CHSPhi_->push_back(i->phi());
    }
  }

  return;
}

template<typename PFJet8CHSCollection>
void AODAnalyzer::fill8CHSJets(const edm::Handle<PFJet8CHSCollection> & jets8CHS, std::string type)
{
  // Selected jets
  //reco::CaloJetCollection recojets;
  typename PFJet8CHSCollection::const_iterator i = jets8CHS->begin();
  for(;i != jets8CHS->end(); i++){
  
  if(type.compare(std::string("PF")) == 0)
    {
      PFJet8CHSPt_->push_back(i->pt());
      PFJet8CHSEta_->push_back(i->eta());
      PFJet8CHSPhi_->push_back(i->phi());
    }
  
  }

  return;
}

template<typename PFJetEICollection>
void AODAnalyzer::fillEIJets(const edm::Handle<PFJetEICollection> & jetsEI, std::string type)
{
  // Selected jets
  //reco::CaloJetCollection recojets;
  typename PFJetEICollection::const_iterator i = jetsEI->begin();
  for(;i != jetsEI->end(); i++){
   
  if(type.compare(std::string("PF")) == 0)
    {
      PFJetEIPt_->push_back(i->pt());
      PFJetEIEta_->push_back(i->eta());
      PFJetEIPhi_->push_back(i->phi());
     }  
  }
  
  return;
}

template<typename PFJet8CHSSoftDropCollection>
void AODAnalyzer::fill8CHSoftDropJets(const edm::Handle<PFJet8CHSSoftDropCollection> & jets8CHSSoftDrop, std::string type)
{
  // Selected jets
  //reco::CaloJetCollection recojets;
  typename PFJet8CHSSoftDropCollection::const_iterator i = jets8CHSSoftDrop->begin();
  for(;i != jets8CHSSoftDrop->end(); i++){
   
  if(type.compare(std::string("PF")) == 0)
    {
      PFJet8CHSSDPt_->push_back(i->pt());
      PFJet8CHSSDEta_->push_back(i->eta());
      PFJet8CHSSDPhi_->push_back(i->phi());
    }
  
  }

  return;
}

template<typename PFJetTopCHSCollection>
void AODAnalyzer::fillTopCHSJets(const edm::Handle<PFJetTopCHSCollection> & jetsTopCHS, std::string type)
{
  // Selected jets
  //reco::CaloJetCollection recojets;
  typename PFJetTopCHSCollection::const_iterator i = jetsTopCHS->begin();
  for(;i != jetsTopCHS->end(); i++){
    
  if(type.compare(std::string("PF")) == 0)
    {
      PFJetTopCHSPt_->push_back(i->pt());
      PFJetTopCHSEta_->push_back(i->eta());
      PFJetTopCHSPhi_->push_back(i->phi());
    }
  
  }

  return;
}

template<typename PFChMETCollection>
void AODAnalyzer::fillPFChMets(const edm::Handle<PFChMETCollection> & pfchmets)
{

  typename PFChMETCollection::const_iterator i = pfchmets->begin();
  for(;i != pfchmets->end(); i++){
    PFChMetPt_->push_back(i->pt());
    PFChMetPhi_->push_back(i->phi());

  }
  return;

}

template<typename PFMETCollection>
void AODAnalyzer::fillPFMets(const edm::Handle<PFMETCollection> & pfmets)
{
  typename PFMETCollection::const_iterator i = pfmets->begin();
  for(;i != pfmets->end(); i++){
    PFMetPt_->push_back(i->pt());
    PFMetPhi_->push_back(i->phi());  //try also eta and energy
  }
  return;

}

template<typename CaloJetCollection>
void AODAnalyzer::fillCaloJets(const edm::Handle<CaloJetCollection> & calojets)
{

  CalJetN_->push_back(calojets->size());

  typename CaloJetCollection::const_iterator i = calojets->begin();
  for(;i != calojets->end(); i++){
        CalJetPt_->push_back(i->pt());
        CalJetEta_->push_back(i->eta());
        CalJetPhi_->push_back(i->phi());
        CalJetEn_->push_back(i->energy());
  }
    
  return;

}

template<typename CaloMETCollection>
void AODAnalyzer::fillCaloMETs(const edm::Handle<CaloMETCollection> & caloMETs)
{
 
  typename CaloMETCollection::const_iterator i = caloMETs->begin();
  for(;i != caloMETs->end(); i++){
        CalMETPt_->push_back(i->pt());
	CalMETPhi_->push_back(i->phi());
        CalMETEn_->push_back(i->energy());
  }
  return;

}


template<typename CaloMETBECollection>
void AODAnalyzer::fillCaloMETBEs(const edm::Handle<CaloMETBECollection> & caloMETBEs)
{
  typename CaloMETBECollection::const_iterator i = caloMETBEs->begin();
  for(;i != caloMETBEs->end(); i++){
        CalMETBEPt_->push_back(i->pt());
	CalMETBEPhi_->push_back(i->phi());
        CalMETBEEn_->push_back(i->energy());
  }
  return;

}

template<typename CaloMETBEFOCollection>
void AODAnalyzer::fillCaloMETBEFOs(const edm::Handle<CaloMETBEFOCollection> & caloMETBEFOs)
{

  typename CaloMETBEFOCollection::const_iterator i = caloMETBEFOs->begin();
  for(;i != caloMETBEFOs->end(); i++){
        CalMETBEFOPt_->push_back(i->pt());
        CalMETBEFOPhi_->push_back(i->phi());
        CalMETBEFOEn_->push_back(i->energy());

  }
  return;

}

template<typename CaloMETMCollection>
void AODAnalyzer::fillCaloMETMs(const edm::Handle<CaloMETMCollection> & caloMETMs)
{

  typename CaloMETMCollection::const_iterator i = caloMETMs->begin();
  for(;i != caloMETMs->end(); i++){
        CalMETMPt_->push_back(i->pt());
        CalMETMPhi_->push_back(i->phi());
        CalMETMEn_->push_back(i->energy());

  }
  return;

}



template<typename SuperClusterCollection>
void AODAnalyzer::fillSC(const edm::Handle<SuperClusterCollection> & superclusters) //ask for jets analogy //SUPERCLUSTERS
{

  // Selected jets
  //reco::CaloJetCollection recojets;
  SCN_->push_back(superclusters->size());
  typename SuperClusterCollection::const_iterator i = superclusters->begin();
  for(;i != superclusters->end(); i++){
      SCEn_->push_back(i->energy());
      SCEta_->push_back(i->eta());
      SCPhi_->push_back(i->phi());
      SCEtaWidth_->push_back(i->etaWidth());
      SCPhiWidth_->push_back(i->phiWidth());

  }

  return;
}

template<typename SuperClusterhfEMCollection>
void AODAnalyzer::fillSChfEM(const edm::Handle<SuperClusterhfEMCollection> & superclustershfEM) //ask for jets analogy //SUPERCLUSTERS
{

  // Selected jets
  //reco::CaloJetCollection recojets;
  typename SuperClusterhfEMCollection::const_iterator i = superclustershfEM->begin();
  for(;i != superclustershfEM->end(); i++){
      SCEnhfEM_->push_back(i->energy());
      SCEtahfEM_->push_back(i->eta());
      SCPhihfEM_->push_back(i->phi());

  }
  return;


}

template<typename SuperCluster5x5Collection>
void AODAnalyzer::fillSC5x5(const edm::Handle<SuperCluster5x5Collection> & superclusters5x5) //ask for jets analogy //SUPERCLUSTERS
{

  // Selected jets
  //reco::CaloJetCollection recojets;
  typename SuperCluster5x5Collection::const_iterator i = superclusters5x5->begin();
  for(;i != superclusters5x5->end(); i++){

      SCEn5x5_->push_back(i->energy());
      SCEta5x5_->push_back(i->eta());
      SCPhi5x5_->push_back(i->phi());
      SCEtaWidth5x5_->push_back(i->etaWidth());
      SCPhiWidth5x5_->push_back(i->phiWidth());

  }
  return;


}

template<typename CaloClusterCollection>
void AODAnalyzer::fillCC(const edm::Handle<CaloClusterCollection> & caloclusters) //ask for jets analogy //SUPERCLUSTERS
{

  // Selected jets
  //reco::CaloJetCollection recojets;
  CCN_->push_back(caloclusters->size());

  typename CaloClusterCollection::const_iterator i = caloclusters->begin();
  for(;i != caloclusters->end(); i++){
      CCEn_->push_back(i->energy());
      CCEta_->push_back(i->eta());
      CCPhi_->push_back(i->phi());

  }
  return;


}

template<typename CaloCluster5x5Collection>
void AODAnalyzer::fillCC5x5(const edm::Handle<CaloCluster5x5Collection> & caloclusters5x5) //ask for jets analogy //SUPERCLUSTERS
{

  // Selected jets
  //reco::CaloJetCollection recojets;
  typename CaloCluster5x5Collection::const_iterator i = caloclusters5x5->begin();
  for(;i != caloclusters5x5->end(); i++){

      CCEn5x5_->push_back(i->energy());
      CCEta5x5_->push_back(i->eta());
      CCPhi5x5_->push_back(i->phi());

  }
  return;


}

template<typename PhotonCollection>
void AODAnalyzer::fillPhotons(const edm::Handle<PhotonCollection> & photons)
{
  std::vector<reco::Photon> myPhotons;

  PhoN_->push_back(photons->size());

  typename PhotonCollection::const_iterator i = photons->begin();
  for(;i != photons->end(); i++){
     
    PhoPt_->push_back(i->pt());
    PhoEta_->push_back(i->eta());
    PhoPhi_->push_back(i->phi());
    PhoEn_->push_back(i->energy());   //GETCORRECTEDENERGY!!
    Phoe1x5_->push_back(i->e1x5());   
    Phoe2x5_->push_back(i->e2x5());
    Phoe3x3_->push_back(i->e3x3());
    Phoe5x5_->push_back(i->e5x5());
    Phomaxenxtal_->push_back(i->maxEnergyXtal());
    Phosigmaeta_->push_back(i->sigmaEtaEta());
    PhosigmaIeta_->push_back(i->sigmaIetaIeta());
    Phor1x5_->push_back(i->r1x5());
    Phor2x5_->push_back(i->r2x5());
    Phor9_->push_back(i->r9());
    myPhotons.push_back(*i);
     
  }

  return;
}

template<typename PhotongedCollection>
void AODAnalyzer::fillgedPhotons(const edm::Handle<PhotongedCollection> & gedphotons)
{
   std::vector<reco::Photon> myGedPhotons;
   typename PhotongedCollection::const_iterator i = gedphotons->begin();
   for(;i != gedphotons->end(); i++){
     
     gedPhoPt_->push_back(i->pt());
     gedPhoEta_->push_back(i->eta());
     gedPhoPhi_->push_back(i->phi());
     gedPhoEn_->push_back(i->energy());
     gedPhoe1x5_->push_back(i->e1x5());   
     gedPhoe2x5_->push_back(i->e2x5());
     gedPhoe3x3_->push_back(i->e3x3());
     gedPhoe5x5_->push_back(i->e5x5());
     gedPhomaxenxtal_->push_back(i->maxEnergyXtal());
     gedPhosigmaeta_->push_back(i->sigmaEtaEta());
     gedPhosigmaIeta_->push_back(i->sigmaIetaIeta());
     gedPhor1x5_->push_back(i->r1x5());
     gedPhor2x5_->push_back(i->r2x5());
     gedPhor9_->push_back(i->r9());
     myGedPhotons.push_back(*i);
   }

  return;

}

template<typename MuonCollection>
void AODAnalyzer::fillMuons(const edm::Handle<MuonCollection> & muons)
{
  
  MuN_->push_back(muons->size());   

   typename MuonCollection::const_iterator i = muons->begin();
    for(;i != muons->end(); i++){

      MuPt_->push_back(i->pt());
      MuEta_->push_back(i->eta());
      MuPhi_->push_back(i->phi());
      MuEn_->push_back(i->energy());   //GETCORRECTEDENERGY!!
      MuCh_->push_back(i->charge());
      MuChi2_->push_back(i->vertexNormalizedChi2());  
      MuNCh_->push_back(i->numberOfMatches());
        
  }

  return;
}

template<typename GsfElectronCollection>
void AODAnalyzer::fillGsf(const edm::Handle<GsfElectronCollection> & electrons)
{

  GsfN_->push_back(electrons->size());

  typename GsfElectronCollection::const_iterator i = electrons->begin();
  for(;i != electrons->end(); i++){

    GsfPt_->push_back(i->p4().Pt());
    GsfPhi_->push_back(i->p4().Phi());
    GsfEta_->push_back(i->p4().Eta());
    
    SigmaIEta_->push_back(i->sigmaIetaIeta());
    SigmaIPhi_->push_back(i->sigmaIphiIphi());
    r9_       ->push_back(i->r9());
    HadOEm_   ->push_back(i->hadronicOverEm());
    drSumPt_  ->push_back(i->dr03TkSumPt());
    drSumEt_  ->push_back(i->dr03EcalRecHitSumEt());
    eSCOP_    ->push_back(i->eSuperClusterOverP());
    ecEn_     ->push_back(i->ecalEnergy());   
  }

  return;

}

template<typename EBEcalRecHitCollection>
void AODAnalyzer::fillEBrecHit(const edm::Handle<EBEcalRecHitCollection> & EBhits)
{

  typename EBEcalRecHitCollection::const_iterator i = EBhits->begin();

  for(;i != EBhits->end(); i++){
    EBenergy_ ->push_back(i->energy());
    EBtime_ ->push_back(i->time());
    EBchi2_ ->push_back(i->chi2());
    EBiEta_->push_back( EBDetId( i->detid() ).ieta() );
    EBiPhi_->push_back( EBDetId( i->detid() ).iphi() );
  }

  return;
}



template<typename EEEcalRecHitCollection>
void AODAnalyzer::fillEErecHit(const edm::Handle<EEEcalRecHitCollection> & EEhits)
{

  typename EEEcalRecHitCollection::const_iterator i = EEhits->begin();

  for(;i != EEhits->end(); i++){
    EEenergy_ ->push_back(i->energy());
    EEtime_ ->push_back(i->time());
    EEchi2_ ->push_back(i->chi2());
    EEix_->push_back( EEDetId( i->detid() ).ix() );
    EEiy_->push_back( EEDetId( i->detid() ).iy() );
  }
  return;
}

template<typename ESEcalRecHitCollection>
void AODAnalyzer::fillESrecHit(const edm::Handle<ESEcalRecHitCollection> & EShits)
{

  typename ESEcalRecHitCollection::const_iterator i = EShits->begin();
  for(;i != EShits->end(); i++){
    ESenergy_ ->push_back(i->energy());
    EStime_ ->push_back(i->time());
    ESix_->push_back( ESDetId( i->detid() ).six() );
    ESiy_->push_back( ESDetId( i->detid() ).siy() );
  }
  return;
}

template<typename HBHERecHitCollection>
void AODAnalyzer::fillHBHErecHit(const edm::Handle<HBHERecHitCollection> & HBHEhits)
{

  typename HBHERecHitCollection::const_iterator i = HBHEhits->begin();
  for(;i != HBHEhits->end(); i++){

    HBHEenergy_ ->push_back(i->energy());
    HBHEtime_ ->push_back(i->time());
    HBHEauxe_ ->push_back(i->eaux()); //const class HBHERecHit' has no member named 'chi2'

    HBHEieta_ ->push_back( HcalDetId( i->detid() ).ieta() );
    HBHEiphi_ ->push_back( HcalDetId( i->detid() ).iphi() );
  }
  return;
}

template<typename HFRecHitCollection>
void AODAnalyzer::fillHFrecHit(const edm::Handle<HFRecHitCollection> & HFhits)
{

  typename HFRecHitCollection::const_iterator i = HFhits->begin();
  for(;i != HFhits->end(); i++){
    HFenergy_ ->push_back(i->energy());
    HFtime_ ->push_back(i->time());
    HFieta_ ->push_back(HcalDetId( i->detid() ).ieta());
    HFiphi_ ->push_back(HcalDetId( i->detid() ).iphi());
  }
  return;
}

template<typename PreshowerClusterCollection>
void AODAnalyzer::fillPreshowerCluster(const edm::Handle<PreshowerClusterCollection> & preshowerclusterhits)
{

  typename PreshowerClusterCollection::const_iterator i = preshowerclusterhits->begin();
  for(;i != preshowerclusterhits->end(); i++){

    PreShEn_->push_back(i->energy());
    PreShEta_->push_back(i->eta());
    PreShPhi_->push_back(i->phi());

  }
  return;
}

template<typename PreshowerClusterCollectionY>
void AODAnalyzer::fillPreshowerClusterY(const edm::Handle<PreshowerClusterCollectionY> & preshowerclusterYhits)
{

  typename PreshowerClusterCollectionY::const_iterator i = preshowerclusterYhits->begin();
  for(;i != preshowerclusterYhits->end(); i++){

    PreShYEn_->push_back(i->energy());
    PreShYEta_->push_back(i->eta());
    PreShYPhi_->push_back(i->phi());

  }
  return;
}


template<typename T>
void AODAnalyzer::computeQuantiles(std::vector<T>* myDistr, std::vector<T>* myQuan, std::vector<double> qq, bool & isInt)
{
  //need to sort the distr to compute quantiles
  std::vector<T> dummyDistr = *myDistr;
  std::sort(dummyDistr.begin(), dummyDistr.end());

  //scan the vector and find quantiles
  unsigned int qItr = 0;
  for (unsigned int itr = 0; itr < dummyDistr.size(); ++itr)
  {
    if(qItr >= qq.size())
      return;

    float prob = ((float)itr+1.)/(float)dummyDistr.size();
    if( prob >= qq[qItr] )
	  {

	    float value=dummyDistr.at(itr);

	    if (isInt){
	      //std::cout << "before " << value << std::endl;

	      float rand1 = ((float) std::rand() / (RAND_MAX));   // [from 0 to 1] to select the sign
	      float rand2 = ((float) std::rand() / (RAND_MAX))*0.5; // [from 0 to 0.5)] to be added to the integer value
	      
	      if (rand1<=0.5 || value<0.0001) value= value + rand2;
	      else value= value -rand2;
	      //std::cout << value << std::endl;
	    };

	    myQuan->push_back(value);
	    ++qItr;
  	}
  }
  return;
}


template<typename T>
void AODAnalyzer::computeMeanAndRms(std::vector<T>* myDistr, std::vector<T>* myVect)
{
  double sum = std::accumulate(myDistr->begin(), myDistr->end(), 0.0); 
  double mean = sum / myDistr->size(); 
  myVect->push_back( mean );

  std::vector<double> diff(myDistr->size());
  std::transform(myDistr->begin(), myDistr->end(), diff.begin(), [mean](double x) { return x - mean; });
  double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0); 
  myVect->push_back( std::sqrt(sq_sum / myDistr->size()) );
}

//===================== beginJob and Analyze =========================

void AODAnalyzer::beginJob() {

  TH1::SetDefaultSumw2() ;
  outTree_ = outfile_-> make<TTree>("NewMLTree","NewMLTree");

  outTree_->Branch("runId",     &runId_,       "runId_/I");
  outTree_->Branch("lumiId",    &lumiId_,      "lumiId_/I");
  outTree_->Branch("lumi",      &lumi_,        "lumi_/F");
  outTree_->Branch("isSig",     &isSig_,       "isSig_/I");
  outTree_->Branch("PU",        &PU_,          "PU_/F");

  lumiEvt_   = new std::vector<float>; //inst lumi and PU per event
  PUEvt_ = new std::vector<float>;

  PFJetN_   = new std::vector<float>;
  PFJetPt_   = new std::vector<float>;
  PFJetEta_  = new std::vector<float>;
  PFJetPhi_  = new std::vector<float>;

  PFJet4CHSPt_   = new std::vector<float>;
  PFJet4CHSEta_  = new std::vector<float>;
  PFJet4CHSPhi_  = new std::vector<float>;

  PFJet8CHSPt_   = new std::vector<float>;
  PFJet8CHSEta_  = new std::vector<float>;
  PFJet8CHSPhi_  = new std::vector<float>;

  PFJetEIPt_   = new std::vector<float>;
  PFJetEIEta_  = new std::vector<float>;
  PFJetEIPhi_  = new std::vector<float>;

  PFJet8CHSSDPt_   = new std::vector<float>;
  PFJet8CHSSDEta_  = new std::vector<float>;
  PFJet8CHSSDPhi_  = new std::vector<float>;

  PFJetTopCHSPt_   = new std::vector<float>;
  PFJetTopCHSEta_  = new std::vector<float>;
  PFJetTopCHSPhi_  = new std::vector<float>;        

  PFChMetPt_     = new std::vector<float>;
  PFChMetPhi_    = new std::vector<float>;
  PFMetPt_     = new std::vector<float>;
  PFMetPhi_    = new std::vector<float>;
  nVtx_      = new std::vector<float>;
  
  CalJetN_   = new std::vector<float>;
  CalJetPt_   = new std::vector<float>;
  CalJetEta_   = new std::vector<float>;
  CalJetPhi_   = new std::vector<float>;
  CalJetEn_   = new std::vector<float>;
  CalMETPt_   = new std::vector<float>;
  CalMETPhi_   = new std::vector<float>;
  CalMETEn_   = new std::vector<float>;

  CalMETBEPt_   = new std::vector<float>;
  CalMETBEPhi_   = new std::vector<float>;
  CalMETBEEn_   = new std::vector<float>;
  CalMETBEFOPt_   = new std::vector<float>;
  CalMETBEFOPhi_   = new std::vector<float>;
  CalMETBEFOEn_   = new std::vector<float>;
  CalMETMPt_   = new std::vector<float>;
  CalMETMPhi_   = new std::vector<float>;
  CalMETMEn_   = new std::vector<float>;

  SCN_       = new std::vector<float>;
  SCEn_      = new std::vector<float>;
  SCEta_     = new std::vector<float>;
  SCPhi_     = new std::vector<float>;
  SCEtaWidth_     = new std::vector<float>;
  SCPhiWidth_     = new std::vector<float>;  
  SCEnhfEM_      = new std::vector<float>;
  SCEtahfEM_     = new std::vector<float>;
  SCPhihfEM_     = new std::vector<float>;
  SCEn5x5_      = new std::vector<float>;
  SCEta5x5_     = new std::vector<float>;
  SCPhi5x5_     = new std::vector<float>;
  SCEtaWidth5x5_     = new std::vector<float>;
  SCPhiWidth5x5_     = new std::vector<float>;  

  CCN_      = new std::vector<float>;
  CCEn_      = new std::vector<float>;
  CCEta_     = new std::vector<float>;
  CCPhi_     = new std::vector<float>;
  CCEn5x5_      = new std::vector<float>;
  CCEta5x5_     = new std::vector<float>;
  CCPhi5x5_     = new std::vector<float>;

  PhoN_     = new std::vector<float>;
  PhoPt_     = new std::vector<float>;
  PhoEta_    = new std::vector<float>;
  PhoPhi_    = new std::vector<float>;
  PhoEn_ = new std::vector<float>;

  Phoe1x5_   = new std::vector<float>;
  Phoe2x5_   = new std::vector<float>;
  Phoe3x3_   = new std::vector<float>;
  Phoe5x5_   = new std::vector<float>;
  Phomaxenxtal_ = new std::vector<float>;
  Phosigmaeta_  = new std::vector<float>;
  PhosigmaIeta_ = new std::vector<float>;
  Phor1x5_   = new std::vector<float>;
  Phor2x5_   = new std::vector<float>;
  Phor9_     = new std::vector<float>;

  gedPhoPt_     = new std::vector<float>;
  gedPhoEta_    = new std::vector<float>;
  gedPhoPhi_    = new std::vector<float>;
  gedPhoEn_ = new std::vector<float>;

  gedPhoe1x5_   = new std::vector<float>;
  gedPhoe2x5_   = new std::vector<float>;
  gedPhoe3x3_   = new std::vector<float>;
  gedPhoe5x5_   = new std::vector<float>;
  gedPhomaxenxtal_ = new std::vector<float>;
  gedPhosigmaeta_  = new std::vector<float>;
  gedPhosigmaIeta_ = new std::vector<float>;
  gedPhor1x5_   = new std::vector<float>;
  gedPhor2x5_   = new std::vector<float>;
  gedPhor9_     = new std::vector<float>;

  MuN_         = new std::vector<float>;
  MuPt_         = new std::vector<float>;
  MuEta_        = new std::vector<float>;
  MuPhi_        = new std::vector<float>;
  MuEn_         = new std::vector<float>;
  MuCh_         = new std::vector<float>;
  MuNCh_         = new std::vector<float>;
  MuChi2_         = new std::vector<float>;  

  //TODO
  GsfN_        = new std::vector<float>;
  GsfPt_       = new std::vector<float>;
  GsfEta_      = new std::vector<float>;
  GsfPhi_      = new std::vector<float>;

  SigmaIEta_ = new std::vector<float>;
  SigmaIPhi_ = new std::vector<float>;
  r9_        = new std::vector<float>;
  HadOEm_    = new std::vector<float>;
  drSumPt_   = new std::vector<float>;
  drSumEt_   = new std::vector<float>;
  eSCOP_     = new std::vector<float>;
  ecEn_      = new std::vector<float>;
 
  EBenergy_    = new std::vector<float>;
  EBtime_      = new std::vector<float>;
  EBchi2_      = new std::vector<float>;
  EBiEta_       = new std::vector<float>;
  EBiPhi_       = new std::vector<float>;

  EEenergy_    = new std::vector<float>;
  EEtime_      = new std::vector<float>;
  EEchi2_      = new std::vector<float>;
  EEix_       = new std::vector<float>;
  EEiy_       = new std::vector<float>;

  ESenergy_    = new std::vector<float>;
  EStime_      = new std::vector<float>;
  ESix_       = new std::vector<float>;
  ESiy_       = new std::vector<float>;

  HBHEenergy_  = new std::vector<float>;
  HBHEtime_    = new std::vector<float>;
  HBHEauxe_    = new std::vector<float>;
  HBHEieta_    = new std::vector<float>;
  HBHEiphi_    = new std::vector<float>;

  HFenergy_    = new std::vector<float>;
  HFtime_      = new std::vector<float>;
  HFieta_      = new std::vector<float>;
  HFiphi_      = new std::vector<float>;
 
  PreShEn_    = new std::vector<float>;
  PreShEta_   = new std::vector<float>;
  PreShPhi_   = new std::vector<float>;

  PreShYEn_    = new std::vector<float>;
  PreShYEta_   = new std::vector<float>;
  PreShYPhi_   = new std::vector<float>;

  pVtxNtr_ = new std::vector<float>;
  pVtxChi2_ = new std::vector<float>;

  qpVtxNtr_ = new std::vector<float>;
  qpVtxChi2_ = new std::vector<float>;

  pVtxX_ = new std::vector<float>;
  pVtxY_ = new std::vector<float>;
  pVtxZ_ = new std::vector<float>;

  qpVtxX_ = new std::vector<float>;
  qpVtxY_ = new std::vector<float>;
  qpVtxZ_ = new std::vector<float>;

  qgTkPt_  = new std::vector<float>;
  qgTkEta_ = new std::vector<float>;
  qgTkPhi_ = new std::vector<float>;

  qgTkN_  = new std::vector<float>;
  qgTkChi2_ = new std::vector<float>;
  qgTkNHits_ = new std::vector<float>;
  qgTkNLay_ = new std::vector<float>;

  gTkN_  = new std::vector<float>;
  gTkChi2_ = new std::vector<float>;
  gTkNHits_ = new std::vector<float>;
  gTkNLay_ = new std::vector<float>;

  gTkPt_  = new std::vector<float>;
  gTkEta_ = new std::vector<float>;
  gTkPhi_ = new std::vector<float>;

  qglobTkPt_  = new std::vector<float>;
  qglobTkEta_ = new std::vector<float>;
  qglobTkPhi_ = new std::vector<float>;

  qglobTkN_  = new std::vector<float>;
  qglobTkChi2_ = new std::vector<float>;
  qglobTkNHits_ = new std::vector<float>;

  globTkN_  = new std::vector<float>;
  globTkChi2_ = new std::vector<float>;
  globTkNHits_ = new std::vector<float>;

  globTkPt_  = new std::vector<float>;
  globTkEta_ = new std::vector<float>;
  globTkPhi_ = new std::vector<float>;

  qlumiEvt_   = new std::vector<float>; //inst lumi and PU per event
  qPUEvt_ = new std::vector<float>;

  qPFJetN_   = new std::vector<float>;
  qPFJetPt_  = new std::vector<float>;
  qPFJetEta_ = new std::vector<float>;
  qPFJetPhi_ = new std::vector<float>;

  qPFJet4CHSPt_   = new std::vector<float>;
  qPFJet4CHSEta_  = new std::vector<float>;
  qPFJet4CHSPhi_  = new std::vector<float>;

  qPFJet8CHSPt_   = new std::vector<float>;
  qPFJet8CHSEta_  = new std::vector<float>;
  qPFJet8CHSPhi_  = new std::vector<float>;

  qPFJetEIPt_   = new std::vector<float>;
  qPFJetEIEta_  = new std::vector<float>;
  qPFJetEIPhi_  = new std::vector<float>;

  qPFJet8CHSSDPt_   = new std::vector<float>;
  qPFJet8CHSSDEta_  = new std::vector<float>;
  qPFJet8CHSSDPhi_  = new std::vector<float>;

  qPFJetTopCHSPt_   = new std::vector<float>;
  qPFJetTopCHSEta_  = new std::vector<float>;
  qPFJetTopCHSPhi_  = new std::vector<float>;

  qPFChMetPt_     = new std::vector<float>;
  qPFChMetPhi_    = new std::vector<float>;
  qPFMetPt_     = new std::vector<float>;
  qPFMetPhi_    = new std::vector<float>;
 
  qCalJetN_   = new std::vector<float>;
  qCalJetPt_   = new std::vector<float>;
  qCalJetEta_   = new std::vector<float>;
  qCalJetPhi_   = new std::vector<float>;
  qCalJetEn_   = new std::vector<float>;
  qCalMETPt_   = new std::vector<float>;
  qCalMETPhi_   = new std::vector<float>;
  qCalMETEn_   = new std::vector<float>;

  qCalMETBEPt_   = new std::vector<float>;
  qCalMETBEPhi_   = new std::vector<float>;
  qCalMETBEEn_   = new std::vector<float>;
  qCalMETBEFOPt_   = new std::vector<float>;
  qCalMETBEFOPhi_   = new std::vector<float>;
  qCalMETBEFOEn_   = new std::vector<float>;
  qCalMETMPt_   = new std::vector<float>;
  qCalMETMPhi_   = new std::vector<float>;
  qCalMETMEn_   = new std::vector<float>;

  qSCN_       = new std::vector<float>;
  qSCEn_      = new std::vector<float>;
  qSCEta_     = new std::vector<float>;
  qSCPhi_     = new std::vector<float>;
  qSCEtaWidth_     = new std::vector<float>;
  qSCPhiWidth_     = new std::vector<float>;  
  qSCEnhfEM_      = new std::vector<float>;
  qSCEtahfEM_     = new std::vector<float>;
  qSCPhihfEM_     = new std::vector<float>;
  qSCEn5x5_      = new std::vector<float>;
  qSCEta5x5_     = new std::vector<float>;
  qSCPhi5x5_     = new std::vector<float>;
  qSCEtaWidth5x5_     = new std::vector<float>;
  qSCPhiWidth5x5_     = new std::vector<float>; 

  qCCN_     = new std::vector<float>;
  qCCEn_     = new std::vector<float>;
  qCCEta_    = new std::vector<float>;
  qCCPhi_    = new std::vector<float>;
  qCCEn5x5_     = new std::vector<float>;
  qCCEta5x5_    = new std::vector<float>;
  qCCPhi5x5_    = new std::vector<float>;

  qPhoN_     = new std::vector<float>;
  qPhoPt_     = new std::vector<float>;
  qPhoEta_    = new std::vector<float>;
  qPhoPhi_    = new std::vector<float>;
  qPhoEn_ = new std::vector<float>;

  qPhoe1x5_   = new std::vector<float>;
  qPhoe2x5_   = new std::vector<float>;
  qPhoe3x3_   = new std::vector<float>;
  qPhoe5x5_   = new std::vector<float>;
  qPhomaxenxtal_ = new std::vector<float>;
  qPhosigmaeta_  = new std::vector<float>;
  qPhosigmaIeta_ = new std::vector<float>;
  qPhor1x5_   = new std::vector<float>;
  qPhor2x5_   = new std::vector<float>;
  qPhor9_     = new std::vector<float>;

  qgedPhoPt_     = new std::vector<float>;
  qgedPhoEta_    = new std::vector<float>;
  qgedPhoPhi_    = new std::vector<float>;
  qgedPhoEn_ = new std::vector<float>;

  qgedPhoe1x5_   = new std::vector<float>;
  qgedPhoe2x5_   = new std::vector<float>;
  qgedPhoe3x3_   = new std::vector<float>;
  qgedPhoe5x5_   = new std::vector<float>;
  qgedPhomaxenxtal_ = new std::vector<float>;
  qgedPhosigmaeta_  = new std::vector<float>;
  qgedPhosigmaIeta_ = new std::vector<float>;
  qgedPhor1x5_   = new std::vector<float>;
  qgedPhor2x5_   = new std::vector<float>;
  qgedPhor9_     = new std::vector<float>;

  qMuN_         = new std::vector<float>;
  qMuPt_         = new std::vector<float>;
  qMuEta_        = new std::vector<float>;
  qMuPhi_        = new std::vector<float>;
  qMuEn_         = new std::vector<float>;
  qMuCh_         = new std::vector<float>;
  qMuNCh_        = new std::vector<float>;
  qMuChi2_       = new std::vector<float>;  
  
  qGsfN_       = new std::vector<float>;
  qGsfPt_       = new std::vector<float>;
  qGsfEta_      = new std::vector<float>;
  qGsfPhi_      = new std::vector<float>;

  qSigmaIEta_= new std::vector<float>;
  qSigmaIPhi_= new std::vector<float>;
  qr9_       = new std::vector<float>;
  qHadOEm_   = new std::vector<float>;
  qdrSumPt_  = new std::vector<float>;
  qdrSumEt_  = new std::vector<float>;
  qeSCOP_    = new std::vector<float>;
  qecEn_     = new std::vector<float>;

  qEBenergy_    = new std::vector<float>;
  qEBtime_      = new std::vector<float>;
  qEBchi2_      = new std::vector<float>;
  qEBiEta_       = new std::vector<float>;
  qEBiPhi_       = new std::vector<float>;

  qEEenergy_    = new std::vector<float>;
  qEEtime_      = new std::vector<float>;
  qEEchi2_      = new std::vector<float>;
  qEEix_       = new std::vector<float>;
  qEEiy_       = new std::vector<float>;

  qESenergy_    = new std::vector<float>;
  qEStime_      = new std::vector<float>;
  qESix_       = new std::vector<float>;
  qESiy_       = new std::vector<float>;

  qHBHEenergy_  = new std::vector<float>;
  qHBHEtime_    = new std::vector<float>;
  qHBHEauxe_    = new std::vector<float>;
  qHBHEieta_    = new std::vector<float>;
  qHBHEiphi_    = new std::vector<float>;

  qHFenergy_    = new std::vector<float>;
  qHFtime_      = new std::vector<float>;
  qHFieta_      = new std::vector<float>;
  qHFiphi_      = new std::vector<float>;

  qPreShEn_     = new std::vector<float>;
  qPreShEta_    = new std::vector<float>;
  qPreShPhi_    = new std::vector<float>;
  qPreShYEn_    = new std::vector<float>;
  qPreShYEta_   = new std::vector<float>;
  qPreShYPhi_   = new std::vector<float>;
  
  qNVtx_       = new std::vector<float>;
  pathRates_   = new std::vector<float>;
  pathNames_   = new std::vector<std::string>;
  
  outTree_->Branch("qpVtxChi2_",    "std::vector<std::float>",      &qpVtxChi2_);
  outTree_->Branch("qpVtxNtr_",    "std::vector<std::float>",      &qpVtxNtr_);

  outTree_->Branch("qpVtxX_",    "std::vector<std::float>",      &qpVtxX_);
  outTree_->Branch("qpVtxY_",    "std::vector<std::float>",      &qpVtxY_);
  outTree_->Branch("qpVtxZ_",    "std::vector<std::float>",      &qpVtxZ_);
 
  outTree_->Branch("qgTkPt",     "std::vector<std::float>",      &qgTkPt_);
  outTree_->Branch("qgTkEta",    "std::vector<std::float>",      &qgTkEta_);
  outTree_->Branch("qgTkPhi",    "std::vector<std::float>",      &qgTkPhi_);

  outTree_->Branch("qgTkN",      "std::vector<std::float>",       &qgTkN_);
  outTree_->Branch("qgTkChi2",   "std::vector<std::float>",       &qgTkChi2_);
  outTree_->Branch("qgTkNHits",  "std::vector<std::float>",       &qgTkNHits_);
  outTree_->Branch("qgTkNLay",  "std::vector<std::float>",        &qgTkNLay_);

  outTree_->Branch("qglobTkPt",     "std::vector<std::float>",      &qglobTkPt_);
  outTree_->Branch("qglobTkEta",    "std::vector<std::float>",      &qglobTkEta_);
  outTree_->Branch("qglobTkPhi",    "std::vector<std::float>",      &qglobTkPhi_);

  outTree_->Branch("qglobTkN",      "std::vector<std::float>",       &qglobTkN_);
  outTree_->Branch("qglobTkChi2",   "std::vector<std::float>",       &qglobTkChi2_);
  outTree_->Branch("qglobTkNHits",  "std::vector<std::float>",       &qglobTkNHits_);

  outTree_->Branch("qPUEvt",     "std::vector<std::float>",      &qPUEvt_);
  outTree_->Branch("qlumiEvt",    "std::vector<std::float>",      &qlumiEvt_);

  outTree_->Branch("qPFJetN",     "std::vector<std::float>",      &qPFJetN_);
  outTree_->Branch("qPFJetPt",     "std::vector<std::float>",      &qPFJetPt_);
  outTree_->Branch("qPFJetEta",    "std::vector<std::float>",      &qPFJetEta_);
  outTree_->Branch("qPFJetPhi",    "std::vector<std::float>",      &qPFJetPhi_);

  outTree_->Branch("qPFJet4CHSPt",     "std::vector<std::float>",      &qPFJet4CHSPt_);
  outTree_->Branch("qPFJet4CHSEta",    "std::vector<std::float>",      &qPFJet4CHSEta_);
  outTree_->Branch("qPFJet4CHSPhi",    "std::vector<std::float>",      &qPFJet4CHSPhi_);

  outTree_->Branch("qPFJet8CHSPt",     "std::vector<std::float>",      &qPFJet8CHSPt_);
  outTree_->Branch("qPFJet8CHSEta",    "std::vector<std::float>",      &qPFJet8CHSEta_);
  outTree_->Branch("qPFJet8CHSPhi",    "std::vector<std::float>",      &qPFJet8CHSPhi_);

  outTree_->Branch("qPFJetEIPt",     "std::vector<std::float>",      &qPFJetEIPt_);
  outTree_->Branch("qPFJetEIEta",    "std::vector<std::float>",      &qPFJetEIEta_);
  outTree_->Branch("qPFJetEIPhi",    "std::vector<std::float>",      &qPFJetEIPhi_);

  outTree_->Branch("qPFJet8CHSSDPt",     "std::vector<std::float>",      &qPFJet8CHSSDPt_);
  outTree_->Branch("qPFJet8CHSSDEta",    "std::vector<std::float>",      &qPFJet8CHSSDEta_);
  outTree_->Branch("qPFJet8CHSSDPhi",    "std::vector<std::float>",      &qPFJet8CHSSDPhi_);

  outTree_->Branch("qPFJetTopCHSPt",     "std::vector<std::float>",      &qPFJetTopCHSPt_);
  outTree_->Branch("qPFJetTopCHSEta",    "std::vector<std::float>",      &qPFJetTopCHSEta_);
  outTree_->Branch("qPFJetTopCHSPhi",    "std::vector<std::float>",      &qPFJetTopCHSPhi_);

  outTree_->Branch("qPFChMetPt",     "std::vector<std::float>",        &qPFChMetPt_);
  outTree_->Branch("qPFChMetPhi",    "std::vector<std::float>",        &qPFChMetPhi_);
  outTree_->Branch("qPFMetPt",     "std::vector<std::float>",        &qPFMetPt_);
  outTree_->Branch("qPFMetPhi",    "std::vector<std::float>",        &qPFMetPhi_);
  outTree_->Branch("qNVtx",        "std::vector<std::float>",        &qNVtx_);

  outTree_->Branch("qCalJetN",     "std::vector<std::float>",        &qCalJetN_);
  outTree_->Branch("qCalJetPt",     "std::vector<std::float>",        &qCalJetPt_);
  outTree_->Branch("qCalJetEta",    "std::vector<std::float>",        &qCalJetEta_);
  outTree_->Branch("qCalJetPhi",    "std::vector<std::float>",        &qCalJetPhi_);
  outTree_->Branch("qCalJetEn",    "std::vector<std::float>",        &qCalJetEn_);

  outTree_->Branch("qCalMETPt",     "std::vector<std::float>",        &qCalMETPt_);
  outTree_->Branch("qCalMETPhi",    "std::vector<std::float>",        &qCalMETPhi_);
  outTree_->Branch("qCalMETEn",    "std::vector<std::float>",        &qCalMETEn_);

  outTree_->Branch("qCalMETBEPt",     "std::vector<std::float>",        &qCalMETBEPt_);
  outTree_->Branch("qCalMETBEPhi",    "std::vector<std::float>",        &qCalMETBEPhi_);
  outTree_->Branch("qCalMETBEEn",    "std::vector<std::float>",         &qCalMETBEEn_);

  outTree_->Branch("qCalMETBEFOPt",     "std::vector<std::float>",        &qCalMETBEFOPt_);
  outTree_->Branch("qCalMETBEFOPhi",    "std::vector<std::float>",        &qCalMETBEFOPhi_);
  outTree_->Branch("qCalMETBEFOEn",    "std::vector<std::float>",         &qCalMETBEFOEn_);

  outTree_->Branch("qCalMETMPt",     "std::vector<std::float>",        &qCalMETMPt_);
  outTree_->Branch("qCalMETMPhi",    "std::vector<std::float>",        &qCalMETMPhi_);
  outTree_->Branch("qCalMETMEn",    "std::vector<std::float>",         &qCalMETMEn_);

  outTree_->Branch("qSCN",     "std::vector<std::float>",        &qSCN_);
  outTree_->Branch("qSCEn",     "std::vector<std::float>",        &qSCEn_);
  outTree_->Branch("qSCEta",    "std::vector<std::float>",        &qSCEta_);
  outTree_->Branch("qSCPhi",    "std::vector<std::float>",        &qSCPhi_);
  outTree_->Branch("qSCEtaWidth",    "std::vector<std::float>",        &qSCEtaWidth_);
  outTree_->Branch("qSCPhiWidth",    "std::vector<std::float>",        &qSCPhiWidth_);  
  outTree_->Branch("qSCEnhfEM",     "std::vector<std::float>",        &qSCEnhfEM_);
  outTree_->Branch("qSCEtahfEM",    "std::vector<std::float>",        &qSCEtahfEM_);
  outTree_->Branch("qSCPhihfEM",    "std::vector<std::float>",        &qSCPhihfEM_);
  outTree_->Branch("qSCEn5x5",     "std::vector<std::float>",        &qSCEn5x5_);
  outTree_->Branch("qSCEta5x5",    "std::vector<std::float>",        &qSCEta5x5_);
  outTree_->Branch("qSCPhi5x5",    "std::vector<std::float>",        &qSCPhi5x5_);
  outTree_->Branch("qSCEtaWidth5x5",    "std::vector<std::float>",        &qSCEtaWidth5x5_);
  outTree_->Branch("qSCPhiWidth5x5",    "std::vector<std::float>",        &qSCPhiWidth5x5_);  

  outTree_->Branch("qCCN",     "std::vector<std::float>",        &qCCN_);
  outTree_->Branch("qCCEn",     "std::vector<std::float>",        &qCCEn_);
  outTree_->Branch("qCCEta",    "std::vector<std::float>",        &qCCEta_);
  outTree_->Branch("qCCPhi",    "std::vector<std::float>",        &qCCPhi_);
  outTree_->Branch("qCCEn5x5",     "std::vector<std::float>",        &qCCEn5x5_);
  outTree_->Branch("qCCEta5x5",    "std::vector<std::float>",        &qCCEta5x5_);
  outTree_->Branch("qCCPhi5x5",    "std::vector<std::float>",        &qCCPhi5x5_);

  outTree_->Branch("qPhoN",     "std::vector<std::float>",        &qPhoN_);
  outTree_->Branch("qPhoPt",     "std::vector<std::float>",        &qPhoPt_);
  outTree_->Branch("qPhoEta",    "std::vector<std::float>",        &qPhoEta_);
  outTree_->Branch("qPhoPhi",    "std::vector<std::float>",        &qPhoPhi_);
  outTree_->Branch("qPhoEn_",    "std::vector<std::float>",    &qPhoEn_);

  outTree_->Branch("qPhoe1x5_",     "std::vector<std::float>",        &qPhoe1x5_);
  outTree_->Branch("qPhoe2x5_",    "std::vector<std::float>",        &qPhoe2x5_);
  outTree_->Branch("qPhoe3x3_",    "std::vector<std::float>",        &qPhoe3x3_);
  outTree_->Branch("qPhoe5x5_",    "std::vector<std::float>",    &qPhoe5x5_);
  outTree_->Branch("qPhomaxenxtal_",     "std::vector<std::float>",        &qPhomaxenxtal_);
  outTree_->Branch("qPhosigmaeta_",    "std::vector<std::float>",        &qPhosigmaeta_);
  outTree_->Branch("qPhosigmaIeta_",    "std::vector<std::float>",        &qPhosigmaIeta_);
  outTree_->Branch("qPhor1x5_",    "std::vector<std::float>",    &qPhor1x5_);
  outTree_->Branch("qPhor2x5_",    "std::vector<std::float>",        &qPhor2x5_);
  outTree_->Branch("qPhor9_",    "std::vector<std::float>",    &qPhor9_);

  outTree_->Branch("qgedPhoPt",     "std::vector<std::float>",     &qgedPhoPt_);
  outTree_->Branch("qgedPhoEta",    "std::vector<std::float>",     &qgedPhoEta_);
  outTree_->Branch("qgedPhoPhi",    "std::vector<std::float>",     &qgedPhoPhi_);
  outTree_->Branch("qgedPhoEn_",    "std::vector<std::float>", &qgedPhoEn_);

  outTree_->Branch("qgedPhoe1x5_",     "std::vector<std::float>",        &qgedPhoe1x5_);
  outTree_->Branch("qgedPhoe2x5_",    "std::vector<std::float>",        &qgedPhoe2x5_);
  outTree_->Branch("qgedPhoe3x3_",    "std::vector<std::float>",        &qgedPhoe3x3_);
  outTree_->Branch("qgedPhoe5x5_",    "std::vector<std::float>",    &qgedPhoe5x5_);
  outTree_->Branch("qgedPhomaxenxtal_",     "std::vector<std::float>",        &qgedPhomaxenxtal_);
  outTree_->Branch("qgedPhosigmaeta_",    "std::vector<std::float>",        &qgedPhosigmaeta_);
  outTree_->Branch("qgedPhosigmaIeta_",    "std::vector<std::float>",        &qgedPhosigmaIeta_);
  outTree_->Branch("qgedPhor1x5_",    "std::vector<std::float>",    &qgedPhor1x5_);
  outTree_->Branch("qgedPhor2x5_",    "std::vector<std::float>",        &qgedPhor2x5_);
  outTree_->Branch("qgedPhor9_",    "std::vector<std::float>",    &qgedPhor9_);

  outTree_->Branch("qMuN",     "std::vector<std::float>",        &qMuN_);
  outTree_->Branch("qMuPt",     "std::vector<std::float>",        &qMuPt_);
  outTree_->Branch("qMuEta",    "std::vector<std::float>",        &qMuEta_);
  outTree_->Branch("qMuPhi",    "std::vector<std::float>",        &qMuPhi_);
  outTree_->Branch("qMuEn_",    "std::vector<std::float>",        &qMuEn_);
  outTree_->Branch("qMuCh_",    "std::vector<std::float>",        &qMuCh_);
  outTree_->Branch("qMuNCh_",    "std::vector<std::float>",        &qMuNCh_);
  outTree_->Branch("qMuChi2_",    "std::vector<std::float>",        &qMuChi2_);  

  outTree_->Branch("qGsfN",    "std::vector<std::float>",     &qGsfN_);

  outTree_->Branch("qGsfPt",    "std::vector<std::float>",     &qGsfPt_);
  outTree_->Branch("qGsfEta",    "std::vector<std::float>",     &qGsfEta_);
  outTree_->Branch("qGsfPhi",    "std::vector<std::float>",     &qGsfPhi_);

  outTree_->Branch("qSigmaIEta",    "std::vector<std::float>",     &qSigmaIEta_);
  outTree_->Branch("qSigmaIPhi",    "std::vector<std::float>",     &qSigmaIPhi_);
  outTree_->Branch("qr9",    "std::vector<std::float>",            &qr9_);
  outTree_->Branch("qHadOEm",    "std::vector<std::float>",        &qHadOEm_);
  outTree_->Branch("qdrSumPt",    "std::vector<std::float>",       &qdrSumPt_);
  outTree_->Branch("qdrSumEt",    "std::vector<std::float>",       &qdrSumEt_);
  outTree_->Branch("qeSCOP",    "std::vector<std::float>",         &qeSCOP_);
  outTree_->Branch("qecEn",    "std::vector<std::float>",          &qecEn_);

  //TODO
  outTree_->Branch("qEBenergy",    "std::vector<std::float>",        &qEBenergy_);
  outTree_->Branch("qEBtime",    "std::vector<std::float>",          &qEBtime_);
  outTree_->Branch("qEBchi2",    "std::vector<std::float>",          &qEBchi2_);
  outTree_->Branch("qEBiEta",    "std::vector<std::float>",          &qEBiEta_);
  outTree_->Branch("qEBiPhi",    "std::vector<std::float>",          &qEBiPhi_);

  outTree_->Branch("qEEenergy",    "std::vector<std::float>",        &qEEenergy_);
  outTree_->Branch("qEEtime",    "std::vector<std::float>",          &qEEtime_);
  outTree_->Branch("qEEchi2",    "std::vector<std::float>",          &qEEchi2_);
  outTree_->Branch("qEEix",    "std::vector<std::float>",          &qEEix_);
  outTree_->Branch("qEEiy",    "std::vector<std::float>",          &qEEiy_);

  outTree_->Branch("qESenergy",    "std::vector<std::float>",        &qESenergy_);
  outTree_->Branch("qEStime",    "std::vector<std::float>",          &qEStime_);
  outTree_->Branch("qESix",    "std::vector<std::float>",          &qESix_);
  outTree_->Branch("qESiy",    "std::vector<std::float>",          &qESiy_);

  outTree_->Branch("qHBHEenergy",    "std::vector<std::float>",        &qHBHEenergy_);
  outTree_->Branch("qHBHEtime",    "std::vector<std::float>",          &qHBHEtime_);
  outTree_->Branch("qHBHEauxe",    "std::vector<std::float>",          &qHBHEauxe_);
  outTree_->Branch("qHBHEieta",    "std::vector<std::float>",        &qHBHEieta_);
  outTree_->Branch("qHBHEiphi",    "std::vector<std::float>",          &qHBHEiphi_);

  outTree_->Branch("qHFenergy",    "std::vector<std::float>",        &qHFenergy_);
  outTree_->Branch("qHFtime",    "std::vector<std::float>",          &qHFtime_);
  outTree_->Branch("qHFieta",    "std::vector<std::float>",          &qHFieta_);
  outTree_->Branch("qHFiphi",    "std::vector<std::float>",          &qHFiphi_);

  
  outTree_->Branch("qPreShEn",     "std::vector<std::float>",        &qPreShEn_);
  outTree_->Branch("qPreShEta",    "std::vector<std::float>",        &qPreShEta_);
  outTree_->Branch("qPreShPhi",    "std::vector<std::float>",        &qPreShPhi_);
  outTree_->Branch("qPreShYEn",     "std::vector<std::float>",        &qPreShYEn_);
  outTree_->Branch("qPreShYEta",    "std::vector<std::float>",        &qPreShYEta_);
  outTree_->Branch("qPreShYPhi",    "std::vector<std::float>",        &qPreShYPhi_);

  
  outTree_->Branch("pathRates",      "std::vector<std::float>",    &pathRates_);
  outTree_->Branch("pathNames",      "std::vector<std::string>",   &pathNames_);

  subsystemQuality_ = new std::vector<bool>;
  outTree_->Branch("subsystemQuality", "std::vector<bool>",        &subsystemQuality_);
  outTree_->Branch("subsystemNames",   "std::vector<std::string>", &subsystemNames_);

}

void AODAnalyzer::endJob() 
{

  delete pVtxChi2_;
  delete pVtxNtr_;

  delete qpVtxChi2_;
  delete qpVtxNtr_;

  delete pVtxX_;
  delete pVtxY_;
  delete pVtxZ_;
  delete qpVtxX_;
  delete qpVtxY_;
  delete qpVtxZ_;

  delete  gTkPt_;
  delete  gTkEta_;
  delete  gTkPhi_;
  delete  gTkChi2_;
  delete  gTkNHits_;
  delete  gTkNLay_;
  delete  gTkN_;

  delete  qgTkPt_;
  delete  qgTkEta_;
  delete  qgTkPhi_;
  delete  qgTkChi2_;
  delete  qgTkNHits_;
  delete  qgTkNLay_;
  delete  qgTkN_;

  delete  globTkPt_;
  delete  globTkEta_;
  delete  globTkPhi_;
  delete  globTkChi2_;
  delete  globTkNHits_;
  delete  globTkN_;

  delete  qglobTkPt_;
  delete  qglobTkEta_;
  delete  qglobTkPhi_;
  delete  qglobTkChi2_;
  delete  qglobTkNHits_;
  delete  qglobTkN_;

  delete PUEvt_;
  delete lumiEvt_;

  delete PFJetN_;
  delete PFJetPt_;
  delete PFJetEta_;
  delete PFJetPhi_;

  delete PFJet4CHSPt_;
  delete PFJet4CHSEta_;
  delete PFJet4CHSPhi_;

  delete PFJet8CHSPt_;
  delete PFJet8CHSEta_;
  delete PFJet8CHSPhi_;

  delete PFJetEIPt_;
  delete PFJetEIEta_;
  delete PFJetEIPhi_;

  delete PFJet8CHSSDPt_;
  delete PFJet8CHSSDEta_;
  delete PFJet8CHSSDPhi_;

  delete PFJetTopCHSPt_;
  delete PFJetTopCHSEta_;
  delete PFJetTopCHSPhi_;

  delete PFChMetPt_;
  delete PFChMetPhi_;
  delete PFMetPt_;
  delete PFMetPhi_;

  delete CalJetN_;
  delete CalJetPt_;
  delete CalJetEta_;
  delete CalJetPhi_;
  delete CalJetEn_;
  delete CalMETPt_;
  delete CalMETPhi_;
  delete CalMETEn_;

  delete CalMETBEPt_;
  delete CalMETBEPhi_;
  delete CalMETBEEn_;
  delete CalMETBEFOPt_;
  delete CalMETBEFOPhi_;
  delete CalMETBEFOEn_;
  delete CalMETMPt_;
  delete CalMETMPhi_;
  delete CalMETMEn_;

  delete SCN_;
  delete SCEn_;
  delete SCEta_;
  delete SCPhi_;
  delete SCEtaWidth_;
  delete SCPhiWidth_;  
  delete SCEnhfEM_;
  delete SCEtahfEM_;
  delete SCPhihfEM_;
  delete SCEn5x5_;
  delete SCEta5x5_;
  delete SCPhi5x5_;
  delete SCEtaWidth5x5_;
  delete SCPhiWidth5x5_;

  delete CCN_;  
  delete CCEn_;
  delete CCEta_;
  delete CCPhi_;
  delete CCEn5x5_;
  delete CCEta5x5_;
  delete CCPhi5x5_;

  delete PhoN_;
  delete PhoPt_;
  delete PhoEta_;
  delete PhoPhi_;
  delete PhoEn_;

  delete Phoe1x5_;
  delete Phoe2x5_;
  delete Phoe3x3_;
  delete Phoe5x5_;
  delete Phomaxenxtal_;
  delete Phosigmaeta_;
  delete PhosigmaIeta_;
  delete Phor1x5_;
  delete Phor2x5_;
  delete Phor9_;

  delete gedPhoPt_;
  delete gedPhoEta_;
  delete gedPhoPhi_;
  delete gedPhoEn_;

  delete gedPhoe1x5_;
  delete gedPhoe2x5_;
  delete gedPhoe3x3_;
  delete gedPhoe5x5_;
  delete gedPhomaxenxtal_;
  delete gedPhosigmaeta_;
  delete gedPhosigmaIeta_;
  delete gedPhor1x5_;
  delete gedPhor2x5_;
  delete gedPhor9_;

  delete MuN_;
  delete MuPt_;
  delete MuEta_;
  delete MuPhi_;
  delete MuEn_;
  delete MuCh_;
  delete MuNCh_;
  delete MuChi2_;
  
  //TODO
  delete GsfN_;

  delete GsfPt_;
  delete GsfEta_;
  delete GsfPhi_;

  delete SigmaIEta_;
  delete SigmaIPhi_;
  delete r9_;
  delete HadOEm_;
  delete drSumPt_;
  delete drSumEt_;
  delete eSCOP_;
  delete ecEn_;

  delete EBenergy_;
  delete EBtime_;
  delete EBchi2_;
  delete EBiEta_;
  delete EBiPhi_;
  delete EEenergy_;
  delete EEtime_;
  delete EEchi2_;
  delete EEix_;
  delete EEiy_;
  delete ESenergy_;
  delete EStime_;
  delete ESix_;
  delete ESiy_;

  delete HBHEenergy_ ;
  delete HBHEtime_ ;
  delete HBHEauxe_ ;
  delete HBHEieta_;
  delete HBHEiphi_;  
  delete HFenergy_ ;
  delete HFtime_ ;
  delete HFieta_;
  delete HFiphi_;
  delete PreShEn_;
  delete PreShEta_;
  delete PreShPhi_;
  delete PreShYEn_;
  delete PreShYEta_;
  delete PreShYPhi_;

  delete qPUEvt_;
  delete qlumiEvt_;

  delete qPFJetN_;
  delete qPFJetPt_;
  delete qPFJetEta_;
  delete qPFJetPhi_;

  delete qPFJet4CHSPt_;
  delete qPFJet4CHSEta_;
  delete qPFJet4CHSPhi_;

  delete qPFJet8CHSPt_;
  delete qPFJet8CHSEta_;
  delete qPFJet8CHSPhi_;

  delete qPFJetEIPt_;
  delete qPFJetEIEta_;
  delete qPFJetEIPhi_;

  delete qPFJet8CHSSDPt_;
  delete qPFJet8CHSSDEta_;
  delete qPFJet8CHSSDPhi_;

  delete qPFJetTopCHSPt_;
  delete qPFJetTopCHSEta_;
  delete qPFJetTopCHSPhi_;

  delete qPFChMetPt_;
  delete qPFChMetPhi_;
  delete qPFMetPt_;
  delete qPFMetPhi_;

  delete qCalJetN_;
  delete qCalJetPt_;
  delete qCalJetEta_;
  delete qCalJetPhi_;
  delete qCalJetEn_;
  delete qCalMETPt_;
  delete qCalMETPhi_;
  delete qCalMETEn_;

  delete qCalMETBEPt_;
  delete qCalMETBEPhi_;
  delete qCalMETBEEn_;
  delete qCalMETBEFOPt_;
  delete qCalMETBEFOPhi_;
  delete qCalMETBEFOEn_;
  delete qCalMETMPt_;
  delete qCalMETMPhi_;
  delete qCalMETMEn_;

  delete qSCN_;
  delete qSCEn_;
  delete qSCEta_;
  delete qSCPhi_;
  delete qSCEtaWidth_;
  delete qSCPhiWidth_;  
  delete qSCEnhfEM_;
  delete qSCEtahfEM_;
  delete qSCPhihfEM_;
  delete qSCEn5x5_;
  delete qSCEta5x5_;
  delete qSCPhi5x5_;
  delete qSCEtaWidth5x5_;
  delete qSCPhiWidth5x5_; 

  delete qCCN_;
  delete qCCEn_;
  delete qCCEta_;
  delete qCCPhi_;
  delete qCCEn5x5_;
  delete qCCEta5x5_;
  delete qCCPhi5x5_;

  delete qPhoN_;
  delete qPhoPt_;
  delete qPhoEta_;
  delete qPhoPhi_;
  delete qPhoEn_;

  delete qPhoe1x5_;
  delete qPhoe2x5_;
  delete qPhoe3x3_;
  delete qPhoe5x5_;
  delete qPhomaxenxtal_;
  delete qPhosigmaeta_;
  delete qPhosigmaIeta_;
  delete qPhor1x5_;
  delete qPhor2x5_;
  delete qPhor9_;

  delete qgedPhoPt_;
  delete qgedPhoEta_;
  delete qgedPhoPhi_;
  delete qgedPhoEn_;

  delete qgedPhoe1x5_;
  delete qgedPhoe2x5_;
  delete qgedPhoe3x3_;
  delete qgedPhoe5x5_;
  delete qgedPhomaxenxtal_;
  delete qgedPhosigmaeta_;
  delete qgedPhosigmaIeta_;
  delete qgedPhor1x5_;
  delete qgedPhor2x5_;
  delete qgedPhor9_;

  delete qMuN_;
  delete qMuPt_;
  delete qMuEta_;
  delete qMuPhi_;
  delete qMuEn_;
  delete qMuCh_;
  delete qMuNCh_;
  delete qMuChi2_;
  
  //TODO
  delete qGsfN_;

  delete qGsfPt_;
  delete qGsfEta_;
  delete qGsfPhi_;

  delete qSigmaIEta_;
  delete qSigmaIPhi_;
  delete qr9_;
  delete qHadOEm_;
  delete qdrSumPt_;
  delete qdrSumEt_;
  delete qeSCOP_;
  delete qecEn_;

  delete qEBenergy_;
  delete qEBtime_;
  delete qEBchi2_;
  delete qEBiEta_;
  delete qEBiPhi_;
  delete qEEenergy_;
  delete qEEtime_;
  delete qEEchi2_;
  delete qEEix_;
  delete qEEiy_;
  delete qESenergy_;
  delete qEStime_;
  delete qESix_;
  delete qESiy_;

  delete qHBHEenergy_ ;
  delete qHBHEtime_ ;
  delete qHBHEauxe_ ;
  delete qHBHEieta_;
  delete qHBHEiphi_;  
  delete qHFenergy_ ;
  delete qHFtime_;
  delete qHFieta_;
  delete qHFiphi_;

  delete qPreShEn_;
  delete qPreShEta_;
  delete qPreShPhi_;
  delete qPreShYEn_;
  delete qPreShYEta_;
  delete qPreShYPhi_;

  delete qNVtx_;
  delete pathRates_;
  delete pathNames_;

  delete subsystemQuality_;

}

AODAnalyzer::~AODAnalyzer()
{

}

void AODAnalyzer::beginLuminosityBlock (const edm::LuminosityBlock & lumi, const edm::EventSetup &eventSetup) 
{
  initialize();

  lumiId_            = lumi.luminosityBlock();
  runId_             = lumi.run();
  lumi_              = 0;
  PU_                = 0;

  isSig_=1;
}

void AODAnalyzer::endLuminosityBlock (const edm::LuminosityBlock & lumi, const edm::EventSetup &eventSetup) 
{

  //compute and store quantiles
  computeMeanAndRms(pVtxChi2_, qpVtxChi2_);
  computeMeanAndRms(pVtxNtr_, qpVtxNtr_);

  computeMeanAndRms(pVtxX_, qpVtxX_);
  computeMeanAndRms(pVtxY_, qpVtxY_);
  computeMeanAndRms(pVtxZ_, qpVtxZ_);

  computeMeanAndRms(gTkPt_, qgTkPt_);
  computeMeanAndRms(gTkEta_,qgTkEta_);
  computeMeanAndRms(gTkPhi_,qgTkPhi_);

  computeMeanAndRms(gTkN_, qgTkN_);
  computeMeanAndRms(gTkChi2_,qgTkChi2_);
  computeMeanAndRms(gTkNHits_,qgTkNHits_);
  computeMeanAndRms(gTkNLay_,qgTkNLay_);

  computeMeanAndRms(globTkPt_, qglobTkPt_);
  computeMeanAndRms(globTkEta_,qglobTkEta_);
  computeMeanAndRms(globTkPhi_,qglobTkPhi_);

  computeMeanAndRms(globTkN_, qglobTkN_);
  computeMeanAndRms(globTkChi2_,qglobTkChi2_);
  computeMeanAndRms(globTkNHits_,qglobTkNHits_);

  computeMeanAndRms(PUEvt_, qPUEvt_);
  computeMeanAndRms(lumiEvt_, qlumiEvt_);

  computeMeanAndRms(PFJetN_, qPFJetN_);
  computeMeanAndRms(PFJetPt_, qPFJetPt_);
  computeMeanAndRms(PFJetEta_,qPFJetEta_);
  computeMeanAndRms(PFJetPhi_,qPFJetPhi_);

  computeMeanAndRms(PFJet4CHSPt_, qPFJet4CHSPt_);
  computeMeanAndRms(PFJet4CHSEta_,qPFJet4CHSEta_);
  computeMeanAndRms(PFJet4CHSPhi_,qPFJet4CHSPhi_);

  computeMeanAndRms(PFJet8CHSPt_, qPFJet8CHSPt_);
  computeMeanAndRms(PFJet8CHSEta_,qPFJet8CHSEta_);
  computeMeanAndRms(PFJet8CHSPhi_,qPFJet8CHSPhi_);

  computeMeanAndRms(PFJetEIPt_, qPFJetEIPt_);
  computeMeanAndRms(PFJetEIEta_,qPFJetEIEta_);
  computeMeanAndRms(PFJetEIPhi_,qPFJetEIPhi_);

  computeMeanAndRms(PFJet8CHSSDPt_, qPFJet8CHSSDPt_);
  computeMeanAndRms(PFJet8CHSSDEta_,qPFJet8CHSSDEta_);
  computeMeanAndRms(PFJet8CHSSDPhi_,qPFJet8CHSSDPhi_);

  computeMeanAndRms(PFJetTopCHSPt_, qPFJetTopCHSPt_);
  computeMeanAndRms(PFJetTopCHSEta_,qPFJetTopCHSEta_);
  computeMeanAndRms(PFJetTopCHSPhi_,qPFJetTopCHSPhi_);

  computeMeanAndRms(PFChMetPt_, qPFChMetPt_);
  computeMeanAndRms(PFChMetPhi_,  qPFChMetPhi_);
  computeMeanAndRms(PFMetPt_, qPFMetPt_);
  computeMeanAndRms(PFMetPhi_,  qPFMetPhi_);
  computeMeanAndRms(nVtx_,    qNVtx_);

  computeMeanAndRms(CalJetN_, qCalJetN_);
  computeMeanAndRms(CalJetPt_, qCalJetPt_);
  computeMeanAndRms(CalJetEta_,qCalJetEta_);
  computeMeanAndRms(CalJetPhi_,qCalJetPhi_);
  computeMeanAndRms(CalJetEn_,qCalJetEn_);

  computeMeanAndRms(CalMETPt_, qCalMETPt_);
  computeMeanAndRms(CalMETPhi_,qCalMETPhi_);
  computeMeanAndRms(CalMETEn_,qCalMETEn_);

  computeMeanAndRms(CalMETBEPt_, qCalMETBEPt_);
  computeMeanAndRms(CalMETBEPhi_,qCalMETBEPhi_);
  computeMeanAndRms(CalMETBEEn_, qCalMETBEEn_);

  computeMeanAndRms(CalMETBEFOPt_, qCalMETBEFOPt_);
  computeMeanAndRms(CalMETBEFOPhi_,qCalMETBEFOPhi_);
  computeMeanAndRms(CalMETBEFOEn_, qCalMETBEFOEn_);

  computeMeanAndRms(CalMETMPt_, qCalMETMPt_);
  computeMeanAndRms(CalMETMPhi_,qCalMETMPhi_);
  computeMeanAndRms(CalMETMEn_, qCalMETMEn_);

  computeMeanAndRms(SCN_, qSCN_);   
  computeMeanAndRms(SCEn_, qSCEn_);   
  computeMeanAndRms(SCEta_, qSCEta_);  
  computeMeanAndRms(SCPhi_, qSCPhi_);
  computeMeanAndRms(SCEtaWidth_, qSCEtaWidth_); 
  computeMeanAndRms(SCPhiWidth_, qSCPhiWidth_);  

  computeMeanAndRms(SCEnhfEM_, qSCEnhfEM_);   
  computeMeanAndRms(SCEtahfEM_, qSCEtahfEM_);  
  computeMeanAndRms(SCPhihfEM_, qSCPhihfEM_); 

  computeMeanAndRms(SCEn5x5_, qSCEn5x5_);   
  computeMeanAndRms(SCEta5x5_, qSCEta5x5_);  
  computeMeanAndRms(SCPhi5x5_, qSCPhi5x5_);
  computeMeanAndRms(SCEtaWidth5x5_, qSCEtaWidth5x5_);  
  computeMeanAndRms(SCPhiWidth5x5_, qSCPhiWidth5x5_);  

  computeMeanAndRms(CCN_, qCCN_);   
  computeMeanAndRms(CCEn_, qCCEn_);   
  computeMeanAndRms(CCEta_, qCCEta_);  
  computeMeanAndRms(CCPhi_, qCCPhi_);
  computeMeanAndRms(CCEn5x5_, qCCEn5x5_);   
  computeMeanAndRms(CCEta5x5_, qCCEta5x5_);  
  computeMeanAndRms(CCPhi5x5_, qCCPhi5x5_); 

  computeMeanAndRms(PhoN_, qPhoN_);
  computeMeanAndRms(PhoPt_, qPhoPt_);
  computeMeanAndRms(PhoEta_,qPhoEta_);
  computeMeanAndRms(PhoPhi_,qPhoPhi_);
  computeMeanAndRms(PhoEn_,qPhoEn_);

  computeMeanAndRms(Phoe1x5_, qPhoe1x5_);
  computeMeanAndRms(Phoe2x5_,qPhoe2x5_);
  computeMeanAndRms(Phoe3x3_,qPhoe3x3_);
  computeMeanAndRms(Phoe5x5_,qPhoe5x5_);
  computeMeanAndRms(Phomaxenxtal_, qPhomaxenxtal_);
  computeMeanAndRms(Phosigmaeta_,  qPhosigmaeta_);
  computeMeanAndRms(PhosigmaIeta_, qPhosigmaIeta_);
  computeMeanAndRms(Phor1x5_, qPhor1x5_);
  computeMeanAndRms(Phor2x5_, qPhor2x5_);
  computeMeanAndRms(Phor9_,   qPhor9_);


  computeMeanAndRms(gedPhoPt_, qgedPhoPt_);
  computeMeanAndRms(gedPhoEta_,qgedPhoEta_);
  computeMeanAndRms(gedPhoPhi_,qgedPhoPhi_);
  computeMeanAndRms(gedPhoEn_,qgedPhoEn_);

  computeMeanAndRms(gedPhoe1x5_, qgedPhoe1x5_);
  computeMeanAndRms(gedPhoe2x5_,qgedPhoe2x5_);
  computeMeanAndRms(gedPhoe3x3_,qgedPhoe3x3_);
  computeMeanAndRms(gedPhoe5x5_,qgedPhoe5x5_);
  computeMeanAndRms(gedPhomaxenxtal_, qgedPhomaxenxtal_);
  computeMeanAndRms(gedPhosigmaeta_,  qgedPhosigmaeta_);
  computeMeanAndRms(gedPhosigmaIeta_, qgedPhosigmaIeta_);
  computeMeanAndRms(gedPhor1x5_, qgedPhor1x5_);
  computeMeanAndRms(gedPhor2x5_, qgedPhor2x5_);
  computeMeanAndRms(gedPhor9_,   qgedPhor9_);

  computeMeanAndRms(MuN_, qMuN_);
  computeMeanAndRms(MuPt_, qMuPt_);
  computeMeanAndRms(MuEta_,qMuEta_);
  computeMeanAndRms(MuPhi_,qMuPhi_);
  computeMeanAndRms(MuEn_,qMuEn_);
  computeMeanAndRms(MuCh_,qMuCh_);
  computeMeanAndRms(MuNCh_,qMuNCh_);
  computeMeanAndRms(MuChi2_,qMuChi2_);

  //TODO
  computeMeanAndRms(GsfN_, qGsfN_);

  computeMeanAndRms(GsfPt_, qGsfPt_);
  computeMeanAndRms(GsfEta_, qGsfEta_);
  computeMeanAndRms(GsfPhi_, qGsfPhi_);

  computeMeanAndRms(SigmaIEta_, qSigmaIEta_);
  computeMeanAndRms(SigmaIPhi_, qSigmaIPhi_);
  computeMeanAndRms(r9_, qr9_);
  computeMeanAndRms(HadOEm_, qHadOEm_);
  computeMeanAndRms(drSumPt_, qdrSumPt_);
  computeMeanAndRms(drSumEt_, qdrSumEt_);
  computeMeanAndRms(eSCOP_, qeSCOP_);
  computeMeanAndRms(ecEn_, qecEn_);

  computeMeanAndRms(EBenergy_, qEBenergy_);
  computeMeanAndRms(EBtime_, qEBtime_);
  computeMeanAndRms(EBchi2_, qEBchi2_);
  computeMeanAndRms(EBiEta_, qEBiEta_);
  computeMeanAndRms(EBiPhi_, qEBiPhi_);

  computeMeanAndRms(EEenergy_, qEEenergy_);
  computeMeanAndRms(EEtime_, qEEtime_);
  computeMeanAndRms(EEchi2_, qEEchi2_);
  computeMeanAndRms(EEix_, qEEix_);
  computeMeanAndRms(EEiy_, qEEiy_);

  computeMeanAndRms(ESenergy_, qESenergy_);
  computeMeanAndRms(EStime_, qEStime_);
  computeMeanAndRms(ESix_, qESix_);
  computeMeanAndRms(ESiy_, qESiy_);

  computeMeanAndRms(HBHEenergy_, qHBHEenergy_);
  computeMeanAndRms(HBHEtime_, qHBHEtime_);
  computeMeanAndRms(HBHEauxe_, qHBHEauxe_);
  computeMeanAndRms(HBHEieta_, qHBHEieta_);
  computeMeanAndRms(HBHEiphi_, qHBHEiphi_);

  computeMeanAndRms(HFenergy_, qHFenergy_);
  computeMeanAndRms(HFtime_, qHFtime_);
  computeMeanAndRms(HFieta_, qHFieta_);
  computeMeanAndRms(HFiphi_, qHFiphi_);

  computeMeanAndRms(PreShEn_, qPreShEn_);   
  computeMeanAndRms(PreShEta_, qPreShEta_);  
  computeMeanAndRms(PreShPhi_, qPreShPhi_);  
  computeMeanAndRms(PreShYEn_, qPreShYEn_);   
  computeMeanAndRms(PreShYEta_, qPreShYEta_);  
  computeMeanAndRms(PreShYPhi_, qPreShYPhi_);  

  bool isInt;
  bool debug=false;

  if (debug) std::cout << "pVtxNtr_" << std::endl;

  computeQuantiles(pVtxNtr_, qpVtxNtr_, quantiles_, isInt=true);
  computeQuantiles(pVtxChi2_, qpVtxChi2_, quantiles_, isInt=false);

  computeQuantiles(pVtxX_, qpVtxX_, quantiles_, isInt=false);
  computeQuantiles(pVtxY_, qpVtxY_, quantiles_, isInt=false);
  computeQuantiles(pVtxZ_, qpVtxZ_, quantiles_, isInt=false);

  computeQuantiles(gTkPt_, qgTkPt_, quantiles_, isInt=false);
  computeQuantiles(gTkEta_,qgTkEta_,quantiles_, isInt=false);
  computeQuantiles(gTkPhi_,qgTkPhi_,quantiles_, isInt=false);

  if (debug) std::cout << "gTkN_" << std::endl;
  computeQuantiles(gTkN_, qgTkN_, quantiles_, isInt=true);
  computeQuantiles(gTkChi2_,qgTkChi2_,quantiles_, isInt=false);
  if (debug) std::cout << "gTkHoits_" << std::endl;
  computeQuantiles(gTkNHits_,qgTkNHits_,quantiles_, isInt=true);
  computeQuantiles(gTkNLay_,qgTkNLay_,quantiles_, isInt=true);

  computeQuantiles(globTkPt_, qglobTkPt_, quantiles_, isInt=false);
  computeQuantiles(globTkEta_,qglobTkEta_,quantiles_, isInt=false);
  computeQuantiles(globTkPhi_,qglobTkPhi_,quantiles_, isInt=false);

  if (debug) std::cout << "globN_" << std::endl;
  computeQuantiles(globTkN_, qglobTkN_, quantiles_, isInt=true);
  computeQuantiles(globTkChi2_,qglobTkChi2_,quantiles_, isInt=false);
  if (debug) std::cout << "globHits_" << std::endl;
  computeQuantiles(globTkNHits_,qglobTkNHits_,quantiles_, isInt=true);

  computeQuantiles(PUEvt_, qPUEvt_, quantiles_, isInt=false);
  computeQuantiles(lumiEvt_, qlumiEvt_, quantiles_, isInt=false);

  computeQuantiles(PFJetN_,  qPFJetN_, quantiles_ , isInt=true);
  computeQuantiles(PFJetPt_, qPFJetPt_, quantiles_, isInt=false);
  computeQuantiles(PFJetEta_,qPFJetEta_,quantiles_, isInt=false);
  computeQuantiles(PFJetPhi_,qPFJetPhi_,quantiles_, isInt=false);

  computeQuantiles(PFJet4CHSPt_, qPFJet4CHSPt_, quantiles_, isInt=false);
  computeQuantiles(PFJet4CHSEta_,qPFJet4CHSEta_,quantiles_, isInt=false);
  computeQuantiles(PFJet4CHSPhi_,qPFJet4CHSPhi_,quantiles_, isInt=false);

  computeQuantiles(PFJet8CHSPt_, qPFJet8CHSPt_, quantiles_, isInt=false);
  computeQuantiles(PFJet8CHSEta_,qPFJet8CHSEta_,quantiles_, isInt=false);
  computeQuantiles(PFJet8CHSPhi_,qPFJet8CHSPhi_,quantiles_, isInt=false);

  computeQuantiles(PFJetEIPt_, qPFJetEIPt_, quantiles_, isInt=false);
  computeQuantiles(PFJetEIEta_,qPFJetEIEta_,quantiles_, isInt=false);
  computeQuantiles(PFJetEIPhi_,qPFJetEIPhi_,quantiles_, isInt=false);

  computeQuantiles(PFJet8CHSSDPt_, qPFJet8CHSSDPt_, quantiles_, isInt=false);
  computeQuantiles(PFJet8CHSSDEta_,qPFJet8CHSSDEta_,quantiles_, isInt=false);
  computeQuantiles(PFJet8CHSSDPhi_,qPFJet8CHSSDPhi_,quantiles_, isInt=false);

  computeQuantiles(PFJetTopCHSPt_, qPFJetTopCHSPt_, quantiles_, isInt=false);
  computeQuantiles(PFJetTopCHSEta_,qPFJetTopCHSEta_,quantiles_, isInt=false);
  computeQuantiles(PFJetTopCHSPhi_,qPFJetTopCHSPhi_,quantiles_, isInt=false);      

  computeQuantiles(PFChMetPt_, qPFChMetPt_,     quantiles_, isInt=false);
  computeQuantiles(PFChMetPhi_,qPFChMetPhi_,    quantiles_, isInt=false);
  computeQuantiles(PFMetPt_, qPFMetPt_,     quantiles_, isInt=false);
  computeQuantiles(PFMetPhi_,qPFMetPhi_,    quantiles_, isInt=false);
  
  if (debug) std::cout << "NVtx_" << std::endl;
  computeQuantiles(nVtx_,    qNVtx_,    quantiles_, isInt=true);

  computeQuantiles(CalJetN_, qCalJetN_, quantiles_, isInt=true);
  computeQuantiles(CalJetPt_, qCalJetPt_, quantiles_, isInt=false);
  computeQuantiles(CalJetEta_,qCalJetEta_,quantiles_, isInt=false);
  computeQuantiles(CalJetPhi_,qCalJetPhi_,quantiles_, isInt=false);
  computeQuantiles(CalJetEn_,qCalJetEn_,  quantiles_, isInt=false);
  computeQuantiles(CalMETPt_, qCalMETPt_, quantiles_, isInt=false);
  computeQuantiles(CalMETPhi_,qCalMETPhi_,quantiles_, isInt=false);
  computeQuantiles(CalMETEn_,qCalMETEn_,  quantiles_, isInt=false);

  computeQuantiles(CalMETBEPt_, qCalMETBEPt_, quantiles_, isInt=false);
  computeQuantiles(CalMETBEPhi_,qCalMETBEPhi_,quantiles_, isInt=false);
  computeQuantiles(CalMETBEEn_, qCalMETBEEn_,  quantiles_, isInt=false);

  computeQuantiles(CalMETBEFOPt_, qCalMETBEFOPt_, quantiles_, isInt=false);
  computeQuantiles(CalMETBEFOPhi_,qCalMETBEFOPhi_,quantiles_, isInt=false);
  computeQuantiles(CalMETBEFOEn_, qCalMETBEFOEn_,  quantiles_, isInt=false);

  computeQuantiles(CalMETMPt_, qCalMETMPt_, quantiles_, isInt=false);
  computeQuantiles(CalMETMPhi_,qCalMETMPhi_,quantiles_, isInt=false);
  computeQuantiles(CalMETMEn_, qCalMETMEn_,  quantiles_, isInt=false);

  computeQuantiles(SCN_, qSCN_,       quantiles_, isInt=true);
  computeQuantiles(SCEn_, qSCEn_,       quantiles_, isInt=false);
  computeQuantiles(SCEta_, qSCEta_,     quantiles_, isInt=false);
  computeQuantiles(SCPhi_, qSCPhi_,     quantiles_, isInt=false);
  computeQuantiles(SCEtaWidth_, qSCEtaWidth_,     quantiles_, isInt=false);
  computeQuantiles(SCPhiWidth_, qSCPhiWidth_,     quantiles_, isInt=false);

  computeQuantiles(SCEnhfEM_, qSCEnhfEM_,       quantiles_, isInt=false);
  computeQuantiles(SCEtahfEM_, qSCEtahfEM_,     quantiles_, isInt=false);
  computeQuantiles(SCPhihfEM_, qSCPhihfEM_,     quantiles_, isInt=false);
  
  computeQuantiles(SCEn5x5_, qSCEn5x5_,       quantiles_, isInt=false);
  computeQuantiles(SCEta5x5_, qSCEta5x5_,     quantiles_, isInt=false);
  computeQuantiles(SCPhi5x5_, qSCPhi5x5_,     quantiles_, isInt=false);
  computeQuantiles(SCEtaWidth5x5_, qSCEtaWidth5x5_,     quantiles_, isInt=false);
  computeQuantiles(SCPhiWidth5x5_, qSCPhiWidth5x5_,     quantiles_, isInt=false);

  computeQuantiles(CCN_, qCCN_,         quantiles_, isInt=true);
  computeQuantiles(CCEn_, qCCEn_,       quantiles_, isInt=false);
  computeQuantiles(CCEta_, qCCEta_,     quantiles_, isInt=false);
  computeQuantiles(CCPhi_, qCCPhi_,     quantiles_, isInt=false);
  computeQuantiles(CCEn5x5_, qCCEn5x5_,       quantiles_, isInt=false);
  computeQuantiles(CCEta5x5_, qCCEta5x5_,     quantiles_, isInt=false);
  computeQuantiles(CCPhi5x5_, qCCPhi5x5_,     quantiles_, isInt=false);

  computeQuantiles(PhoN_, qPhoN_, quantiles_, isInt=true);
  computeQuantiles(PhoPt_, qPhoPt_, quantiles_, isInt=false);
  computeQuantiles(PhoEta_,qPhoEta_,quantiles_, isInt=false);
  computeQuantiles(PhoPhi_,qPhoPhi_,quantiles_, isInt=false);
  computeQuantiles(PhoEn_,qPhoEn_,quantiles_, isInt=false);

  computeQuantiles(Phoe1x5_, qPhoe1x5_, quantiles_, isInt=false);
  computeQuantiles(Phoe2x5_,qPhoe2x5_,quantiles_, isInt=false);
  computeQuantiles(Phoe3x3_,qPhoe3x3_,quantiles_, isInt=false);
  computeQuantiles(Phoe5x5_,qPhoe5x5_,quantiles_, isInt=false);
  computeQuantiles(Phomaxenxtal_, qPhomaxenxtal_, quantiles_, isInt=false);
  computeQuantiles(Phosigmaeta_,qPhosigmaeta_,quantiles_, isInt=false);
  computeQuantiles(PhosigmaIeta_,qPhosigmaIeta_,quantiles_, isInt=false);
  computeQuantiles(Phor1x5_,qPhor1x5_,quantiles_, isInt=false);
  computeQuantiles(Phor2x5_, qPhor2x5_, quantiles_, isInt=false);
  computeQuantiles(Phor9_,qPhor9_,quantiles_, isInt=false);

  computeQuantiles(gedPhoPt_, qgedPhoPt_, quantiles_, isInt=false);
  computeQuantiles(gedPhoEta_,qgedPhoEta_,quantiles_, isInt=false);
  computeQuantiles(gedPhoPhi_,qgedPhoPhi_,quantiles_, isInt=false);
  computeQuantiles(gedPhoEn_,qgedPhoEn_,quantiles_, isInt=false);

  computeQuantiles(gedPhoe1x5_, qgedPhoe1x5_, quantiles_, isInt=false);
  computeQuantiles(gedPhoe2x5_,qgedPhoe2x5_,quantiles_, isInt=false);
  computeQuantiles(gedPhoe3x3_,qgedPhoe3x3_,quantiles_, isInt=false);
  computeQuantiles(gedPhoe5x5_,qgedPhoe5x5_,quantiles_, isInt=false);
  computeQuantiles(gedPhomaxenxtal_, qgedPhomaxenxtal_, quantiles_, isInt=false);
  computeQuantiles(gedPhosigmaeta_,qgedPhosigmaeta_,quantiles_, isInt=false);
  computeQuantiles(gedPhosigmaIeta_,qgedPhosigmaIeta_,quantiles_, isInt=false);
  computeQuantiles(gedPhor1x5_,qgedPhor1x5_,quantiles_, isInt=false);
  computeQuantiles(gedPhor2x5_, qgedPhor2x5_, quantiles_, isInt=false);
  computeQuantiles(gedPhor9_,qgedPhor9_,quantiles_, isInt=false);

  computeQuantiles(MuN_, qMuN_, quantiles_, isInt=true);
  computeQuantiles(MuPt_, qMuPt_, quantiles_, isInt=false);
  computeQuantiles(MuEta_,qMuEta_,quantiles_, isInt=false);
  computeQuantiles(MuPhi_,qMuPhi_,quantiles_, isInt=false);
  computeQuantiles(MuEn_,qMuEn_,quantiles_, isInt=false);
  computeQuantiles(MuCh_,qMuCh_,quantiles_, isInt=false);
  computeQuantiles(MuNCh_,qMuNCh_,quantiles_, isInt=true);
  computeQuantiles(MuChi2_,qMuChi2_,quantiles_, isInt=false);
  
  computeQuantiles(GsfN_, qGsfN_, quantiles_, isInt=true);

  computeQuantiles(GsfPt_, qGsfPt_, quantiles_, isInt=false);
  computeQuantiles(GsfEta_, qGsfEta_, quantiles_, isInt=false);
  computeQuantiles(GsfPhi_, qGsfPhi_, quantiles_, isInt=false);

  computeQuantiles(SigmaIEta_, qSigmaIEta_, quantiles_, isInt=false);
  computeQuantiles(SigmaIPhi_, qSigmaIPhi_, quantiles_, isInt=false);
  computeQuantiles(r9_, qr9_, quantiles_, isInt=false);
  computeQuantiles(HadOEm_, qHadOEm_, quantiles_, isInt=false);
  computeQuantiles(drSumPt_, qdrSumPt_, quantiles_, isInt=false);
  computeQuantiles(drSumEt_, qdrSumEt_, quantiles_, isInt=false);
  computeQuantiles(eSCOP_, qeSCOP_, quantiles_, isInt=false);
  computeQuantiles(ecEn_, qecEn_, quantiles_, isInt=false);

  computeQuantiles(EBenergy_, qEBenergy_, quantiles_, isInt=false);
  computeQuantiles(EBtime_, qEBtime_, quantiles_, isInt=false);
  computeQuantiles(EBchi2_, qEBchi2_, quantiles_, isInt=false);
  computeQuantiles(EBiEta_, qEBiEta_, quantiles_, isInt=false);
  computeQuantiles(EBiPhi_, qEBiPhi_, quantiles_, isInt=false);

  computeQuantiles(EEenergy_, qEEenergy_, quantiles_, isInt=false);
  computeQuantiles(EEtime_, qEEtime_, quantiles_, isInt=false);
  computeQuantiles(EEchi2_, qEEchi2_, quantiles_, isInt=false);
  computeQuantiles(EEix_, qEEix_, quantiles_, isInt=false);
  computeQuantiles(EEiy_, qEEiy_, quantiles_, isInt=false);

  computeQuantiles(ESenergy_, qESenergy_, quantiles_, isInt=false);
  computeQuantiles(EStime_, qEStime_, quantiles_, isInt=false);
  computeQuantiles(ESix_, qESix_, quantiles_, isInt=false);
  computeQuantiles(ESiy_, qESiy_, quantiles_, isInt=false);

  computeQuantiles(HBHEenergy_, qHBHEenergy_, quantiles_, isInt=false);
  computeQuantiles(HBHEtime_, qHBHEtime_, quantiles_, isInt=false);
  computeQuantiles(HBHEauxe_, qHBHEauxe_, quantiles_, isInt=false);
  computeQuantiles(HBHEieta_, qHBHEieta_, quantiles_, isInt=false);
  computeQuantiles(HBHEiphi_, qHBHEiphi_, quantiles_, isInt=false);

  computeQuantiles(HFenergy_, qHFenergy_, quantiles_, isInt=false);
  computeQuantiles(HFtime_, qHFtime_, quantiles_, isInt=false);
  computeQuantiles(HFieta_, qHFieta_, quantiles_, isInt=false);
  computeQuantiles(HFiphi_, qHFiphi_, quantiles_, isInt=false);

  computeQuantiles(PreShEn_, qPreShEn_,         quantiles_, isInt=false);
  computeQuantiles(PreShEta_, qPreShEta_,       quantiles_, isInt=false);
  computeQuantiles(PreShPhi_, qPreShPhi_,       quantiles_, isInt=false);
  computeQuantiles(PreShYEn_, qPreShYEn_,       quantiles_, isInt=false);
  computeQuantiles(PreShYEta_, qPreShYEta_,     quantiles_, isInt=false);
  computeQuantiles(PreShYPhi_, qPreShYPhi_,     quantiles_, isInt=false);

  PU_=float(PU_/LSeventCounter);//average PU in the LS
  lumi_=float(lumi_/LSeventCounter);

  //if (qNVtx_->size()>=2)  std::cout << " qNvtx " << qNVtx_->at(0) << " " << qNVtx_->at(1) << std::endl;

  for(std::map<std::string,int>::const_iterator itr = rateMap.begin(); itr != rateMap.end(); ++itr)
    {
      pathNames_->push_back(itr->first);
      pathRates_->push_back(itr->second/lumi_);
    }

  //fill tree once per LS
  outTree_->Fill();

}


void AODAnalyzer::beginRun (const edm::Run &run, const edm::EventSetup &eventSetup) 
{
 bool isConfigChanged = false;
 edm::InputTag myTag("TriggerResults::HLT");
 hltConfigProvider_.init(run, eventSetup, myTag.process(), isConfigChanged);
}


void AODAnalyzer::analyze (const edm::Event &event, const edm::EventSetup &eventSetup) 
{
  ++LSeventCounter;

  edm::Handle<LumiScalersCollection> LScalers;
  event.getByToken(lScalers_,LScalers);
  if(LScalers.isValid())
    {
      float lumiEvt=LScalers->begin()->instantLumi();
      float PUEvt=LScalers->begin()->pileup();
      fillPUandLumiEvt(PUEvt,lumiEvt);

      lumi_+=lumiEvt;
      PU_+=PUEvt;
    }
 
  //fill Jets
  edm::Handle<reco::PFJetCollection> PFJets;
  event.getByToken(PFJetToken_,PFJets);
  if(PFJets.isValid())
    {
      fillJets(PFJets, std::string("PF")); 
    }

  edm::Handle<reco::TrackCollection> gTracksh;
  event.getByToken(gTkToken_,gTracksh);
  if(gTracksh.isValid())
    fillgTracks(gTracksh, std::string(""));

 edm::Handle<reco::TrackCollection> globTracksh;
  event.getByToken(globTkToken_,globTracksh);
  if(globTracksh.isValid())
    fillglobTracks(globTracksh, std::string(""));

  //fill PFJet4CHS Jets
  edm::Handle<reco::PFJetCollection> PF4CHSJets;
  event.getByToken(PFJet4CHSToken_,PF4CHSJets);
  if(PF4CHSJets.isValid())
    fill4CHSJets(PF4CHSJets, std::string("PF"));

    //fill PFJet8CHS Jets
  edm::Handle<reco::PFJetCollection> PF8CHSJets;
  event.getByToken(PFJet8CHSToken_,PF8CHSJets);
  if(PF8CHSJets.isValid())
    fill8CHSJets(PF8CHSJets, std::string("PF"));

  //fill PFJetEI Jets
  edm::Handle<reco::PFJetCollection> PFEIJets;
  event.getByToken(PFJetEIToken_,PFEIJets);
  if(PFEIJets.isValid())
    fillEIJets(PFEIJets, std::string("PF"));

  //fill PFJet8CHSSoftDrop Jets
  edm::Handle<reco::PFJetCollection> PF8CHSSoftDropJets;
  event.getByToken(PFJet8CHSSoftDropToken_,PF8CHSSoftDropJets);
  if(PF8CHSSoftDropJets.isValid())
    fill8CHSoftDropJets(PF8CHSSoftDropJets, std::string("PF"));

  //fill PFJetTopCHS Jets
  edm::Handle<reco::PFJetCollection> PFTopCHSJets;
  event.getByToken(PFJetTopCHSToken_,PFTopCHSJets);
  if(PFTopCHSJets.isValid())
    fillTopCHSJets(PFTopCHSJets, std::string("PF"));

  //fill PFMet
  edm::Handle<reco::PFMETCollection> pfmetlocalv;
  event.getByToken(PFMETToken_, pfmetlocalv);
  if(pfmetlocalv.isValid())
    fillPFMets(pfmetlocalv);
  
  //fill Calo Jet
  edm::Handle<reco::CaloJetCollection> calojetlocalv;
  event.getByToken(CaloJetToken_, calojetlocalv);
  if(calojetlocalv.isValid())
    fillCaloJets(calojetlocalv);

  //fill calomet
  edm::Handle<reco::CaloMETCollection> caloMETlocalv;
  event.getByToken(CaloMETToken_, caloMETlocalv);
  if(caloMETlocalv.isValid())
    fillCaloMETs(caloMETlocalv);

  //fill calomet BE
  edm::Handle<reco::CaloMETCollection> caloMETBElocalv;
  event.getByToken(CaloMETBEToken_, caloMETBElocalv);
  if(caloMETBElocalv.isValid())
    fillCaloMETBEs(caloMETBElocalv);

  //fill calomet BEFO
  edm::Handle<reco::CaloMETCollection> caloMETBEFOlocalv;
  event.getByToken(CaloMETBEFOToken_, caloMETBEFOlocalv);
  if(caloMETBEFOlocalv.isValid())
    fillCaloMETBEFOs(caloMETBEFOlocalv);

  //fill calomet M
  edm::Handle<reco::CaloMETCollection> caloMETMlocalv;
  event.getByToken(CaloMETMToken_, caloMETMlocalv);
  if(caloMETMlocalv.isValid())
    fillCaloMETMs(caloMETMlocalv);

  //fill vtx
  edm::Handle<reco::VertexCollection> recVtxs;
  event.getByToken(vtxToken_,recVtxs);
  if(recVtxs.isValid()){
    nVtx_->push_back(recVtxs->size());

    reco::VertexCollection::const_iterator i = recVtxs->begin();
    for(;i != recVtxs->end(); i++){
      
      pVtxNtr_->push_back(i->nTracks());
      pVtxChi2_->push_back(i->normalizedChi2());
      pVtxX_->push_back(i->x());
      pVtxY_->push_back(i->y());
      pVtxZ_->push_back(i->z());

    }

  }

  //Bits
  edm::Handle<edm::TriggerResults> triggerBits;
  event.getByToken(triggerBits_, triggerBits);
  
  //Fill SuperCluster
  edm::Handle<reco::SuperClusterCollection> SuperClusterlocalv;
  event.getByToken(SuperClusterToken_, SuperClusterlocalv);
  if(SuperClusterlocalv.isValid())
    fillSC(SuperClusterlocalv);

  edm::Handle<reco::SuperClusterCollection> SuperClusterhfEMlocalv;
  event.getByToken(SuperClusterhfEMToken_, SuperClusterhfEMlocalv);
  if(SuperClusterhfEMlocalv.isValid())
    fillSChfEM(SuperClusterhfEMlocalv);

  edm::Handle<reco::SuperClusterCollection> SuperCluster5x5localv;
  event.getByToken(SuperCluster5x5Token_, SuperCluster5x5localv);
  if(SuperCluster5x5localv.isValid())
    fillSC5x5(SuperCluster5x5localv);

  //Fill CaloCluster
  edm::Handle<reco::CaloClusterCollection> CaloClusterlocalv;
  event.getByToken(CaloClusterToken_, CaloClusterlocalv);
  if(CaloClusterlocalv.isValid())
    fillCC(CaloClusterlocalv);

  edm::Handle<reco::CaloClusterCollection> CaloCluster5x5localv;
  event.getByToken(CaloCluster5x5Token_, CaloCluster5x5localv);
  if(CaloCluster5x5localv.isValid())
    fillCC5x5(CaloCluster5x5localv);

  edm::Handle<reco::PhotonCollection> photonlocalv;
  event.getByToken(PhotonToken_, photonlocalv);
  if(photonlocalv.isValid())
    fillPhotons(photonlocalv);

  edm::Handle<reco::PhotonCollection> gedphotonlocalv;
  event.getByToken(gedPhotonToken_, gedphotonlocalv);
  if(gedphotonlocalv.isValid())
    fillgedPhotons(gedphotonlocalv);

  edm::Handle<reco::MuonCollection> muonlocalv;
  event.getByToken(MuonToken_, muonlocalv);
  if(muonlocalv.isValid())
    fillMuons(muonlocalv);

  //fill GsF
  edm::Handle<reco::GsfElectronCollection> GsfElectronlocalv;
  event.getByToken(GsfElectronToken_, GsfElectronlocalv);
  if(GsfElectronlocalv.isValid())
     fillGsf(GsfElectronlocalv);

  //fill EcalRec EB    
  edm::Handle<EcalRecHitCollection> ebRHs;   
  event.getByToken(ebRHSrcToken_, ebRHs);
  if(ebRHs.isValid())
    fillEBrecHit(ebRHs);

  //fill EcalRec EE
  edm::Handle<EcalRecHitCollection> eeRHs;
  event.getByToken(eeRHSrcToken_, eeRHs);
  if(eeRHs.isValid())
    fillEErecHit(eeRHs);

  //fill EcalRec ES
  edm::Handle<EcalRecHitCollection> esRHs;
  event.getByToken(esRHSrcToken_, esRHs);
  if(esRHs.isValid())
    fillESrecHit(esRHs);

  //fill hbhereco  
  edm::Handle<HBHERecHitCollection> hbheRHs;    
  event.getByToken(hbheRHcToken_, hbheRHs);
  if(hbheRHs.isValid())
    fillHBHErecHit(hbheRHs);

  //fill hfreco
  edm::Handle<HFRecHitCollection> hfRHs;
  event.getByToken(hfRHcToken_, hfRHs);
  if(hfRHs.isValid())
    fillHFrecHit(hfRHs);

  // fill PreshowerCluster
  edm::Handle<reco::PreshowerClusterCollection> prShs;
  event.getByToken(preshowerXToken_, prShs);
  if(prShs.isValid())
    fillPreshowerCluster(prShs);

  edm::Handle<reco::PreshowerClusterCollection> prShYs;
  event.getByToken(preshowerYToken_, prShYs);
  if(prShYs.isValid())
    fillPreshowerClusterY(prShYs);

 //PLAYGROUND-------------------------

   const edm::TriggerNames &names = event.triggerNames(*triggerBits);
   const std::vector<std::string>& triggerNames = hltConfigProvider_.triggerNames();
   for (size_t ts = 0; ts < triggerNames.size(); ts++) {
       std::string trig = triggerNames[ts]; //--adding because of test
       //       std::cout << trig << std::endl;
    const unsigned int prescaleSize = hltConfigProvider_.prescaleSize();
        for (unsigned int ps = 0; ps < prescaleSize; ps++) 
          {
            const unsigned int prescaleValue = hltConfigProvider_.prescaleValue(ps, trig);
               if(rateMap.find(names.triggerName(ts)) != rateMap.end())
                  rateMap[names.triggerName(ts)] += prescaleValue;
               else
                  rateMap[names.triggerName(ts)] = prescaleValue;
                // std::cout << prescaleValue << " ";  //adding because of test
          }
      }

 //PLAYGROUND ENDS...-------------------------------------
 
}

DEFINE_FWK_MODULE(AODAnalyzer);
