// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomContent.hpp>

namespace STDAIR {
  
  FacBomContent* FacBomContent::_instance = NULL;

  // ////////////////////////////////////////////////////////////////////
  FacBomContent& FacBomContent::instance () {

    if (_instance == NULL) {
      _instance = new FacBomContent();
      assert (_instance != NULL);

      FacSupervisor::instance().registerBomContentFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  FacBomContent::~FacBomContent() {
    clean ();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBomContent::setContent (BomStructure& ioBomStructure,
                                  BomContent& ioBomContent) {
    ioBomStructure._content = &ioBomContent;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FacBomContent::clean() {
    for (StructureMapFromContent_T::iterator itBom = _structureMap.begin();
	 itBom != _structureMap.end(); itBom++) {
      const BomContent* currentBom_ptr = itBom->first;
      assert (currentBom_ptr != NULL);
      
      _structureMap.erase (currentBom_ptr);
      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _structureMap.clear();

    // Reset the static instance
    _instance = NULL;
  }

}
