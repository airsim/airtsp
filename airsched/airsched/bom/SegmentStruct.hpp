#ifndef __AIRSCHED_BOM_SEGMENTSTRUCT_HPP
#define __AIRSCHED_BOM_SEGMENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/StructAbstract.hpp>
// AIRSCHED
#include <airsched/bom/SegmentCabinStruct.hpp>

// Forward declarations
namespace stdair {
  class SegmentDate;
}

namespace AIRSCHED {
  /** Utility Structure for the parsing of Segment structures. */
  struct SegmentStruct_T : public stdair::StructAbstract {
    // Attributes
    stdair::AirportCode_T _boardPoint;
    stdair::Date_T _boardDate;
    stdair::Duration_T _boardTime;
    stdair::AirportCode_T _offPoint;
    stdair::Date_T _offDate;
    stdair::Duration_T _offTime;
    stdair::Duration_T _elapsed;
    SegmentCabinStructList_T _cabinList;

    /** Fill the SegmentDate objects with the attributes of the
        SegmentStruct. */
    void fill (stdair::SegmentDate&) const;
      
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;
  };

  /** List of Segment strucutres. */
  typedef std::vector<SegmentStruct_T> SegmentStructList_T;

}
#endif // __AIRSCHED_BOM_SEGMENTSTRUCT_HPP