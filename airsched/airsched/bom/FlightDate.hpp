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
    typedef stdair::FlightDateStructure_T BomStructure_T;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~FlightDate();

  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATE_HPP
