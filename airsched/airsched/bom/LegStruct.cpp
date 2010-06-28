// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// STDAIR
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/bom/LegDate.hpp>
// AIRSCHED
#include <airsched/bom/LegStruct.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  LegStruct_T::LegStruct_T ()
    : _boardingDateOffset (stdair::DEFAULT_DATE_OFFSET),
      _offDateOffset (stdair::DEFAULT_DATE_OFFSET) {
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string LegStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << "    " << _boardingPoint << " / "
         << boost::posix_time::to_simple_string(_boardingTime);
    if (_boardingDateOffset.days() != 0) {
      ostr << " [" << _boardingDateOffset.days() << "]";
    }
    ostr << " -- " << _offPoint << " / "
         << boost::posix_time::to_simple_string(_offTime);
    if (_offDateOffset.days() != 0) {
      ostr << " [" << _offDateOffset.days() << "]";
    }
    ostr << " --> "
         << boost::posix_time::to_simple_string(_elapsed)
         << std::endl;
    for (LegCabinStructList_T::const_iterator itCabin = _cabinList.begin();
         itCabin != _cabinList.end(); itCabin++) {
      const LegCabinStruct_T& lCabin = *itCabin;
      ostr << lCabin.describe();
    }
    ostr << std::endl;
    
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void LegStruct_T::fill (const stdair::Date_T& iRefDate,
                          stdair::LegDate& ioLegDate) const {
    // Set the Off Point
    ioLegDate.setOffPoint (_offPoint);

    // Set the Boarding Date
    ioLegDate.setBoardingDate (iRefDate + _boardingDateOffset);

    // Set the Boarding Time
    ioLegDate.setBoardingTime (_boardingTime);
      
    // Set the Off Date
    ioLegDate.setOffDate (iRefDate + _offDateOffset);

    // Set the Off Time
    ioLegDate.setOffTime (_offTime);

    // Set the Elapsed Time
    ioLegDate.setElapsedTime (_elapsed);
  }

}
