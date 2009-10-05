// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <string>
// STDAIR
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/BomIterator.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Types.hpp>
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/LegDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void Simulator::simulate () {
    // DEBUG
    AIRSCHED_LOG_DEBUG ("Welcome to Air-Schedule");

    // Step 0.0: initialisation
    // Create the root of the Bom tree (i.e., a BomContentRoot object)
    BomContentRoot_T& lBomContentRoot =
      stdair::FacBomContent::instance().createBomRoot<Inventory>();
    
    
    // Step 0.1: Inventory level
    // Create an Inventory (BA)
    const stdair::AirlineCode_T lAirlineCode ("BA");
    const InventoryKey_T lInventoryKey (lAirlineCode);

    Inventory& lInventory =
      stdair::FacBomContent::instance().create<Inventory> (lBomContentRoot,
                                                           lInventoryKey);
    
    // Display the inventory
    AIRSCHED_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const stdair::FlightNumber_T lFlightNumber = 15;
    const stdair::Date_T lDate (2010, 6, 10);
    const FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

    FlightDate& lFlightDate =
      stdair::FacBomContent::instance().create<FlightDate> (lInventory,
                                                            lFlightDateKey);
    
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

    SegmentDate& lLHRSYDSegment =
      stdair::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


    // Create a second SegmentDate (LHR-BKK)
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = SegmentDateKey_T (lLHR, lBKK);

    SegmentDate& lLHRBKKSegment =
      stdair::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = SegmentDateKey_T (lBKK, lSYD);

    SegmentDate& lBKKSYDSegment =
      stdair::FacBomContent::instance().create<SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
    // Step 0.4: Leg-date level
    // Create a first LegDate (LHR)
    LegDateKey_T lLegDateKey (lLHR);

    LegDate& lLHRLeg =
      stdair::FacBomContent::instance().create<LegDate> (lFlightDate,
                                                         lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
    // Create a second LegDate (BKK)
    lLegDateKey = LegDateKey_T (lBKK);

    LegDate& lBKKLeg =
      stdair::FacBomContent::instance().create<LegDate> (lFlightDate,
                                                         lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());
    
    // Step 0.5: Initialisation results
    // Display the full structure and content
    AIRSCHED_LOG_DEBUG ("Full Inventory: " << lInventory.toString());


    testIteratorInventory (lInventory);
  }

  // ////////////////////////////////////////////////////////////////
  void Simulator::testIteratorInventory (const Inventory& iInventory) {
    AIRSCHED_LOG_DEBUG ("Test iterator.");

    // Browse the list with a for-loop
    AIRSCHED_LOG_DEBUG ("Browse the list");
    for (Inventory::list_const_iterator itInv =
           iInventory.flightDateListConstIteratorBegin();
         itInv != iInventory.flightDateListConstIteratorEnd(); ++itInv) {
      AIRSCHED_LOG_DEBUG ("Current flight-date: " << *itInv);
    }
    
    // Browse the map with a for-loop
    AIRSCHED_LOG_DEBUG ("Browse the map with const_iterator");
    for (Inventory::map_const_iterator itInv =
           iInventory.flightDateMapConstIteratorBegin();
         itInv != iInventory.flightDateMapConstIteratorEnd(); ++itInv) {
      const FlightDate* lCurrentFlightDate_ptr = itInv->second;
      AIRSCHED_LOG_DEBUG ("Current flight-date: "
                          << lCurrentFlightDate_ptr->toString());
    }

    AIRSCHED_LOG_DEBUG ("Browse the map with reverse_iterator");
    for (Inventory::map_reverse_iterator itInv =
           iInventory.flightDateMapIteratorRBegin();
         itInv != iInventory.flightDateMapIteratorREnd(); ++itInv) {
      FlightDate* lCurrentFlightDate_ptr = itInv->second;
      AIRSCHED_LOG_DEBUG ("Current flight-date: "
                          << lCurrentFlightDate_ptr->toString());
    }

    AIRSCHED_LOG_DEBUG ("Test operators: ");
    Inventory::list_const_iterator itBegin =
      iInventory.flightDateListConstIteratorBegin();
    Inventory::list_const_iterator itEnd =
      iInventory.flightDateListConstIteratorEnd();
    AIRSCHED_LOG_DEBUG ("itEnd - itBegin, should be 1: " << itEnd - itBegin);
    AIRSCHED_LOG_DEBUG ("itBegin - itEnd, should be -1: " << itBegin - itEnd);
    AIRSCHED_LOG_DEBUG ("itBegin < itEnd, should be 1: " << (itBegin < itEnd));
    AIRSCHED_LOG_DEBUG ("itEnd - (1 + itBegin), should be 0: "
                        << (itEnd - (1 + itBegin)));
    AIRSCHED_LOG_DEBUG ( *(itEnd - 1));
    AIRSCHED_LOG_DEBUG ( *(itEnd -=1));
  }
  
}
