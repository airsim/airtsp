#ifndef __AIRSCHED_FAC_FACFLIGHTDATE_HPP
#define __AIRSCHED_FAC_FACFLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED 
#include <stdair/factory/FacBomContent.hpp>

// Forward declarations
namespace STDAIR {
  class FlightDateKey;
  class FlightDate;
}

namespace AIRSCHED {

  // Forward declarations.
  class FlightDate;
  
  /** Factory for FlightDate objects. */
  class FacFlightDate : public STDAIR::FacBomContent {
    friend class FacSegmentDate;
  private:
    /** Retrieve the FlightDate structure/holder object corresponding
        to a given FlightDate content object. */
    STDAIR::FlightDate* getFlightDateStructure (const FlightDate&);

  private:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacFlightDate () {}

    /** Destructor.
        <br>The Destruction put the _instance to NULL
        in order to be clean for the next FacFlightDate::instance() */
    virtual ~FacFlightDate();

  };

}
#endif // __AIRSCHED_FAC_FACFLIGHTDATE_HPP

