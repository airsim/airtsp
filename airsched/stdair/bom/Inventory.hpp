#ifndef __STDAIR_BOM_INVENTORY_HPP
#define __STDAIR_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>

namespace stdair {

  // Forward declaration
  class BomStructureRoot;
  class FlightDate;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific Inventory class (for instance,
      in the AIRSCHED library). */
  class Inventory : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef InventoryKey BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef BomStructureRoot ParentBomStructure_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<FlightDate> ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<mpl_::void_> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the first children bom holder type. */
    typedef BomChildrenHolderImp<FlightDate> FirstChildrenBomHolder_T;
  
  public:
    // /////////// Getters /////////////
    /** Get the (parent) BomStructureRoot object. */
    ParentBomStructure_T* getBomStructureRootPtr() const {
      return _parent;
    }
    
    /** Get the (parent) BomStructureRoot object. */
    ParentBomStructure_T& getBomStructureRoot() const;
    
    /** Get the flight-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the list of flight-dates. */
    const FirstChildrenBomHolder_T& getFirstChildrenList() const {
      return *_firstChildrenList;
    }

     /** Get the list of flight-dates. */
    void getChildrenList (FirstChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _firstChildrenList;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) Inventory object. */
    void setBomStructureRoot (ParentBomStructure_T& ioParent) {
      _parent = &ioParent;
    }

    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }
    
    /** Set the first children list. */
    void setChildrenList (FirstChildrenBomHolder_T&);


  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Dump a Business Object with all its children into an output stream.
        @param ostream& the output stream. */
    void describeFull (std::ostringstream& ioOut) const;

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

    /** Dump the flight-date children list in to an output stream.
        @param ostream& the output stream. */
    void displayFlightDateList (std::ostringstream& ioOut) const;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);
    Inventory (const BomKey_T&);

    /** Destructor. */
    virtual ~Inventory();

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;

    /** The key of both the structure and content objects. */
    BomKey_T _key;
    
    /** List of flight-dates. */
    FirstChildrenBomHolder_T* _firstChildrenList;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

