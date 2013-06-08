#ifndef __AIRTSP_BOM_AIRPORTLIST_HPP
#define __AIRTSP_BOM_AIRPORTLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <set>
#include <vector>
// StdAir
#include <stdair/stdair_basic_types.hpp>

namespace AIRTSP {

  /** Define lists of Airport Codes. */
  typedef std::set<stdair::AirportCode_T> AirportList_T;
  typedef std::vector<stdair::AirportCode_T> AirportOrderedList_T;

}
#endif // __AIRTSP_BOM_AIRPORTLIST_HPP
