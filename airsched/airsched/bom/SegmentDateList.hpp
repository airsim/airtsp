#ifndef __AIRSCHED_BOM_SEGMENTDATELIST_HPP
#define __AIRSCHED_BOM_SEGMENTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED
#include <airsched/bom/FlightDateTypes.hpp>
#include <airsched/bom/SegmentDateTypes.hpp>

// Forward declarations
namespace stdair {
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
}
  
namespace AIRSCHED {
  /** Structure which handles the iterators for a segment-date list. */
  struct SegmentDateList_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the segment-date list iterators. */
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureList_T::const_iterator> iterator;
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the list. */
    iterator begin () const;
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the list. */
    iterator end () const;

    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the list. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the end of the list. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    SegmentDateList_T ();
    SegmentDateList_T (const SegmentDateList_T&);
    SegmentDateList_T (const FlightDateStructure_T&);

    /** Destructor. */
    virtual ~SegmentDateList_T();

  private:
    // Attributes
    /** Reference structure. */
    const FlightDateStructure_T& _flightDateStructure;
  };

}
#endif // __AIRSCHED_BOM_SEGMENTDATELIST_HPP

