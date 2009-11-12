// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iomanip>
#include <sstream>
#include <iostream>
// STDAIR
#include <stdair/bom/AirlineFeatureSet.hpp>
// AIRSCHED
#include <airsched/basic/BasConst_AIRSCHED_Service.hpp>
#include <airsched/bom/BomRoot.hpp>
#include <airsched/factory/FacAIRSCHEDServiceContext.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/command/ScheduleParser.hpp>
#include <airsched/service/AIRSCHED_ServiceContext.hpp>
#include <airsched/service/Logger.hpp>
#include <airsched/AIRSCHED_Service.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::AIRSCHED_Service () {
    // Initialise the context
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext = 
      FacAIRSCHEDServiceContext::instance().create ();
    _airschedServiceContext = &lAIRSCHED_ServiceContext;
  }

  // //////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::AIRSCHED_Service (const AIRSCHED_Service& iService) :
    _airschedServiceContext (iService._airschedServiceContext) {
  }

  // //////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::AIRSCHED_Service (std::ostream& ioLogStream) {
    // Initialise the context
    init (ioLogStream);
  }

  // //////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::~AIRSCHED_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::init (std::ostream& ioLogStream) {
    // Set the log file
    logInit (LOG::DEBUG, ioLogStream);

    // Initialise the context
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext = 
      FacAIRSCHEDServiceContext::instance().create ();
    _airschedServiceContext = &lAIRSCHED_ServiceContext;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::logInit (const LOG::EN_LogLevel iLogLevel,
                                    std::ostream& ioLogOutputFile) {
    Logger::instance().setLogParameters (iLogLevel, ioLogOutputFile);
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::
  addTravelSolution  (const std::string& iDepartureAirport,
                      const std::string& iArrivalAirport,
                      const Date_T& iDepartureDate,
                      const Duration_T& iDepartureTime,
                      const Duration_T& iArrivalTime,
                      const Duration_T& iDuration,
                      const bool iRefundability,
                      const std::string& iAirlineCode,
                      const std::string& iCabinCode,
                      const int iFlightNumber, double iFare,
                      int iStopsNumber,  bool iSNS, bool iChangeability) {
    assert (_airschedServiceContext != NULL);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::simulate()  {
    // add travel solutions to the travelsolution holder
    assert (_airschedServiceContext != NULL);

    // AF404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), false,
                       "AF", "ECO", 404, 200, 0, false, false);
    
    // AF404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), true, "AF",
                       "ECO", 404, 200, 0, false, false);
    
    // BA404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), false, "BA",
                       "ECO", 404, 200, 0, true, false);
    
    // BA404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), true, "BA",
                       "ECO", 404, 200, 0, true, false);

    // Call the underlying Use Case (command)
    Simulator::simulate ();
  }


  // //////////////////////////////////////////////////////////////////////
  stdair::BomRoot& AIRSCHED_Service::
  generateInventories (const std::string& iScheduleInputFilename,
                       const stdair::AirlineFeatureSet& iAirlineFeatureSet,
                       const stdair::Date_T& iStartAnalysisDate) {
    
    // Parse the schedule input file, and generate the Inventories
    stdair::BomRoot& oBomRoot =
      ScheduleParser::generateInventories (iScheduleInputFilename,
                                           iAirlineFeatureSet,
                                           iStartAnalysisDate);
    
    // DEBUG
    /* AIRSCHED_LOG_DEBUG ("Generated BomRoot:");
       oBomRoot.display();*/
    
    return oBomRoot;
  }
  
}
