#ifndef __STDAIR_BOM_SEGMENTDATESTRUCTURE_HPP
#define __STDAIR_BOM_SEGMENTDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>
#include <stdair/bom/SegmentCabinStructure.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific SegmentDate class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class SegmentDateStructure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;
    
  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef typename BOM_CONTENT::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::Parent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector <SegmentCabinStructure<ContentChild_T>,
                                BomStopStructure> ChildrenBomTypeList_T;

    /** Definition allowing to retrieve the default children bom holder type. */
    typedef BomChildrenHolderImp<BomStopContent> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;
    
    /** Define the associated leg-date type. */
    typedef typename BOM_CONTENT::LegDateContent_T LegDate_T;
    
    /** Define the associated leg-date holder type. */
    typedef BomChildrenHolderImp<LegDate_T> LegDateHolder_T;
    
    /** Define the map of leg-date. */
    typedef BomMap_T<LegDate_T> LegDateMap_T;

  public:
    // /////////// Getters /////////////
    /** Get the (parent) FlightDateStructure object. */
    ParentBomStructure_T* getFlightDateStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) FlightDateStructure object. */
    ParentBomStructure_T& getFlightDateStructure() const {
      assert (_parent != NULL);
      return *_parent;
    }
    
    /** Get the segment-date key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey ();
    }

    /** Get the holder of segment-cabins. */
    const ChildrenBomHolder_T& getChildrenHolder() const {
      assert (_childrenHolder != NULL);
      return *_childrenHolder;
    }

    /** Get the holder of leg-dates. */
    const LegDateHolder_T& getLegDateHolder() const {
      assert (_legDateHolder != NULL);
      return *_legDateHolder;
    }

    /** Get the holder of segment-cabins. */
    void getChildrenHolder (ChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _childrenHolder;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDateStructure object. */
    void setFlightDateStructure (ParentBomStructure_T& ioFlightDateStructure) {
      _parent = &ioFlightDateStructure;
    }
    
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }

    /** Set the segment-cabin children holder. */
    void setChildrenHolder (ChildrenBomHolder_T& ioChildrenHolder) {
      _childrenHolder = &ioChildrenHolder;
    }

    /** Set the leg-date holder.*/
    void setLegDateHolder (LegDateHolder_T& ioLegDateHolder) {
      _legDateHolder = &ioLegDateHolder;
    }
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { 
      ioOut << toString() << std::endl;
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeShortKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return getKey().describe(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return getKey().toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    SegmentDateStructure () : _parent (NULL), _content (NULL),
                              _childrenHolder (NULL), _legDateHolder (NULL) { }
    SegmentDateStructure (const SegmentDateStructure&);

    /** Destructor. */
    virtual ~SegmentDateStructure() { }

  private:
    // Attributes
    /** Parent flight-date. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** Holder of segment-cabins. */
    ChildrenBomHolder_T* _childrenHolder;

    /** Holder of associated leg-dates. */
    LegDateHolder_T* _legDateHolder;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATESTRUCTURE_HPP
