// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <algorithm>
// STDAIR
#include <stdair/bom/FlightDate.hpp>
// AIRSCHED 
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/bom/LegDate.hpp>
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

