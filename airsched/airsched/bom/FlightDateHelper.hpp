#ifndef __AIRSCHED_BOM_FLIGHTDATEHELPER_HPP
#define __AIRSCHED_BOM_FLIGHTDATEHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations
namespace stdair {
  class FlightDate;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline flight-date. */
  class FlightDateHelper  {
  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (const stdair::FlightDate&);
  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATEHELPER_HPP
