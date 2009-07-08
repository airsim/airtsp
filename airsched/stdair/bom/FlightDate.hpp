#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>

namespace stdair {

  // Forward declaration
  class Inventory;
  class SegmentDate;
  class LegDate;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific FlightDate class (for instance,
      in the AIRSCHED library). */
  class FlightDate : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef Inventory ParentBomStructure_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<SegmentDate, LegDate> ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<mpl_::void_> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the first children bom holder type. */
    typedef BomChildrenHolderImp<SegmentDate> FirstChildrenBomHolder_T;

    /** Definition allowing to retrive the second children bom holder type. */
    typedef BomChildrenHolderImp<LegDate> SecondChildrenBomHolder_T;
    
  public:
    // /////////// Getters /////////////
    /** Get the (parent) Inventory object. */
    ParentBomStructure_T* getInventoryPtr() const {
      return _parent;
    }
    
    /** Get the (parent) Inventory object. */
    ParentBomStructure_T& getInventory() const;
    
    /** Get the flight-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the list of segment-dates. */
    const FirstChildrenBomHolder_T& getFirstChildrenList() const {
      return *_firstChildrenList;
    }

    /** Get the list of leg-dates. */
    const SecondChildrenBomHolder_T& getSecondChildrenList() const {
      return *_secondChildrenList;
    }

    /** Get the list of segment-dates. */
    void getChildrenList (FirstChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _firstChildrenList;
    }

    /** Get the list of leg-dates. */
    void getChildrenList (SecondChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _secondChildrenList;
    }

    /** Dump the segment-date children list in to an output stream.
        @param ostream& the output stream. */
    void displaySegmentDateList (std::ostringstream& ioOut) const;

    /** Dump the leg-date children list in to an output stream.
        @param ostream& the output stream. */
    void displayLegDateList (std::ostringstream& ioOut) const;
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDate object. */
    void setBomStructureRoot (ParentBomStructure_T& ioParent) {
      _parent = &ioParent;
    }
    
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }
    
    /** Set the segment-date children list. */
    void setChildrenList (FirstChildrenBomHolder_T&);

    /** Set the leg-date children list. */
    void setChildrenList (SecondChildrenBomHolder_T&);


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


  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (const BomKey_T&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;

    /** The key of both the structure and content objects. */
    BomKey_T _key;
    
    /** List of segment-dates. */
    FirstChildrenBomHolder_T* _firstChildrenList;

    /** List of leg-dates. */
    SecondChildrenBomHolder_T* _secondChildrenList;

  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

