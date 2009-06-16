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

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const STDAIR::FlightDate& iFlightStructure)
    : _flightStructure (iFlightStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::toStream (std::ostream& ioOut) const {
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string FlightDate::toString() const {
    std::string oString;

    // Retrieve the list of flight-date holders
    const STDAIR::SegmentDateList_T& lSegmentList =
      _flightStructure.getSegmentList();

    // Browse the tree structure, i.e., the segment-dates
    for (STDAIR::SegmentDateList_T::const_iterator itSegment =
           lSegmentList.begin();
         itSegment != lSegmentList.end(); ++itSegment) {
      const STDAIR::SegmentDate* lSegmentStructure_ptr = itSegment->second;
      assert (lSegmentStructure_ptr != NULL);

      // Get the content out of the structure/holder
      const SegmentDate& lSegmentDate =
        lSegmentStructure_ptr->getContent<SegmentDate>();

      oString += lSegmentDate.toString();
    }
    
    return oString;
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeKey() const {
    std::string oKey;

    return oKey;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeShortKey() const {
    std::string oKey;

    return oKey;
  }

}

