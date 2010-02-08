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
#include <stdair/bom/Network.hpp>
#include <stdair/bom/NetworkDate.hpp>
#include <stdair/bom/OutboundPathTypes.hpp>
#include <stdair/bom/OutboundPath.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/service/Logger.hpp>
// AIRSCHED
#include <airsched/command/TravelSolutionProvider.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::Network& iNetwork,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    
    // Get the requested departure date.
    const stdair::Date_T lDepartureDate =
      iBookingRequest.getPreferedDepartureDate ();
    // Retrieve the NetworkDate for that departure date.
    const stdair::NetworkDate* lNetworkDate_ptr =
      iNetwork.getNetworkDate (lDepartureDate);
    assert (lNetworkDate_ptr != NULL);

    // Get the departure airport.
    const stdair::AirportCode_T& lOrigin = iBookingRequest.getOrigin ();
    // Retrieve the AirportDate for that origin.
    const stdair::AirportDate* lAirportDate_ptr =
      lNetworkDate_ptr->getAirportDate (lOrigin);
    assert (lAirportDate_ptr != NULL);

    const stdair::OutboundPathList_T& lOutboundPathList =
      lAirportDate_ptr->getOutboundPathList ();

    getTravelSolutions(ioTravelSolutionList, lOutboundPathList, iBookingRequest);
  }

  // //////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      const stdair::OutboundPathList_T& iOutboundPathList,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Retrieve the destination of the booking request.
    const stdair::AirportCode_T& lDestination = iBookingRequest.getDestination();

    // Browse the outbound path list for those with the appropriate destination.
    for (stdair::OutboundPathList_T::iterator itOutboundPath =
           iOutboundPathList.begin();
         itOutboundPath != iOutboundPathList.end(); ++itOutboundPath) {
      stdair::OutboundPath& lOutboundPath = *itOutboundPath;

      const stdair::AirportCode_T& lCurrentDestination =
        lOutboundPath.getDestination();

      if (lDestination == lCurrentDestination) {
        getTravelSolutions(ioTravelSolutionList, lOutboundPath, iBookingRequest);
      }
    } 
  }

  // //////////////////////////////////////////////////////////////////////
  void TravelSolutionProvider::
  getTravelSolutions (stdair::TravelSolutionList_T& ioTravelSolutionList,
                      stdair::OutboundPath& ioOutboundPath,
                      const stdair::BookingRequestStruct& iBookingRequest) {
    // Create an empty list of booking classes.
    stdair::BookingClassSTLList_T lBookingClassSTLList;

    // Browse the segment-date list and take the first (least
    // expensive) booking class to build the least expensive travel
    // solution.
    const stdair::SegmentDateList_T lSegmentDateList =
      ioOutboundPath.getSegmentDateList ();
    
    for (stdair::SegmentDateList_T::iterator itSegmentDate =
           lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      const stdair::SegmentDate& lSegmentDate = *itSegmentDate;

      const stdair::SegmentCabinList_T lSegmentCabinList =
        lSegmentDate.getSegmentCabinList();
      stdair::SegmentCabinList_T::reverse_iterator itLastCabin =
        lSegmentCabinList.rbegin();
      assert (itLastCabin != lSegmentCabinList.rend());
      const stdair::SegmentCabin& lSegmentCabin = *itLastCabin;

      const stdair::BookingClassList_T lBookingClassList =
        lSegmentCabin.getBookingClassList();
      stdair::BookingClassList_T::reverse_iterator itLastBookingClass =
        lBookingClassList.rbegin();
      assert (itLastBookingClass != lBookingClassList.rend());
      stdair::BookingClass& lBookingClass = *itLastBookingClass;

      lBookingClassSTLList.push_back (&lBookingClass);
    }
    
    stdair::TravelSolutionStruct lTravelSolution (ioOutboundPath,
                                                  lBookingClassSTLList);
    ioTravelSolutionList.push_back (lTravelSolution);
  }

}
