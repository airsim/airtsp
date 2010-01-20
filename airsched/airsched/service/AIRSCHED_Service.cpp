// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
#include <iomanip>
// StdAir
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/service/Logger.hpp>
// AIRSCHED
#include <airsched/basic/BasConst_AIRSCHED_Service.hpp>
#include <airsched/bom/BomRoot.hpp>
#include <airsched/factory/FacAIRSCHEDServiceContext.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/command/ScheduleParser.hpp>
#include <airsched/command/NetworkGenerator.hpp>
#include <airsched/service/AIRSCHED_ServiceContext.hpp>
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
    logInit (stdair::LOG::DEBUG, ioLogStream);

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (iScheduleInputFilename);
    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The schedule input file, '" << iScheduleInputFilename
                        << "', can not be retrieved on the file-system");
      throw FileNotFoundException();
    }

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
    
    // DEBUG
    STDAIR_LOG_DEBUG ("Generated BomRoot:");
    stdair::BomManager::display (ioLogStream, oBomRoot);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::logInit (const stdair::LOG::EN_LogLevel iLogLevel,
                                  std::ostream& ioLogOutputFile) {
    stdair::Logger::instance().setLogParameters (iLogLevel, ioLogOutputFile);
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

    // Retrieve, from the service context, the root of the BOM tree
    stdair::BomRoot& lBomRoot = lAIRSCHED_ServiceContext.getBomRoot();
    
    // Call the underlying Use Case (command)
    stdair::BasChronometer lSimulateChronometer;
    lSimulateChronometer.start();
    Simulator::simulate (lBomRoot);
    const double lSimulateMeasure = lSimulateChronometer.elapsed();

    // DEBUG
    STDAIR_LOG_DEBUG ("Simulation: " << lSimulateMeasure << " - "
                      << lAIRSCHED_ServiceContext.display());
  }

}
