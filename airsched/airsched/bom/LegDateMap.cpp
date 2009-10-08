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
#include <airsched/bom/LegDateMap.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  LegDateMap_T::
  LegDateMap_T (const FlightDateStructure_T& iFlightDateStructure)
    : _flightDateStructure (iFlightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateMap_T::
  LegDateMap_T (const LegDateMap_T& iSDMap)
    : _flightDateStructure (iSDMap._flightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateMap_T::~LegDateMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateMap_T::iterator LegDateMap_T::begin () const {
    return _flightDateStructure.legDateMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateMap_T::iterator LegDateMap_T::end () const {
    return _flightDateStructure.legDateMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateMap_T::reverse_iterator LegDateMap_T::rbegin () const {
    return _flightDateStructure.legDateMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateMap_T::reverse_iterator LegDateMap_T::rend () const {
    return _flightDateStructure.legDateMapREnd ();
  }

}

