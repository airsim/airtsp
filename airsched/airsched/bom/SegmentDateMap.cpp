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
#include <airsched/bom/SegmentDateMap.hpp>
#include <airsched/bom/LegDate.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::
  SegmentDateMap_T (const FlightDateStructure_T& iFlightDateStructure)
    : _flightDateStructure (iFlightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::
  SegmentDateMap_T (const SegmentDateMap_T& iSDMap)
    : _flightDateStructure (iSDMap._flightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::~SegmentDateMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::iterator SegmentDateMap_T::begin () const {
    return _flightDateStructure.segmentDateMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::iterator SegmentDateMap_T::end () const {
    return _flightDateStructure.segmentDateMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::reverse_iterator SegmentDateMap_T::rbegin () const {
    return _flightDateStructure.segmentDateMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::reverse_iterator SegmentDateMap_T::rend () const {
    return _flightDateStructure.segmentDateMapREnd ();
  }

}
