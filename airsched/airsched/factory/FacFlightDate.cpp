// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// AIRSCHED 
#include <airsched/factory/FacFlightDate.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/factory/FacSupervisor.hpp>
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

      FacSupervisor::instance().registerBomFactory (_instance);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate& FacFlightDate::create () {
    FlightDate* aFlightDate_ptr = NULL;

    aFlightDate_ptr = new FlightDate ();
    assert (aFlightDate_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aFlightDate_ptr);

    return *aFlightDate_ptr;
  }

}

