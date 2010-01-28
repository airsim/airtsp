#ifndef __AIRSCHED_CMD_SCHEDULEPARSER_HPP
#define __AIRSCHED_CMD_SCHEDULEPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
// AirSched
#include <airsched/command/CmdAbstract.hpp>

// Forward declarations.
namespace stdair {
  class BomRoot;
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
    static void generateInventories (const stdair::Filename_T&, stdair::BomRoot&,
                                     const stdair::Date_T&);
  };
}
#endif // __AIRSCHED_CMD_SCHEDULEPARSER_HPP
