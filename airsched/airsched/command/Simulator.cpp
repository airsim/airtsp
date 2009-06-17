// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <iomanip>
#include <string>
// STDAIR
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
// AIRSCHED
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/factory/FacFlightDate.hpp>
#include <airsched/factory/FacSegmentDate.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void Simulator::simulate () {
    // DEBUG
    AIRSCHED_LOG_DEBUG ("Welcome to Air-Schedule");

    // Create a FlightDate (BA15/10-JUN-2010)
    const STDAIR::FlightNumber_T lFlightNumber = 15;
    const STDAIR::Date_T lDate (2010, 6, 10);
    const STDAIR::FlightDateKey lFlightDateKey (lFlightNumber, lDate);
    FlightDate& lFlightDate = FacFlightDate::instance().create (lFlightDateKey);
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate);

    // Create a FlightDate (BA16/10-JUN-2010)
    const STDAIR::FlightNumber_T lFlightNumber2 = 16;
    const STDAIR::Date_T lDate2 (2010, 6, 10);
    const STDAIR::FlightDateKey lFlightDateKey2 (lFlightNumber2, lDate2);
    FlightDate& lFlightDate2 =
      FacFlightDate::instance().create (lFlightDateKey2);
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate2);

    // Create a first SegmentDate (LHR-SYD)
    const STDAIR::AirportCode_T lLHR ("LHR");
    const STDAIR::AirportCode_T lSYD ("SYD");
    STDAIR::SegmentDateKey lSegmentDateKey (lLHR, lSYD);
    SegmentDate& lLHRSYDSegment =
      FacSegmentDate::instance().create (lFlightDate, lSegmentDateKey);
    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment);

    // Create a second SegmentDate (LHR-BKK)
    const STDAIR::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = STDAIR::SegmentDateKey (lLHR, lBKK);
    SegmentDate& lLHRBKKSegment =
      FacSegmentDate::instance().create (lFlightDate, lSegmentDateKey);
    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment);

    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = STDAIR::SegmentDateKey (lBKK, lSYD);
    SegmentDate& lBKKSYDSegment =
      FacSegmentDate::instance().create (lFlightDate, lSegmentDateKey);
    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment);

    // Display the full structure and content
    AIRSCHED_LOG_DEBUG ("Full FlightDate: " << lFlightDate);
  }
  
}
