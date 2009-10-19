#ifndef __AIRSCHED_BOM_INVENTORY_HPP
#define __AIRSCHED_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/InventoryTypes.hpp>
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
    typedef stdair::InventoryStructure_T BomStructure_T;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);
    Inventory (BomStructure_T&);

    /** Destructor. */
    virtual ~Inventory();

  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

