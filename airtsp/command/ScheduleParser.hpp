#ifndef __AIRTSP_CMD_SCHEDULEPARSER_HPP
#define __AIRTSP_CMD_SCHEDULEPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/command/CmdAbstract.hpp>
#include <stdair/stdair_file.hpp>

// Forward declarations.
namespace stdair {
  class BomRoot;
}

namespace AIRTSP {
  
  /** Class wrapping the parser entry point. */
  class ScheduleParser : public stdair::CmdAbstract {
  public:
    /** Parse the CSV file describing the airline schedules for the
        simulator, and generates the inventories accordingly.
        @param const stdair::ScheduleFilePath& The file-name of the
        CSV-formatted schedule input file.
        @param stdair::BomRoot& Root of the BOM tree. */
    static void generateInventories (const stdair::ScheduleFilePath&,
                                     stdair::BomRoot&);
  };
}
#endif // __AIRTSP_CMD_SCHEDULEPARSER_HPP
