/*!
 * \page AirlineScheduleTestSuite_cpp Command-Line Test to Demonstrate How To Test the AirSched Project
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <fstream>
#include <string>
// Boost Unit Test Framework (UTF)
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE InventoryTestSuite
#include <boost/test/unit_test.hpp>
// Boost Date-Time
#include <boost/date_time/gregorian/gregorian.hpp>
// StdAir
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/service/Logger.hpp>
// AirSched
#include <airsched/AIRSCHED_Types.hpp>
#include <airsched/AIRSCHED_Service.hpp>
#include <airsched/config/airsched-paths.hpp>

namespace boost_utf = boost::unit_test;

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("AirlineScheduleTestSuite_utfresults.xml");

/**
 * Configuration for the Boost Unit Test Framework (UTF)
 */
struct UnitTestConfig {
  /** Constructor. */
  UnitTestConfig() {
    boost_utf::unit_test_log.set_stream (utfReportStream);
    boost_utf::unit_test_log.set_format (boost_utf::XML);
    boost_utf::unit_test_log.set_threshold_level (boost_utf::log_test_units);
    //boost_utf::unit_test_log.set_threshold_level (boost_utf::log_successful_tests);
  }

  /** Destructor. */
  ~UnitTestConfig() {
  }
};

// //////////////////////////////////////////////////////////////////////
/**
 * Build a list of travel solution
 */
 const unsigned int testScheduleHelper (const unsigned short iTestFlag,
                                        const stdair::Filename_T& iScheduleInputFilename,
                                        const stdair::Filename_T& iODInputFilename,
                                        const bool isBuiltin,
                                        const bool isWithOnD) {
  
  // Output log File
  std::ostringstream oStr;
  oStr << "AirlineScheduleTestSuite_" << iTestFlag << ".log";
  const stdair::Filename_T lLogFilename (oStr.str());

  // Set the log parameters
  std::ofstream logOutputFile;
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();

  // Instantiate the AirSched service
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  AIRSCHED::AIRSCHED_Service airschedService (lLogParams);

  stdair::AirportCode_T lOrigin;
  stdair::AirportCode_T lDestination;
  stdair::AirportCode_T lPOS;
  stdair::Date_T lPreferredDepartureDate;;
  stdair::Date_T lRequestDate;

  // Check wether or not a (CSV) input file should be read
  if (isBuiltin == true) {

    // Build the default sample BOM tree (filled with schedules)
    airschedService.buildSampleBom();

    lOrigin = "SIN";
    lDestination = "BKK";
    lPOS = "SIN";
    lPreferredDepartureDate = boost::gregorian::from_string ("2010/02/08");
    lRequestDate = boost::gregorian::from_string ("2010/01/21");

  } else {

    if (isWithOnD == false) {

      // Build the BOM tree from parsing input files
      const stdair::ScheduleFilePath lScheduleFilePath (iScheduleInputFilename);
      airschedService.parseAndLoad (lScheduleFilePath);

      lOrigin = "NCE";
      lDestination = "BKK";
      lPOS = "NCE";
      lPreferredDepartureDate = boost::gregorian::from_string ("2007/04/21");
      lRequestDate = boost::gregorian::from_string ("2007/03/21");
    
    } else {

      // Build the BOM tree from parsing input files
      const stdair::ScheduleFilePath lScheduleFilePath (iScheduleInputFilename);
      const stdair::ODFilePath lODFilePath (iODInputFilename);
      airschedService.parseAndLoad (lScheduleFilePath,
                                    lODFilePath);

      lOrigin = "SIN";
      lDestination = "BKK";
      lPOS = "SIN";
      lPreferredDepartureDate = boost::gregorian::from_string ("2012/06/04");
      lRequestDate = boost::gregorian::from_string ("2012/01/01");
    }
    
  }

  // Create a booking request structure
  const stdair::Duration_T lRequestTime (boost::posix_time::hours(8));
  const stdair::DateTime_T lRequestDateTime (lRequestDate, lRequestTime);
  const stdair::CabinCode_T lPreferredCabin ("Bus");
  const stdair::PartySize_T lPartySize (3);
  const stdair::ChannelLabel_T lChannel ("DF");
  const stdair::TripType_T lTripType ("RO");
  const stdair::DayDuration_T lStayDuration (5);
  const stdair::FrequentFlyer_T lFrequentFlyerType ("NONE");
  const stdair::Duration_T lPreferredDepartureTime (boost::posix_time::hours(10));
  const stdair::WTP_T lWTP (2000.0);
  const stdair::PriceValue_T lValueOfTime (20.0);
  const stdair::ChangeFees_T lChangeFees (true);
  const stdair::Disutility_T lChangeFeeDisutility (50);
  const stdair::NonRefundable_T lNonRefundable (true);
  const stdair::Disutility_T lNonRefundableDisutility (50);
      
  const stdair::BookingRequestStruct lBookingRequest (lOrigin, lDestination,
                                                      lPOS,
                                                      lPreferredDepartureDate,
                                                      lRequestDateTime,
                                                      lPreferredCabin,
                                                      lPartySize, lChannel,
                                                      lTripType, lStayDuration,
                                                      lFrequentFlyerType,
                                                      lPreferredDepartureTime,
                                                      lWTP, lValueOfTime,
                                                      lChangeFees,
                                                      lChangeFeeDisutility,
                                                      lNonRefundable,
                                                      lNonRefundableDisutility);
    
  // Build the segment path list
  stdair::TravelSolutionList_T lTravelSolutionList;
  airschedService.buildSegmentPathList (lTravelSolutionList, lBookingRequest);
  const unsigned int lNbOfTravelSolutions = lTravelSolutionList.size();

  STDAIR_LOG_DEBUG ("The number of travel solutions for the booking request '"
                    << lBookingRequest.describe() << "' is equal to "
                    << lNbOfTravelSolutions << ".");

  // Close the Log outputFile
  logOutputFile.close();
  
  return lNbOfTravelSolutions;
}


