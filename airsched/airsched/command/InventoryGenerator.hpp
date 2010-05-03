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
  class Inventory;
  class FlightDate;
  class LegDate;
  class LegCabin;
  class SegmentDate;
  class SegmentCabin;
}

namespace AIRSCHED {

  // Forward declarations
  struct FlightPeriodStruct_T;
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
    /** Generate the flight-date objects corresponding to the given
        Flight-Period, and add them to the given BomRoot. */
    static void createFlightDates (stdair::BomRoot&,
                                   const FlightPeriodStruct_T&);

    /** Generate a flight-date. */
    static stdair::FlightDate& createFlightDate (const stdair::Inventory&,
                                                 const stdair::Date_T&,
                                                 const FlightPeriodStruct_T&);
      
    /** Generate a leg-date. */
    static stdair::LegDate& createLegDate (const stdair::FlightDate&,
                                           const stdair::Date_T&,
                                           const LegStruct_T&);

    /** Generate a leg-cabin. */
    static void createLegCabin (const stdair::LegDate&, const LegCabinStruct_T&);
      
    /** Generate a segment-date. */
    static void createSegmentDate (const stdair::FlightDate&, 
                                   const SegmentStruct_T&);
      
    /** Generate a segment-cabin. */
    static void createSegmentCabin (const stdair::SegmentDate&,
                                    const SegmentCabinStruct_T&);
      
    /** Generate a booking class. */
    static void createClass (const stdair::SegmentCabin&, 
                             const stdair::ClassCode_T&);

    /** Create the list of previous built similar flights, e.g. flights
        departed at the same week day before.*/
    static void createSimilarFlightDateList (const stdair::FlightDate&,
                                             const stdair::Inventory&,
                                             const stdair::Date_T&,
                                             const stdair::Date_T&);

    /** Create the direct accesses within the invetories suck as links between
        leg-date and segment-date, ect. */
    static void createDirectAccesses (const stdair::BomRoot&);
    static void createDirectAccesses (const stdair::Inventory&);
    static void createDirectAccesses (const stdair::FlightDate&);
    static void createDirectAccesses (const stdair::SegmentDate&);


  };

}
#endif // __AIRSCHED_CMD_INVENTORYGENERATOR_HPP
