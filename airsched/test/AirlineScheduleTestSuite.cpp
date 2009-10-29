// STL
#include <iostream>
#include <string>
// CPPUNIT
#include <test/com/CppUnitCore.hpp>
// STDAIR
#include <stdair/bom/BomRootKey.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/LegDateKey.hpp>
#include <stdair/bom/SegmentCabinKey.hpp>
#include <stdair/bom/LegCabinKey.hpp>
#include <stdair/bom/BookingClassKey.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AIRSCHED
#include <airsched/bom/BomRoot.hpp>
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/bom/LegDate.hpp>
#include <airsched/bom/SegmentCabin.hpp>
#include <airsched/bom/LegCabin.hpp>
#include <airsched/bom/BookingClass.hpp>
#include <airsched/command/Simulator.hpp>
#include <airsched/service/Logger.hpp>
#include <airsched/AIRSCHED_Service.hpp>
// AIRSCHED Test Suite
#include <test/AirlineScheduleTestSuite.hpp>

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
    AIRSCHED::BomRoot& lBomRoot =
      stdair::FacBomContent::instance().create<AIRSCHED::BomRoot>();
    
    
    // Step 0.1: Inventory level
    // Create an Inventory (BA)
    const stdair::AirlineCode_T lAirlineCode ("BA");
    const stdair::InventoryKey_T lInventoryKey (lAirlineCode);

    AIRSCHED::Inventory& lInventory =
      stdair::FacBomContent::
      instance().create<AIRSCHED::Inventory> (lBomRoot, lInventoryKey);
    
    // Display the inventory
    AIRSCHED_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const stdair::FlightNumber_T lFlightNumber = 15;
    const stdair::Date_T lDate (2010, 6, 10);
    const stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

    AIRSCHED::FlightDate& lFlightDate =
      stdair::FacBomContent::
      instance().create<AIRSCHED::FlightDate> (lInventory, lFlightDateKey);
    
    // Display the flight-date
    AIRSCHED_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    stdair::SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

    AIRSCHED::SegmentDate& lLHRSYDSegment =
      stdair::FacBomContent::
      instance().create<AIRSCHED::SegmentDate> (lFlightDate, lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


    // Create a second SegmentDate (LHR-BKK)
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = stdair::SegmentDateKey_T (lLHR, lBKK);

    AIRSCHED::SegmentDate& lLHRBKKSegment =
      stdair::FacBomContent::
      instance().create<AIRSCHED::SegmentDate> (lFlightDate,
                                                lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = stdair::SegmentDateKey_T (lBKK, lSYD);

    AIRSCHED::SegmentDate& lBKKSYDSegment =
      stdair::FacBomContent::
      instance().create<AIRSCHED::SegmentDate> (lFlightDate,
                                                lSegmentDateKey);

    // Display the segment-date
    AIRSCHED_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
    // Step 0.4: Leg-date level
    // Create a first LegDate (LHR)
    stdair::LegDateKey_T lLegDateKey (lLHR);

    AIRSCHED::LegDate& lLHRLeg =
      stdair::FacBomContent::instance().create<AIRSCHED::LegDate> (lFlightDate,
                                                                   lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
    // Create a second LegDate (BKK)
    lLegDateKey = stdair::LegDateKey_T (lBKK);

    AIRSCHED::LegDate& lBKKLeg =
      stdair::FacBomContent::instance().create<AIRSCHED::LegDate> (lFlightDate,
                                                                   lLegDateKey);

    // Display the leg-date
    AIRSCHED_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) of the Segment LHR-BKK;
    const stdair::CabinCode_T lY ("Y");
    stdair::SegmentCabinKey_T lYSegmentCabinKey (lY);

    AIRSCHED::SegmentCabin& lLHRBKKSegmentYCabin =
      stdair::FacBomContent::
      instance().create<AIRSCHED::SegmentCabin> (lLHRBKKSegment, 
                                                 lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    AIRSCHED::SegmentCabin& lBKKSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<AIRSCHED::SegmentCabin> (lBKKSYDSegment, 
                                                 lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    AIRSCHED::SegmentCabin& lLHRSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<AIRSCHED::SegmentCabin> (lLHRSYDSegment, 
                                                 lYSegmentCabinKey);

    // Display the segment-cabin
    AIRSCHED_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    
    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) of the Leg LHR-BKK;
    stdair::LegCabinKey_T lYLegCabinKey (lY);

    AIRSCHED::LegCabin& lLHRLegYCabin =
      stdair::FacBomContent::
      instance().create<AIRSCHED::LegCabin> (lLHRLeg, lYLegCabinKey);

    // Display the leg-cabin
    AIRSCHED_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) of the Leg BKK-SYD;
    AIRSCHED::LegCabin& lBKKLegYCabin =
      stdair::FacBomContent::
      instance().create<AIRSCHED::LegCabin> (lBKKLeg, lYLegCabinKey);

    // Display the leg-cabin
    AIRSCHED_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    // Step 0.7: booking class level
    // Create a BookingClass (Q) of the Segment LHR-BKK, cabin Y;
    const stdair::ClassCode_T lQ ("Q");
    stdair::BookingClassKey_T lQBookingClassKey (lQ);

    AIRSCHED::BookingClass& lLHRBKKSegmentYCabinQClass =
      stdair::FacBomContent::
      instance().create<AIRSCHED::BookingClass> (lLHRBKKSegmentYCabin, 
                                                 lQBookingClassKey);

    // Display the booking class
    AIRSCHED_LOG_DEBUG ("BookingClass: "
                        << lLHRBKKSegmentYCabinQClass.toString());
    
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
AirlineScheduleTestSuite::AirlineScheduleTestSuite () {
  _describeKey << "Running test on AIRSCHED Optimisation function";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()
