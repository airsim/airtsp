// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/BomRoot.hpp>
// AirSched
#include <airsched/command/OnDParserHelper.hpp>
#include <airsched/command/OnDParser.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void OnDParser::generateOnDPeriods (const stdair::ODFilePath& iODFilename,
                                      stdair::BomRoot& ioBomRoot) {

    const stdair::Filename_T lFilename = iODFilename.name();

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (lFilename);

    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The O&D input file, '" << lFilename
                        << "', can not be retrieved on the file-system");
      throw OnDInputFileNotFoundException ("The O&D file " + lFilename
                                           + " does not exist or can not be "
                                           "read");
    }

    // Initialise the O&D-Period file parser.
    OnDPeriodFileParser lOnDPeriodParser (lFilename, ioBomRoot);

    // Parse the CSV-formatted O&D input file, and generate the
    // corresponding O&D-Period for the airlines.
    lOnDPeriodParser.generateOnDPeriods();
  }

}
