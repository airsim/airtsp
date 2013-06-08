#ifndef __AIRTSP_SVC_AIRTSP_SERVICE_CONTEXT_HPP
#define __AIRTSP_SVC_AIRTSP_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/stdair_service_types.hpp>
#include <stdair/service/ServiceAbstract.hpp>
// AirTSP
#include <airtsp/AIRTSP_Types.hpp>

namespace AIRTSP {

  /**
   * @brief Class holding the context of the Airtsp services.
   */
  class AIRTSP_ServiceContext : public stdair::ServiceAbstract {
    /**
     * The AIRTSP_Service class should be the sole class to get access to
     * ServiceContext content: general users do not want to bother
     * with a context interface.
     */
    friend class AIRTSP_Service;
    friend class FacAIRTSPServiceContext;

  private:
    // ///////////////// Getters ///////////////////
    /**
     * Get the pointer on the STDAIR service handler.
     */
    stdair::STDAIR_ServicePtr_T getSTDAIR_ServicePtr() const {
      return _stdairService;
    }

    /**
     * Get the STDAIR service handler.
     */
    stdair::STDAIR_Service& getSTDAIR_Service() const;

    /**
     * State whether or not RMOL owns the STDAIR service resources.
     */
    const bool getOwnStdairServiceFlag() const {
      return _ownStdairService;
    }


  private:
    // ///////////////// Setters ///////////////////
    /**
     * Set the pointer on the STDAIR service handler.
     */
    void setSTDAIR_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                            const bool iOwnStdairService) {
      _stdairService = ioSTDAIR_ServicePtr;
      _ownStdairService = iOwnStdairService;
    }


  private:
    // //////////////////// Display Methods /////////////////////
    /**
     * Display the short AIRTSP_ServiceContext content.
     */
    const std::string shortDisplay() const;
    
    /**
     * Display the full AIRTSP_ServiceContext content.
     */
    const std::string display() const;
    
    /**
     * Display of the structure.
     */
    const std::string describe() const;


  private:
    /// //////////////// Constructors and destructors /////////////
    /**
     * Default constructor.
     */
    AIRTSP_ServiceContext();

    /**
     * Copy constructor.
     */
    AIRTSP_ServiceContext (const AIRTSP_ServiceContext&);

    /**
     * Initialisation.
     */
    void init();

    /**
     * Destructor.
     */
    ~AIRTSP_ServiceContext();

    /**
     * Clear the context (specific BOM tree objects).
     */
    void reset();


  private:
    // /////////////// Children ///////////////
    /**
     * Standard Airline (StdAir) Service Handler.
     */
    stdair::STDAIR_ServicePtr_T _stdairService;

    /**
     * State whether or not RMOL owns the STDAIR service resources.
     */
    bool _ownStdairService;
  };

}
#endif // __AIRTSP_SVC_AIRTSP_SERVICE_CONTEXT_HPP
