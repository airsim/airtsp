// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/SegmentDate.hpp>
// AIRSCHED
#include <airsched/bom/SegmentStruct.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << "    " << _boardPoint << " / "
         << boost::posix_time::to_simple_string(_boardTime)
         << " -- " << _offPoint << " / "
         << boost::posix_time::to_simple_string(_offTime)
         << " --> "
         << boost::posix_time::to_simple_string(_elapsed)
         << std::endl;
    for (SegmentCabinStructList_T::const_iterator itCabin =
           _cabinList.begin(); itCabin != _cabinList.end(); itCabin++) {
      const SegmentCabinStruct_T& lCabin = *itCabin;
      ostr << lCabin.describe();
    }
    ostr << std::endl;
    
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentStruct_T::fill (stdair::SegmentDate& ioSegmentDate) const {
    // Note that some parameters (board date, board time, off date, off time,
    // elapsed time) are set by SegmentDate::fillFromRouting() when
    // the routing (with legs) is built. So, it is useless to set those
    // parameters here.

    // At that time, there are no other parameters.
  }

}
