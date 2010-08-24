// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_TravelSolution.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightPeriod.hpp>
#include <stdair/bom/SegmentPeriod.hpp>
#include <stdair/bom/BomManager.hpp>
// AIRSCHED
#include <airsched/bom/SegmentPathPeriod.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriod::SegmentPathPeriod (const Key_T& iKey)
    :  _key (iKey) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriod::~SegmentPathPeriod () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentPathPeriod::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::SegmentPeriod* SegmentPathPeriod::getLastSegmentPeriod () const {
    // Retrieve the last segment of the list
    stdair::SegmentPeriodDetailedList_T& lSegmentPeriodDetailedList =
      stdair::BomManager::getDetailedList<stdair::SegmentPeriod> (*this);
    stdair::SegmentPeriodDetailedList_T::reverse_iterator itLastSegment =
      lSegmentPeriodDetailedList.rbegin();

    if (itLastSegment == lSegmentPeriodDetailedList.rend()) {
      return NULL;
    }
    
    stdair::SegmentPeriod* oSegment_ptr = itLastSegment->second;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::SegmentPeriod* SegmentPathPeriod::getFirstSegmentPeriod () const{
    // Retrieve the first segment of the list
    stdair::SegmentPeriodDetailedList_T& lSegmentPeriodDetailedList =
      stdair::BomManager::getDetailedList<stdair::SegmentPeriod> (*this);
    stdair::SegmentPeriodDetailedList_T::iterator itFirstSegment = 
      lSegmentPeriodDetailedList.begin();

    if (itFirstSegment == lSegmentPeriodDetailedList.end()) {
      return NULL;
    }
    
    stdair::SegmentPeriod* oSegment_ptr = itFirstSegment->second;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::AirportCode_T& SegmentPathPeriod::getDestination () const {
    const stdair::SegmentPeriod* lLastSegment_ptr = getLastSegmentPeriod();
    assert (lLastSegment_ptr != NULL);
    return lLastSegment_ptr->getOffPoint();
  }  

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  isAirlineFlown (const stdair::AirlineCode_T& iAirlineCode) const {
    bool oAirlineFlown = false;

    const stdair::SegmentPeriodDetailedList_T& lSegmentPeriodDetailedList = 
      stdair::BomManager::getDetailedList<stdair::SegmentPeriod> (*this);
    for (stdair::SegmentPeriodDetailedList_T::const_iterator itSegmentPeriod =
           lSegmentPeriodDetailedList.begin();
         itSegmentPeriod != lSegmentPeriodDetailedList.end(); ++itSegmentPeriod){
      const stdair::MapKey_T lKey = itSegmentPeriod->first;
      stdair::AirlineCode_T lSegmentAirlineCode = "";
      lSegmentAirlineCode = lKey.at(0) + lKey.at(1);
      if (lSegmentAirlineCode == iAirlineCode) {
        oAirlineFlown = true;
        break;
      }
    }

    return oAirlineFlown;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodKey SegmentPathPeriod::
  connectWithAnotherSegment(const SegmentPathPeriod& iSingleSegmentPath) const {
    SegmentPathPeriodKey oSegmentPathPeriodKey;

    // Retrieve the (only) segment period of the single segment path.
    stdair::SegmentPeriodDetailedList_T& lNextSegmentPeriodDetailedList =
      stdair::BomManager::
      getDetailedList<stdair::SegmentPeriod> (iSingleSegmentPath);
    stdair::SegmentPeriodDetailedList_T::iterator itNextSegment = 
      lNextSegmentPeriodDetailedList.begin();
    assert (itNextSegment != lNextSegmentPeriodDetailedList.end());
    const stdair::SegmentPeriod* lNextSegmentPeriod_ptr =
      itNextSegment->second; 
    assert (lNextSegmentPeriod_ptr != NULL);

    // Retrive the last segment period of the current segment path and check
    // if the combination of the last segment and the next segment that we
    // want to add to the current segment path will create a new segment
    // (i.e., the two segment period belongs to the same flight number).
    stdair::SegmentPeriodDetailedList_T& lCurrentSegmentPeriodDetailedList =
      stdair::BomManager::getDetailedList<stdair::SegmentPeriod> (*this);
    stdair::SegmentPeriodDetailedList_T::reverse_iterator itLastSegment =
      lCurrentSegmentPeriodDetailedList.rbegin();
    assert (itLastSegment != lCurrentSegmentPeriodDetailedList.rend());
    const stdair::SegmentPeriod* lLastSegmentPeriod_ptr =
      itLastSegment->second;
    assert (lLastSegmentPeriod_ptr != NULL);
    
    if (itNextSegment->first == itLastSegment->first) {
      return oSegmentPathPeriodKey;
    }
    
    // Check if the new segment period will create a circle.
    const stdair::AirportCode_T& lDestination =
      lNextSegmentPeriod_ptr->getOffPoint();
    if (checkCircle (lDestination) == true) {
      return oSegmentPathPeriodKey;
    }

    // Check if a passenger can connect from the last segment of the
    // current segment path to the first segment of the to-be-added
    // segment path. If yes, build a new departure period for the new
    // segment path.
    DateOffsetList_T lBoardingDateOffsetList = 
      getBoardingDateOffsetList();
    const stdair::PeriodStruct_T& lCurrentDeparturePeriod = getDeparturePeriod();
    const stdair::PeriodStruct_T& lNextDeparturePeriod =
      iSingleSegmentPath.getDeparturePeriod();
    const stdair::Duration_T& lLastOffTime =
      lLastSegmentPeriod_ptr->getOffTime();
    const stdair::Duration_T& lNextBoardingTime =
      lNextSegmentPeriod_ptr->getBoardingTime();
    // If the next boarding time is later than the last off time, check if
    // the passengers will have enough time for the transfer. If the next
    // boarding time is earlier than the last off time, check if the passengers
    // can connect to a flight in the next day.
    if (lNextBoardingTime >= lLastOffTime) {
      const stdair::Duration_T lStopTime = lNextBoardingTime - lLastOffTime;
      if (lStopTime < stdair::DEFAULT_MINIMAL_CONNECTION_TIME) {
        return oSegmentPathPeriodKey;
      } else {
        // Calulcate the date offset of the next segment compare to
        // the first one. In this case, this value is equal to the offset
        // of the off date of the last segment compare to the boarding date
        // of the first segment.
        const stdair::DateOffset_T& lLastBoardingDateOffset =
          lBoardingDateOffsetList.at (getNbOfSegments() - 1);
        const stdair::DateOffset_T lNextBoardingDateOffset =
          lLastBoardingDateOffset + lLastSegmentPeriod_ptr->getOffDateOffset()
          - lLastSegmentPeriod_ptr->getBoardingDateOffset();
        const stdair::DateOffset_T lNegativeNextBoardingDateOffset =
          stdair::DateOffset_T (0) - lNextBoardingDateOffset;

        // Compute the adjusted departure period of the next segment by
        // substracting the origin one with the boarding date offset.
        const stdair::PeriodStruct_T lAdjustedNextDeparturePeriod =
          lNextDeparturePeriod.addDateOffset (lNegativeNextBoardingDateOffset);

        // Build the intersection of the two periods.
        const stdair::PeriodStruct_T lNewDeparturePeriod =
          lCurrentDeparturePeriod.intersection (lAdjustedNextDeparturePeriod);
        stdair::Duration_T lNewElapsed = getElapsedTime() + lStopTime +
          lNextSegmentPeriod_ptr->getElapsedTime();
        lBoardingDateOffsetList.push_back (lNextBoardingDateOffset);
        oSegmentPathPeriodKey.setPeriod (lNewDeparturePeriod);
        oSegmentPathPeriodKey.setElapsedTime (lNewElapsed);
      }
    } else {
      const stdair::Duration_T lStopTime = 
        lNextBoardingTime - lLastOffTime + stdair::Duration_T (24, 0, 0);
      if (lStopTime < stdair::DEFAULT_MINIMAL_CONNECTION_TIME) {
        return oSegmentPathPeriodKey;
      } else {
        // Calulcate the date offset of the next segment compare to
        // the first one.
        const stdair::DateOffset_T& lLastBoardingDateOffset =
          lBoardingDateOffsetList.at (getNbOfSegments() - 1);
        const stdair::DateOffset_T lNextBoardingDateOffset =
          lLastBoardingDateOffset + lLastSegmentPeriod_ptr->getOffDateOffset()
          - lLastSegmentPeriod_ptr->getBoardingDateOffset() +
          stdair::DateOffset_T (1);
        const stdair::DateOffset_T lNegativeNextBoardingDateOffset =
          stdair::DateOffset_T (0) - lNextBoardingDateOffset;

        // Compute the adjusted departure period of the next segment by
        // substracting the origin one with the boarding date offset.
        const stdair::PeriodStruct_T lAdjustedNextDeparturePeriod =
          lNextDeparturePeriod.addDateOffset (lNegativeNextBoardingDateOffset);

        // Build the intersection of the two periods.
        const stdair::PeriodStruct_T lNewDeparturePeriod =
          lCurrentDeparturePeriod.intersection (lAdjustedNextDeparturePeriod);
        stdair::Duration_T lNewElapsed = getElapsedTime() + lStopTime +
          lNextSegmentPeriod_ptr->getElapsedTime();
        lBoardingDateOffsetList.push_back (lNextBoardingDateOffset);
        oSegmentPathPeriodKey.setPeriod (lNewDeparturePeriod);
        oSegmentPathPeriodKey.setElapsedTime (lNewElapsed);
      }
    }
    
    const stdair::Duration_T& lBoardingTime = getBoardingTime();
    oSegmentPathPeriodKey.setBoardingTime (lBoardingTime);
    oSegmentPathPeriodKey.setBoardingDateOffsetList (lBoardingDateOffsetList);
    
    return oSegmentPathPeriodKey;
  }

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  checkCircle (const stdair::AirlineCode_T& iDestination) const {
    const stdair::SegmentPeriodDetailedList_T& lSegmentPeriodDetailedList =
      stdair::BomManager::getDetailedList<stdair::SegmentPeriod> (*this);
    for (stdair::SegmentPeriodDetailedList_T::const_iterator itSegment =
           lSegmentPeriodDetailedList.begin();
         itSegment != lSegmentPeriodDetailedList.end(); ++itSegment) {
      const stdair::SegmentPeriod* lCurrentSegment_ptr = itSegment->second;
      assert (lCurrentSegment_ptr != NULL);
      const stdair::AirlineCode_T& lCurrentBoardingPoint =
        lCurrentSegment_ptr->getBoardingPoint();
      if (lCurrentBoardingPoint == iDestination) {
        return true;
      }
    }
    return false;
  }

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  isDepartureDateValid (const stdair::Date_T& iDepartureDate) const {
    const stdair::PeriodStruct_T& lPeriod = getDeparturePeriod ();

    // Check if the departure date is within the date range.
    const stdair::DatePeriod_T& lDeparturePeriod = lPeriod.getDateRange ();
    if (lDeparturePeriod.contains (iDepartureDate) == false) {
      return false;
    }

    // Check if the departure date is valid within the DOW.
    // 0 = Sunday, 1 = Monday, etc.
    const short lDay = iDepartureDate.day_of_week ();
    const stdair::DoWStruct_T& lDoW = lPeriod.getDoW ();
    if (lDoW.getStandardDayOfWeek (lDay) == false) {
      return false;
    }

    return true;
  }

}

