#ifndef __STDAIR_BOM_SEGMENTDATE_HPP
#define __STDAIR_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomStructureList.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
// MPL
#include <boost/mpl/vector.hpp>

namespace stdair {

  // Forward declaration
  class FlightDate;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific SegmentDate class (for instance,
      in the AIRSCHED library). */
  class SegmentDate : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class PrintBomContent;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentDateKey BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef FlightDate ParentBomStructure_T;
    
    /** Definition allowing to retrieve the associated children BOM structure. */
    typedef BomStructureOrderedList_T ChildrenBomList_T;

     /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector <> ChildrenBomTypeList_T;

  public:
    // /////////// Getters /////////////
    /** Get the (parent) FlightDate object. */
    ParentBomStructure_T* getFlightDatePtr() const {
      return _parent;
    }
    
    /** Get the (parent) FlightDate object. */
    ParentBomStructure_T& getFlightDate() const;
    
    /** Get the segment-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the list of children. */
    const BomStructureOrderedList_T& getChildrenList() const {
      return _childrenList;
    }

  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDate object. */
    void setFlightDate (ParentBomStructure_T& ioFlightDate) {
      _parent = &ioFlightDate;
    }

    
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
    SegmentDate ();
    SegmentDate (const SegmentDate&);
    SegmentDate (const BomKey_T&);

    /** Destructor. */
    virtual ~SegmentDate();

  private:
    // Attributes
    /** Parent flight-date. */
    ParentBomStructure_T* _parent;

    /** The key of both the structure and content objects. */
    BomKey_T _key;

    /** List of children. */
    ChildrenBomList_T _childrenList;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATE_HPP
