// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
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

    // Retrieve the list of flight-date holders
    const stdair::BomStructureList_T& lBomStructureList =
      _flightStructure.getChildrenList();

    // Browse the tree structure, i.e., the segment-dates
    oStr << "SegmentDates:" << std::endl;
    unsigned short idx = 0;
    for (stdair::BomStructureList_T::const_iterator itBomStructure =
           lBomStructureList.begin();
         itBomStructure != lBomStructureList.end(); ++itBomStructure, ++idx) {
      const stdair::BomStructure* lBomStructure_ptr = itBomStructure->second;

      const stdair::SegmentDate* lSegmentStructure_ptr =
        dynamic_cast<const stdair::SegmentDate*> (lBomStructure_ptr);
      if (lSegmentStructure_ptr == NULL) {
        continue;
      }
      assert (lSegmentStructure_ptr != NULL);

      // Get the content out of the structure/holder
      const SegmentDate& lSegmentDate =
        lSegmentStructure_ptr->getContent<SegmentDate>();

      oStr << "[" << idx << "]: " << lSegmentDate.toString();
    }
    
    // Browse the tree structure, i.e., the leg-dates
    oStr << "LegDates:" << std::endl;
    idx = 0;
    for (stdair::BomStructureList_T::const_iterator itBomStructure =
           lBomStructureList.begin();
         itBomStructure != lBomStructureList.end(); ++itBomStructure, ++idx) {
      const stdair::BomStructure* lBomStructure_ptr = itBomStructure->second;

      const stdair::LegDate* lLegStructure_ptr =
        dynamic_cast<const stdair::LegDate*> (lBomStructure_ptr);
      if (lLegStructure_ptr == NULL) {
        continue;
      }
      assert (lLegStructure_ptr != NULL);

      // Get the content out of the structure/holder
      const LegDate& lLegDate =
        lLegStructure_ptr->getContent<LegDate>();

      oStr << "[" << idx << "]: " << lLegDate.toString();
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

