// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <string>
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/Network.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AirSched
#include <airsched/command/ScheduleParserHelper.hpp>
#include <airsched/command/ScheduleParser.hpp>
#include <airsched/command/InventoryGenerator.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  stdair::BomRoot& ScheduleParser::
  generateInventories (const std::string& iFilename,
                       const stdair::AirlineFeatureSet& iAirlineFeatureSet,
                       const Date_T& iStartAnalysisDate) {
    stdair::BomRoot& oBomRoot =
      stdair::FacBomContent::instance().create<stdair::BomRoot> ();

    // Set the AirlineFeatureSet for the BomRoot.
    oBomRoot.setAirlineFeatureSet (&iAirlineFeatureSet);

    // Initialise the Flight-Period file parser.
    FlightPeriodFileParser lFlightPeriodParser (oBomRoot, iStartAnalysisDate,
                                                iFilename);

    // Parse the CSV-formatted schedule input file, and generate the
    // corresponding Inventories for the airlines.
    lFlightPeriodParser.generateInventories ();
      
    // Complete the BomRoot BOM building
    // Create the routings for all the inventories.
    InventoryGenerator::createDirectAccesses (oBomRoot);

    return oBomRoot;
  }

}
