// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomStructure.hpp>
#include <stdair/factory/FacFlightDate.hpp>
// AIRSCHED 
#include <airsched/factory/FacFlightDate.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  FacFlightDate* FacFlightDate::_instance = NULL;

  // ////////////////////////////////////////////////////////////////////
  FacFlightDate::~FacFlightDate () {
    _instance = NULL;
  }

  // ////////////////////////////////////////////////////////////////////
  FacFlightDate& FacFlightDate::instance () {

    if (_instance == NULL) {
      _instance = new FacFlightDate();
      assert (_instance != NULL);

      STDAIR::FacSupervisor::instance().registerBomContentFactory (_instance);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate& FacFlightDate::create (const STDAIR::FlightDateKey& iKey) {
    
    // Create the flight-date structure/holder
    STDAIR::FlightDate& lFlightDateStructure =
      STDAIR::FacFlightDate::instance().create (iKey);

    // The created flight-date content (BomContent) object gets a constant
    // reference on its corresponding flight-date structure/holder object
    FlightDate* aFlightDate_ptr = new FlightDate (lFlightDateStructure);
    assert (aFlightDate_ptr != NULL);

    // Link the flight-date structure/holder object with its corresponding
    // content object
    STDAIR::FacBomStructure::setContent (lFlightDateStructure, *aFlightDate_ptr);

    // The new object is added to the Bom pool
    const bool hasInsertBeenSuccessful = _pool.
      insert (FacBomContent::BomPool_T::value_type (aFlightDate_ptr,
                                                    &lFlightDateStructure)).second;
    if (hasInsertBeenSuccessful == false) {
      AIRSCHED_LOG_ERROR ("The flight-date object " << *aFlightDate_ptr
                          << " can not be added to the factory-held pool"
                          << " of flight-date objects.");
      throw new MemoryAllocationException();
    }
    
    return *aFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  STDAIR::FlightDate* FacFlightDate::
  getFlightDateStructure (const FlightDate& iFlightDate) {
    STDAIR::FlightDate* oFlightDateStructure_ptr = NULL;
    
    FacBomContent::BomPool_T::iterator itFlightDateStructure =
      _pool.find (&iFlightDate);
    if (itFlightDateStructure != _pool.end()) {
      oFlightDateStructure_ptr =
        dynamic_cast<STDAIR::FlightDate*> (itFlightDateStructure->second);
    }
    
    return oFlightDateStructure_ptr;
  }
  
}

