// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/STDAIR_Service.hpp>
// AirTSP
#include <airtsp/basic/BasConst_AIRTSP_Service.hpp>
#include <airtsp/service/AIRTSP_ServiceContext.hpp>

namespace AIRTSP {
  
  // //////////////////////////////////////////////////////////////////////
  AIRTSP_ServiceContext::AIRTSP_ServiceContext()
    : _ownStdairService (false) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  AIRTSP_ServiceContext::
  AIRTSP_ServiceContext (const AIRTSP_ServiceContext&) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  AIRTSP_ServiceContext::~AIRTSP_ServiceContext() {
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::STDAIR_Service& AIRTSP_ServiceContext::getSTDAIR_Service() const {
    assert (_stdairService != NULL);
    return *_stdairService;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AIRTSP_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "AIRTSP_ServiceContext -- Owns StdAir service: "
         << _ownStdairService;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AIRTSP_ServiceContext::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AIRTSP_ServiceContext::describe() const {
    return shortDisplay();
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRTSP_ServiceContext::reset() {

    // The shared_ptr<>::reset() method drops the refcount by one.
    // If the count result is dropping to zero, the resource pointed to
    // by the shared_ptr<> will be freed.
    
    // Reset the stdair shared pointer
    _stdairService.reset();
  }

}
