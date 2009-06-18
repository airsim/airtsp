// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomStructure.hpp>
#include <stdair/factory/FacFlightDate.hpp>
#include <stdair/factory/FacSegmentDate.hpp>
// AIRSCHED 
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/factory/FacFlightDate.hpp>
#include <airsched/factory/FacSegmentDate.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  FacSegmentDate* FacSegmentDate::_instance = NULL;

  // ////////////////////////////////////////////////////////////////////
  FacSegmentDate::~FacSegmentDate () {
    _instance = NULL;
  }

  // ////////////////////////////////////////////////////////////////////
  FacSegmentDate& FacSegmentDate::instance () {

    if (_instance == NULL) {
      _instance = new FacSegmentDate();
      assert (_instance != NULL);

      STDAIR::FacSupervisor::instance().registerBomContentFactory (_instance);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate& FacSegmentDate::create (const FlightDate& iFlightDate,
                                       const STDAIR::SegmentDateKey& iKey) {
    // Create the segment-date structure/holder
    STDAIR::SegmentDate& lSegmentDateStructure =
      STDAIR::FacSegmentDate::instance().create (iKey);

    // The created segment-date content (BomContent) object gets a constant
    // reference on its corresponding segment-date structure/holder object
    SegmentDate* aSegmentDate_ptr = new SegmentDate (lSegmentDateStructure);
    assert (aSegmentDate_ptr != NULL);

    // Link the segment-date structure/holder object with its corresponding
    // content object
    STDAIR::FacBomStructure::setContent (lSegmentDateStructure,
                                        *aSegmentDate_ptr);

    // The new object is added to the Bom pool
    bool hasInsertBeenSuccessful = _pool.
      insert (FacBomContent::BomPool_T::value_type (aSegmentDate_ptr,
                                                    &lSegmentDateStructure)).second;

    if (hasInsertBeenSuccessful == false) {
      AIRSCHED_LOG_ERROR ("The segment-date object "
                          << aSegmentDate_ptr->describeShortKey()
                          << " can not be added to the factory-held pool"
                          << " of segment-date objects.");
      throw new MemoryAllocationException();
    }

    // Retrieve the flight-date structure object (STDAIR::FlightDate)
    STDAIR::FlightDate* lFlightDateStructure_ptr =
      FacFlightDate::instance().getFlightDateStructure (iFlightDate);
    
    if (lFlightDateStructure_ptr == NULL) {
      AIRSCHED_LOG_ERROR ("The flight-date object "
                          << iFlightDate.describeShortKey()
                          << " can not be retrieved from the factory-held pool"
                          << " of flight-date objects.");
      throw new MemoryAllocationException();
    }
    assert (lFlightDateStructure_ptr != NULL);

    // Link the FlightDateStructure (STDAIR::FlightDate) with the
    // SegmentDateStructure
    hasInsertBeenSuccessful = STDAIR::FacFlightDate::
      linkFlightDateWithSegmentDate (*lFlightDateStructure_ptr,
                                     lSegmentDateStructure);
    
    if (hasInsertBeenSuccessful == false) {
      AIRSCHED_LOG_ERROR ("The segment-date object " << iKey
                          << " can not be added to the dedicated list "
                          << " of segment-date objects within the flight-date "
                          << iFlightDate.describeShortKey());
      throw new MemoryAllocationException();
    }
    
    return *aSegmentDate_ptr;
  }

}

