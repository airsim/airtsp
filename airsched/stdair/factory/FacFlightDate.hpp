#ifndef __STDAIR_FAC_FACFLIGHTDATE_HPP
#define __STDAIR_FAC_FACFLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/factory/FacBomStructure.hpp>

namespace STDAIR {

  /** Factory for FlightDate objects. */
  class FacFlightDate : public FacBomStructure {
  private:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacFlightDate () {}

    /** Destructor.
        <br>The Destruction put the _instance to NULL
        in order to be clean for the next FacFlightDate::instance() */
    virtual ~FacFlightDate() {}
  };

}
#endif // __STDAIR_FAC_FACFLIGHTDATE_HPP

