#ifndef __AIRSCHED_BOM_INVENTORY_HPP
#define __AIRSCHED_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/Inventory.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline inventory. */
  class Inventory : public stdair::Inventory {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::InventoryStructure_T Structure_T;
    
  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (const stdair::Inventory&);

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    Inventory (const Key_T&, Structure_T&);
    /** Destructor. */
    ~Inventory();
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);

  };

}
#endif // __AIRSCHED_BOM_INVENTORY_HPP
