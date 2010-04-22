#ifndef __AIRSCHED_BOM_FLIGHTDATE_HPP
#define __AIRSCHED_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FlightDate.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline flight-date. */
  class FlightDate : public stdair::FlightDate {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::FlightDateStructure_T Structure_T;

  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (const stdair::FlightDate&);
    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    FlightDate (const Key_T&, Structure_T&);
    /** Destructor. */
    ~FlightDate();
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);

  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATE_HPP
