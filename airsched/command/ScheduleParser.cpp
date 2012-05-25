// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
// StdAir
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomRoot.hpp>
// AirSched
#include <airsched/command/SegmentPathGenerator.hpp>
#include <airsched/command/ScheduleParserHelper.hpp>
#include <airsched/command/ScheduleParser.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void ScheduleParser::generateInventories
  (const stdair::ScheduleFilePath& iScheduleFilename,
   stdair::BomRoot& ioBomRoot) {

    const stdair::Filename_T lFilename = iScheduleFilename.name();

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (lFilename);

    if (doesExistAndIsReadable == false) {
      throw ScheduleInputFileNotFoundException ("The schedule file " + lFilename
                                                + " does not exist or can not "
                                                "be read");
    }

    // Initialise the Flight-Period file parser.
    FlightPeriodFileParser lFlightPeriodParser (ioBomRoot, lFilename);

    // Parse the CSV-formatted schedule input file, and generate the
    // corresponding Inventories for the airlines.
    lFlightPeriodParser.generateInventories();
  }

}
