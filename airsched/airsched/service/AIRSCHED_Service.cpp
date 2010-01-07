// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
#include <iomanip>
// STDAIR
#include <stdair/bom/AirlineFeatureSet.hpp>
// AIRSCHED
#include <airsched/basic/BasConst_AIRSCHED_Service.hpp>
#include <airsched/bom/BomRoot.hpp>
#include <airsched/factory/FacAIRSCHEDServiceContext.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/command/ScheduleParser.hpp>
#include <airsched/command/NetworkGenerator.hpp>
#include <airsched/service/AIRSCHED_ServiceContext.hpp>
#include <airsched/service/Logger.hpp>
#include <airsched/AIRSCHED_Service.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::AIRSCHED_Service () {
    // Initialise the context
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext = 
      FacAIRSCHEDServiceContext::instance().create ();
    _airschedServiceContext = &lAIRSCHED_ServiceContext;
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::AIRSCHED_Service (const AIRSCHED_Service& iService) :
    _airschedServiceContext (iService._airschedServiceContext) {
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::
  AIRSCHED_Service (std::ostream& ioLogStream,
                    const stdair::AirlineFeatureSet& iAirlineFeatureSet,
                    const stdair::Date_T& iStartAnalysisDate,
                    const stdair::Filename_T& iScheduleInputFilename) {
    // Initialise the context
    init (ioLogStream,
          iAirlineFeatureSet, iStartAnalysisDate, iScheduleInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::~AIRSCHED_Service () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::
  init (std::ostream& ioLogStream,
        const stdair::AirlineFeatureSet& iAirlineFeatureSet,
        const stdair::Date_T& iStartAnalysisDate,
        const stdair::Filename_T& iScheduleInputFilename) {
    // Set the log file
    logInit (LOG::DEBUG, ioLogStream);

    // Initialise the context
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext = 
      FacAIRSCHEDServiceContext::instance().create ();
    _airschedServiceContext = &lAIRSCHED_ServiceContext;

    // Store the AirlineFeatureSet object within the service context
    lAIRSCHED_ServiceContext.setAirlineFeatureSet (iAirlineFeatureSet);
    
    // Store the beginning date of analysis within the service context
    lAIRSCHED_ServiceContext.setStartAnalysisDate (iStartAnalysisDate);
    
    // Parse the schedule input file, and generate the Inventories
    stdair::BomRoot& oBomRoot =
      ScheduleParser::generateInventories (iScheduleInputFilename,
                                           iAirlineFeatureSet,
                                           iStartAnalysisDate);

    // Build the network from the schedule.
    NetworkGenerator::createNetworks (oBomRoot);
    
    // Store the BOM object tree within the service context
    lAIRSCHED_ServiceContext.setBomRoot (oBomRoot);
    
    // TODO: Implement a (recursive) display() method in BomRoot
    // DEBUG
    // AIRSCHED_LOG_DEBUG ("Generated BomRoot:");
    // oBomRoot.display();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::logInit (const LOG::EN_LogLevel iLogLevel,
                                  std::ostream& ioLogOutputFile) {
    Logger::instance().setLogParameters (iLogLevel, ioLogOutputFile);
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::
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

    if (_airschedServiceContext == NULL) {
      throw NonInitialisedServiceException();
    }
    assert (_airschedServiceContext != NULL);
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext= *_airschedServiceContext;

    // Add the travel solution to the service context
    lAIRSCHED_ServiceContext.addTravelSolution (iDepartureAirport,
                                                iArrivalAirport, iDepartureDate,
                                                iDepartureTime, iArrivalTime,
                                                iDuration, iRefundability,
                                                iAirlineCode, iCabinCode,
                                                iFlightNumber, iFare,
                                                iStopsNumber, iSNS,
                                                iChangeability);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::simulate()  {

    if (_airschedServiceContext == NULL) {
      throw NonInitialisedServiceException();
    }
    assert (_airschedServiceContext != NULL);
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext= *_airschedServiceContext;

    // Add travel solutions to the travelsolution holder

    // AF404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), false,
                       "AF", "ECO", 404, 200, 0, false, false);
    
    // AF404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), true,
                       "AF", "ECO", 404, 200, 0, false, false);
    
    // BA404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), false,
                       "BA", "ECO", 404, 200, 0, true, false);
    
    // BA404, NCE-LHR, 01-JUN-09 12:00 -> 14:00 (02:00), Eco
    addTravelSolution ("NCE","LHR", Date_T(2009,06,1), Duration_T(12,00,00),
                       Duration_T(14,00,00), Duration_T(02,00,00), true,
                       "BA", "ECO", 404, 200, 0, true, false);

    // Retrieve, from the service context, the root of the BOM tree
    stdair::BomRoot& lBomRoot = lAIRSCHED_ServiceContext.getBomRoot();
    
    // Call the underlying Use Case (command)
    Simulator::simulate (lBomRoot);
  }

}
