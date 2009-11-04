#ifndef __AIRSCHED_BOM_LEGSTRUCT_HPP
#define __AIRSCHED_BOM_LEGSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/StructAbstract.hpp>
// AIRSCHED
#include <airsched/bom/LegCabinStruct.hpp>

// Forward declarations
namespace stdair {
  class LegDate;
}

namespace AIRSCHED {

  /** Utility Structure for the parsing of Leg structures. */
  struct LegStruct_T : public stdair::StructAbstract {
    // Attributes
    stdair::AirportCode_T _boardPoint;
    stdair::DateOffSet_T _boardDateOffSet;
    stdair::Duration_T _boardTime;
    stdair::AirportCode_T _offPoint;
    stdair::DateOffSet_T _offDateOffSet;
    stdair::Duration_T _offTime;
    stdair::Duration_T _elapsed;
    LegCabinStructList_T _cabinList;

    /** Fill the LegDate objects with the attributes of the LegStruct.
        <br>The given reference date corresponds to the date of the
        FlightDate. Indeed, each Leg gets date off-sets, when compared
        to that (reference) flight-date, both for the board date
        and for the off date. */
    void fill (const stdair::Date_T& iRefDate, stdair::LegDate&) const;
      
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;

    /** Default Constructor. */
    LegStruct_T();
  };

  /** List of Leg strucutres. */
  typedef std::vector<LegStruct_T> LegStructList_T;

}
#endif // __AIRSCHED_BOM_LEGSTRUCT_HPP
