// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/factory/FacBomStructure.hpp>

namespace STDAIR {
  
  // //////////////////////////////////////////////////////////////////////
  FacBomStructure::~FacBomStructure() {
    clean ();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBomStructure::setContent (BomStructure& ioBomStructure,
                                   BomContent& ioBomContent) {
    ioBomStructure._content = &ioBomContent;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FacBomStructure::clean() {
    for (BomPool_T::iterator itBom = _structurePool.begin();
	 itBom != _structurePool.end(); itBom++) {
      BomStructure* currentBom_ptr = *itBom;
      assert (currentBom_ptr != NULL);

      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _structurePool.clear();
  }

}
