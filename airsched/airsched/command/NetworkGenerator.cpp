// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/NetworkKey.hpp>
#include <stdair/bom/BomSource.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>
// AirSched
#include <airsched/command/NetworkGenerator.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  void NetworkGenerator::createNetworks (const stdair::BomRoot& iBomRoot) {
    // TODO: build several networks instead of just one.
    // Create a generic network key and a empty network.
    stdair::NetworkKey_T lNetworkKey ("Whole Network");
    stdair::Network& lNetwork =
      stdair::CmdBomManager::createNetwork (iBomRoot, lNetworkKey);
    // Build the network by creating the list of OutboundPath objects.
    buildNetwork (lNetwork, iBomRoot);
  }

  // ////////////////////////////////////////////////////////////////////
  void NetworkGenerator::buildNetwork (const stdair::Network& iNetwork,
                                       const stdair::BomRoot& iBomRoot) {
    // Build the list of single-segment OutboundPath objects.
    const stdair::InventoryList_T& lInventoryList = iBomRoot.getInventoryList();
    for (stdair::InventoryList_T::iterator itInventory = lInventoryList.begin();
         itInventory != lInventoryList.end(); ++itInventory) {
      const stdair::Inventory& lCurrentInventory = *itInventory;

      createSinglePaths (iNetwork, lCurrentInventory);
    }

    // Build the lists of i-fixed-length OutboundPath objects. In
    // other words, build the whole network.
    for (stdair::NbOfSegments_T i = 2;
         i <= stdair::MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND; ++i) {
      buildNetwork (iNetwork, i);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  createSinglePaths (const stdair::Network& iNetwork,
                     const stdair::Inventory& iInventory) {
    const stdair::FlightDateList_T& lFlightDateList =
      iInventory.getFlightDateList ();
    for (stdair::FlightDateList_T::iterator itFlightDate=lFlightDateList.begin();
         itFlightDate != lFlightDateList.end(); ++itFlightDate) {
      const stdair::FlightDate& lCurrentFlightDate = *itFlightDate;

      createSinglePaths (iNetwork, lCurrentFlightDate);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  createSinglePaths (const stdair::Network& iNetwork,
                     const stdair::FlightDate& iFlightDate) {
    const stdair::SegmentDateList_T& lSegmentDateList =
      iFlightDate.getSegmentDateList ();
    for (stdair::SegmentDateList_T::iterator itSegmentDate =
           lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      const stdair::SegmentDate& lCurrentSegmentDate = *itSegmentDate;

      createSinglePaths (iNetwork, lCurrentSegmentDate);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  createSinglePaths (const stdair::Network& iNetwork,
                     const stdair::SegmentDate& iSegmentDate) {
    // Retrieve the reference date for the AirportDate, which is also
    // the boarding date for the SegmentDate.
    const stdair::Date_T& lReferenceDate = iSegmentDate.getBoardingDate();
    
    // If a NetworkDate with that reference date does not yet exist,
    // create one.
    stdair::NetworkDate* lNetworkDate_ptr =
      iNetwork.getNetworkDate (lReferenceDate);
    if (lNetworkDate_ptr == NULL) {
      // Create the NetworkDate with the primary key (reference date)
      lNetworkDate_ptr =
        &stdair::CmdBomManager::createNetworkDate (iNetwork, lReferenceDate);
    }
    assert (lNetworkDate_ptr != NULL);
    
    // Go down recursively in the Network-BOM depth for the origin
    // (boarding point of the SegmentDate), but not for the destination (off
    // point of the SegmentDate), as the Network is made of origin nodes
    // and outbound pathes.
    createSinglePaths (*lNetworkDate_ptr, iSegmentDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  createSinglePaths (const stdair::NetworkDate& iNetworkDate,
                     const stdair::SegmentDate& iSegmentDate) {
    // Retrieve the origin for the AirportDate, which is also
    // the boarding point for the SegmentDate.
    const stdair::AirportCode_T& lOrigin = iSegmentDate.getBoardingPoint();

    // If an AirportDate with that reference date does not exist yet,
    // create one.
    stdair::AirportDate* lAirportDate_ptr =
      iNetworkDate.getAirportDate (lOrigin);
    if (lAirportDate_ptr == NULL) {
      lAirportDate_ptr =
        &stdair::CmdBomManager::createAirportDate (iNetworkDate, lOrigin);
    }
    assert (lAirportDate_ptr != NULL);

    // Go down recursively in the Network-BOM depth for the origin
    // (boarding point of the SegmentDate), but not for the destination (off
    // point of the SegmentDate), as the Network is made of origin nodes
    // and outbound pathes.
    createSinglePaths (*lAirportDate_ptr, iSegmentDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  createSinglePaths (stdair::AirportDate& ioAirportDate,
                     const stdair::SegmentDate& iSegmentDate) {
    // Build the OutboundPath key elements
    //const stdair::AirportDateKey_T& lAirportDateKey = ioAirportDate.getKey();
    const stdair::AirportCode_T& lDestination = iSegmentDate.getOffPoint();
    const stdair::Duration_T& lElapsedTime = iSegmentDate.getElapsedTime();
    // There is a single segment in the list
    const stdair::NbOfSegments_T lNbOfSegments = 1;
    // There is a single airline in the list (since there is a single segment)
    const stdair::NbOfAirlines_T lNbOfAirlines = 1;
    const stdair::Duration_T& lBoardingTime = iSegmentDate.getBoardingTime();

    // Create an outbound-path object for that (single) segment-date.
    // By construction, no other identical outbound-path (i.e., segment-date
    // in our case) is already in the list for that airport-date. Indeed,
    // the segment-dates are browsed once, and only once.
    // <br>However, an airport-date may get several (single segment-date)
    // outbound-pathes with the same characteristics, in particular in case
    // of commutting. For instance, BA175 LHR-JFK and BA179 LHR-JFK get
    // exactly the same characteristics (origin, destination,
    // elapsed time, number of segments, number of airlines).
    const stdair::OutboundPathKey_T lOutboundPathKey (lDestination,
                                                      lElapsedTime,
                                                      lNbOfSegments,
                                                      lNbOfAirlines,
                                                      lBoardingTime);
    stdair::OutboundPath& lOutboundPath = 
      stdair::CmdBomManager::createOutboundPath (ioAirportDate,lOutboundPathKey);
    // Build the list of lists of outbound paths.
    ioAirportDate.buildOutboundPathListList (lOutboundPath);
    
    // Add the SegmentDate reference to the dedicated list within
    // the OutboundPath. Note that this must be done before the
    // link between the OutboundPath and AirportDate, as that latter
    // method uses the number of segments within the OutboundPath
    // object.
    stdair::FacBomContent::addFullObjectToTheDedicatedList (lOutboundPath,
                                                            iSegmentDate);
    lOutboundPath.updateAfterAddingSegmentDate (iSegmentDate);
    // Update the AirlineCode of the OutboundPath
    lOutboundPath.updateAirlineCode();
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  buildNetwork (const stdair::Network& iNetwork,
                const stdair::NbOfSegments_T& iNbOfSegments) {
    assert (iNbOfSegments >= 2
            && iNbOfSegments <= stdair::MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND);

    // Iterate on the NetworkDate objects
    const stdair::NetworkDateList_T& lNetworkDateList =
      iNetwork.getNetworkDateList();
    for (stdair::NetworkDateList_T::iterator itNetworkDate =
           lNetworkDateList.begin();
         itNetworkDate != lNetworkDateList.end(); ++itNetworkDate) {
      stdair::NetworkDate& lNetworkDate = *itNetworkDate;

      buildNetwork (lNetworkDate, iNbOfSegments);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  buildNetwork (const stdair::NetworkDate& iNetworkDate,
                const stdair::NbOfSegments_T& iNbOfSegments) {
    // Iterate on the AirportDate objects
    const stdair::AirportDateList_T& lAirportDateList =
      iNetworkDate.getAirportDateList();
    for (stdair::AirportDateList_T::iterator itAirportDate =
           lAirportDateList.begin();
         itAirportDate != lAirportDateList.end(); ++itAirportDate) {
      stdair::AirportDate& lAirportDate = *itAirportDate;

      buildNetwork (lAirportDate, iNbOfSegments);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkGenerator::
  buildNetwork (stdair::AirportDate& ioAirportDate,
                const stdair::NbOfSegments_T& iNbOfSegments) {
    // The goal of that method is to build the i-fixed-length
    // Outbound-Path objects, knowing that all the
    // lower-fixed-length Outbound-Path objects have already been
    // built during the previous steps. Once an i-fixed-length
    // Outbound-Path object is created, it is added to the list of
    // the (fixed-length Outbound-Path object) lists.
    //
    // Hence, at that iteration, by construction, the list of the
    // (fixed-length Outbound-Path object) lists should already get
    // a size of i-1, if there were such possibilities (in terms of
    // Outbound Paths). In that case, at the end of the method, its
    // size should be of i.
    //
    // If the size of the list of the (fixed-length Outbound-Path
    // object) lists is (strictly) less than i-1, it means that that
    // airport date has no more possibilities of destinations. We
    // are thus done at that stage.
    const stdair::OutboundPathListList_T& lOutboundPathListList =
      ioAirportDate.getOutboundPathListList();
    const short lNbOfSegments_m1 = iNbOfSegments - 1;
    assert (lNbOfSegments_m1 >= 0);
    if (lOutboundPathListList.size() < lNbOfSegments_m1) {
      return;
    }
      
    // Retrieve the (i-1)-fixed-length Outbound-Path list (i = number of
    // segments).
    //
    // Note that a STL vector starts at 0, whereas the number of segments
    // starts at 1. Hence, (i-1) for the length (in number of segments)
    // corresponds to [iNbOfSegments-2] for the STL vector.
    //  
    // As the lOutboundPathListList may change during the next loop
    // iterations (as some OutboundPath objects are created and linked to
    // AirportDate), we need to take the initial copy of that list.
    const stdair::OutboundPathLightList_T lOutboundPathLightList_im1 =
      lOutboundPathListList.at (iNbOfSegments-2);

    // Iterate on the (i-1)-fixed-length Outbound-Path objects, in order
    // to build a i-fixed-length Outbound-Path objects. There are two steps:
    // 1. Retrieve the airport-dates at a (i-1) length (in number of segments)
    //    of the origin airport-date.
    // 2. From each of such (i-1) airport-date, add the single-segment pathes
    //    to the (i-1)-length pathes, so as to make i-length pathes.
    for (stdair::OutboundPathLightList_T::const_iterator itOutboundList =
           lOutboundPathLightList_im1.begin();
         itOutboundList != lOutboundPathLightList_im1.end();
         ++itOutboundList) {
      stdair::OutboundPath* lOutboundPath_im1_ptr = *itOutboundList;
      assert (lOutboundPath_im1_ptr != NULL);

      // Get the off point of the (i-1)-length OutboundPath attached to
      // the current AirportDate (*lAirportDate_ptr).
      // Note that "im1" stands for "i minus 1", i.e., (i-1).
      const stdair::AirportDate* lDestination_im1_ptr =
        lOutboundPath_im1_ptr->getDestinationAirportDate();

      // If there is no AirportDate corresponding to the destination (off
      // point of the last SegmentDate), it means that the destination is
      // an end point (no other SegmentDate is starting from there).
      // Hence, there is nothing else to do for now for that (final)
      // destination, and we can process the next (i-1)-outbound-path.
      if (lDestination_im1_ptr == NULL) {
        continue;
      }
      assert (lDestination_im1_ptr != NULL);
        
      // Retrieve the single-segment Outbound-Path list,
      // so as to make a i-length OutboundPath.
      const stdair::OutboundPathListList_T& lDestinationOutboundPathListList =
        lDestination_im1_ptr->getOutboundPathListList();
      assert (lDestinationOutboundPathListList.size() >= 1);

      // As the lDestinationOutboundPathListList may change during
      // the next loop iterations (as some OutboundPath objects are
      // created and linked to AirportDate), we need to take the initial
      // copy of that list.
      const stdair::OutboundPathLightList_T lDestinationOutboundPathLightList_1 =
        lDestinationOutboundPathListList.at (0);

      for (stdair::OutboundPathLightList_T::const_iterator
             itDestinationOutboundList =
             lDestinationOutboundPathLightList_1.begin();
           itDestinationOutboundList
             != lDestinationOutboundPathLightList_1.end();
           ++itDestinationOutboundList) {
        stdair::OutboundPath* lOutboundPath_1_ptr =
          *itDestinationOutboundList;
        assert (lOutboundPath_1_ptr != NULL);

        // Check that a passenger can connect (i.e., be able to do the
        // transfer from one plane to another). If the transfer/connection
        // is not feasible, then the current single-segment outbound-path
        // must not be added. There is nothing more to do at that stage,
        // and we can handle the next single-segment outbound-path.
        const bool isConnectable =
          lOutboundPath_im1_ptr->isConnectable (*lOutboundPath_1_ptr);
        if (isConnectable == false) {
          continue;
        }
          
        // Get the off point of the single-segment OutboundPath
        // attached to the intermediate destination (im1). That off point is
        // at a length i of the initial AirportDate: (i-1) + 1.
        const stdair::AirportCode_T& lDestination_i =
          lOutboundPath_1_ptr->getDestination();

        // If the new destination leads the full outbound path (length of i)
        // back to the origin (even if the dates are different), it is
        // useless to add that single-segment to the (i-1) outbound path:
        // there is nothing more to be done at that stage, and we can handle
        // the next single-segment outbound-path.
        if (lDestination_i == ioAirportDate.getOrigin()) {
          continue;
        }

        // Build the i-length OutboundPath
        // Get the parameters of the last segment
        const stdair::SegmentDate* lSegmentDate_1_ptr =
          lOutboundPath_1_ptr->getFirstSegmentDate();
        assert (lSegmentDate_1_ptr != NULL);
          
        // Calculate the number of airlines flown by the i-length
        // outbound path
        const stdair::AirlineCode_T& lAirlineCode_1 =
          lSegmentDate_1_ptr->getAirlineCode();
        stdair::NbOfAirlines_T lNbOfAirlines_i =
          lOutboundPath_im1_ptr->getNbOfAirlines();
        if (lOutboundPath_im1_ptr->isAirlineFlown(lAirlineCode_1) == false) {
          ++lNbOfAirlines_i;
        }

        // It may happen that the combination of the (single-segment)
        // outbound path with the last segment-date of the (i-1)-outbound path
        // produces a segment-date of the same flight-date. For instance,
        // BA9 LHR-BKK and BA9 BKK-SYD add up to BA9 LHR-SYD, which is
        // already a segment-date of the BA9 flight-date.
        // In that case, there is no need to add up the segment-date
        // to the (single-segment) outbound-path.
        const stdair::SegmentDate* lSegment_im1_ptr =
          lOutboundPath_im1_ptr->getLastSegmentDate();
        assert (lSegment_im1_ptr != NULL);
        if (lSegment_im1_ptr->getAirlineCode() == lAirlineCode_1
            && lSegment_im1_ptr->getFlightNumber()
            == lSegmentDate_1_ptr->getFlightNumber()) {
          continue;
        }
        
        // Calculate the total elapsed time flown by the i-length
        // outbound path
        const stdair::Date_T& lOutboundPathOffDate =
          lOutboundPath_im1_ptr->getOffDate();
        const stdair::AirportCode_T& lOutboundPathOffPoint = 
          lOutboundPath_im1_ptr->getDestination();
        const stdair::Date_T& lSegmentDateBoardingDate =
          lSegmentDate_1_ptr->getBoardingDate();
        const stdair::AirportCode_T& lSegmentDateBoardingPoint=
          lSegmentDate_1_ptr->getBoardingPoint();
        
        assert (lOutboundPathOffDate == lSegmentDateBoardingDate
                && lOutboundPathOffPoint == lSegmentDateBoardingPoint);

        const stdair::Duration_T lElapsedTime_i = lOutboundPath_im1_ptr->
          calculateElapsedTimeFromRouting (*lSegmentDate_1_ptr);

        const stdair::Duration_T& lBoardingTime_i =
          lOutboundPath_im1_ptr->getBoardingTime();
          
        const stdair::OutboundPathKey_T lOutboundPathKey_i (lDestination_i,
                                                            lElapsedTime_i,
                                                            iNbOfSegments,
                                                            lNbOfAirlines_i,
                                                            lBoardingTime_i);
        stdair::OutboundPath& lOutboundPath_i = stdair::FacBomContent::
          instance().create<stdair::OutboundPath> (lOutboundPathKey_i);

        // Clone the list of SegmentDate references of the given OutboundPath
        // object (passed as the second parameter).
        stdair::FacBomContent::cloneChildrenHolder<
        stdair::OutboundPath, stdair::SegmentDate> (lOutboundPath_i,
                                                    *lOutboundPath_im1_ptr);
       
        // Clone the flight path
        const stdair::FlightPathCode_T lFlightPathCode =
          lOutboundPath_im1_ptr->getFlightPathCode();
        lOutboundPath_i.setFlightPathCode (lFlightPathCode);
        
        // Add the SegmentDate reference to the dedicated list within
        // the OutboundPath. Note that this must be done before the
        // link between the OutboundPath and AirportDate, as that latter
        // method uses the number of segments within the OutboundPath
        // object.
        stdair::FacBomContent::
          addFullObjectToTheDedicatedList (lOutboundPath_i, *lSegmentDate_1_ptr);
        lOutboundPath_i.updateAfterAddingSegmentDate (*lSegmentDate_1_ptr);
        // update the AirlineCode of the OutboundPath
        lOutboundPath_i.updateAirlineCode();
          
        // Link the OutboundPath to the AirportDate
        stdair::FacBomContent::linkWithParent (lOutboundPath_i, ioAirportDate);
        ioAirportDate.buildOutboundPathListList (lOutboundPath_i);
      }
    }
  } 
  
}
