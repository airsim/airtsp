#ifndef __AIRSCHED_BOM_SEGMENTDATE_HPP
#define __AIRSCHED_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentDate.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline segment-date. */
  class SegmentDate : public stdair::SegmentDate {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::SegmentDateStructure_T BomStructure_T;

  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (stdair::SegmentDate&);
    
    /** Calculate and set the elapsed time according to the leg routing.
        <br>Actually, the elapsed time of the segment is the sum of the
        elapsed times of the routing legs, plus the stop-over times.
        The stop-over time is the difference between the board time of a
        routing leg, and the off time of the previous leg. That is, it is
        the time spent at the corresponding airport.
        <br>Of course, in case of mono-leg segments, there is no stop-over,
        and the elapsed time of the segment is equal to the elapsed time
        of the single routing leg. */
    static void updateElapsedTimeFromRouting (stdair::SegmentDate&);
      
    /** Method computing the distance of the segment (in kilometers).*/
    static void updateDistanceFromElapsedTime (stdair::SegmentDate&);

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    SegmentDate ();
    SegmentDate (const SegmentDate&);
    SegmentDate (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~SegmentDate();

  };

}
#endif // __AIRSCHED_BOM_SEGMENTDATE_HPP
