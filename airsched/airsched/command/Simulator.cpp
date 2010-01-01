// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <sstream>
// STDAIR
#include <stdair/bom/BomManager.hpp>
// AIRSCHED
#include <airsched/bom/BomRoot.hpp>
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/bom/LegDate.hpp>
#include <airsched/bom/SegmentCabin.hpp>
#include <airsched/bom/LegCabin.hpp>
#include <airsched/bom/BookingClass.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void Simulator::simulate (stdair::BomRoot& ioBomRoot) {

    // Delegate to the dedicated StdAir utility class
    std::ostringstream oStream;
    stdair::BomManager::display (oStream, ioBomRoot);

    // DEBUG
    AIRSCHED_LOG_DEBUG ("BOM Tree: ");
    AIRSCHED_LOG_DEBUG (oStream.str());
  }

}
