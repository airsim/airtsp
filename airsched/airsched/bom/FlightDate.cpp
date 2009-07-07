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
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/PrintBomContent.hpp>
// AIRSCHED 
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/LegDate.hpp>
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

//     // Retrieve the list of flight-date holders
//     const stdair::BomStructureList_T& lBomStructureList =
//       _flightStructure.getChildrenList();

//     // Browse the tree structure, i.e., the segment-dates
//     oStr << "SegmentDates:" << std::endl;
//     unsigned short idx = 0;
//     stdair::PrintBomContent lPrintBomContent (oStr, idx);
    
//     for (stdair::BomStructureList_T::const_iterator itBomStructure =
//            lBomStructureList.begin();
//          itBomStructure != lBomStructureList.end(); ++itBomStructure) {
//       lPrintBomContent.
//         printBomContent<stdair::SegmentDate, SegmentDate> (*itBomStructure);
//     }
    
//     // Browse the tree structure, i.e., the leg-dates
//     oStr << "LegDates:" << std::endl;
//     idx = 0;
//     for (stdair::BomStructureList_T::const_iterator itBomStructure =
//            lBomStructureList.begin();
//          itBomStructure != lBomStructureList.end(); ++itBomStructure) {
//       lPrintBomContent.
//         printBomContent<stdair::LegDate, LegDate> (*itBomStructure);
//     }

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

