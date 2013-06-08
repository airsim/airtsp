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
#include <stdair/bom/BomManager.hpp> 
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// AirTSP
#include <airtsp/basic/BasConst_AIRTSP_Service.hpp>
#include <airtsp/factory/FacAIRTSPServiceContext.hpp>
#include <airtsp/command/Simulator.hpp>
#include <airtsp/command/ScheduleParser.hpp>
#include <airtsp/command/OnDParser.hpp>
#include <airtsp/command/SegmentPathProvider.hpp>
#include <airtsp/command/InventoryGenerator.hpp>
#include <airtsp/command/SegmentPathGenerator.hpp>
#include <airtsp/service/AIRTSP_ServiceContext.hpp>
#include <airtsp/AIRTSP_Service.hpp>

namespace AIRTSP {

  // ////////////////////////////////////////////////////////////////////
  AIRTSP_Service::AIRTSP_Service() : _airtspServiceContext (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRTSP_Service::AIRTSP_Service (const AIRTSP_Service& iService)
    : _airtspServiceContext (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRTSP_Service::AIRTSP_Service (const stdair::BasLogParams& iLogParams) 
    : _airtspServiceContext (NULL) {
    
    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams);
    
    // Initialise the service context
    initServiceContext();
    
    // Add the StdAir service context to the Airtsp service context
    // \note Airtsp owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);
    
    // Initialise the (remaining of the) context
    initAirtspService();
  }

  // ////////////////////////////////////////////////////////////////////
  AIRTSP_Service::AIRTSP_Service (const stdair::BasLogParams& iLogParams,
                                      const stdair::BasDBParams& iDBParams) 
    : _airtspServiceContext (NULL) {
    
    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams, iDBParams);
    
    // Initialise the service context
    initServiceContext();
    
    // Add the StdAir service context to the Airtsp service context
    // \note Airtsp owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);
    
    // Initialise the (remaining of the) context
    initAirtspService();
  }

  // ////////////////////////////////////////////////////////////////////
  AIRTSP_Service::
  AIRTSP_Service (stdair::STDAIR_ServicePtr_T ioSTDAIRServicePtr)
    : _airtspServiceContext (NULL) {

    // Initialise the service context
    initServiceContext();
    
    // Add the StdAir service context to the Airtsp service context.
    // \note Airtsp does not own the STDAIR service resources here.
    const bool doesNotOwnStdairService = false;
    addStdAirService (ioSTDAIRServicePtr, doesNotOwnStdairService);
    
    // Initialise the context
    initAirtspService();
  }

  // ////////////////////////////////////////////////////////////////////
  AIRTSP_Service::~AIRTSP_Service() {
    // Delete/Clean all the objects from memory
    finalise();
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::finalise() {
    assert (_airtspServiceContext != NULL);
    // Reset the (Boost.)Smart pointer pointing on the STDAIR_Service object.
    _airtspServiceContext->reset();
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::initServiceContext() {
    // Initialise the service context
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext = 
      FacAIRTSPServiceContext::instance().create();
    _airtspServiceContext = &lAIRTSP_ServiceContext;
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::
  addStdAirService (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr,
                    const bool iOwnStdairService) {

    // Retrieve the Airtsp service context
    assert (_airtspServiceContext != NULL);
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;

    // Store the STDAIR service object within the (Airtsp) service context
    lAIRTSP_ServiceContext.setSTDAIR_Service (ioSTDAIR_Service_ptr,
                                                iOwnStdairService);
  }

  // //////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T AIRTSP_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams) {

    /**
     * Initialise the STDAIR service handler.
     *
     * \note The (Boost.)Smart Pointer keeps track of the references
     *       on the Service object, and deletes that object when it is
     *       no longer referenced (e.g., at the end of the process).
     */
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams);

    return lSTDAIR_Service_ptr;
  }
  
  // //////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T AIRTSP_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams,
                     const stdair::BasDBParams& iDBParams) {

    /**
     * Initialise the STDAIR service handler.
     *
     * \note The (Boost.)Smart Pointer keeps track of the references
     *       on the Service object, and deletes that object when it is
     *       no longer referenced (e.g., at the end of the process).
     */
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams, iDBParams);

