// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <string>
// STDAIR
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/bom/BomContentRoot.hpp>
// AIRSCHED
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void Simulator::simulate () {
    // DEBUG
    AIRSCHED_LOG_DEBUG ("Welcome to Air-Schedule");

    // Step 0.0: initialisation
    // Create the root of the Bom tree (i.e., a BomContentRoot object)
    STDAIR::BomContentRoot& lBomContentRoot =
      STDAIR::FacBomContent::instance().createBomRoot();
    

    // Step 0.1: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const STDAIR::FlightNumber_T lFlightNumber = 15;
    const STDAIR::Date_T lDate (2010, 6, 10);
    const STDAIR::FlightDateKey lFlightDateKey (lFlightNumber, lDate);

    FlightDate& lFlightDate =
      STDAIR::FacBomContent::instance().create<FlightDate> (lBomContentRoot,
                                                            lFlightDateKey);
    
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate);

    
    // Step 0.2: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const STDAIR::AirportCode_T lLHR ("LHR");
    const STDAIR::AirportCode_T lSYD ("SYD");
    STDAIR::SegmentDateKey lSegmentDateKey (lLHR, lSYD);

    SegmentDate& lLHRSYDSegment =
      STDAIR::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // SegmentDate& lLHRSYDSegment =
    // FacSegmentDate::instance().create (lFlightDate, lSegmentDateKey);
    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment);


    // Create a second SegmentDate (LHR-BKK)
    const STDAIR::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = STDAIR::SegmentDateKey (lLHR, lBKK);

    SegmentDate& lLHRBKKSegment =
      STDAIR::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // SegmentDate& lLHRBKKSegment =
    // FacSegmentDate::instance().create (lFlightDate, lSegmentDateKey);
    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment);


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = STDAIR::SegmentDateKey (lBKK, lSYD);

    SegmentDate& lBKKSYDSegment =
      STDAIR::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // SegmentDate& lBKKSYDSegment =
    // FacSegmentDate::instance().create (lFlightDate, lSegmentDateKey);
    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment);

    
    // Step 0.3: Initialisation results
    // Display the full structure and content
    AIRSCHED_LOG_DEBUG ("Full FlightDate: " << lFlightDate);
  }
  
}
