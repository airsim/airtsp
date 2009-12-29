#ifndef __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP
#define __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <ostream>
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
    /** Constructor. */
    AIRSCHED_Service (std::ostream& ioLogStream);
    /** Destructor. */
    ~AIRSCHED_Service();

    /** Add a travel solution to the context */
    void addTravelSolution (const std::string& iDepartureAirport,
                            const std::string& iArrivalAirport,
                            const Date_T& iDepartureDate,
                            const Duration_T& iDepartureTime,
                            const Duration_T& iArrivalTime,
                            const Duration_T& iDuration,
                            const bool iRefundability,
                            const std::string& iAirlineCode,
                            const std::string& iCabinCode,
                            const int iFlightNumber, double iFare,
                            int iStopsNumber,  bool iSNS, bool iChangeability);

    /** Perform a small simulation, which uses the Customer Choice Model.*/
    void simulate();

    /** Parses the CSV file describing the airline schedules for the
        simulator, and generates the inventories accordingly. */
    static stdair::BomRoot&
    generateInventories (const std::string&,
                         const stdair::AirlineFeatureSet&, const Date_T&);

    /** Set the BomRoot of the context. */
    void setBomRoot (stdair::BomRoot&);
    

  private:
    /** Default Constructors. */
    AIRSCHED_Service ();
    AIRSCHED_Service (const AIRSCHED_Service&);

    /** Initialise. */
    void init (std::ostream& ioLogStream);
    
    /** Initialise the log. */
    void logInit (const LOG::EN_LogLevel iLogLevel, std::ostream& ioLogStream);

    /** Finaliser. */
    void finalise ();

  private:
    // ////////// Service Context //////////
    /** Service Context. */
    AIRSCHED_ServiceContext* _airschedServiceContext;
  };
}
#endif // __AIRSCHED_SVC_AIRSCHED_SERVICE_HPP
