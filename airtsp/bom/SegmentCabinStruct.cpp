// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/SegmentCabin.hpp>
// AirTSP
#include <airtsp/bom/SegmentCabinStruct.hpp>

namespace AIRTSP {

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentCabinStruct::describe() const {
    std::ostringstream ostr;
    ostr << "        " << _cabinCode << " " << _classes;
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentCabinStruct::fill (stdair::SegmentCabin& ioSegmentCabin) const {  
  }

}
