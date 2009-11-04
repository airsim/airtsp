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
   //  /** Generate the Flight-Date objects corresponding to the given
//         Flight-Period, and add them to the given BomRoot. */
//     static void createFlightDates (stdair::BomRoot&,
//                                    const Date_T& iStartAnalysisDate,
//                                    const FlightPeriodStruct_T&);
//     /** Generate an Inventory. */
//     static Inventory& createInventory (stdair::BomRoot&, const AirlineCode_T&);
      
//     /** Generate a FlightDate. */
//     static FlightDate& createFlightDate (stdair::Inventory&, const Date_T&,
//                                          const Date_T&,
//                                          const FlightPeriodStruct_T&);
      
//     /** Generate a LegDate. */
//     static LegDate& createLegDate (stdair::FlightDate&, const LegStruct_T& iLeg,
//                                    const AnalysisStatus_T&);

//     /** Generate a LegCabin. */
//     static void createLegCabin (stdair::LegDate&, const LegCabinStruct_T&,
//                                 const AnalysisStatus_T&);
      
//     /** Generate a SegmentDate. */
//     static void createSegmentDate (stdair::FlightDate&, const SegmentStruct_T&);
      
//     /** Generate a SegmentCabin. */
//     static void createSegmentCabin (stdair::FlightDate&,
//                                     stdair::SegmentDate&,
//                                     const SegmentCabinStruct_T&);
      
//     /** Generate a Class. */
//     static void createClass (stdair::SegmentCabin&, const ClassCode_T&);

//     /** Create the routing between the legs and segments for all the
//         Inventories of the given BomRoot object. */
//     static void createRouting (stdair::BomRoot&);

//     /** Compute the number of available seats
//         for all flights. */
//     static void recalculateAvailabilities (stdair::BomRoot&);

//     /** Create the list of previous built similar flights, e.g. flights
//         departed at the same week day before.*/
//     static void createSimilarFlightDateList (stdair::FlightDate&,
//                                              stdair::Inventory&,
//                                              const Date_T&, const Date_T&);

//     /** Create the list of policies and store them in the segment cabin.*/
//     static void createPolicies (stdair::SegmentCabin&);
  };

}
#endif // __AIRSCHED_CMD_INVENTORYGENERATOR_HPP
