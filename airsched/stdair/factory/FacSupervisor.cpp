// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/factory/FacBomAbstract.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/factory/FacSupervisor.hpp>

namespace STDAIR {

  FacSupervisor* FacSupervisor::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor& FacSupervisor::instance() {
    if (_instance == NULL) {
      _instance = new FacSupervisor();
    }

    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::
  registerBomAbstractFactory (FacBomAbstract* ioFacBomAbstract_ptr) {
    _bomAbstractPool.push_back (ioFacBomAbstract_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::
  registerBomContentFactory (FacBomContent* ioFacBomContent_ptr) {
    _bomContentPool.push_back (ioFacBomContent_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor::~FacSupervisor() {
    cleanBomAbstractLayer();
    cleanBomContentLayer();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanBomAbstractLayer() {
    for (BomAbstractFactoryPool_T::const_iterator itFactory =
           _bomAbstractPool.begin();
         itFactory != _bomAbstractPool.end(); itFactory++) {
      const FacBomAbstract* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }

    // Empty the pool of BomAbstract Factories
    _bomAbstractPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanBomContentLayer() {
    for (BomContentFactoryPool_T::const_iterator itFactory =
           _bomContentPool.begin();
         itFactory != _bomContentPool.end(); itFactory++) {
      const FacBomContent* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }

    // Empty the pool of BomContent Factories
    _bomContentPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanFactory () {
	if (_instance != NULL) {
		_instance->cleanBomAbstractLayer();
		_instance->cleanBomContentLayer();
 	}
    delete _instance; _instance = NULL;
  }

}
