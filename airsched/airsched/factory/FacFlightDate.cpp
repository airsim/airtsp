// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/factory/FacSupervisor.hpp>
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

    FlightDate* aFlightDate_ptr = new FlightDate (lFlightDateStructure);
    assert (aFlightDate_ptr != NULL);

    // The new object is added to the Bom pool
    const bool hasInsertBeenSuccessful = _pool.
      insert (FacBomContent::BomPool_T::value_type (aFlightDate_ptr,
                                                    &lFlightDateStructure)).second;
    AIRSCHED_LOG_DEBUG ("Pool size = " << _pool.size());
    if (hasInsertBeenSuccessful == false) {
      AIRSCHED_LOG_ERROR ("The flight-date object " << *aFlightDate_ptr
                          << " can not be added to the factory-held pool"
                          << " of flight-date objects.");
      throw new MemoryAllocationException();
    }
    
    return *aFlightDate_ptr;
  }

}

