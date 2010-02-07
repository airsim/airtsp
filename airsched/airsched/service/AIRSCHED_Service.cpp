// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/NetworkKey.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// AirSched
#include <airsched/basic/BasConst_AIRSCHED_Service.hpp>
#include <airsched/bom/BomRoot.hpp>
#include <airsched/factory/FacAIRSCHEDServiceContext.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/command/ScheduleParser.hpp>
#include <airsched/command/NetworkGenerator.hpp>
#include <airsched/command/TravelSolutionProvider.hpp>
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
  AIRSCHED_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                    const stdair::Date_T& iStartAnalysisDate,
                    const stdair::Filename_T& iScheduleInputFilename)
    : _airschedServiceContext (NULL) {

    // Initialise the service context
    initServiceContext ();
    
    // Retrieve the AirSched service context
    assert (_airschedServiceContext != NULL);
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext =
      *_airschedServiceContext;
    
    // Store the STDAIR service object within the (AIRSCHED) service context
    lAIRSCHED_ServiceContext.setSTDAIR_Service (ioSTDAIR_ServicePtr);
    
    // Initialise the context
    init (iStartAnalysisDate, iScheduleInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::
  AIRSCHED_Service (const stdair::BasLogParams& iLogParams,
                    const stdair::Date_T& iStartAnalysisDate,
                    const stdair::Filename_T& iScheduleInputFilename) 
    : _airschedServiceContext (NULL) {
    
    // Initialise the service context
    initServiceContext ();
    
    // Initialise the STDAIR service handler
    initStdAirService (iLogParams);
    
    // Initialise the (remaining of the) context
    init (iStartAnalysisDate, iScheduleInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRSCHED_Service::~AIRSCHED_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::initServiceContext () {
    // Initialise the service context
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext = 
      FacAIRSCHEDServiceContext::instance().create ();
    _airschedServiceContext = &lAIRSCHED_ServiceContext;
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams) {

    // Retrieve the AirSched service context
    assert (_airschedServiceContext != NULL);
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext =
      *_airschedServiceContext;
    
    // Initialise the STDAIR service handler
    // Note that the track on the object memory is kept thanks to the Boost
    // Smart Pointers component.
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams);

    // Store the STDAIR service object within the (AIRSCHED) service context
    lAIRSCHED_ServiceContext.setSTDAIR_Service (lSTDAIR_Service_ptr);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRSCHED_Service::
  init (const stdair::Date_T& iStartAnalysisDate,
        const stdair::Filename_T& iScheduleInputFilename) {

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (iScheduleInputFilename);
    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The schedule input file, '" << iScheduleInputFilename
                        << "', can not be retrieved on the file-system");
      throw stdair::FileNotFoundException();
    }

    // Retrieve the AirSched service context
    assert (_airschedServiceContext != NULL);
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext =
      *_airschedServiceContext;

    // Store the beginning date of analysis within the service context
    lAIRSCHED_ServiceContext.setStartAnalysisDate (iStartAnalysisDate);

    // Retrieve the StdAir service context
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      lAIRSCHED_ServiceContext.getSTDAIR_Service();
    assert (lSTDAIR_Service_ptr != NULL);
    
    // Get the root of the BOM tree, on which all of the other BOM objects
    // will be attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service_ptr->getBomRoot();

    // Parse the schedule input file, and generate the Inventories
    ScheduleParser::generateInventories (iScheduleInputFilename, lBomRoot,
                                         iStartAnalysisDate);

    // // Build the network from the schedule.
    NetworkGenerator::createNetworks (lBomRoot);
    
    // DEBUG
    STDAIR_LOG_DEBUG ("Generated BomRoot:");
    std::ostringstream oStream;
    stdair::BomManager::display (oStream, lBomRoot);
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
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext = *_airschedServiceContext;

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
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext =
      *_airschedServiceContext;

    // Retrieve the StdAir service context
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      lAIRSCHED_ServiceContext.getSTDAIR_Service();
    assert (lSTDAIR_Service_ptr != NULL);
    
    // Create the root of the BOM tree, on which all of the other BOM objects
    // will be attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service_ptr->getBomRoot();

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
  void AIRSCHED_Service::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    if (_airschedServiceContext == NULL) {
      throw NonInitialisedServiceException();
    }
    assert (_airschedServiceContext != NULL);
    AIRSCHED_ServiceContext& lAIRSCHED_ServiceContext = *_airschedServiceContext;

    // Retrieve the network.
    const stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      lAIRSCHED_ServiceContext.getSTDAIR_Service();
    assert (lSTDAIR_Service_ptr != NULL);
    
    const stdair::BomRoot& lBomRoot = lSTDAIR_Service_ptr->getBomRoot();
    const stdair::NetworkID_T lNetworkID ("Whole Network");
    const stdair::Network* lNetwork_ptr = lBomRoot.getNetwork (lNetworkID);
    assert (lNetwork_ptr != NULL);
    
    TravelSolutionProvider::getTravelSolutions (ioTravelSolutionList,
                                                *lNetwork_ptr, iBookingRequest);
  }

}
