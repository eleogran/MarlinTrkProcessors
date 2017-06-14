#ifndef TruthTrackFinder_h
#define TruthTrackFinder_h 1

#include "marlin/Processor.h"

#include "lcio.h"

#include <string>
#include <vector>
#include <map>

#include <gsl/gsl_rng.h>
#include "DDRec/Surface.h"
#include <EVENT/LCCollection.h>
#include "MarlinTrk/IMarlinTrkSystem.h"
#include "EVENT/TrackerHit.h"
#include <UTIL/CellIDDecoder.h>

#include <AIDA/AIDA.h>

using namespace lcio ;
using namespace marlin ;
using namespace AIDA ;

class TruthTrackFinder : public Processor {
		
 public:
	
  virtual Processor*  newProcessor() { return new TruthTrackFinder ; }
	
  TruthTrackFinder() ;
	
  // Initialisation - run at the beginning to start histograms, etc.
  virtual void init() ;
	
  // Called at the beginning of every run
  virtual void processRunHeader( LCRunHeader* run ) ;
	
  // Run over each event - the main algorithm
  virtual void processEvent( LCEvent * evt ) ;
	
  // Run at the end of each event
  virtual void check( LCEvent * evt ) ;
	
  // Called at the very end for cleanup, histogram saving, etc.
  virtual void end() ;
	
  // Call to get collections
  void getCollection(LCCollection*&, std::string, LCEvent*);
	
  // Get the subdetector ID from a hit
  int getSubdetector(TrackerHit*, UTIL::BitField64&);

  // Get the layer ID from a hit
  int getLayer(TrackerHit*, UTIL::BitField64&);

  // Remove hits in the same layer of the same subdetector
  TrackerHitVec removeHitsSameLayer(std::vector<TrackerHit*>, UTIL::BitField64&);

	
 protected:
	
  // Collection names for (in/out)put
  std::vector<std::string> m_inputTrackerHitCollections ;
  std::vector<std::string> m_inputTrackerHitRelationCollections ;
  std::string m_inputParticleCollection ;
  std::string m_outputTrackCollection ;
  std::string m_outputTrackRelationCollection;

  bool m_useTruthInPrefit;
  bool m_fitForward;
 	
  // Run and event counters
  int m_eventNumber ;
  int m_runNumber ;
  
  // Track fit factory
  MarlinTrk::IMarlinTrkSystem* trackFactory;

  // Track fit parameters
  double m_initialTrackError_d0;
  double m_initialTrackError_phi0;
  double m_initialTrackError_omega;
  double m_initialTrackError_z0;
  double m_initialTrackError_tanL;
  double m_maxChi2perHit;
  double m_magneticField;
  int m_fitFails;

		
} ;

bool sort_by_radius(EVENT::TrackerHit*, EVENT::TrackerHit*);


#endif



