// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// AIRSCHED
#include <airsched/bom/BomRoot.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (BomStructure_T& ioBomRootStructure)
    : stdair::BomRoot (ioBomRootStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

}