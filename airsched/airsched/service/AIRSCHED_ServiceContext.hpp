#ifndef __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP
#define __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <cassert>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomRoot.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Types.hpp>
#include <airsched/service/ServiceAbstract.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
  class AirlineFeatureSet;
}

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
    AIRSCHED_ServiceContext ();
    AIRSCHED_ServiceContext (const AIRSCHED_ServiceContext&);
    void init ();
    /** Destructor. */
    ~AIRSCHED_ServiceContext();

    /** Initialise the StudyStatManager. */
    void initStudyStatManager ();

    
    // ///////////////// Getters ///////////////////
    /** Get a reference on the BomRoot object.
        <br>If the service context has not been initialised, that
        method throws an exception (failing assertion). */
    stdair::BomRoot& getBomRoot () const;

    /** Get a reference on the AirlineFeatureSet object.
        <br>If the service context has not been initialised, that
        method throws an exception (failing assertion). */
    const stdair::AirlineFeatureSet& getAirlineFeatureSet () const;

    /** Get the requested date for the beginning of analysis. */
    const Date_T& getStartAnalysisDate() const {
      return _startAnalysisDate;
    }

    
    // ///////////////// Setters ///////////////////
    /** Set the BomRoot object. */
    void setBomRoot (stdair::BomRoot& ioBomRoot) {
      _bomRoot = &ioBomRoot;
    }

    /** Set the AirlineFeatureSet object. */
    void setAirlineFeatureSet (const stdair::AirlineFeatureSet& iAirlineFeatureSet) {
      _airlineFeatureSet = &iAirlineFeatureSet;
    }

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
    // /////////////// Attributes ///////////////
    /** The BomRoot which contents all the inventory objects. */
    stdair::BomRoot* _bomRoot;

    /** Set of airline required features. */
    const stdair::AirlineFeatureSet* _airlineFeatureSet;

    /** Requested date for the beginning of analysis. */
    stdair::Date_T _startAnalysisDate;
  };

}
#endif // __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP
