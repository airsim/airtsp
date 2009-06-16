// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomContent.hpp>
#include <stdair/factory/FacBomContent.hpp>

namespace STDAIR {
  
  // //////////////////////////////////////////////////////////////////////
  FacBomContent::~FacBomContent() {
    clean ();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBomContent::clean() {
    for (BomPool_T::iterator itBom = _pool.begin();
	 itBom != _pool.end(); itBom++) {
      const STDAIR::BomContent* currentBom_ptr = itBom->first;
      assert (currentBom_ptr != NULL);
      
      _pool.erase (currentBom_ptr);
      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _pool.clear();
  }

}
