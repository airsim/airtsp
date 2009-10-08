#ifndef __AIRSCHED_BOM_FLIGHTDATEMAP_HPP
#define __AIRSCHED_BOM_FLIGHTDATEMAP_HPP

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
  struct FlightDateMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the flight-date map iterators. */
    typedef stdair::BomIterator_T<FlightDate,
                                  FlightDateStructureMap_T::const_iterator> iterator;
    typedef stdair::BomIterator_T<FlightDate,
                                  FlightDateStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the map. */
    iterator begin () const;
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the map. */
    iterator end () const;

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the map. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the map. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    FlightDateMap_T ();
    FlightDateMap_T (const FlightDateMap_T&);
    FlightDateMap_T (const InventoryStructure_T&);

    /** Destructor. */
    virtual ~FlightDateMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const InventoryStructure_T& _inventoryStructure;
  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATEMAP_HPP

