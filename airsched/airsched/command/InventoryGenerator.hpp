#ifndef __AIRSCHED_CMD_INVENTORYGENERATOR_HPP
#define __AIRSCHED_CMD_INVENTORYGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED 
#include <airsched/AIRSCHED_Types.hpp>
#include <airsched/command/CmdAbstract.hpp>

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
  class InventoryGenerator : public CmdAbstract {
    // Only the following class may use methods of InventoryGenerator.
    // Indeed, as those methods build the BOM, it is not good to expose
    // them publicly.
    friend class FlightPeriodFileParser;
    friend class FFFlightPeriodFileParser;
    friend struct ScheduleParserHelper::doEndFlight;
    friend class ScheduleParser;
  private:
    /** Generate the Flight-Date objects corresponding to the given
        Flight-Period, and add them to the given BomRoot. */
    static void createFlightDates (stdair::BomRoot&,
                                   const Date_T& iStartAnalysisDate,
                                   const FlightPeriodStruct_T&);

    /** Generate an Inventory. */
    static stdair::Inventory& createInventory (stdair::BomRoot&,
                                               const stdair::AirlineCode_T&);
      
    /** Generate a FlightDate. */
    static stdair::FlightDate& createFlightDate (stdair::Inventory&,
                                                 const Date_T&, const Date_T&,
                                                 const FlightPeriodStruct_T&);
      
    /** Generate a LegDate. */
    static stdair::LegDate& createLegDate (stdair::FlightDate&,
                                           const stdair::Date_T&,
                                           const LegStruct_T&,
                                           const stdair::AnalysisStatus_T&);

    /** Generate a LegCabin. */
    static void createLegCabin (stdair::LegDate&, const LegCabinStruct_T&,
                                const stdair::AnalysisStatus_T&);
      
    /** Generate a SegmentDate. */
    static void createSegmentDate (stdair::FlightDate&, const SegmentStruct_T&);
      
    /** Generate a SegmentCabin. */
    static void createSegmentCabin (stdair::FlightDate&,
                                    stdair::SegmentDate&,
                                    const SegmentCabinStruct_T&);
      
    /** Generate a Class. */
    static void createClass (stdair::SegmentCabin&, const stdair::ClassCode_T&);

    /** Create the direct accesses within the invetories such as
        links between inventory and booking class, links between
        leg-date and segment-date, ect. */
    static void createDirectAccesses (stdair::BomRoot&);

//     /** Compute the number of available seats
//         for all flights. */
//     static void recalculateAvailabilities (stdair::BomRoot&);

    /** Create the list of previous built similar flights, e.g. flights
        departed at the same week day before.*/
    static void createSimilarFlightDateList (stdair::FlightDate&,
                                             stdair::Inventory&,
                                             const stdair::Date_T&,
                                             const stdair::Date_T&);

//     /** Create the list of policies and store them in the segment cabin.*/
//     static void createPolicies (stdair::SegmentCabin&);
  };

}
#endif // __AIRSCHED_CMD_INVENTORYGENERATOR_HPP
