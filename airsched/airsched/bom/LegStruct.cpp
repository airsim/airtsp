// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
// STDAIR
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/bom/LegDate.hpp>
// AIRSCHED
#include <airsched/bom/LegStruct.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  LegStruct_T::LegStruct_T ()
    : _boardDateOffSet (stdair::DEFAULT_DATE_OFFSET),
      _offDateOffSet (stdair::DEFAULT_DATE_OFFSET) {
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string LegStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << "    " << _boardPoint << " / "
         << boost::posix_time::to_simple_string(_boardTime);
    if (_boardDateOffSet.days() != 0) {
      ostr << " [" << _boardDateOffSet.days() << "]";
    }
    ostr << " -- " << _offPoint << " / "
         << boost::posix_time::to_simple_string(_offTime);
    if (_offDateOffSet.days() != 0) {
      ostr << " [" << _offDateOffSet.days() << "]";
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

    // Set the Board Date
    const boost::gregorian::date_duration lBoardDateOffSet (_boardDateOffSet);
    ioLegDate.setBoardDate (iRefDate+ lBoardDateOffSet);

    // Set the Board Time
    ioLegDate.setBoardTime (_boardTime);
      
    // Set the Off Date
    const boost::gregorian::date_duration lOffDateOffSet (_offDateOffSet);
    ioLegDate.setOffDate (iRefDate + lOffDateOffSet);

    // Set the Off Time
    ioLegDate.setOffTime (_offTime);

    // Set the Elapsed Time
    ioLegDate.setElapsedTime (_elapsed);
  }

}
