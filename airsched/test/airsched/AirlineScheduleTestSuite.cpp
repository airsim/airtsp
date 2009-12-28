// STL
#include <iostream>
#include <string>
// CPPUNIT
#include <extracppunit/CppUnitCore.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomRootKey.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/LegDateKey.hpp>
#include <stdair/bom/SegmentCabinKey.hpp>
#include <stdair/bom/LegCabinKey.hpp>
#include <stdair/bom/BookingClassKey.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/factory/FacSupervisor.hpp>
// AIRSCHED
#include <airsched/factory/FacSupervisor.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>
#include <airsched/AIRSCHED_Service.hpp>
// AIRSCHED Test Suite
#include <test/airsched/AirlineScheduleTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
void externalMemoryManagementHelper() {
  try {
    
    // Output log File
    std::string lLogFilename ("AirlineScheduleTestSuite.log");
    
    // Set the log parameters
    std::ofstream logOutputFile;
    // open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    AIRSCHED::AIRSCHED_Service airschedService (logOutputFile);

    // DEBUG
    AIRSCHED_LOG_DEBUG ("Welcome to Air-Schedule");

    // Step 0.0: initialisation
    // Create the root of the Bom tree (i.e., a BomRoot object)
    stdair::BomRoot& lBomRoot =
      stdair::FacBomContent::instance().create<stdair::BomRoot>();
    
    
    // Step 0.1: Inventory level
    // Create an Inventory (BA)
    const stdair::AirlineCode_T lAirlineCode ("BA");
    stdair::InventoryKey_T lInventoryKey (lAirlineCode);

    stdair::Inventory& lInventory =
      stdair::FacBomContent::
      instance().create<stdair::Inventory> (lBomRoot, lInventoryKey);
    
    // Display the inventory
    AIRSCHED_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const stdair::FlightNumber_T lFlightNumber = 15;
    const stdair::Date_T lDate (2010, 6, 10);
    stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

    stdair::FlightDate& lFlightDate =
      stdair::FacBomContent::
      instance().create<stdair::FlightDate> (lInventory, lFlightDateKey);
    
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    stdair::SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

    stdair::SegmentDate& lLHRSYDSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lFlightDate, lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


    // Create a second SegmentDate (LHR-BKK)
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = stdair::SegmentDateKey_T (lLHR, lBKK);

    stdair::SegmentDate& lLHRBKKSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lFlightDate,
                                                lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = stdair::SegmentDateKey_T (lBKK, lSYD);

    stdair::SegmentDate& lBKKSYDSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lFlightDate,
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

    // Browse the BomRoot and display the created objects.
    AIRSCHED_LOG_DEBUG ("Browse the BomRoot");
    
    const stdair::InventoryList_T& lInventoryList = lBomRoot.getInventoryList();
    for (stdair::InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory& lCurrentInventory = *itInv;
      AIRSCHED_LOG_DEBUG ("Inventory: " << lCurrentInventory.toString());
    }
    
    // Close the Log outputFile
    logOutputFile.close();

    // Clean the memory.
//     stdair::FacSupervisor::instance().cleanBomContentLayer();
//     stdair::FacSupervisor::instance().cleanBomStructureLayer();
//     AIRSCHED::FacSupervisor::instance().cleanServiceLayer();
//     AIRSCHED::FacSupervisor::instance().cleanLoggerService();

  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }
}

// //////////////////////////////////////////////////////////////////////
void AirlineScheduleTestSuite::externalMemoryManagement() {
  CPPUNIT_ASSERT_NO_THROW (externalMemoryManagementHelper(););
}

