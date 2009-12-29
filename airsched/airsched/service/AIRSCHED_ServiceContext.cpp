// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// AIRSCHED
#include <airsched/basic/BasConst_AIRSCHED_Service.hpp>
#include <airsched/factory/FacSupervisor.hpp>
#include <airsched/service/AIRSCHED_ServiceContext.hpp>
#include <airsched/command/FileMgr.hpp>

namespace AIRSCHED {
  
  // //////////////////////////////////////////////////////////////////////
  AIRSCHED_ServiceContext::AIRSCHED_ServiceContext () {
    init ();
  }
  
  // //////////////////////////////////////////////////////////////////////
  AIRSCHED_ServiceContext::
  AIRSCHED_ServiceContext (const AIRSCHED_ServiceContext&) : _bomRoot (NULL) {
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  AIRSCHED_ServiceContext::~AIRSCHED_ServiceContext() {
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_ServiceContext::init () {
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_ServiceContext::
  addTravelSolution (std::string dAirport, std::string aAirport,
                     Date_T depDate,
                     Duration_T depTime, Duration_T arTime, Duration_T dur,
                     bool Ref, std::string airline, std::string cabin,
                     int flightNum, double fare, int lagsNum, bool SNS,
                     bool change) {
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_ServiceContext::
  readFromInputFile (const std::string& iInputFileName) {

    FileMgr::readAndProcessTravelSolutionInputFile (iInputFileName);
  }

}
