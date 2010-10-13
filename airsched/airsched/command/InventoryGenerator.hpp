#ifndef __AIRSCHED_CMD_INVENTORYGENERATOR_HPP
#define __AIRSCHED_CMD_INVENTORYGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/command/CmdAbstract.hpp>
// AirSched
#include <airsched/AIRSCHED_Types.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
  class FlightPeriod;
}

namespace AIRSCHED {

  // Forward declarations
  struct FlightPeriodStruct_T;
  struct LegStruct_T;
  struct SegmentStruct_T;
  struct LegCabinStruct_T;
  struct SegmentCabinStruct_T;
  namespace ScheduleParserHelper {
    struct doEndFlight;
  }
    
  /** Class handling the generation / instantiation of the Inventory BOM. */
  class InventoryGenerator : public stdair::CmdAbstract {
    // Only the following class may use methods of InventoryGenerator.
    // Indeed, as those methods build the BOM, it is not good to expose
    // them publicly.
    friend class FlightPeriodFileParser;
    friend class FFFlightPeriodFileParser;
    friend struct ScheduleParserHelper::doEndFlight;
    friend class ScheduleParser;

  private:
    /** Generate the flight-period objects corresponding to the given
        FlightPeriodStruct, and add them to the given BomRoot. */
    static void createFlightPeriod (stdair::BomRoot&,
                                    const FlightPeriodStruct_T&);

    /** Generate a segment-period. */
    static void createSegmentPeriods (stdair::FlightPeriod&,
                                      const FlightPeriodStruct_T&);

  };

}
#endif // __AIRSCHED_CMD_INVENTORYGENERATOR_HPP