    return lSTDAIR_Service_ptr;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::initAirtspService() {
    // Do nothing at this stage. A sample BOM tree may be built by
    // calling the buildSampleBom() method
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::
  parseAndLoad (const stdair::ScheduleFilePath& iScheduleInputFilePath) {
    
    // Retrieve the BOM tree root
    assert (_airtspServiceContext != NULL);
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext; 
    const bool doesOwnStdairService =
      lAIRTSP_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (Airtsp) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lPersistentBomRoot = 
      lSTDAIR_Service.getPersistentBomRoot();

    /**
     * 1. Parse the schedule input file, and generate the Inventories
     */
    stdair::BasChronometer lINVGeneration; lINVGeneration.start();
    ScheduleParser::generateInventories (iScheduleInputFilePath, 
					 lPersistentBomRoot);  
    /**
     * 2. Delegate the complementary building of objects and links by the
     *    appropriate levels/components
     * 
     * \note: Currently, no more things to do by Airtsp at that stage,
     *        as there is no child
     */
  
    /**
     * 3. Build the complementary links.
     */
    buildComplementaryLinks (lPersistentBomRoot);

    const double lGenerationMeasure = lINVGeneration.elapsed();
    
    /**
     * 4. Have Airtsp clone the whole persistent BOM tree, only when the 
     *    StdAir service is owned by the current component (Airtsp here).
     */
    if (doesOwnStdairService == true) {
 
      //
      clonePersistentBom ();
    } 

    // DEBUG
    STDAIR_LOG_DEBUG ("Inventory generation time: " << lGenerationMeasure); 
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::
  parseAndLoad (const stdair::ScheduleFilePath& iScheduleInputFilePath,
                const stdair::ODFilePath& iODInputFilePath) {

    // First, build the airline inventories from the schedule file
    parseAndLoad (iScheduleInputFilePath);

    // Retrieve the BOM tree root
    assert (_airtspServiceContext != NULL);
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext; 
    const bool doesOwnStdairService =
      lAIRTSP_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (Airtsp) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lPersistentBomRoot = 
      lSTDAIR_Service.getPersistentBomRoot();

    /**
     * 1. Parse the O&D input file, and generate the O&D periods
     */
    stdair::BasChronometer lOnDGeneration; lOnDGeneration.start();
    OnDParser::generateOnDPeriods (iODInputFilePath, lPersistentBomRoot);
    const double lGenerationMeasure = lOnDGeneration.elapsed();  

    /**
     * 2. Delegate the complementary building of objects and links by the
     *    appropriate levels/components
     * 
     * \note: Currently, no more things to do by Airtsp at that stage,
     *        as there is no child
     */

    /**
     * 3. Have Airtsp clone the whole persistent BOM tree, only when the 
     *    StdAir service is owned by the current component (Airtsp here).
     */
    if (doesOwnStdairService == true) {
 
      //
      lSTDAIR_Service.clonePersistentBom ();
    }  

    /**
     * 4. Build the complementary objects/links for the current component (here,
     *    Airtsp)
     */
    stdair::BomRoot& lBomRoot = 
      lSTDAIR_Service.getBomRoot();
    buildComplementaryLinks (lBomRoot);

    // DEBUG
    STDAIR_LOG_DEBUG ("O&D generation time: " << lGenerationMeasure);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::buildSampleBom() {

    // Retrieve the Airtsp service context
    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service has "
                                                    "not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    // Retrieve the Airtsp service context and whether it owns the Stdair
    // service
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;
    const bool doesOwnStdairService =
      lAIRTSP_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (Airtsp) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();

    /**
     * 1. Have StdAir build the whole BOM tree, only when the StdAir service is
     *    owned by the current component (Airtsp here)
     */
    if (doesOwnStdairService == true) {
      //
      lSTDAIR_Service.buildSampleBom();
    }

    /**
     * 2. Delegate the complementary building of objects and links by the
     *    appropriate levels/components
     * 
     * \note: Currently, no more things to do by Airtsp at that stage,
     *        as there is no child
     */

    /**
     * 3. Build the complementary objects/links for the current component (here,
     *    Airtsp)
     */
    stdair::BomRoot& lPersistentBomRoot = 
      lSTDAIR_Service.getPersistentBomRoot();
    buildComplementaryLinks (lPersistentBomRoot);
    
    /**
     * 4. Have Airtsp clone the whole persistent BOM tree, only when the 
     *    StdAir service is owned by the current component (Airtsp here).
     */
    if (doesOwnStdairService == true) {
 
      //
      clonePersistentBom ();
    }
  } 

  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::clonePersistentBom () { 

    // Retrieve the Airtsp service context
    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service has "
                                                    "not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    // Retrieve the Airtsp service context and whether it owns the Stdair
    // service
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;
    const bool doesOwnStdairService =
      lAIRTSP_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (Airtsp) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service(); 

    /**
     * 1. Have StdAir clone the whole persistent BOM tree, only when the StdAir
     *    service is owned by the current component (Airtsp here).
     */
    if (doesOwnStdairService == true) {
 
      //
      lSTDAIR_Service.clonePersistentBom ();
    }
  
    /**
     * 2. Delegate the complementary building of objects and links to the
     *    appropriate command
     */
    stdair::BomRoot& lBomRoot = 
      lSTDAIR_Service.getBomRoot();
    buildComplementaryLinks (lBomRoot); 
  }  

  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::buildComplementaryLinks (stdair::BomRoot& ioBomRoot) {
 
    // Retrieve the Airtsp service context
    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service has "
                                                    "not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    /**
     *  Airtsp has to build the network from the schedule.
     */
    SegmentPathGenerator::createSegmentPathNetwork (ioBomRoot); 
  }

  // ////////////////////////////////////////////////////////////////////
  std::string AIRTSP_Service::
  jsonExportFlightDateObjects (const stdair::AirlineCode_T& iAirlineCode,
			       const stdair::FlightNumber_T& iFlightNumber,
			       const stdair::Date_T& iDepartureDate) const {

    // Retrieve the Airtsp service context
    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service "
                                                    "has not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    // Retrieve the StdAir service object from the (Airtsp) service context
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();

    // Delegate the JSON export to the dedicated service
    return lSTDAIR_Service.jsonExportFlightDateObjects (iAirlineCode,
							iFlightNumber,
							iDepartureDate);
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string AIRTSP_Service::csvDisplay() const {

    // Retrieve the Airtsp service context
    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service has "
                                                    "not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    // Retrieve the STDAIR service object from the (Airtsp) service context
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();  
    const stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Delegate the BOM building to the dedicated service
    return lSTDAIR_Service.csvDisplay(lBomRoot);
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string AIRTSP_Service::
  csvDisplay (const stdair::AirlineCode_T& iAirlineCode,
              const stdair::FlightNumber_T& iFlightNumber,
              const stdair::Date_T& iDepartureDate) const {

    // Retrieve the Airtsp service context
    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service has "
                                                    "not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    // Retrieve the STDAIR service object from the (Airtsp) service context
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM display to the dedicated service
    return lSTDAIR_Service.csvDisplay (iAirlineCode, iFlightNumber,
                                       iDepartureDate);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::simulate() {

    // Retrieve the Airtsp service context
    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service has "
                                                    "not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    // Retrieve the BOM tree root
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Call the underlying Use Case (command)
    stdair::BasChronometer lSimulateChronometer; lSimulateChronometer.start();
    Simulator::simulate (lBomRoot);
    const double lSimulateMeasure = lSimulateChronometer.elapsed();

    // DEBUG
    STDAIR_LOG_DEBUG ("Simulation: " << lSimulateMeasure << " - "
                      << lAIRTSP_ServiceContext.display());
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_Service::
  buildSegmentPathList (stdair::TravelSolutionList_T& ioTravelSolutionList,
			const stdair::BookingRequestStruct& iBookingRequest) {

    if (_airtspServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Airtsp service has "
                                                    "not been initialised");
    }
    assert (_airtspServiceContext != NULL);

    // Retrieve the BOM tree root
    AIRTSP_ServiceContext& lAIRTSP_ServiceContext =
      *_airtspServiceContext;
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRTSP_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();
    
    // Delegate the call to the dedicated command
    stdair::BasChronometer lBuildChronometer; lBuildChronometer.start();
    SegmentPathProvider::buildSegmentPathList (ioTravelSolutionList,
					       lBomRoot, iBookingRequest);
    const double lBuildMeasure = lBuildChronometer.elapsed();

    // DEBUG
    STDAIR_LOG_DEBUG ("Segment-path build: " << lBuildMeasure << " - "
                      << lAIRTSP_ServiceContext.display());
  }

}
