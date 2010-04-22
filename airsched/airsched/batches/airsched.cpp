// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BomSource.hpp>
#include <stdair/bom/BomTypes.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Service.hpp>
#include <airsched/config/airsched-paths.hpp>


// //////// Type definitions ///////
typedef std::vector<std::string> WordList_T;


// //////// Constants //////
/** Default name and location for the log file. */
const std::string K_AIRSCHED_DEFAULT_LOG_FILENAME ("airsched.log");

/** Default name and location for the (CSV) input file. */
const std::string K_AIRSCHED_DEFAULT_INPUT_FILENAME ("../../test/samples/schedule03.csv");

/** Default booking request string, to be seached against the AirSched
    network. */
const std::string K_AIRSCHED_DEFAULT_BOOKING_REQUEST ("NCE BKK NCE 2007-04-21 2007-03-21 08:32:00 C 1 DF RO 5 NONE 10:00:00 2000.0 20.0");

// //////////////////////////////////////////////////////////////////////
void tokeniseStringIntoWordList (const std::string& iPhrase,
                                 WordList_T& ioWordList) {
  // Empty the word list
  ioWordList.clear();
  
  // Boost Tokeniser
  typedef boost::tokenizer<boost::char_separator<char> > Tokeniser_T;
  
  // Define the separators
  const boost::char_separator<char> lSepatorList(" .,;:|+-*/_=!@#$%`~^&(){}[]?'<>\"");
  
  // Initialise the phrase to be tokenised
  Tokeniser_T lTokens (iPhrase, lSepatorList);
  for (Tokeniser_T::const_iterator tok_iter = lTokens.begin();
       tok_iter != lTokens.end(); ++tok_iter) {
    const std::string& lTerm = *tok_iter;
    ioWordList.push_back (lTerm);
  }
  
}

// //////////////////////////////////////////////////////////////////////
std::string createStringFromWordList (const WordList_T& iWordList) {
  std::ostringstream oStr;

  unsigned short idx = iWordList.size();
  for (WordList_T::const_iterator itWord = iWordList.begin();
       itWord != iWordList.end(); ++itWord, --idx) {
    const std::string& lWord = *itWord;
    oStr << lWord;
    if (idx > 1) {
      oStr << " ";
    }
  }
  
  return oStr.str();
}

// ///////// Parsing of Options & Configuration /////////
// A helper function to simplify the main part.
template<class T> std::ostream& operator<< (std::ostream& os,
                                            const std::vector<T>& v) {
  std::copy (v.begin(), v.end(), std::ostream_iterator<T> (std::cout, " ")); 
  return os;
}

/** Early return status (so that it can be differentiated from an error). */
const int K_AIRSCHED_EARLY_RETURN_STATUS = 99;

