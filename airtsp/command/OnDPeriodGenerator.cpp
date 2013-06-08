// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
// AirTSP
#include <airtsp/bom/OnDPeriodStruct.hpp>
#include <airtsp/command/OnDPeriodGenerator.hpp>

namespace AIRTSP {

  // ////////////////////////////////////////////////////////////////////
  void OnDPeriodGenerator::
  createOnDPeriod (stdair::BomRoot& ioBomRoot,
                   const OnDPeriodStruct& iOnDPeriodStruct) {
  }
}
