// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
// AIRSCHED
#include <airsched/bom/FlightDateHelper.hpp>
#include <airsched/bom/SegmentDateHelper.hpp>

namespace AIRSCHED {
  // ////////////////////////////////////////////////////////////////////
  void FlightDateHelper::fillFromRouting (const stdair::FlightDate& iFlightDate){
    stdair::SegmentDateList_T& lSegmentDateList =
      stdair::BomManager::getList<stdair::SegmentDate> (iFlightDate);

    // Browse the list of segment-dates and update each segment-date.
    for (stdair::SegmentDateList_T::iterator itSegmentDate =
           lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      stdair::SegmentDate* lCurrentSegmentDate_ptr = *itSegmentDate;
      assert (lCurrentSegmentDate_ptr != NULL);
      SegmentDateHelper::fillFromRouting (*lCurrentSegmentDate_ptr);
    }
  }

}
