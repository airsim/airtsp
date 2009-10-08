#ifndef __AIRSCHED_BOM_FLIGHTDATELIST_HPP
#define __AIRSCHED_BOM_FLIGHTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED
#include <airsched/bom/InventoryTypes.hpp>
#include <airsched/bom/FlightDateTypes.hpp>

// Forward declarations
namespace stdair {
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
}
  
namespace AIRSCHED {
  /** Structure which handles the iterators for a flight-date list. */
  struct FlightDateList_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the flight-date list iterators. */
    typedef stdair::BomIterator_T<FlightDate,
                                  FlightDateStructureList_T::const_iterator> iterator;
    typedef stdair::BomIterator_T<FlightDate,
                                  FlightDateStructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the list. */
    iterator begin () const;
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the list. */
    iterator end () const;

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the list. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the list. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    FlightDateList_T ();
    FlightDateList_T (const FlightDateList_T&);
    FlightDateList_T (const InventoryStructure_T&);

    /** Destructor. */
    virtual ~FlightDateList_T();

  private:
    // Attributes
    /** Reference structure. */
    const InventoryStructure_T& _inventoryStructure;
  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATELIST_HPP

