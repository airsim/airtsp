#ifndef __AIRSCHED_CMD_SEGMENTPATHGENERATOR_HPP
#define __AIRSCHED_CMD_SEGMENTPATHGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/command/CmdAbstract.hpp>
// AirSched
#include <airsched/AIRSCHED_Types.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
  class Inventory;
  class FlightPeriod;
  class SegmentPeriod;
}

namespace AIRSCHED {
  //Forward declarations
  class ReachableUniverse;
  class OriginDestinationSet;
  class SegmentPathPeriod;
  
  /** Class handling the generation / instantiation of the network BOM. */
  class SegmentPathGenerator : public stdair::CmdAbstract {
  public:
    /** Generate the segment path network. */
    static void createSegmentPathNetwork (stdair::BomRoot&);

    /** Generate the single-segment segment path periods while browsing the
        inventory and flight-period lists. */
    static void createSinglePaths (stdair::BomRoot&, const stdair::Inventory&);
    static void createSinglePaths (stdair::BomRoot&, const stdair::Inventory&,
                                   const stdair::FlightPeriod&);

    /** Generate the single-segment segment path period with the
        given segment-period. */
    static void createSinglePath (stdair::BomRoot&, const stdair::Inventory&,
                                  const stdair::FlightPeriod&,
                                  stdair::SegmentPeriod&);
    static void createSinglePath (ReachableUniverse&, const stdair::Inventory&,
                                  const stdair::FlightPeriod&,
                                  stdair::SegmentPeriod&);

    /** Generate the i-fixed-length list of segment path period objects. */
    static void buildSegmentPathNetwork (const stdair::BomRoot&,
                                         const stdair::NbOfSegments_T&);
    static void buildSegmentPathNetwork (const stdair::BomRoot&,
                                         ReachableUniverse&,
                                         const stdair::NbOfSegments_T&);

    
  };
 
}
#endif // __AIRSCHED_CMD_SEGMENTPATHGENERATOR_HPP