/** Read and parse the command line options. */
int readConfiguration (int argc, char* argv[], int& ioRandomDraws, 
                       stdair::Filename_T& ioInputFilename,
                       std::string& ioLogFilename,
                       std::string& ioBookingRequestString) {
  
  // Initialise the travel query string, if that one is empty
  if (ioBookingRequestString.empty() == true) {
    ioBookingRequestString = K_AIRSCHED_DEFAULT_BOOKING_REQUEST;
  }
  
  // Transform the query string into a list of words (STL strings)
  WordList_T lWordList;
  tokeniseStringIntoWordList (ioBookingRequestString, lWordList);

    
  // Declare a group of options that will be allowed only on command line
  boost::program_options::options_description generic ("Generic options");
  generic.add_options()
    ("prefix", "print installation prefix")
    ("version,v", "print version string")
    ("help,h", "produce help message");
    
  // Declare a group of options that will be allowed both on command
  // line and in config file
  boost::program_options::options_description config ("Configuration");
  config.add_options()
    ("input,i",
     boost::program_options::value< std::string >(&ioInputFilename)->default_value(K_AIRSCHED_DEFAULT_INPUT_FILENAME),
     "(CVS) input file for the demand distributions")
    ("log,l",
     boost::program_options::value< std::string >(&ioLogFilename)->default_value(K_AIRSCHED_DEFAULT_LOG_FILENAME),
     "Filename for the logs")
    ("bkg_req,b",
     boost::program_options::value< WordList_T >(&lWordList)->multitoken(),
     "Booking request word list (e.g. NCE BKK NCE 2007-04-21 2007-04-21 10:00:00 C 1 DF RO 5 NONE 10:0:0 2000.0 20.0), which sould be located at the end of the command line (otherwise, the other options would be interpreted as part of that booking request word list)")
    ;

  // Hidden options, will be allowed both on command line and
  // in config file, but will not be shown to the user.
  boost::program_options::options_description hidden ("Hidden options");
  hidden.add_options()
    ("copyright",
     boost::program_options::value< std::vector<std::string> >(),
     "Show the copyright (license)");
        
  boost::program_options::options_description cmdline_options;
  cmdline_options.add(generic).add(config).add(hidden);

  boost::program_options::options_description config_file_options;
  config_file_options.add(config).add(hidden);

  boost::program_options::options_description visible ("Allowed options");
  visible.add(generic).add(config);
        
  boost::program_options::positional_options_description p;
  p.add ("copyright", -1);
        
  boost::program_options::variables_map vm;
  boost::program_options::
    store (boost::program_options::command_line_parser (argc, argv).
           options (cmdline_options).positional(p).run(), vm);

  std::ifstream ifs ("airsched.cfg");
  boost::program_options::store (parse_config_file (ifs, config_file_options),
                                 vm);
  boost::program_options::notify (vm);
    
  if (vm.count ("help")) {
    std::cout << visible << std::endl;
    return K_AIRSCHED_EARLY_RETURN_STATUS;
  }

  if (vm.count ("version")) {
    std::cout << PACKAGE_NAME << ", version " << PACKAGE_VERSION << std::endl;
    return K_AIRSCHED_EARLY_RETURN_STATUS;
  }

  if (vm.count ("prefix")) {
    std::cout << "Installation prefix: " << PREFIXDIR << std::endl;
    return K_AIRSCHED_EARLY_RETURN_STATUS;
  }

  if (vm.count ("input")) {
    ioInputFilename = vm["input"].as< std::string >();
    std::cout << "Input filename is: " << ioInputFilename << std::endl;
  }

  if (vm.count ("log")) {
    ioLogFilename = vm["log"].as< std::string >();
    std::cout << "Log filename is: " << ioLogFilename << std::endl;
  }

  // Rebuild the booking request query string
  ioBookingRequestString = createStringFromWordList (lWordList);

  // Suppress some potential separators (such as ':', '-' or '/')
  tokeniseStringIntoWordList (ioBookingRequestString, lWordList);
  ioBookingRequestString = createStringFromWordList (lWordList);
  std::cout << "The booking request string is: " << ioBookingRequestString
            << std::endl;
    
  return 0;
}

// //////////////////////////////////////////////////////////////
stdair::BookingRequestStruct
parseBookingRequest (const std::string& iRequestOption) {

  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  boost::char_separator<char> sep(" ");

  tokenizer tokens (iRequestOption, sep);

  // Origin (e.g., "NCE")
  tokenizer::iterator tok_iter = tokens.begin();
  assert (tok_iter != tokens.end());
  const stdair::AirportCode_T iOrigin (*tok_iter);

  // Destination (e.g., "BKK")
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::AirportCode_T iDestination (*tok_iter);
  
  // POS (e.g., "NCE")
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::AirportCode_T iPOS (*tok_iter);
  
  // Preferred departure date (e.g., "2007-04-21")
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lDepDateYear = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lDepDateMonth = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lDepDateDay = boost::lexical_cast<short> (*tok_iter);
  const stdair::Date_T iDepartureDate(lDepDateYear, lDepDateMonth, lDepDateDay);

  // Request date (e.g., "2007-03-21")
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lReqDateYear = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lReqDateMonth = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lReqDateDay = boost::lexical_cast<short> (*tok_iter);
  const stdair::Date_T iRequestDate (lReqDateYear, lReqDateMonth, lReqDateDay);

  // Request time (e.g., "08:34:23")
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lReqTimeHours = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lReqTimeMinutes = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lReqTimeSeconds = boost::lexical_cast<short> (*tok_iter);
  const stdair::Duration_T iRequestTime (lReqTimeHours, lReqTimeMinutes,
                                         lReqTimeSeconds);

  // Request date-time (aggregation of the two items above)
  const stdair::DateTime_T iRequestDateTime (iRequestDate, iRequestTime);
  
  // Preferred cabin (e.g., "C")
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::CabinCode_T iPreferredCabin (*tok_iter);
  
  // Party size (e.g., 1)
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::NbOfSeats_T iPartySize = 1;
  
  // Channel (e.g., "DF")
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::ChannelLabel_T iChannel (*tok_iter);
  
  // Trip type (e.g., "RO")
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::TripType_T iTripType (*tok_iter);
  
  // Stay duration (e.g., 5)
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::DayDuration_T iStayDuration = 5;
  
  // Frequent flyer (e.g., "NONE")
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::FrequentFlyer_T iFrequentFlyerType ("NONE");
  
  // Preferred departure time (e.g., "10:00:00")
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lPrefTimeHours = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lPrefTimeMinutes = boost::lexical_cast<short> (*tok_iter);
  ++tok_iter; assert (tok_iter != tokens.end());
  const short lPrefTimeSeconds = boost::lexical_cast<short> (*tok_iter);
  const stdair::Duration_T iPreferredDepartureTime (lPrefTimeHours,
                                                    lPrefTimeMinutes,
                                                    lPrefTimeSeconds);

  // Willingness-to-pay (e.g., 2000.0)
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::WTP_T iWTP = 2000.0;
  
  // Value of time (e.g., 20.0)
  ++tok_iter; assert (tok_iter != tokens.end());
  const stdair::PriceValue_T iValueOfTime = 20.0;

  // Build and return the booking request structure
  return stdair::BookingRequestStruct (iOrigin, iDestination, iPOS,
                                       iDepartureDate, iRequestDateTime,
                                       iPreferredCabin, iPartySize, iChannel,
                                       iTripType, iStayDuration,
                                       iFrequentFlyerType,
                                       iPreferredDepartureTime, iWTP,
                                       iValueOfTime);
}

// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
  // try {
    
    // Number of random draws to be generated (best if greater than 100)
    int lRandomDraws = 0;
    
    // Input file name
    stdair::Filename_T lInputFilename;

    // Output log File
    std::string lLogFilename;

    // Booking request string
    std::string lBookingRequestString;
    
    // Call the command-line option parser
    const int lOptionParserStatus = 
      readConfiguration (argc, argv, lRandomDraws, lInputFilename,
                         lLogFilename, lBookingRequestString);

    if (lOptionParserStatus == K_AIRSCHED_EARLY_RETURN_STATUS) {
      return 0;
    }

    // Check wether or not a (CSV) input file should be read
    bool hasInputFile = false;
    if (lInputFilename.empty() == false) {
      hasInputFile = true;
    }

    // Set the log parameters
    std::ofstream logOutputFile;
    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // The analysis starts at January 1, 2000
    const stdair::Date_T lStartAnalysisDate (2000, 1, 1);

    // Initialise the AirSched service object
    const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
    AIRSCHED::AIRSCHED_Service airschedService (lLogParams, lStartAnalysisDate,
                                                lInputFilename);


    // Create a booking request
    // const stdair::BookingRequestStruct& lBookingRequest =
    //   parseBookingRequest (lBookingRequestString);

    // DEBUG
    // std::cout << "Booking request: " << lBookingRequest << std::endl;

    // Get the corresponding travel solutions
    // stdair::TravelSolutionList_T lTravelSolutionList;
   //  airschedService.getTravelSolutions (lTravelSolutionList, lBookingRequest);

   //  unsigned short idx = 1;
   //  for (stdair::TravelSolutionList_T::const_iterator itTS =
   //         lTravelSolutionList.begin();
   //       itTS != lTravelSolutionList.end(); ++itTS, ++idx) {
   //    const stdair::TravelSolutionStruct& lTS = *itTS;

   //    const stdair::OutboundPath& lOutboundPath = lTS.getOutboundPath();

   //    std::ostringstream oStr;
   //    const stdair::SegmentDateList_T& lSegmentDateList =
   //      lOutboundPath.getSegmentDateList();
   //    unsigned short idxSeg = 0;
   //    for (stdair::SegmentDateList_T::iterator itSegment =
   //           lSegmentDateList.begin();
   //         itSegment != lSegmentDateList.end(); ++itSegment, ++idxSeg) {
   //      if (idxSeg != 0) {
   //        oStr << " -> ";
   //      }
   //      const stdair::SegmentDate& lSegmentDate = *itSegment;
   //      oStr << "[" << idxSeg << "] " << lSegmentDate.describeKey();
   //    }

   //    // DEBUG
   //    std::cout << "Travel solution #" << idx << ": "
   //              << lTS.describeShortKey() << ", i.e.: " << oStr.str()
   //              << std::endl;
   // }
    
    // Start a mini-simulation
    // airschedService.simulate();
    
  // } catch (const std::exception& stde) {
  //   std::cerr << "Standard exception: " << stde.what() << std::endl;
  //   return -1;
    
  // } catch (...) {
  //   return -1;
  // }
  
  return 0;	
}
