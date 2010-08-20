// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
// AIRSCHED
#include <airsched/bom/InventoryHelper.hpp>
#include <airsched/bom/FlightDateHelper.hpp>

namespace AIRSCHED {
  // ////////////////////////////////////////////////////////////////////
  void InventoryHelper::fillFromRouting (const stdair::Inventory& iInventory) {
    const stdair::FlightDateList_T& lFlightDateList =
      stdair::BomManager::getList<stdair::FlightDate> (iInventory);

    // Browse the list of flight-dates and update each flight-date.
    for (stdair::FlightDateList_T::const_iterator itFlightDate =
           lFlightDateList.begin();
         itFlightDate != lFlightDateList.end(); ++itFlightDate) {
      const stdair::FlightDate* lCurrentFlightDate_ptr = *itFlightDate;
      assert (lCurrentFlightDate_ptr != NULL);
      FlightDateHelper::fillFromRouting (*lCurrentFlightDate_ptr);
    }
  }
  
}
