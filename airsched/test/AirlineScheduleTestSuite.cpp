// STL
#include <iostream>
#include <string>
// CPPUNIT
#include <test/com/CppUnitCore.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Service.hpp>
// AIRSCHED Test Suite
#include <test/AirlineScheduleTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
void testAirlineScheduleHelper() {

  try {
    
    // Output log File
    std::string lLogFilename ("AirlineScheduleTestSuite.log");
    
    // Number of random draws to be generated (best if greater than 100)
    // const int K = 100000;
    
    // Input file name
    // const std::string inputFileName ("samples/sample2.csv");
    // const bool hasInputFile = true;
    
    // Set the log parameters
    std::ofstream logOutputFile;
    // open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // Initialise the list of classes/buckets
    // AIRSCHED::AIRSCHED_Service airschedService (logOutputFile);
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }
}

// //////////////////////////////////////////////////////////////////////
void AirlineScheduleTestSuite::testAirlineSchedule() {
  CPPUNIT_ASSERT_NO_THROW (testAirlineScheduleHelper(););
}

// //////////////////////////////////////////////////////////////////////
// void AirlineScheduleTestSuite::errorCase () {
//  CPPUNIT_ASSERT (false);
// }

// //////////////////////////////////////////////////////////////////////
AirlineScheduleTestSuite::AirlineScheduleTestSuite () {
  _describeKey << "Running test on AIRSCHED Optimisation function";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()
