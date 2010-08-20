// //////////////////////////////////////////////////////////////////////
#ifndef __AIRSCHED_BOM_ORIGINDESTINATIONSETTYPES_HPP
#define __AIRSCHED_BOM_ORIGINDESTINATIONSETTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace AIRSCHED {

  // Forward declarations.
  class OriginDestinationSet;

  /** Define the OriginDestinationSet list. */
  typedef std::list<OriginDestinationSet*> OriginDestinationSetList_T;

  /** Define the OriginDestinationSet map. */
  typedef std::map<const stdair::MapKey_T,
                   OriginDestinationSet*> OriginDestinationSetMap_T;
  
}
#endif // __AIRSCHED_BOM_ORIGINDESTINATIONSETTYPES_HPP

