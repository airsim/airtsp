// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>
// AIRSCHED
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const Key_T& iKey,
                          Structure_T& ioFlightDateStructure)
    : stdair::FlightDate (iKey, ioFlightDateStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDate::fillFromRouting (const stdair::FlightDate& iFlightDate) {
    const stdair::SegmentDateList_T& lSegmentDateList =
      iFlightDate.getSegmentDateList();

    // Browse the list of inventories and update each inventory.
    for (stdair::SegmentDateList_T::iterator itSegmentDate =
           lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      stdair::SegmentDate& lCurrentSegmentDate = *itSegmentDate;
      SegmentDate::fillFromRouting (lCurrentSegmentDate);
    }
  }

}
