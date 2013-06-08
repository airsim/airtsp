// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/LegCabin.hpp>
// AirTSP
#include <airtsp/bom/LegCabinStruct.hpp>

namespace AIRTSP {

  // //////////////////////////////////////////////////////////////////////
  const std::string LegCabinStruct::describe() const {
    std::ostringstream ostr;
    ostr << "        " << _cabinCode << " " << _capacity << ", ";
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void LegCabinStruct::fill (stdair::LegCabin& ioLegCabin) const {
    // Set the Capacity
    ioLegCabin.setCapacities (_capacity);
  }

}
