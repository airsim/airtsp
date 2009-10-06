#ifndef __AIRSCHED_COM_CMD_SIMULATOR_HPP
#define __AIRSCHED_COM_CMD_SIMULATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED
#include <airsched/command/CmdAbstract.hpp>

namespace AIRSCHED {

  class Inventory;
  class FlightDate;

  /** Class implementing a small simulation, which uses the Airline Schedule. */
  class Simulator : public CmdAbstract {
  public:

    // ////////// Business Methods /////////
    /** Perform a small simulation, which uses the Airline Schedule. */
    static void simulate ();

    /** Test the iterator. */
    static void testIteratorInventory (const Inventory&);
    static void testIteratorFlightDate (const FlightDate&);
  };

}
#endif // __AIRSCHED_COM_CMD_SIMULATOR_HPP
