#ifndef __AIRSCHED_CMD_NETWORKGENERATOR_HPP
#define __AIRSCHED_CMD_NETWORKGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/command/CmdAbstract.hpp>
#include <stdair/bom/OutboundPathTypes.hpp>
// AirSched
#include <airsched/AIRSCHED_Types.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
  class Inventory;
  class FlightDate;
  class SegmentDate;
  class Network;
  class NetworkDate;
  class AirportDate;
  class OutboundPath;
}

namespace AIRSCHED {
  /** Class handling the generation / instantiation of the Network BOM. */
  class NetworkGenerator : public stdair::CmdAbstract {
  public:
    /** Generate the networks.*/
    static void createNetworks (stdair::BomRoot&);

    /** Build the given network.
        <br> Create the OutboundPath objects. */
    static void buildNetwork (stdair::Network&, const stdair::BomRoot&);

    /** Generate the AirportDate and OutboundPath objects corresponding to
        the given Inventory, and add them to the given Network. */
    static void createSinglePaths (stdair::Network&, const stdair::Inventory&);

    /** Generate the AirportDate and OutboundPath objects corresponding to
        the given FlightDate, and add them to the given Network. */
    static void createSinglePaths (stdair::Network&, const stdair::FlightDate&);

    /** Generate the AirportDate and OutboundPath objects corresponding to
        the given SegmentDate, and add them to the given Network. */
    static void createSinglePaths (stdair::Network&, const stdair::SegmentDate&);

    /** Generate the AirportDate and OutboundPath objects corresponding to
        the given SegmentDate, and add them to the given NetworkDate. */
    static void createSinglePaths (stdair::NetworkDate&,
                                   const stdair::SegmentDate&);

    /** Generate the OutboundPath object corresponding to
        the given SegmentDate, and add them to the given AirportDate. */
    static void createSinglePaths (stdair::AirportDate&,
                                   const stdair::SegmentDate&);

    /** Generate the i-fixed-length list of OutboundPath objects for the
        given number of segments (i). */
    static void buildNetwork (stdair::Network&, const stdair::NbOfSegments_T&);

    /** Generate the i-fixed-length list of OutboundPath objects for the
        given number of segments (i). */
    static void buildNetwork (stdair::NetworkDate&,
                               const stdair::NbOfSegments_T&);

    /** Generate the i-fixed-length list of OutboundPath objects for the
        given number of segments (i). */
    static void buildNetwork (stdair::AirportDate&,
                              const stdair::NbOfSegments_T&);

    
  };
 
}
#endif // __AIRSCHED_CMD_NETWORKGENERATOR_HPP
