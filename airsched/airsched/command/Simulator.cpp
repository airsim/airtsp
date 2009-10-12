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
#include <stdair/bom/InventoryStructure.hpp>
#include <stdair/bom/FlightDateStructure.hpp>
#include <stdair/bom/LegDateStructure.hpp>
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/LegCabinStructure.hpp>
#include <stdair/bom/SegmentCabinStructure.hpp>
#include <stdair/bom/BookingClassStructure.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/BomIterator.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateList.hpp>
#include <stdair/bom/FlightDateMap.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegDateList.hpp>
#include <stdair/bom/LegDateMap.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateList.hpp>
#include <stdair/bom/SegmentDateMap.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AIRSCHED
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void Simulator::simulate () {
    // DEBUG
    AIRSCHED_LOG_DEBUG ("Welcome to Air-Schedule");

    // Step 0.0: initialisation
    // Create the root of the Bom tree (i.e., a BomContentRoot object)
    stdair::BomContentRoot_T& lBomContentRoot =
      stdair::FacBomContent::instance().createBomRoot<stdair::Inventory>();
    
    
    // Step 0.1: Inventory level
    // Create an Inventory (BA)
    const stdair::AirlineCode_T lAirlineCode ("BA");
    const stdair::InventoryKey_T lInventoryKey (lAirlineCode);

    stdair::Inventory& lInventory =
      stdair::FacBomContent::
      instance().create<stdair::Inventory> (lBomContentRoot, lInventoryKey);
    
    // Display the inventory
    AIRSCHED_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const stdair::FlightNumber_T lFlightNumber = 15;
    const stdair::Date_T lDate (2010, 6, 10);
    const stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

    stdair::FlightDate& lFlightDate =
      stdair::FacBomContent::instance().create<stdair::FlightDate> (lInventory,
                                                            lFlightDateKey);
    
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    stdair::SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

    stdair::SegmentDate& lLHRSYDSegment =
      stdair::FacBomContent::instance().create<stdair::SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


    // Create a second SegmentDate (LHR-BKK)
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = stdair::SegmentDateKey_T (lLHR, lBKK);

    stdair::SegmentDate& lLHRBKKSegment =
      stdair::FacBomContent::instance().create<stdair::SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = stdair::SegmentDateKey_T (lBKK, lSYD);

    stdair::SegmentDate& lBKKSYDSegment =
      stdair::FacBomContent::instance().create<stdair::SegmentDate> (lFlightDate,
                                                             lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
    // Step 0.4: Leg-date level
    // Create a first LegDate (LHR)
    stdair::LegDateKey_T lLegDateKey (lLHR);

    stdair::LegDate& lLHRLeg =
      stdair::FacBomContent::instance().create<stdair::LegDate> (lFlightDate,
                                                         lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
    // Create a second LegDate (BKK)
    lLegDateKey = stdair::LegDateKey_T (lBKK);

    stdair::LegDate& lBKKLeg =
      stdair::FacBomContent::instance().create<stdair::LegDate> (lFlightDate,
                                                         lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) of the Segment LHR-BKK;
    const stdair::CabinCode_T lY ("Y");
    stdair::SegmentCabinKey_T lYSegmentCabinKey (lY);

    stdair::SegmentCabin& lLHRBKKSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lLHRBKKSegment, 
                                               lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    stdair::SegmentCabin& lBKKSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lBKKSYDSegment, 
                                               lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    stdair::SegmentCabin& lLHRSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lLHRSYDSegment, 
                                               lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    
    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) of the Leg LHR-BKK;
    stdair::LegCabinKey_T lYLegCabinKey (lY);

    stdair::LegCabin& lLHRLegYCabin =
      stdair::FacBomContent::
      instance().create<stdair::LegCabin> (lLHRLeg, lYLegCabinKey);

    // Display the leg-cabin
    AIRSCHED_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) of the Leg BKK-SYD;
    stdair::LegCabin& lBKKLegYCabin =
      stdair::FacBomContent::
      instance().create<stdair::LegCabin> (lBKKLeg, lYLegCabinKey);

    // Display the leg-cabin
    AIRSCHED_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    // Step 0.7: booking class level
    // Create a BookingClass (Q) of the Segment LHR-BKK, cabin Y;
    const stdair::ClassCode_T lQ ("Q");
    stdair::BookingClassKey_T lQBookingClassKey (lQ);

    stdair::BookingClass& lLHRBKKSegmentYCabinQClass =
      stdair::FacBomContent::
      instance().create<stdair::BookingClass> (lLHRBKKSegmentYCabin, 
                                               lQBookingClassKey);

    // Display the booking class
    AIRSCHED_LOG_DEBUG ("BookingClass: "
                        << lLHRBKKSegmentYCabinQClass.toString());

        
    // Step 0.8: Initialisation results
    // Display the full structure and content
    AIRSCHED_LOG_DEBUG ("Full Inventory: " << lInventory.toString());


    testIteratorInventory (lInventory);
    testIteratorFlightDate (lFlightDate);
  }

  // ////////////////////////////////////////////////////////////////
  void Simulator::testIteratorInventory (const stdair::Inventory& iInventory) {
    AIRSCHED_LOG_DEBUG ("Test iterator.");

    // Browse the list with a for-loop
    AIRSCHED_LOG_DEBUG ("Browse the list");
    stdair::FlightDateList_T lFDList = iInventory.getFlightDateList();
    for (stdair::FlightDateList_T::iterator itFD = lFDList.begin();
         itFD != lFDList.end(); ++itFD) {
      AIRSCHED_LOG_DEBUG ("Current flight-date: " << *itFD);
    }
    
    // Browse the map with a for-loops
    AIRSCHED_LOG_DEBUG ("Browse the map with iterator");
    stdair::FlightDateMap_T lFDMap = iInventory.getFlightDateMap();
    for (stdair::FlightDateMap_T::iterator itFD = lFDMap.begin();
         itFD != lFDMap.end(); ++itFD) {
      const stdair::FlightDate* lCurrentFlightDate_ptr = itFD->second;
      AIRSCHED_LOG_DEBUG ("Current flight-date: "
                          << lCurrentFlightDate_ptr->toString());
    }

    AIRSCHED_LOG_DEBUG ("Browse the map with reverse_iterator");
    for (stdair::FlightDateMap_T::reverse_iterator itFD = lFDMap.rbegin();
         itFD != lFDMap.rend(); ++itFD) {
      const stdair::FlightDate* lCurrentFlightDate_ptr = itFD->second;
      AIRSCHED_LOG_DEBUG ("Current flight-date: "
                          << lCurrentFlightDate_ptr->toString());
    }

    AIRSCHED_LOG_DEBUG ("Test operators: ");
    stdair::FlightDateList_T::iterator itBegin = lFDList.begin();
    stdair::FlightDateList_T::iterator itEnd = lFDList.end();
    AIRSCHED_LOG_DEBUG ("itEnd - itBegin, should be 1: " << itEnd - itBegin);
    AIRSCHED_LOG_DEBUG ("itBegin - itEnd, should be -1: " << itBegin - itEnd);
    AIRSCHED_LOG_DEBUG ("itBegin < itEnd, should be 1: " << (itBegin < itEnd));
    AIRSCHED_LOG_DEBUG ("itEnd - (1 + itBegin), should be 0: "
                        << (itEnd - (1 + itBegin)));
    AIRSCHED_LOG_DEBUG ( *(itEnd - 1));
    AIRSCHED_LOG_DEBUG ( *(itEnd -= 1));
  }

  // ////////////////////////////////////////////////////////////////
  void Simulator::
  testIteratorFlightDate (const stdair::FlightDate& iFlightDate) {
    AIRSCHED_LOG_DEBUG ("Test iterator.");

    // Browse the list with a for-loop
    AIRSCHED_LOG_DEBUG ("Browse the segment-date list");
    stdair::SegmentDateList_T lSDList = iFlightDate.getSegmentDateList();
    for (stdair::SegmentDateList_T::iterator itSD = lSDList.begin();
         itSD != lSDList.end(); ++itSD) {
      AIRSCHED_LOG_DEBUG ("Current segment-date: " << *itSD);
    }
    
    // Browse the map with a for-loop
    AIRSCHED_LOG_DEBUG ("Browse the segment_date map with iterator");
    stdair::SegmentDateMap_T lSDMap = iFlightDate.getSegmentDateMap();
    for (stdair::SegmentDateMap_T::iterator itSD = lSDMap.begin();
         itSD != lSDMap.end(); ++itSD) {
      const stdair::SegmentDate* lCurrentSegmentDate_ptr = itSD->second;
      AIRSCHED_LOG_DEBUG ("Current segment-date: "
                          << lCurrentSegmentDate_ptr->toString());
    }

    
    // Browse the list with a for-loop
    AIRSCHED_LOG_DEBUG ("Browse the leg-date list");
    stdair::LegDateList_T lLDList = iFlightDate.getLegDateList();
    for (stdair::LegDateList_T::iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      AIRSCHED_LOG_DEBUG ("Current leg-date: " << *itLD);
    }
    
    // Browse the map with a for-loop
    AIRSCHED_LOG_DEBUG ("Browse the leg-date map with iterator");
    stdair::LegDateMap_T lLDMap = iFlightDate.getLegDateMap();
    for (stdair::LegDateMap_T::iterator itLD = lLDMap.begin();
         itLD != lLDMap.end(); ++itLD) {
      const stdair::LegDate* lCurrentLegDate_ptr = itLD->second;
      AIRSCHED_LOG_DEBUG ("Current leg-date: "
                          << lCurrentLegDate_ptr->toString());
    }
  }
  
}
