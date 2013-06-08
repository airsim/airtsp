// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/service/FacSupervisor.hpp>
// AirTSP
#include <airtsp/factory/FacAIRTSPServiceContext.hpp>
#include <airtsp/service/AIRTSP_ServiceContext.hpp>

namespace AIRTSP {

  FacAIRTSPServiceContext* FacAIRTSPServiceContext::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacAIRTSPServiceContext::~FacAIRTSPServiceContext() {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacAIRTSPServiceContext& FacAIRTSPServiceContext::instance () {

    if (_instance == NULL) {
      _instance = new FacAIRTSPServiceContext();
      assert (_instance != NULL);
      
      stdair::FacSupervisor::instance().registerServiceFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  AIRTSP_ServiceContext& FacAIRTSPServiceContext::create () {
    AIRTSP_ServiceContext* aServiceContext_ptr = NULL;

    aServiceContext_ptr = new AIRTSP_ServiceContext();
    assert (aServiceContext_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aServiceContext_ptr);

    return *aServiceContext_ptr;
  }

}
