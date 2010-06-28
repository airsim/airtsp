// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
// StdAir
#include <stdair/bom/BomSource.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/FlightPeriodTypes.hpp>
#include <stdair/bom/SegmentPeriodTypes.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>
// AirSched
#include <airsched/command/SegmentPathGenerator.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathGenerator::
  createSegmentPathNetwork (const stdair::BomRoot& iBomRoot) {
    // Build the list of single-segment segment path objects.
    const stdair::InventoryList_T& lInventoryList = iBomRoot.getInventoryList ();
    for (stdair::InventoryList_T::iterator itInventory = lInventoryList.begin();
         itInventory != lInventoryList.end(); ++itInventory) {
      const stdair::Inventory& lCurrentInventory = *itInventory;
      createSinglePaths (lCurrentInventory);
    }

    // Build the list of i-fixed-length segment path objects. In other words,
    // build the whole segment path network.
    for (stdair::NbOfSegments_T i = 2;
         i <= stdair::MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND; ++i) {
      buildSegmentPathNetwork (iBomRoot, i);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void SegmentPathGenerator::
  createSinglePaths (const stdair::Inventory& iInventory) {
    const stdair::FlightPeriodList_T& lFlightPeriodList =
      iInventory.getFlightPeriodList ();
    for (stdair::FlightPeriodList_T::iterator itFlightPeriod =
           lFlightPeriodList.begin();
         itFlightPeriod != lFlightPeriodList.end(); ++itFlightPeriod) {
      const stdair::FlightPeriod& lCurrentFlightPeriod = *itFlightPeriod;
      createSinglePaths (lCurrentFlightPeriod);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathGenerator::
  createSinglePaths (const stdair::FlightPeriod& iFlightPeriod) {
    const stdair::SegmentPeriodList_T& lSegmentPeriodList =
      iFlightPeriod.getSegmentPeriodList ();
    for (stdair::SegmentPeriodList_T::iterator itSegmentPeriod =
           lSegmentPeriodList.begin();
         itSegmentPeriod != lSegmentPeriodList.end(); ++itSegmentPeriod) {
      const stdair::SegmentPeriod& lCurrentSegmentPeriod = *itSegmentPeriod;
      createSinglePath (lCurrentSegmentPeriod);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathGenerator::
  createSinglePath (const stdair::SegmentPeriod& iSegmentPeriod) {
    const stdair::AirportCode_T& lOrigin = iSegmentPeriod.getBoardingPoint ();
    const stdair::BomRoot& lBomRoot =
      iSegmentPeriod.getParent().getParent().getParent();

    // Retrieve the ReachableUniverse (if existed) which corresponds
    // to the origin. If it does not exist, then create one.
    stdair::ReachableUniverse* lReachableUniverse_ptr =
      lBomRoot.getReachableUniverse (lOrigin);
    if (lReachableUniverse_ptr == NULL) {
      lReachableUniverse_ptr =
        &stdair::CmdBomManager::createReachableUniverse (lBomRoot, lOrigin);
    }
    createSinglePath (*lReachableUniverse_ptr, iSegmentPeriod);
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathGenerator::
  createSinglePath (stdair::ReachableUniverse& ioReachableUniverse,
                    const stdair::SegmentPeriod& iSegmentPeriod) {
    const stdair::AirportCode_T& lDestination = iSegmentPeriod.getOffPoint ();

    // Retrieve the origin-destination set (if existed) which corresponds
    // to the destination. If it does not exist, then create one.
    stdair::OriginDestinationSet* lOriginDestinationSet_ptr =
      ioReachableUniverse.getOriginDestinationSet (lDestination);
    if (lOriginDestinationSet_ptr == NULL) {
      lOriginDestinationSet_ptr =
        &stdair::CmdBomManager::createOriginDestinationSet (ioReachableUniverse,
                                                            lDestination);
    }

    // Create a segment path period and add it to the corresponding
    // origin-destination set and reachable-universe.
    const stdair::DatePeriod_T& lDeparturePeriod =
      iSegmentPeriod.getDeparturePeriod();
    const stdair::DoWStruct_T& lDoW = iSegmentPeriod.getDoW();
    const stdair::Duration_T& lBoardingTime = iSegmentPeriod.getBoardingTime();
    const stdair::Duration_T& lElapsed = iSegmentPeriod.getElapsedTime();
    const stdair::SegmentPathPeriodKey_T lSegmentPathKey (lDeparturePeriod,
                                                          lDoW, lBoardingTime,
                                                          lElapsed, 1, 1);
    stdair::SegmentPathPeriod& lSegmentPathPeriod =
      stdair::CmdBomManager::createSegmentPathPeriod (*lOriginDestinationSet_ptr,
                                                      lSegmentPathKey);
    ioReachableUniverse.addSegmentPathPeriod (lSegmentPathPeriod);
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathGenerator::
  buildSegmentPathNetwork (const stdair::BomRoot& iBomRoot,
                           const stdair::NbOfSegments_T& lNbOfSegments) {
    // Browse the reachable-universe list and create the i-fixed-length
    // segment path period objects corresponding to the boarding point of
    // the current reachable-universe object.
    const stdair::ReachableUniverseList_T& lReachableUniverseList =
      iBomRoot.getReachableUniverseList();
    for (stdair::ReachableUniverseList_T::iterator itReachableUniverse =
           lReachableUniverseList.begin();
         itReachableUniverse != lReachableUniverseList.end();
         ++itReachableUniverse) {
      stdair::ReachableUniverse& lReachableUniverse = *itReachableUniverse;
      buildSegmentPathNetwork (lReachableUniverse, lNbOfSegments);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathGenerator::
  buildSegmentPathNetwork (stdair::ReachableUniverse& ioReachableUniverse,
                           const stdair::NbOfSegments_T& iNbOfSegments) {
    
    // The goal of that method is to build the i-fixed-length
    // segment path period objects, knowing that all the
    // lower-fixed-length segment path period objects have already been
    // built during the previous steps. Once an i-fixed-length
    // segment path period object is created, it is added to the list of
    // the (fixed-length segment path period object) lists.
    
    // Hence, at that iteration, by construction, the list of the
    // (fixed-length segment path period object) lists should already get
    // a size of i-1, if there were such possibilities (in terms of
    // segment path period). In that case, at the end of the method, its
    // size should be of i.
    
    // If the size of the list of the (fixed-length segment path period
    // object) lists is (strictly) less than i-1, it means that that
    // reachable universe has no more possibilities of destinations. We
    // are thus done at that stage.
    const stdair::SegmentPathPeriodListList_T& lSegmentPathPeriodListList =
      ioReachableUniverse.getSegmentPathPeriodListList();
    const short lNbOfSegments_m1 = iNbOfSegments - 1;
    assert (lNbOfSegments_m1 >= 0);
    if (lSegmentPathPeriodListList.size() < lNbOfSegments_m1) {
      return;
    }
      
    // Retrieve the (i-1)-fixed-length segment path period list (i = number of
    // segments).
    
    // Note that a STL vector starts at 0, whereas the number of segments
    // starts at 1. Hence, (i-1) for the length (in number of segments)
    // corresponds to [iNbOfSegments-2] for the STL vector.
    
    // As the lSegmentPathPeriodListList may change during the next loop
    // iterations (as some SegmentPathPeriod objects are created and linked to
    // ReachableUniverse), we need to take the initial copy of that list.
    const stdair::SegmentPathPeriodLightList_T lSegmentPathPeriodLightList_im1 =
      lSegmentPathPeriodListList.at (iNbOfSegments-2);

    // Iterate on the (i-1)-fixed-length segment path period objects, in order
    // to build a i-fixed-length segment path period objects. 
    // There are two steps:
    // 1. Retrieve the airport-dates at a (i-1) length (in number of segments)
    //    of the origin airport-date.
    // 2. From each of such (i-1) airport-date, add the single-segment pathes
    //    to the (i-1)-length pathes, so as to make i-length pathes.
    for (stdair::SegmentPathPeriodLightList_T::const_iterator itSegmentPathPeriodList = lSegmentPathPeriodLightList_im1.begin();
         itSegmentPathPeriodList != lSegmentPathPeriodLightList_im1.end();
         ++itSegmentPathPeriodList) {
      const stdair::SegmentPathPeriod* lSegmentPathPeriod_im1_ptr = 
        *itSegmentPathPeriodList;
      assert (lSegmentPathPeriod_im1_ptr != NULL);

      // Get the reachable-universe departing from the destination of
      // the current segment path period.
      const stdair::AirportCode_T& lDestination_im1 =
        lSegmentPathPeriod_im1_ptr->getDestination();
      const stdair::BomRoot& lBomRoot = ioReachableUniverse.getParent();
      const stdair::ReachableUniverse* lReachableUniverseFromDestination_im1_ptr = lBomRoot.getReachableUniverse (lDestination_im1);

      // If there is no ReachableUniverse corresponding to the destination (off
      // point of the last SegmentDate), it means that the destination is
      // an end point (no other SegmentDate is starting from there).
      // Hence, there is nothing else to do for now for that (final)
      // destination, and we can process the next (i-1)-segment path period.
      if (lReachableUniverseFromDestination_im1_ptr == NULL) {
        continue;
      }
      assert (lReachableUniverseFromDestination_im1_ptr != NULL);
        
      // Retrieve the single-segment segment path period list,
      // so as to make a i-length SegmentPathPeriod.
      const stdair::SegmentPathPeriodListList_T& 
        lSegmentPathPeriodListListFromDestination_im1 = 
        lReachableUniverseFromDestination_im1_ptr->
        getSegmentPathPeriodListList();
      assert (lSegmentPathPeriodListListFromDestination_im1.size() >= 1);

      // As the lSegmentPathPeriodListListFromDestination_im1 may change during
      // the next loop iterations (as some SegmentPathPeriod objects are
      // created and linked to ReachableUniverse), we need to take the initial
      // copy of that list.
      const stdair::SegmentPathPeriodLightList_T lSingleSegmentPathPeriodLightListFromDestination_im1 =
        lSegmentPathPeriodListListFromDestination_im1.at (0);

      for (stdair::SegmentPathPeriodLightList_T::const_iterator
             itSegmentPathPeriodFromDestination_im1 =
             lSingleSegmentPathPeriodLightListFromDestination_im1.begin();
           itSegmentPathPeriodFromDestination_im1
             != lSingleSegmentPathPeriodLightListFromDestination_im1.end();
           ++itSegmentPathPeriodFromDestination_im1) {
        const stdair::SegmentPathPeriod* lSingleSegmentPathPeriodFromDestination_im1_ptr =
          *itSegmentPathPeriodFromDestination_im1;
        assert (lSingleSegmentPathPeriodFromDestination_im1_ptr != NULL);

        // Check if the (i-1)-length segment path period can be fused with the
        // single segment segment path period in order to create an i-length
        // segment path period. The function will return a valid or non-valid
        // segment path period key.

        // The two segment path period above can be fused (and will produce a
        // valid new segment path period key) if:
        // 1. A passenger can connect from the last segment of the
        // first segment path and the first segment of the next segment path.
        // These two segments should not create another segment.
        // 2. There is no circle within the new segment path.
        // 3. The intersection of the two periods is non-empty.

        const stdair::SegmentPathPeriodKey_T lSegmentPathPeriodKey_i =
          lSegmentPathPeriod_im1_ptr->connectWithAnotherSegment (*lSingleSegmentPathPeriodFromDestination_im1_ptr);
       

        // Check that a passenger can connect (i.e., be able to do the
        // transfer from one plane to another). If the transfer/connection
        // is not feasible, then the current single-segment outbound-path
        // must not be added. There is nothing more to do at that stage,
        // and we can handle the next single-segment outbound-path.
        const bool isConnectable =
          lSegmentPathPeriod_im1_ptr->isConnectable (*lSingleSegmentPathPeriodFromDestination_im1_ptr);
        if (isConnectable == false) {
          continue;
        }
          
        // Get the off point of the single-segment SegmentPathPeriod
        // attached to the intermediate destination (im1). That off point is
        // at a length i of the initial ReachableUniverse: (i-1) + 1.
        const stdair::AirportCode_T& lDestination_i =
          lSingleSegmentPathPeriodFromDestination_im1_ptr->getDestination();

        // Check if the the single segment path period does not go the
        // one of the airports passed by the (i-1) segment path period.
        const bool lCircleExistence =
          lSegmentPathPeriod_im1_ptr->checkCircle (lDestination_i);
        if (lCircleExistence == true) {
          continue;
        }

        // Build the i-length SegmentPathPeriod
        // Get the parameters of the last segment
        const stdair::SegmentDate* lSegmentDate_1_ptr =
          lSingleSegmentPathPeriodFromDestination_im1_ptr->getFirstSegmentDate();
        assert (lSegmentDate_1_ptr != NULL);
          
        // Calculate the number of airlines flown by the i-length
        // outbound path
        const stdair::AirlineCode_T& lAirlineCode_1 =
          lSegmentDate_1_ptr->getAirlineCode();
        stdair::NbOfAirlines_T lNbOfAirlines_i =
          lSegmentPathPeriod_im1_ptr->getNbOfAirlines();
        if (lSegmentPathPeriod_im1_ptr->isAirlineFlown(lAirlineCode_1) == false){
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
          lSegmentPathPeriod_im1_ptr->getLastSegmentDate();
        assert (lSegment_im1_ptr != NULL);
        if (lSegment_im1_ptr->getAirlineCode() == lAirlineCode_1
            && lSegment_im1_ptr->getFlightNumber()
            == lSegmentDate_1_ptr->getFlightNumber()) {
          continue;
        }
        
        // Calculate the total elapsed time flown by the i-length
        // outbound path
        const stdair::Date_T& lSegmentPathPeriodOffDate =
          lSegmentPathPeriod_im1_ptr->getOffDate();
        const stdair::AirportCode_T& lSegmentPathPeriodOffPoint = 
          lSegmentPathPeriod_im1_ptr->getDestination();
        const stdair::Date_T& lSegmentDateBoardingDate =
          lSegmentDate_1_ptr->getBoardingDate();
        const stdair::AirportCode_T& lSegmentDateBoardingPoint=
          lSegmentDate_1_ptr->getBoardingPoint();
        
        assert (lSegmentPathPeriodOffDate == lSegmentDateBoardingDate
                && lSegmentPathPeriodOffPoint == lSegmentDateBoardingPoint);

        const stdair::Duration_T lElapsedTime_i = lSegmentPathPeriod_im1_ptr->
          calculateElapsedTimeFromRouting (*lSegmentDate_1_ptr);

        const stdair::Duration_T& lBoardingTime_i =
          lSegmentPathPeriod_im1_ptr->getBoardingTime();
          
        const stdair::SegmentPathPeriodKey_T lSegmentPathPeriodKey_i (lDestination_i,
                                                            lElapsedTime_i,
                                                            iNbOfSegments,
                                                            lNbOfAirlines_i,
                                                            lBoardingTime_i);
        stdair::SegmentPathPeriod& lSegmentPathPeriod_i = stdair::FacBomContent::
          instance().create<stdair::SegmentPathPeriod> (lSegmentPathPeriodKey_i);

        // Clone the list of SegmentDate references of the given SegmentPathPeriod
        // object (passed as the second parameter).
        stdair::FacBomContent::cloneChildrenHolder<
        stdair::SegmentPathPeriod, stdair::SegmentDate> (lSegmentPathPeriod_i,
                                                    *lSegmentPathPeriod_im1_ptr);
       
        // Clone the flight path
        const stdair::FlightPathCode_T lFlightPathCode =
          lSegmentPathPeriod_im1_ptr->getFlightPathCode();
        lSegmentPathPeriod_i.setFlightPathCode (lFlightPathCode);
        
        // Add the SegmentDate reference to the dedicated list within
        // the SegmentPathPeriod. Note that this must be done before the
        // link between the SegmentPathPeriod and ReachableUniverse, as that latter
        // method uses the number of segments within the SegmentPathPeriod
        // object.
        stdair::FacBomContent::
          addFullObjectToTheDedicatedList (lSegmentPathPeriod_i, *lSegmentDate_1_ptr);
        lSegmentPathPeriod_i.updateAfterAddingSegmentDate (*lSegmentDate_1_ptr);
        // update the AirlineCode of the SegmentPathPeriod
        lSegmentPathPeriod_i.updateAirlineCode();
          
        // Link the SegmentPathPeriod to the ReachableUniverse
        stdair::FacBomContent::linkWithParent (lSegmentPathPeriod_i, ioReachableUniverse);
        ioReachableUniverse.buildSegmentPathPeriodListList (lSegmentPathPeriod_i);
      }
    }
  }
}
