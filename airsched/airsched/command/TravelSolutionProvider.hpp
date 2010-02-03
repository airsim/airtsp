#ifndef __AIRSCHED_COM_CMD_TRAVELSOLUTIONPROVIDER_HPP
#define __AIRSCHED_COM_CMD_TRAVELSOLUTIONPROVIDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/TravelSolutionTypes.hpp>
// AIRSCHED
#include <airsched/command/CmdAbstract.hpp>

// Forward declarations
namespace stdair {
  class Network;
  struct BookingRequestStruct;
}

namespace AIRSCHED {
  
  /** Class handling the generation / instantiation of the travel
      solution block and travel solutions. */
  class TravelSolutionProvider : public CmdAbstract {
    friend class AIRSCHED_Service;
    
  private:
    // ////////// Business Methods /////////
    /** Calculate and return a list of travel solutions corresponding to a given
        product demand. */
    static void getTravelSolutions (stdair::TravelSolutionList_T&,
                                    const stdair::Network&,
                                    const stdair::BookingRequestStruct&);

    
    /** Calculate and return a list of travel solutions corresponding to a given
        product demand. */
    static void getTravelSolutions (stdair::TravelSolutionList_T&,
                                    const stdair::OutboundPathList_T&,
                                    const stdair::BookingRequestStruct&);

    /** Calculate and return a list of travel solutions corresponding to a given
        product demand. */
    static void getTravelSolutions (stdair::TravelSolutionList_T&,
                                    stdair::OutboundPath&,
                                    const stdair::BookingRequestStruct&);
  };

}
#endif // __AIRSCHED_COM_CMD_TRAVELSOLUTIONPROVIDER_HPP
