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
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Service.hpp>
#include <airsched/config/airsched-paths.hpp>


// //////// Constants //////
/** Default name and location for the log file. */
const std::string K_AIRSCHED_DEFAULT_LOG_FILENAME ("airsched.log");

/** Default name and location for the (CSV) input file. */
const std::string K_AIRSCHED_DEFAULT_INPUT_FILENAME ("../../test/samples/schedule01.csv");

/** Default number of random draws to be generated (best if over 100). */
const int K_AIRSCHED_DEFAULT_RANDOM_DRAWS = 100000;

/** Default airline code. */
const std::string K_AIRSCHED_DEFAULT_AIRLINE_CODE ("BA");


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
                       stdair::AirlineCode_T& ioAirlineCode) {
  
    
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
    ("draws,d",
     boost::program_options::value<int>(&ioRandomDraws)->default_value(K_AIRSCHED_DEFAULT_RANDOM_DRAWS), 
     "Number of to-be-generated random draws")
    ("airline,a",
     boost::program_options::value< std::string >(&ioAirlineCode)->default_value(K_AIRSCHED_DEFAULT_AIRLINE_CODE),
     "Airline code")
    ("input,i",
     boost::program_options::value< std::string >(&ioInputFilename)->default_value(K_AIRSCHED_DEFAULT_INPUT_FILENAME),
     "(CVS) input file for the demand distributions")
    ("log,l",
     boost::program_options::value< std::string >(&ioLogFilename)->default_value(K_AIRSCHED_DEFAULT_LOG_FILENAME),
     "Filename for the logs")
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

  std::cout << "The number of random draws is: " << ioRandomDraws << std::endl;
  
  return 0;
}


// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
   try {
    
    // Number of random draws to be generated (best if greater than 100)
    int lRandomDraws = 0;
    
    // Input file name
    stdair::Filename_T lInputFilename;

    // Output log File
    std::string lLogFilename;

    // Airline code
    stdair::AirlineCode_T lAirlineCode ("BA");

    // Call the command-line option parser
    const int lOptionParserStatus = 
      readConfiguration (argc, argv, lRandomDraws, lInputFilename,
                         lLogFilename, lAirlineCode);

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
    
    // Initialise the set of required airline features
    stdair::AirlineFeatureSet& lAirlineFeatureSet =
      stdair::FacBomContent::instance().create<stdair::AirlineFeatureSet>();

    // Initialise an AirlineFeature object
    stdair::AirlineFeatureKey_T lAirlineFeatureKey (lAirlineCode);
    stdair::AirlineFeature& lAirlineFeature = stdair::FacBomContent::
      instance().create<stdair::AirlineFeature> (lAirlineFeatureKey);
    stdair::FacBomContent::
      linkWithParent<stdair::AirlineFeature> (lAirlineFeature,
                                              lAirlineFeatureSet);
    
    // The analysis starts at January 1, 2000
    const stdair::Date_T lStartAnalysisDate (2000, 1, 1);

    // Initialise the AirSched service object
    const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
    AIRSCHED::AIRSCHED_Service airschedService (lLogParams,
                                                lAirlineFeatureSet,
                                                lStartAnalysisDate,
                                                lInputFilename);

    // Start a mini-simulation
    airschedService.simulate();
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
