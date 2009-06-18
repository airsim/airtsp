// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// STDAIR 
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacFlightDate.hpp>

namespace STDAIR {

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

      FacSupervisor::instance().registerBomStructureFactory (_instance);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate& FacFlightDate::create (const FlightDateKey& iKey) {
    FlightDate* aFlightDate_ptr = NULL;

    aFlightDate_ptr = new FlightDate (iKey);
    assert (aFlightDate_ptr != NULL);

    // The new object is added to the Bom pool
    _structurePool.push_back (aFlightDate_ptr);

    return *aFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  bool FacFlightDate::
  linkFlightDateWithSegmentDate (FlightDate& ioFlightDate,
                                 SegmentDate& ioSegmentDate) {

    // Set the parent of the SegmentDate object
    ioSegmentDate.setFlightDate (ioFlightDate);

    // Retrieve the short key
    const SegmentDateKey& lSegmentDateKey = ioSegmentDate.getKey();
    const std::string& lSegmentDateKeyStr = lSegmentDateKey.toString();

    // Insert the SegmentDate object in the dedicated list
    const bool hasInsertBeenSuccessful = ioFlightDate._segmentList.
      insert (SegmentDateList_T::value_type (lSegmentDateKeyStr,
                                             &ioSegmentDate)).second;

    if (hasInsertBeenSuccessful == false) {
      return hasInsertBeenSuccessful;
    }

    return true;
  }

}
