// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>
// AIRSCHED
#include <airsched/bom/BomRoot.hpp>
#include <airsched/bom/Inventory.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const Key_T& iKey, Structure_T& ioBomRootStructure)
    : stdair::BomRoot (iKey, ioBomRootStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

  // ////////////////////////////////////////////////////////////////////
  void BomRoot::fillFromRouting (const stdair::BomRoot& iBomRoot) {
    const stdair::InventoryList_T& lInventoryList = iBomRoot.getInventoryList();

    // Browse the list of inventories and update each inventory.
    for (stdair::InventoryList_T::iterator itInventory = lInventoryList.begin();
         itInventory != lInventoryList.end(); ++itInventory) {
      const stdair::Inventory& lCurrentInventory = *itInventory;
      Inventory::fillFromRouting (lCurrentInventory);
    }
  }

}
