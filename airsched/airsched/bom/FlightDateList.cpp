// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/Inventory.hpp>
// AIRSCHED
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/FlightDateList.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  FlightDateList_T::
  FlightDateList_T (const InventoryStructure_T& iInventoryStructure)
    : _inventoryStructure (iInventoryStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateList_T::
  FlightDateList_T (const FlightDateList_T& iFDList)
    : _inventoryStructure (iFDList._inventoryStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateList_T::~FlightDateList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::iterator FlightDateList_T::begin () const {
    return _inventoryStructure.flightDateListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::iterator FlightDateList_T::end () const {
    return _inventoryStructure.flightDateListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::reverse_iterator FlightDateList_T::rbegin () const {
    return _inventoryStructure.flightDateListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::reverse_iterator FlightDateList_T::rend () const {
    return _inventoryStructure.flightDateListREnd ();
  }

}

