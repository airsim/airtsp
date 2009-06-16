// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR 
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacSegmentDate.hpp>

namespace STDAIR {

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

      FacSupervisor::instance().registerBomAbstractFactory (_instance);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate& FacSegmentDate::create (const SegmentDateKey& iKey) {
    SegmentDate* aSegmentDate_ptr = NULL;

    aSegmentDate_ptr = new SegmentDate (iKey);
    assert (aSegmentDate_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aSegmentDate_ptr);

    return *aSegmentDate_ptr;
  }

}

