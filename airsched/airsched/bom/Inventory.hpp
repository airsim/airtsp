#ifndef __AIRSCHED_BOM_INVENTORY_HPP
#define __AIRSCHED_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED 
#include <stdair/bom/BomContent.hpp>

// Forward declarations
namespace stdair {
  class BomContentRoot;
  class Inventory;
  class FacBomContent;
}
  
namespace AIRSCHED {

  /** Class representing the actual functional/business content for
      an airline inventory. */
  class Inventory : public stdair::BomContent {
    friend class stdair::FacBomContent;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef stdair::BomContentRoot ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::Inventory BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef stdair::InventoryKey BomKey_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);
    Inventory (const BomStructure_T&);

    /** Destructor. */
    virtual ~Inventory();

  private:
    // Attributes
    /** Reference structure. */
    const BomStructure_T& _inventoryStructure;
  };

}
#endif // __AIRSCHED_BOM_INVENTORY_HPP

