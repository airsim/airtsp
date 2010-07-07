// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <sstream>
// StdAir
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BomTypes.hpp>
#include <stdair/bom/BomSource.hpp>
#include <stdair/service/Logger.hpp>
// AIRSCHED
#include <airsched/command/TravelSolutionProvider.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::BomRoot& iBomRoot,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Retrieve  the reachable  universe object  corresponding  to the
    // origin of the booking request.
    const stdair::AirportCode_T& lOrigin = iBookingRequest.getOrigin ();
    const stdair::ReachableUniverse* lReachableUniverse_ptr =
      iBomRoot.getReachableUniverse (lOrigin);
    assert (lReachableUniverse_ptr != NULL);

    getTravelSolutions (ioTravelSolutionList, *lReachableUniverse_ptr,
                        iBookingRequest);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::ReachableUniverse& iReachableUniverse,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Retrieve the origin-destination set objet correponding to the
    // destination of the booking request.
    const stdair::AirportCode_T& lDestination = iBookingRequest.getDestination();
    const stdair::OriginDestinationSet* lOriginDestinationSet_ptr =
      iReachableUniverse.getOriginDestinationSet (lDestination);
    assert (lOriginDestinationSet_ptr != NULL);

    getTravelSolutions (ioTravelSolutionList, *lOriginDestinationSet_ptr,
                        iBookingRequest);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::OriginDestinationSet& iOriginDestinationSet,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Retrieve the departure date of the booking request.
    const stdair::Date_T& lPreferedDepartureDate =
      iBookingRequest.getPreferedDepartureDate ();

    // Browse the list of segment path periods and find those which content
    // the prefered departure date.
    const stdair::SegmentPathPeriodList_T& lSegmentPathPeriodList =
      iOriginDestinationSet.getSegmentPathPeriodList ();
    for (stdair::SegmentPathPeriodList_T::iterator itSegmentPath =
           lSegmentPathPeriodList.begin ();
         itSegmentPath != lSegmentPathPeriodList.end (); ++itSegmentPath) {
      const stdair::SegmentPathPeriod& lCurrentSegmentPath = *itSegmentPath;
      if (lCurrentSegmentPath.isDepartureDateValid (lPreferedDepartureDate)) {
        getTravelSolutions (ioTravelSolutionList, lCurrentSegmentPath,
                            iBookingRequest);
      }
    }
  } 

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::SegmentPathPeriod& iSegmentPathPeriod,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Create a new travel solution.
    stdair::TravelSolutionStruct lTravelSolution;
    
    // Browse the list of segments and retrieve the necessary informations
    // for identifying the corresponding segment-date.
    const stdair::Date_T& lPreferedDepartureDate =
      iBookingRequest.getPreferedDepartureDate ();
    const stdair::SegmentPeriodList_T& lSegmentPeriodList =
      iSegmentPathPeriod.getSegmentPeriodList ();
    const stdair::DateOffsetList_T& lBoardingDateOffsetList =
      iSegmentPathPeriod.getBoardingDateOffsetList ();
    assert (lSegmentPeriodList.size() == lBoardingDateOffsetList.size());
    stdair::DateOffsetList_T::const_iterator itOffset =
      lBoardingDateOffsetList.begin();
    for (stdair::SegmentPeriodList_T::iterator itSegment =
           lSegmentPeriodList.begin();
         itSegment != lSegmentPeriodList.end(); ++itSegment) {
      const stdair::SegmentPeriod& lSegmentPeriod = *itSegment;
      const stdair::DateOffset_T& lBoardingDateOffset = *itOffset;

      // Find the corresponding segment-date within the segment period.
      const stdair::DateOffset_T& lSegmentBoardingDateOffset =
        lSegmentPeriod.getBoardingDateOffset();
      const stdair::Date_T& lReferenceFlightDate = lPreferedDepartureDate 
        + lBoardingDateOffset - lSegmentBoardingDateOffset;

      // Build the whole segment-date key string.
      std::ostringstream oStr;
      oStr << lSegmentPeriod.getParent().getParent().getAirlineCode()
           << ", " << lSegmentPeriod.getParent().getFlightNumber()
           << ", " << lReferenceFlightDate;

      lTravelSolution.addSegmentDateKey (oStr.str());

      // Retrieve a class code within the segment-date.
      const stdair::CabinBookingClassMap_T& lCabinBookingClassMap =
        lSegmentPeriod.getCabinBookingClassMap ();
      stdair::CabinBookingClassMap_T::const_reverse_iterator
        itCabinBookingClassList = lCabinBookingClassMap.rbegin();
      if (itCabinBookingClassList != lCabinBookingClassMap.rend()) {
        const stdair::ClassList_String_T& lClassList =
          itCabinBookingClassList->second;
        const unsigned int lNbOfClasses = lClassList.size();
        if (lNbOfClasses > 0) {
          const char lClassCode = lClassList.at (lNbOfClasses-1);
          lTravelSolution.addBookingClassKey (lClassCode);
        }
      }
      
      ++itOffset;
    }

    ioTravelSolutionList.push_back (lTravelSolution);
  }

}
