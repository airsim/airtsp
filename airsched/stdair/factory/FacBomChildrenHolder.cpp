// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomChildrenHolder.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomChildrenHolder.hpp>

namespace stdair {
  
  FacBomChildrenHolder* FacBomChildrenHolder::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacBomChildrenHolder::~FacBomChildrenHolder() {
    clean ();
  }

  // ////////////////////////////////////////////////////////////////////
  FacBomChildrenHolder& FacBomChildrenHolder::instance () {

    if (_instance == NULL) {
      _instance = new FacBomChildrenHolder();
      assert (_instance != NULL);

      FacSupervisor::instance().registerBomChildrenHolderFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBomChildrenHolder::clean() {
    for (BomChildrenHolderPool_T::iterator itBom = _childrenHolderPool.begin();
	 itBom != _childrenHolderPool.end(); itBom++) {
      // BomChildrenHolder<class BOM_CHILD>* currentBom_ptr = *itBom;
      BomChildrenHolder* currentBom_ptr = *itBom;
      assert (currentBom_ptr != NULL);

      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _childrenHolderPool.clear();

    // Reset the static instance
    _instance = NULL;
  }

}
