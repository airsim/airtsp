#ifndef __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP
#define __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Types.hpp>

// Forward declarations.
namespace stdair {
  class AirlineFeatureSet;
  class BomRoot;
}

namespace AIRSCHED {

  /** Forward declaration. */
  class AIRSCHED_ServiceContext;

  
  /** Interface for the AIRSCHED Services. */
  class AIRSCHED_Service {
  public:
    // ////////////////// Constructors and Destructors //////////////////    
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        @param std::ostream& Output log stream.
        @param const stdair::AirlineFeatureSet& Set of airline features.
        @param const stdair::Date_T& Date for the beginning of analysis.
        @param const stdair::Filename_T& Filename of the input schedule file. */
    AIRSCHED_Service (std::ostream& ioLogStream,
                      const stdair::AirlineFeatureSet&,
                      const stdair::Date_T& iStartAnalysisDate,
                      const stdair::Filename_T& iScheduleInputFilename);
    /** Destructor. */
    ~AIRSCHED_Service();

    
    // ////////////////// Business support methods //////////////////    
    /** Add a travel solution to the service context.
        <br>Currently, that method does nothing. */
    void addTravelSolution (const stdair::AirportCode_T& iDepartureAirport,
                            const stdair::AirportCode_T& iArrivalAirport,
                            const stdair::Date_T& iDepartureDate,
                            const stdair::Duration_T& iDepartureTime,
                            const stdair::Duration_T& iArrivalTime,
                            const stdair::Duration_T& iDuration,
                            const bool iRefundability,
                            const stdair::AirlineCode_T& iAirlineCode,
                            const stdair::CabinCode_T& iCabinCode,
                            const stdair::FlightNumber_T& iFlightNumber,
                            const stdair::Fare_T& iFare,
                            int iStopsNumber, bool iSNS, bool iChangeability);

    /** Calculate and return the travel solutions corresponding to a given
        product demand. */
    void getTravelSolutions (const stdair::BookingRequestStruct&);

    /** Perform a small simulation, which uses the Customer Choice Model.
        <br>Currently, that method does nothing.*/
    void simulate();

    
  private:
    // ////////////////// Constructors and Destructors //////////////////    
    /** Default Constructors. */
    AIRSCHED_Service ();
    AIRSCHED_Service (const AIRSCHED_Service&);

    /** Initialise.
        <br>The CSV file, describing the airline schedules for the
        simulator, is parsed and the inventories are generated accordingly.
        <br>A reference on the root of the BOM tree, namely the BomRoot object,
        is stored within the service context for later use.
        @param std::ostream& Output log stream.
        @param const stdair::AirlineFeatureSet& Set of airline features.
        @param const stdair::Date_T& Date for the beginning of analysis.
        @param const stdair::Filename_T& Filename of the input schedule file. */
    void init (std::ostream& ioLogStream,
               const stdair::AirlineFeatureSet& iAirlineFeatureSet,
               const stdair::Date_T& iStartAnalysisDate,
               const stdair::Filename_T& iScheduleInputFilename);
    
    /** Initialise the log. */
    void logInit (const stdair::LOG::EN_LogLevel iLogLevel,
                  std::ostream& ioLogStream);

    /** Finaliser. */
    void finalise ();

    
  private:
    // ////////////////// Service Context //////////////////
    /** Service Context. */
    AIRSCHED_ServiceContext* _airschedServiceContext;
  };
}
#endif // __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP
