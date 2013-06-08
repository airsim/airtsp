#ifndef __AIRTSP_FAC_FACAIRTSPSERVICECONTEXT_HPP
#define __AIRTSP_FAC_FACAIRTSPSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/service/FacServiceAbstract.hpp>

namespace AIRTSP {

  /// Forward declarations.
  class AIRTSP_ServiceContext;

  /**
   * @brief Factory for the service context.
   */
  class FacAIRTSPServiceContext : public stdair::FacServiceAbstract {
  public:

    /**
     * Provide the unique instance.
     *
     * The singleton is instantiated when first used.
     * @return FacServiceContext&
     */
    static FacAIRTSPServiceContext& instance();

    /**
     * Destructor.
     *
     * The Destruction put the _instance to NULL in order to be clean
     * for the next FacAIRTSPServiceContext::instance().
     */
    ~FacAIRTSPServiceContext();

    /**
     * Create a new ServiceContext object.
     *
     * This new object is added to the list of instantiated objects.
     *
     * @return ServiceContext& The newly created object.
     */
    AIRTSP_ServiceContext& create();


  protected:
    /**
     * Default Constructor.
     *
     * This constructor is protected in order to ensure the singleton pattern.
     */
    FacAIRTSPServiceContext() {}

  private:
    /**
     * The unique instance.
     */
    static FacAIRTSPServiceContext* _instance;

  };
}
#endif // __AIRTSP_FAC_FACAIRTSPSERVICECONTEXT_HPP
