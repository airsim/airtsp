// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
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
  stdair::BomRoot& AIRSCHED_ServiceContext::getBomRoot () const {
    assert (_bomRoot != NULL);
    return *_bomRoot;
  }

  // //////////////////////////////////////////////////////////////////////
  const stdair::AirlineFeatureSet& AIRSCHED_ServiceContext::
  getAirlineFeatureSet () const {
    assert (_airlineFeatureSet != NULL);
    return *_airlineFeatureSet;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AIRSCHED_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "AIRSCHED_ServiceContext: " << std::endl
         << "Start analysis date: " << _startAnalysisDate
         << std::endl;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AIRSCHED_ServiceContext::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_ServiceContext::
  addTravelSolution (const stdair::AirportCode_T& iDepartureAirport,
                     const stdair::AirportCode_T& iArrivalAirport,
                     const stdair::Date_T& iDepartureDate,
                     const stdair::Duration_T& iDepartureTime,
                     const stdair::Duration_T& iArrivalTime,
                     const stdair::Duration_T& iDuration,
                     const bool iRefundability,
                     const stdair::AirlineCode_T& iAirlineCode,
                     const stdair::CabinCode_T& iCabinCode,
                     const stdair::FlightNumber_T& iFlightNumber,
                     const stdair::Fare_T& iFare,
                     int iStopsNumber, bool iSNS, bool iChangeability) {
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_ServiceContext::
  readFromInputFile (const std::string& iInputFileName) {

    FileMgr::readAndProcessTravelSolutionInputFile (iInputFileName);
  }

}
