#ifndef __AIRTSP_BOM_SEGMENTPERIODHELPER_HPP
#define __AIRTSP_BOM_SEGMENTPERIODHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AirTSP
#include <airtsp/bom/LegStruct.hpp>
#include <airtsp/bom/SegmentStruct.hpp>

// Forward declarations
namespace stdair {
  class SegmentPeriod;
}

namespace AIRTSP {

  /** 
   * @brief Class representing the actual business functions for
   *        an airline segment-period. 
   */
  class SegmentPeriodHelper {
  public:
    // ////////// Business Methods /////////
    /**
     * Fill the attributes of the given segment-period with the cabins
     * and classes. 
     */
    static void fill (stdair::SegmentPeriod&, const SegmentStruct&);
    
    /**
     * Fill the attributes of the given segment-period with the list of used
     * legs.
     */
    static void fill (stdair::SegmentPeriod&, const LegStructList_T&);
  };

}
#endif // __AIRTSP_BOM_SEGMENTPERIODHELPER_HPP
