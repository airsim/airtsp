// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/FlightDate.hpp>
// AIRSCHED
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/bom/SegmentDateList.hpp>
#include <airsched/bom/LegDate.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::
  SegmentDateList_T (const FlightDateStructure_T& iFlightDateStructure)
    : _flightDateStructure (iFlightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::
  SegmentDateList_T (const SegmentDateList_T& iSDList)
    : _flightDateStructure (iSDList._flightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::~SegmentDateList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::iterator SegmentDateList_T::begin () const {
    return _flightDateStructure.segmentDateListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::iterator SegmentDateList_T::end () const {
    return _flightDateStructure.segmentDateListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::reverse_iterator SegmentDateList_T::rbegin () const {
    return _flightDateStructure.segmentDateListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::reverse_iterator SegmentDateList_T::rend () const {
    return _flightDateStructure.segmentDateListREnd ();
  }

}