// /////////////// Main: Unit Test Suite //////////////

// Set the UTF configuration (re-direct the output to a specific file)
BOOST_GLOBAL_FIXTURE (UnitTestConfig);

// Start the test suite
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test a simple build of travel solution
 */
BOOST_AUTO_TEST_CASE (airsched_simple_build) {

  // Input file name
  const stdair::Filename_T lScheduleInputFilename (STDAIR_SAMPLE_DIR
                                                   "/schedule03.csv");

  // State whether the BOM tree should be built-in or parsed from input files
  const bool isBuiltin = false;
  const bool isWithOnD = false;

  // Try to build a travel solution list
  unsigned int lNbOfTravelSolutions = 0;
  BOOST_CHECK_NO_THROW (lNbOfTravelSolutions =
                        testScheduleHelper (0, lScheduleInputFilename, " ",
                                            isBuiltin, isWithOnD));

  // Check the size of the travel solution list
  const unsigned int lExpectedNbOfTravelSolutions = 4;    
  BOOST_CHECK_MESSAGE(lNbOfTravelSolutions == lExpectedNbOfTravelSolutions,
                      "The number of travel solutions is "
                      << lNbOfTravelSolutions << ", but it should be equal to "
                      << lExpectedNbOfTravelSolutions);
  
}

/**
 * Test a simple build of travel solution with the default BOM tree
 */
BOOST_AUTO_TEST_CASE (airsched_default_bom_tree_simple_build) {

  // State whether the BOM tree should be built-in or parsed from input files
  const bool isBuiltin = true;
  const bool isWithOnD = false;

  // Try to build a travel solution list
  unsigned int lNbOfTravelSolutions = 0;
  BOOST_CHECK_NO_THROW (lNbOfTravelSolutions =
                        testScheduleHelper (1, " ", " ", isBuiltin, isWithOnD));

  // Check the size of the travel solution list
  const unsigned int lExpectedNbOfTravelSolutions = 1;    
  BOOST_CHECK_MESSAGE(lNbOfTravelSolutions == lExpectedNbOfTravelSolutions,
                      "The number of travel solutions is "
                      << lNbOfTravelSolutions << ", but it should be equal to "
                      << lExpectedNbOfTravelSolutions);
  
}

