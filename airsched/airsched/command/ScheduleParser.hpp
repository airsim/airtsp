#ifndef __AIRSCHED_CMD_SCHEDULEPARSER_HPP
#define __AIRSCHED_CMD_SCHEDULEPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// AIRSCHED
#include <airsched/command/CmdAbstract.hpp>

// Forward declarations.
namespace stdair {
  class AirlineFeatureSet;
}

namespace AIRSCHED {
  // Forward declarations.
  class BomRoot;
  
  /** Class wrapping the parser entry point. */
  class ScheduleParser : public CmdAbstract {
  public:
    /** Parses the CSV file describing the airline schedules for the
        simulator, and generates the inventories accordingly.
        @param const std::string& The file-name of the CSV-formatted schedule
        input file. */
    static stdair::BomRoot& generateInventories(const std::string&,
                                                const stdair::AirlineFeatureSet&,
                                                const Date_T&);
  };
}
#endif // __AIRSCHED_CMD_SCHEDULEPARSER_HPP
