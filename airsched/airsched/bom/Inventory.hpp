#ifndef __AIRSCHED_BOM_INVENTORY_HPP
#define __AIRSCHED_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/BomIterator.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Types.hpp>
#include <airsched/bom/InventoryTypes.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}
  
namespace AIRSCHED {

  // Forward declarations.
  class FlightDate;

  /** Class representing the actual functional/business content for
      an airline inventory. */
  class Inventory : public stdair::BomContent {
    friend class stdair::FacBomContent;

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the types which require to be specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomContentRoot_T ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef InventoryStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef InventoryKey_T BomKey_T;

    /** Definition allowing to retrieve the associated first BOM content child
        type. */
    typedef FlightDate FirstContentChild_T;
    // /////////////////////////////////////////////////////////////////////////
    
  public:
    /** Iterator on the FlightDate objects. */
    typedef FlightDateListConstIterator_T const_iterator;

    
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

    // /////////// Iteration methods //////////
    /** Initialise the internal iterators on flight date:
        return the iterator at the begining of the list. */
    const_iterator flightDateListBegin () const;
    
    /** Initialise the internal iterators on flight date:
        return the iterator at the end of the list. */
    const_iterator flightDateListEnd () const;

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _inventoryStructure;
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);
    Inventory (BomStructure_T&);

    /** Destructor. */
    virtual ~Inventory();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _inventoryStructure;
  };

}
#endif // __AIRSCHED_BOM_INVENTORY_HPP

