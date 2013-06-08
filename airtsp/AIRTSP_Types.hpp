#ifndef __AIRTSP_AIRTSP_TYPES_HPP
#define __AIRTSP_AIRTSP_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/stdair_exceptions.hpp>

namespace AIRTSP {

  // Forward declarations
  class AIRTSP_Service;


  // ///////// Exceptions ///////////
  /**
   * Specific exception when some BOM objects can not be found within
   * the schedule.
   */
  class SegmentDateNotFoundException : public stdair::ParserException {
  public:
    /**
     * Constructor.
     */
    SegmentDateNotFoundException (const std::string& iWhat)
      : stdair::ParserException (iWhat) {}
  };

  /**
   * The O&D input file cannot be retrieved.
   */
  class OnDInputFileNotFoundException : public stdair::FileNotFoundException {
  public:
    /**
     * Constructor.
     */
    OnDInputFileNotFoundException (const std::string& iWhat)
      : stdair::FileNotFoundException (iWhat) {}
  };

  /**
   * The schedule input file cannot be retrieved.
   */
  class ScheduleInputFileNotFoundException
    : public stdair::FileNotFoundException {
  public:
    /**
     * Constructor.
     */
    ScheduleInputFileNotFoundException (const std::string& iWhat)
      : stdair::FileNotFoundException (iWhat) {}
  };


  // //////// Type definitions specific to Airtsp /////////
  /**
   * (Smart) Pointer on the Airtsp service handler.
   */
  typedef boost::shared_ptr<AIRTSP_Service> AIRTSP_ServicePtr_T;
  
}
#endif // __AIRTSP_AIRTSP_TYPES_HPP
