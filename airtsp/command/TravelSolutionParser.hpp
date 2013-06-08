#ifndef __AIRTSP_CMD_TRAVELSOLUTIONPARSER_HPP
#define __AIRTSP_CMD_TRAVELSOLUTIONPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/command/CmdAbstract.hpp>

namespace AIRTSP {  

  /**
   * @brief Class filling the TravelSolutionHolder structure (representing
   * a list of classes/travelSolutions) from a given input file.
   */
  class TravelSolutionParser : public stdair::CmdAbstract {
  public:
    /**
     * Parse the input values from a CSV-formatted travel solution file.
     *
     * @param const std::string& iInputFileName Travel solution file
     *        to be parsed.
     * @return bool Whether or not the parsing was successful.
     */
    static bool parseInputFileAndBuildBom (const stdair::Filename_T&);
  };
}
#endif // __AIRTSP_CMD_TRAVELSOLUTIONPARSER_HPP
