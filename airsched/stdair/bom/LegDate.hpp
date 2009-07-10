#ifndef __STDAIR_BOM_LEGDATE_HPP
#define __STDAIR_BOM_LEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/LegDateKey.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>

namespace stdair {

  // Forward declaration
  class FlightDate;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific LegDate class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class LegDate : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegDateKey BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::ParentBomContent_T::BomStructure_T ParentBomStructure_T;

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
    
    /** Get the leg-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDate object. */
    void setFlightDate (ParentBomStructure_T& ioFlightDate) {
      _parent = &ioFlightDate;
    }
    
    /** Default children list setter. */
    void setChildrenList (BomChildrenHolderImp<mpl_::void_>&) { }

    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { 
      ioOut << toString() << std::endl;
    }

    /** Dump a Business Object with all its children into an output stream.
        @param ostream& the output stream. */
    void describeFull (std::ostringstream& ioOut) const {
      ioOut << describeShortKey () << std::endl;
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return _key.toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegDate ();
    LegDate (const LegDate&);
    LegDate (const BomKey_T& iKey) : _parent (NULL), _key (iKey) { }

    /** Destructor. */
    virtual ~LegDate() { }

  private:
    // Attributes
    /** Parent flight-date. */
    ParentBomStructure_T* _parent;
    
     /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** The key of both the structure and content objects. */
    BomKey_T _key;
  };

}
#endif // __STDAIR_BOM_LEGDATE_HPP
