#ifndef __AIRSCHED_BOM_AIRPORTLIST_HPP
#define __AIRSCHED_BOM_AIRPORTLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <set>
#include <vector>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace AIRSCHED {

  /** Define lists of Airport Codes. */
  typedef std::set<stdair::AirportCode_T> AirportList_T;
  typedef std::vector<stdair::AirportCode_T> AirportOrderedList_T;

}
#endif // __AIRSCHED_BOM_AIRPORTLIST_HPP