/**
 * Test a simple build of travel solution with an OnD input file
 */
BOOST_AUTO_TEST_CASE (airsched_OnD_input_file) {

  // Input file names
  const stdair::Filename_T lScheduleInputFilename (STDAIR_SAMPLE_DIR
                                                   "/rds01/schedule05.csv");
  const stdair::Filename_T lODInputFilename (STDAIR_SAMPLE_DIR
                                             "/ond01.csv");

  // State whether the BOM tree should be built-in or parsed from input files
  const bool isBuiltin = false;
  const bool isWithOnD = true;

  // Try to build a travel solution list
  unsigned int lNbOfTravelSolutions = 0;   
  BOOST_CHECK_NO_THROW  (lNbOfTravelSolutions =
                         testScheduleHelper (2, lScheduleInputFilename,
                                             lODInputFilename,
                                             isBuiltin, isWithOnD));
  
  // Check the size of the travel solution list
  const unsigned int lExpectedNbOfTravelSolutions = 1;    
  BOOST_CHECK_MESSAGE(lNbOfTravelSolutions == lExpectedNbOfTravelSolutions,
                      "The number of travel solutions is "
                      << lNbOfTravelSolutions << ", but it should be equal to "
                      << lExpectedNbOfTravelSolutions);
}

/**
 * Test a simple error case: missing OnD input file
 */
BOOST_AUTO_TEST_CASE (airsched_missing_OnD_input_file) {

  // Input file names
  const stdair::Filename_T lScheduleInputFilename (STDAIR_SAMPLE_DIR
                                                   "/schedule03.csv");
  const stdair::Filename_T lODInputFilename (STDAIR_SAMPLE_DIR
                                             "/missingFiles.csv");

  // State whether the BOM tree should be built-in or parsed from input files
  const bool isBuiltin = false;
  const bool isWithOnD = true;

  // Try to build a travel solution list
  BOOST_CHECK_THROW (testScheduleHelper (3, lScheduleInputFilename,
                                         lODInputFilename,
                                         isBuiltin, isWithOnD),
                     AIRSCHED::OnDInputFileNotFoundException);
}

/**
 * Test a simple error case: missing schedule input file
 */
BOOST_AUTO_TEST_CASE (airsched_missing_schedule_input_file) {

  // Input file name
  const stdair::Filename_T lScheduleInputFilename (STDAIR_SAMPLE_DIR
                                                   "/missingFiles.csv");

  // State whether the BOM tree should be built-in or parsed from input files
  const bool isBuiltin = false;
  const bool isWithOnD = false;

  // Try to build a travel solution list
  BOOST_CHECK_THROW (testScheduleHelper (4, lScheduleInputFilename, " ",
                                         isBuiltin, isWithOnD),
                     AIRSCHED::ScheduleInputFileNotFoundException);

}

/**
 * Test a simple error case: segment date not found
 */
BOOST_AUTO_TEST_CASE (airsched_segment_date_not_found) {

  // Input file name
  const stdair::Filename_T lScheduleInputFilename (STDAIR_SAMPLE_DIR
                                                   "/scheduleError03.csv");

  // State whether the BOM tree should be built-in or parsed from input files
  const bool isBuiltin = false;
  const bool isWithOnD = false;

  // Try to build a travel solution list  
  BOOST_CHECK_THROW  (testScheduleHelper (5, lScheduleInputFilename,
                                          " " ,
                                          isBuiltin, isWithOnD),
                      AIRSCHED::SegmentDateNotFoundException);
  

}


// End the test suite
BOOST_AUTO_TEST_SUITE_END()

/*!
 * \endcode
 */

