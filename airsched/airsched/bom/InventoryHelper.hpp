#ifndef __AIRSCHED_BOM_INVENTORYHELPER_HPP
#define __AIRSCHED_BOM_INVENTORYHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations
namespace stdair {
  class Inventory;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline inventory. */
  class InventoryHelper {    
  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (const stdair::Inventory&);
  };

}
#endif // __AIRSCHED_BOM_INVENTORYHELPER_HPP
