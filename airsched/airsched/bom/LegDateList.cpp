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
#include <airsched/bom/LegDate.hpp>
#include <airsched/bom/LegDateList.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  LegDateList_T::
  LegDateList_T (const FlightDateStructure_T& iFlightDateStructure)
    : _flightDateStructure (iFlightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateList_T::
  LegDateList_T (const LegDateList_T& iSDList)
    : _flightDateStructure (iSDList._flightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateList_T::~LegDateList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateList_T::iterator LegDateList_T::begin () const {
    return _flightDateStructure.legDateListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateList_T::iterator LegDateList_T::end () const {
    return _flightDateStructure.legDateListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateList_T::reverse_iterator LegDateList_T::rbegin () const {
    return _flightDateStructure.legDateListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateList_T::reverse_iterator LegDateList_T::rend () const {
    return _flightDateStructure.legDateListREnd ();
  }

}

