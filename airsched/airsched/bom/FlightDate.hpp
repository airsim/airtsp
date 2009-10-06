#ifndef __AIRSCHED_BOM_FLIGHTDATE_HPP
#define __AIRSCHED_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomStructureList.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BomIterator.hpp>
// AIRSCHED 
#include <airsched/bom/FlightDateTypes.hpp>
#include <airsched/bom/SegmentDateTypes.hpp>
#include <airsched/bom/LegDateTypes.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
  class BomStructure;
}
  
namespace AIRSCHED {

  // Forward declarations
  class Inventory;
  
  /** Class representing the actual functional/business content for a
      flight-date. */
  class FlightDate : public stdair::BomContent {
    friend class stdair::FacBomContent;

  public:
    // Type definitions
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the types which require to be specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Inventory ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef FlightDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef SegmentDate ContentChild_T;

        /** Definition allowing to retrieve the associated second
         BOM content child type. */
    typedef LegDate SecondContentChild_T;

    public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the segment-date list iterators. */
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureList_T::const_iterator> segment_date_list_iterator;
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureList_T::const_reverse_iterator> segment_date_list_reverse_iterator;

    /** Define the segment-date map iterators. */
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureMap_T::const_iterator> segment_date_map_iterator;
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureMap_T::const_reverse_iterator> segment_date_map_reverse_iterator;

    /** Define the leg-date list iterators. */
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureList_T::const_iterator> leg_date_list_iterator;
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureList_T::const_reverse_iterator> leg_date_list_reverse_iterator;

    /** Define the leg-date map iterators. */
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureMap_T::const_iterator> leg_date_map_iterator;
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureMap_T::const_reverse_iterator> leg_date_map_reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
  
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
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _flightDateStructure;
    }

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the list. */
    segment_date_list_iterator segmentDateListBegin () const;
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the list. */
    segment_date_list_iterator segmentDateListEnd () const;

    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the list. */
    segment_date_list_reverse_iterator segmentDateListRBegin () const;
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the end of the list. */
    segment_date_list_reverse_iterator segmentDateListREnd () const;

    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the map. */
    segment_date_map_iterator segmentDateMapBegin () const;
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the map. */
    segment_date_map_iterator segmentDateMapEnd () const;

    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the map. */
    segment_date_map_reverse_iterator segmentDateMapRBegin () const;
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the end of the map. */
    segment_date_map_reverse_iterator segmentDateMapREnd () const;

    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the list. */
    leg_date_list_iterator legDateListBegin () const;
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the list. */
    leg_date_list_iterator legDateListEnd () const;

    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the list. */
    leg_date_list_reverse_iterator legDateListRBegin () const;
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the end of the list. */
    leg_date_list_reverse_iterator legDateListREnd () const;

    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the map. */
    leg_date_map_iterator legDateMapBegin () const;
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the map. */
    leg_date_map_iterator legDateMapEnd () const;

    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the map. */
    leg_date_map_reverse_iterator legDateMapRBegin () const;
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the end of the map. */
    leg_date_map_reverse_iterator legDateMapREnd () const;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (BomStructure_T&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _flightDateStructure;
  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATE_HPP

