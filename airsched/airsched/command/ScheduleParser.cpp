// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <string>
// STDAIR
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AIRSCHED
#include <airsched/command/ScheduleParserHelper.hpp>
#include <airsched/command/ScheduleParser.hpp>
#include <airsched/command/InventoryGenerator.hpp>
#include <airsched/service/Logger.hpp>

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
      
    // Complete the BomRoot BOM building: create the routings
    // for all the flights of the (world) schedule.
    //InventoryGenerator::createRouting (oBomRoot);

    // Complete the BomRoot BOM building: compute the number of
    // available seats for all flights.
    //InventoryGenerator::recalculateAvailabilities (oBomRoot);

    return oBomRoot;
  }

}
