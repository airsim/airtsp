// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
// StdAir
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/Network.hpp>
// AirSched
#include <airsched/command/ScheduleParserHelper.hpp>
#include <airsched/command/ScheduleParser.hpp>
#include <airsched/command/InventoryGenerator.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void ScheduleParser::
  generateInventories (const stdair::Filename_T& iFilename,
                       stdair::BomRoot& ioBomRoot,
                       const stdair::Date_T& iStartAnalysisDate) {

    // Initialise the Flight-Period file parser.
    FlightPeriodFileParser lFlightPeriodParser (ioBomRoot, iStartAnalysisDate,
                                                iFilename);

    // Parse the CSV-formatted schedule input file, and generate the
    // corresponding Inventories for the airlines.
    lFlightPeriodParser.generateInventories ();
      
    // Complete the BomRoot BOM building
    // Create the routings for all the inventories.
    //InventoryGenerator::createDirectAccesses (ioBomRoot);
  }

}
