// //////////////////////////////////////////////////////////////////////
#ifndef __AIRSCHED_BOM_SEGMENTDATETYPES_HPP
#define __AIRSCHED_BOM_SEGMENTDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations.
namespace stdair {
  template <typename BOM_CONTENT> class SegmentDate;
  template <typename BOM_CONTENT> class SegmentDateKey;
}

namespace AIRSCHED {

  // Forward declarations.
  class SegmentDate;
  
  /** Define the SegmentDate structure. */
  typedef stdair::SegmentDate<SegmentDate> SegmentDateStructure_T;
  
  /** Define the SegmentDate key. */
  typedef stdair::SegmentDateKey<SegmentDate> SegmentDateKey_T;
  
  /** Define the segment-date structure list. */
  typedef std::vector<SegmentDateStructure_T*> SegmentDateStructureList_T;

  /** Define the segment-date structure map. */
  typedef std::map<const std::string, SegmentDateStructure_T*> SegmentDateStructureMap_T;

}
#endif // __AIRSCHED_BOM_SEGMENTDATETYPES_HPP

