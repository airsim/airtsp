// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
// AIRSCHED 
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const BomStructure_T& iFlightStructure)
    : _flightStructure (iFlightStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string FlightDate::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Retrieve the list of flight-date holders
    const stdair::SegmentDateList_T& lSegmentList =
      _flightStructure.getSegmentList();

    // Browse the tree structure, i.e., the segment-dates
    unsigned short idx = 0;
    for (stdair::SegmentDateList_T::const_iterator itSegment =
           lSegmentList.begin();
         itSegment != lSegmentList.end(); ++itSegment, ++idx) {
      const stdair::SegmentDate* lSegmentStructure_ptr = itSegment->second;
      assert (lSegmentStructure_ptr != NULL);

      // Get the content out of the structure/holder
      const SegmentDate& lSegmentDate =
        lSegmentStructure_ptr->getContent<SegmentDate>();

      oStr << "[" << idx << "]: " << lSegmentDate.toString() << std::endl;
    }
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeKey() const {
    return _flightStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeShortKey() const {
    return _flightStructure.describeShortKey();
  }

}

