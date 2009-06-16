#ifndef __AIRSCHED_FAC_FACSEGMENTDATE_HPP
#define __AIRSCHED_FAC_FACSEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED 
#include <stdair/factory/FacBomContent.hpp>

// Forward declarations
namespace STDAIR {
  class SegmentDateKey;
}

namespace AIRSCHED {

  // Forward declarations.
  class FlightDate;
  class SegmentDate;
  
  /** Factory for SegmentDate objects. */
  class FacSegmentDate : public STDAIR::FacBomContent {
  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used
        @return FacSegmentDate& */
    static FacSegmentDate& instance();

    /** Destructor.
        <br>The Destruction put the _instance to NULL
        in order to be clean for the next FacSegmentDate::instance() */
    virtual ~FacSegmentDate();

    /** Create a new SegmentDate object.
        <br>This new object is added to the list of instantiated objects.
        @return SegmentDate& The newly created object. */
    SegmentDate& create (const FlightDate&, const STDAIR::SegmentDateKey&);

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacSegmentDate () {}

  private:
    /** The unique instance.*/
    static FacSegmentDate* _instance;
  };

}
#endif // __AIRSCHED_FAC_FACSEGMENTDATE_HPP

