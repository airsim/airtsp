// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// STDAIR
#include <stdair/bom/SegmentCabin.hpp>
// AIRSCHED
#include <airsched/bom/SegmentCabinStruct.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentCabinStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << "        " << _cabinCode << " " << _classes;
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentCabinStruct_T::fill (stdair::SegmentCabin& ioSegmentCabin) const {  
  }

}
