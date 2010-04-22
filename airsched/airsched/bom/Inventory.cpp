// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>
// AIRSCHED
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Key_T& iKey,
                        Structure_T& ioInventoryStructure)
    : stdair::Inventory (iKey, ioInventoryStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory () {
  }

  // ////////////////////////////////////////////////////////////////////
  void Inventory::fillFromRouting (const stdair::Inventory& iInventory) {
    const stdair::FlightDateList_T& lFlightDateList =
      iInventory.getFlightDateList();

    // Browse the list of inventories and update each inventory.
    for (stdair::FlightDateList_T::iterator itFlightDate =
           lFlightDateList.begin();
         itFlightDate != lFlightDateList.end(); ++itFlightDate) {
      const stdair::FlightDate& lCurrentFlightDate = *itFlightDate;
      FlightDate::fillFromRouting (lCurrentFlightDate);
    }
  }
  
}
