// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
// AIRSCHED
#include <airsched/bom/BomRootHelper.hpp>
#include <airsched/bom/InventoryHelper.hpp>

namespace AIRSCHED {
  // ////////////////////////////////////////////////////////////////////
  void BomRootHelper::fillFromRouting (const stdair::BomRoot& iBomRoot) {
    const stdair::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (iBomRoot);
    
    // Browse the list of inventories and update each inventory.
    for (stdair::InventoryList_T::const_iterator itInventory =
           lInventoryList.begin();
         itInventory != lInventoryList.end(); ++itInventory) {
      const stdair::Inventory* lCurrentInventory_ptr = *itInventory;
      assert (lCurrentInventory_ptr != NULL);
      InventoryHelper::fillFromRouting (*lCurrentInventory_ptr);
    }
  }

}
