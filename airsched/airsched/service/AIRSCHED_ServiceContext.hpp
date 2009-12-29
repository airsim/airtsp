#ifndef __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP
#define __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <cassert>
// STDAIR
#include <stdair/bom/BomRoot.hpp>
// AIRSCHED
#include <airsched/AIRSCHED_Types.hpp>
#include <airsched/service/ServiceAbstract.hpp>

// Forward declarations.
namespace stdair {
  class BomRoot;
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
    /** Constructors. */
    AIRSCHED_ServiceContext ();
    AIRSCHED_ServiceContext (const AIRSCHED_ServiceContext&);
    void init ();

    /** Initialise the StudyStatManager. */
    void initStudyStatManager ();
    /** Destructor. */
    ~AIRSCHED_ServiceContext();

    // ///////////////// GETTERS ///////////////////
    /** Get the BomRoot object. */
    const stdair::BomRoot& getBomRoot () const {
      assert (_bomRoot != NULL);
      return *_bomRoot;
    }
    
    // ///////////////// SETTERS ///////////////////
    /** Set the BomRoot attribute. */
    void setBomRoot (stdair::BomRoot& ioBomRoot) {
      _bomRoot = &ioBomRoot;
    }

    /** Add a travel solution to the TravelSolutionHolder */
    void addTravelSolution (std::string dAirport, std::string aAirport,
                            Date_T depDate,
                            Duration_T depTime, Duration_T arTime,
                            Duration_T dur, bool Ref, std::string airline,
                            std::string cabin, int flightNum, double fare,
                            int lagsNum,  bool SNS, bool change);

    /** Read the input data from a file */
    void readFromInputFile (const std::string& iInputFileName);


  private:
    // /////// Attributes ///////
    /** The BomRoot which contents all the inventory objects. */
    stdair::BomRoot* _bomRoot;
  };

}
#endif // __AIRSCHED_SVC_AIRSCHED_SERVICE_CONTEXT_HPP
