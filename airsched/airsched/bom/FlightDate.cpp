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
  FlightDate::FlightDate (BomStructure_T& ioFlightStructure)
    : _flightDateStructure (ioFlightStructure) {
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
    return _flightDateStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeShortKey() const {
    return _flightDateStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_iterator FlightDate::segmentDateListBegin () const {
    return _flightDateStructure.segmentDateListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_iterator FlightDate::segmentDateListEnd () const {
    return _flightDateStructure.segmentDateListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_reverse_iterator FlightDate::segmentDateListRBegin () const {
    return _flightDateStructure.segmentDateListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_reverse_iterator FlightDate::segmentDateListREnd () const {
    return _flightDateStructure.segmentDateListREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_iterator FlightDate::segmentDateMapBegin () const {
    return _flightDateStructure.segmentDateMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_iterator FlightDate::segmentDateMapEnd () const {
    return _flightDateStructure.segmentDateMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_reverse_iterator FlightDate::segmentDateMapRBegin () const {
    return _flightDateStructure.segmentDateMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_reverse_iterator FlightDate::segmentDateMapREnd () const {
    return _flightDateStructure.segmentDateMapREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_iterator FlightDate::legDateListBegin () const {
    return _flightDateStructure.legDateListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_iterator FlightDate::legDateListEnd () const {
    return _flightDateStructure.legDateListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_reverse_iterator FlightDate::legDateListRBegin () const {
    return _flightDateStructure.legDateListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_reverse_iterator FlightDate::legDateListREnd () const {
    return _flightDateStructure.legDateListREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_iterator FlightDate::legDateMapBegin () const {
    return _flightDateStructure.legDateMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_iterator FlightDate::legDateMapEnd () const {
    return _flightDateStructure.legDateMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_reverse_iterator FlightDate::legDateMapRBegin () const {
    return _flightDateStructure.legDateMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_reverse_iterator FlightDate::legDateMapREnd () const {
    return _flightDateStructure.legDateMapREnd ();
  }

}

