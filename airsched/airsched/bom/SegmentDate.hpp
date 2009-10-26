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
