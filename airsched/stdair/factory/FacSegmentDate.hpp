#ifndef __STDAIR_FAC_FACSEGMENTDATE_HPP
#define __STDAIR_FAC_FACSEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/factory/FacBomStructure.hpp>

namespace STDAIR {

  /** Factory for SegmentDate objects. */
  class FacSegmentDate : public FacBomStructure {
  private:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacSegmentDate () {}

    /** Destructor.
        <br>The Destruction put the _instance to NULL
        in order to be clean for the next FacSegmentDate::instance() */
    virtual ~FacSegmentDate() {}
  };

}
#endif // __STDAIR_FAC_FACSEGMENTDATE_HPP