// //////////////////////////////////////////////////////////////////////
void scheduleParsingHelper() {
  try {
    
    // DEBUG
    AIRSCHED_LOG_DEBUG ("Schedule Parsing Test");
    
    // Output log File
    std::string lLogFilename ("AirlineScheduleTestSuite.log");
    
    // Set the log parameters
    std::ofstream logOutputFile;
    // open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    AIRSCHED::AIRSCHED_Service airschedService (logOutputFile);

    // Input file name
    std::string lInputFilename ("samples/schedule01.csv");

    // Create a dummy AirlineFeature object for the test.
    stdair::AirlineFeatureSet& lAirlineFeatureSet =
      stdair::FacBomContent::instance().create<stdair::AirlineFeatureSet>();
    const stdair::AirlineCode_T lAirlineCode ("BA");
    stdair::AirlineFeatureKey_T lAirlineFeatureKey (lAirlineCode);

    stdair::AirlineFeature& lAirlineFeature = stdair::FacBomContent::instance().
      create<stdair::AirlineFeature> (lAirlineFeatureSet, lAirlineFeatureKey);

    const stdair::Date_T lStartAnalysisDate (2000, 1, 1);

    stdair::BomRoot& lBomRoot =
      AIRSCHED::AIRSCHED_Service::generateInventories (lInputFilename,
                                                       lAirlineFeatureSet,
                                                       lStartAnalysisDate);

    // Display the all the inventories.
    // Browse the BomRoot.
    const stdair::InventoryList_T lInventoryList = lBomRoot.getInventoryList ();
    for (stdair::InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory& lCurrentInventory = *itInv;
      AIRSCHED_LOG_DEBUG ("Inventory: " << lCurrentInventory.toString());

      // Browse the Inventory.
      const stdair::FlightDateList_T lFDList =
        lCurrentInventory.getFlightDateList ();
      for (stdair::FlightDateList_T::iterator itFD = lFDList.begin();
           itFD != lFDList.end(); ++itFD) {
        const stdair::FlightDate& lCurrentFD = *itFD;
        AIRSCHED_LOG_DEBUG ("Flight-date: " << lCurrentFD.toString());

        // Browse the FlightDate.
        const stdair::LegDateList_T lLDList = lCurrentFD.getLegDateList();
        for (stdair::LegDateList_T::iterator itLD = lLDList.begin();
             itLD != lLDList.end(); ++itLD) {
          const stdair::LegDate& lCurrentLD = *itLD;
          AIRSCHED_LOG_DEBUG ("Leg-date: " << lCurrentLD.toString());
          
          // Browse the LegDate.
          const stdair::LegCabinList_T lLCList = lCurrentLD.getLegCabinList();
          for (stdair::LegCabinList_T::iterator itLC = lLCList.begin();
               itLC != lLCList.end(); ++itLC) {
            const stdair::LegCabin& lCurrentLC = *itLC;
            AIRSCHED_LOG_DEBUG ("Leg-cabin: " << lCurrentLC.toString());
          }
        }
        
        const stdair::SegmentDateList_T lSDList =
          lCurrentFD.getSegmentDateList();
        for (stdair::SegmentDateList_T::iterator itSD = lSDList.begin();
             itSD != lSDList.end(); ++itSD) {
          const stdair::SegmentDate& lCurrentSD = *itSD;
          AIRSCHED_LOG_DEBUG ("Segment-date: " << lCurrentSD.toString());

          // Browse the SegmentDate.
          const stdair::SegmentCabinList_T lSCList =
            lCurrentSD.getSegmentCabinList();
          for (stdair::SegmentCabinList_T::iterator itSC = lSCList.begin();
               itSC != lSCList.end(); ++itSC) {
            const stdair::SegmentCabin& lCurrentSC = *itSC;
            AIRSCHED_LOG_DEBUG ("Segment-cabin: " << lCurrentSC.toString());

            // Browse the SegmentCabin
            const stdair::BookingClassList_T lBCList =
              lCurrentSC.getBookingClassList ();
            for (stdair::BookingClassList_T::iterator itBC = lBCList.begin();
                   itBC != lBCList.end(); ++itBC) {
              const stdair::BookingClass& lCurrentBC = *itBC;
              AIRSCHED_LOG_DEBUG ("Booking class: " << lCurrentBC.toString());
            }
          }
        }
      }
    }

    // Browse the inventory for the booking classes.
    AIRSCHED_LOG_DEBUG ("Browse the inventory for the booking classes");
    for (stdair::InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory& lCurrentInventory = *itInv;
      AIRSCHED_LOG_DEBUG ("Inventory: " << lCurrentInventory.toString());

      // Browse the Inventory.
      const stdair::BookingClassList_T lBCList =
        lCurrentInventory.getBookingClassList();
      for (stdair::BookingClassList_T::iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        const stdair::BookingClass& lCurrentBC = *itBC;
        AIRSCHED_LOG_DEBUG ("Booking class: " << lCurrentBC.getKey().describe());
      }
    }
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }
}

// //////////////////////////////////////////////////////////////////////
void AirlineScheduleTestSuite::scheduleParsing() {
  CPPUNIT_ASSERT_NO_THROW (scheduleParsingHelper(););
}

// //////////////////////////////////////////////////////////////////////
AirlineScheduleTestSuite::AirlineScheduleTestSuite () {
  _describeKey << "Running test on AIRSCHED Optimisation function";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()
