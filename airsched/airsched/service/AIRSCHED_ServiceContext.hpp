#ifndef __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP
#define __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/shared_ptr.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Types.hpp>
#include <airsched/service/ServiceAbstract.hpp>

namespace AIRSCHED {

  /** Inner class holding the context for the AIRSCHED Service object. */
  class AIRSCHED_ServiceContext : public ServiceAbstract {
    /** The AIRSCHED_Service class should be the sole class to get access to
        ServiceContext content: general users do not want to bother
        with a context interface. */
    friend class AIRSCHED_Service;
    friend class FacAIRSCHEDServiceContext;

  private:
    /// //////////////// Constructors and destructors /////////////
    /** Default constructor. */
    AIRSCHED_ServiceContext ();
    /** Default copy constructor. */
    AIRSCHED_ServiceContext (const AIRSCHED_ServiceContext&);
    /** Initialisation. */
    void init ();
    /** Destructor. */
    ~AIRSCHED_ServiceContext();

    /** Initialise the StudyStatManager. */
    void initStudyStatManager ();

    
    // ///////////////// Getters ///////////////////
    /** Get the pointer on the STDAIR service handler. */
    stdair::STDAIR_Service& getSTDAIR_Service () const;
    
    /** Get the requested date for the beginning of analysis. */
    const stdair::Date_T& getStartAnalysisDate() const {
      return _startAnalysisDate;
    }

    
    // ///////////////// Setters ///////////////////
    /** Set the pointer on the STDAIR service handler. */
    void setSTDAIR_Service (stdair::STDAIR_ServicePtr_T);
    
    /** Set the requested date for the beginning of analysis. */
    void setStartAnalysisDate (const Date_T& iStartAnalysisDate) {
      _startAnalysisDate = iStartAnalysisDate;
    }

    
    // ///////// Display Methods //////////
    /** Display the short SIMCRS_ServiceContext content. */
    const std::string shortDisplay() const;
    
    /** Display the full SIMCRS_ServiceContext content. */
    const std::string display() const;
    

    // ///////////// Business support methods ////////////
    /** Add a travel solution to the TravelSolutionHolder */
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

    
    /** Read the input data from a file */
    void readFromInputFile (const std::string& iInputFileName);


  private:
    // ///////////// Children ////////////
    /** Standard Airline (StdAir) Service Handler. */
    stdair::STDAIR_ServicePtr_T _stdairService;

    
  private:
    // ////////////// Attributes ////////////////
    /** Requested date for the beginning of analysis. */
    stdair::Date_T _startAnalysisDate;
  };

}
#endif // __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP
