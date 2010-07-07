#ifndef __AIRSCHED_BOM_SEGMENTPERIOD_HPP
#define __AIRSCHED_BOM_SEGMENTPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentPeriod.hpp>
// AIRSCHED
#include <airsched/bom/LegStruct.hpp>
#include <airsched/bom/SegmentStruct.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  
  /** Class representing the actual business functions for
      an airline segment-period. */
  class SegmentPeriod : public stdair::SegmentPeriod {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::SegmentPeriodStructure_T Structure_T;

  public:
    // ////////// Business Methods /////////
    /** Fill the attributes of the given segment-period with the cabins
        and classes. */
    static void fill (stdair::SegmentPeriod&, const SegmentStruct_T&);
    
    /** Fill the attributes of the given segment-period with the list of used
        legs. */
    static void fill (stdair::SegmentPeriod&, const LegStructList_T&);
    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    SegmentPeriod (const Key_T&, Structure_T&);
    /** Destructor. */
    ~SegmentPeriod();
    /** Default constructors. */
    SegmentPeriod ();
    SegmentPeriod (const SegmentPeriod&);

  };

}
#endif // __AIRSCHED_BOM_SEGMENTPERIOD_HPP
