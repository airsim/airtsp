// //////////////////////////////////////////////////////////////////////
#ifndef __AIRSCHED_BOM_INVENTORYTYPES_HPP
#define __AIRSCHED_BOM_INVENTORYTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations.
namespace stdair {
  template <typename BOM_CONTENT> class Inventory;
  template <typename BOM_CONTENT> class InventoryKey;
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
}

namespace AIRSCHED {

  // Forward declarations.
  class Inventory;
  
  /** Define the Inventory structure. */
  typedef stdair::Inventory<Inventory> InventoryStructure_T;
  
  /** Define the Inventory key. */
  typedef stdair::InventoryKey<Inventory> InventoryKey_T;
  
}
#endif // __AIRSCHED_BOM_INVENTORYTYPES_HPP

