#ifndef __AIRSCHED_BOM_SEGMENTCABIN_HPP
#define __AIRSCHED_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentCabin.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline segment-cabin. */
  class SegmentCabin : public stdair::SegmentCabin {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::SegmentCabinStructure_T Structure_T;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    SegmentCabin (const Key_T&, Structure_T&);
    /** Destructor. */
    ~SegmentCabin();
    /** Default constructors. */
    SegmentCabin ();
    SegmentCabin (const SegmentCabin&);

  };

}
#endif // __AIRSCHED_BOM_SEGMENTCABIN_HPP
