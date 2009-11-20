// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/LegDate.hpp>
// AIRSCHED
#include <airsched/bom/SegmentDate.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const BomKey_T& iKey,
                            BomStructure_T& ioSegmentDateStructure)
    : stdair::SegmentDate (iKey, ioSegmentDateStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentDate::~SegmentDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDate::fillFromRouting (stdair::SegmentDate& ioSegmentDate) {
    // Retrieve the first and the last legs of the routing.
    // Note that in the majority of the cases, as flights are mono-legs,
    // the first and last legs are thus the same.
    const stdair::LegDateList_T& lLegDateList = ioSegmentDate.getLegDateList();
    stdair::LegDateList_T::iterator itFirstLeg = lLegDateList.begin();
    const stdair::LegDate& lFirstLeg = *itFirstLeg;

    stdair::LegDateList_T::reverse_iterator itLastLeg = lLegDateList.rbegin();
    const stdair::LegDate& lLastLeg = *itLastLeg;
    
    // Set the Board Date
    const stdair::Date_T& lBoardDate = lFirstLeg.getBoardDate();
    ioSegmentDate.setBoardDate (lBoardDate);

    // Set the Board Time
    const stdair::Duration_T& lBoardTime = lFirstLeg.getBoardTime();
    ioSegmentDate.setBoardTime (lBoardTime);
      
    // Set the Off Date
    const stdair::Date_T& lOffDate = lLastLeg.getOffDate();
    ioSegmentDate.setOffDate (lOffDate);

    // Set the Off Time
    const stdair::Duration_T& lOffTime = lLastLeg.getOffTime();
    ioSegmentDate.setOffTime (lOffTime);

    // Set the Elapsed Time for the whole path
    updateElapsedTimeFromRouting (ioSegmentDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::
  updateElapsedTimeFromRouting (stdair::SegmentDate& ioSegmentDate) {

    const stdair::LegDateList_T& lLegDateList = ioSegmentDate.getLegDateList();
    stdair::LegDateList_T::iterator itLegDate = lLegDateList.begin();
    const stdair::LegDate* lCurrentLegDate_ptr = &*itLegDate;
    // No need to do an assertion here.

    // Retrieve the elapsed time of the first leg
    stdair::Duration_T lElapsedTime = lCurrentLegDate_ptr->getElapsedTime();

    // Go to the next leg, if existing. If not existing, the following
    // loop will not be entered (as it means: currentLeg == _legDateList.end()).
    ++itLegDate;

    for (const stdair::LegDate* lPreviousLegDate_ptr = lCurrentLegDate_ptr;
         itLegDate != lLegDateList.end();
         ++itLegDate, lPreviousLegDate_ptr = lCurrentLegDate_ptr) {
      lCurrentLegDate_ptr = &*itLegDate;
      
      // As the board point of the current leg is the same as the off point
      // of the previous leg (by construction), there is no time difference.
      assert (lCurrentLegDate_ptr->getBoardPoint()
              == lPreviousLegDate_ptr->getOffPoint());
      const stdair::Duration_T& lStopOverTime =
        lCurrentLegDate_ptr->getBoardTime() - lPreviousLegDate_ptr->getOffTime();
      lElapsedTime += lStopOverTime;

      // Add the elapsed time of the current segment
      const stdair::Duration_T& currentElapsedTime =
        lCurrentLegDate_ptr->getElapsedTime();
      lElapsedTime += currentElapsedTime;
    }
      
    // Store the result
    ioSegmentDate.setElapsedTime (lElapsedTime);
    // From the elapsed time, update the distance
    updateDistanceFromElapsedTime (ioSegmentDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::
  updateDistanceFromElapsedTime (stdair::SegmentDate& ioSegmentDate) {
    const stdair::Duration_T& lElapsedTime = ioSegmentDate.getElapsedTime();
    const double lElapseInHours=static_cast<const double>(lElapsedTime.hours());
    const long int lDistance =
      static_cast<const long int>(stdair::DEFAULT_FLIGHT_SPEED*lElapseInHours);
    ioSegmentDate.setDistance (lDistance);
  }

}


const ClassCodeParameters* apParam = getClassCodeParameters(iClassCode);

if (apParam == NULL) {
  lancer l exception
  assert (apParam != NULL);
 }

return computeValue(apParam->getMin(), apParam->isMinPercentage(), iOfferedCapacity);
