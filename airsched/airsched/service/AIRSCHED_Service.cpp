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
  AIRSCHED_Service::AIRSCHED_Service () : _airschedServiceContext (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::AIRSCHED_Service (const AIRSCHED_Service& iService) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::
  AIRSCHED_Service (const stdair::AirlineFeatureSet& iAirlineFeatureSet,
                    const stdair::Date_T& iStartAnalysisDate,
                    const stdair::Filename_T& iScheduleInputFilename)
    : _airschedServiceContext (NULL) {
    // Initialise the context
    init (iAirlineFeatureSet, iStartAnalysisDate, iScheduleInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::
  AIRSCHED_Service (const stdair::BasLogParams& iLogParams,
                    const stdair::AirlineFeatureSet& iAirlineFeatureSet,
                    const stdair::Date_T& iStartAnalysisDate,
                    const stdair::Filename_T& iScheduleInputFilename) 
    : _airschedServiceContext (NULL) {
    
    // Set the log file
    logInit (iLogParams);

    // Initialise the (remaining of the) context
    init (iAirlineFeatureSet, iStartAnalysisDate, iScheduleInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::~AIRSCHED_Service () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::logInit (const stdair::BasLogParams& iLogParams) {
    stdair::Logger::init (iLogParams);
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::
  init (const stdair::AirlineFeatureSet& iAirlineFeatureSet,
        const stdair::Date_T& iStartAnalysisDate,
        const stdair::Filename_T& iScheduleInputFilename) {

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
    std::ostringstream oStream;
    stdair::BomManager::display (oStream, oBomRoot);
    STDAIR_LOG_DEBUG (oStream.str());
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

  // ////////////////////////////////////////////////////////////////////
  stdair::BomRoot& AIRSCHED_Service::getBomRoot () const {
    assert (_airschedServiceContext != NULL);
    return _airschedServiceContext->getBomRoot();
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::OutboundPathLightList_T AIRSCHED_Service::
  getTravelSolutions (const stdair::BookingRequestStruct& iBookingRequest) {
    // Initiate an empty list of outbound paths/travel solutions.
    stdair::OutboundPathLightList_T oOutboundPathList;

    return oOutboundPathList;
  }

}
