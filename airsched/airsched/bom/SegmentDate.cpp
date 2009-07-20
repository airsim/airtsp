// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/SegmentDate.hpp>
// AIRSCHED 
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const BomStructure_T& iSegmentStructure)
    : _bomStructure (iSegmentStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentDate::~SegmentDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SegmentDate::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeKey() const {
    return _bomStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeShortKey() const {
    return _bomStructure.describeShortKey();
  }

}

