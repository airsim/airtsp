#ifndef __AIRSCHED_COM_CMD_SIMULATOR_HPP
#define __AIRSCHED_COM_CMD_SIMULATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED
#include <airsched/command/CmdAbstract.hpp>

namespace AIRSCHED {
  /** Class implementing a small simulation, which uses the Airline Schedule. */
  class Simulator : public CmdAbstract {
  public:

    // ////////// Business Methods /////////
    /** Perform a small simulation, which uses the Airline Schedule. */
    static void simulate ();
  };

}
#endif // __AIRSCHED_COM_CMD_SIMULATOR_HPP
