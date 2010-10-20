#ifndef __AIRSCHED_AIRSCHED_TYPES_HPP
#define __AIRSCHED_AIRSCHED_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
#include <list>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// Boost
#include <boost/date_time/posix_time/posix_time.hpp>

namespace AIRSCHED {

   // ///////// Exceptions ///////////
  class RootException : public std::exception {
  public:
    /** Constructors. */
    RootException (const std::string& iWhat) : _what (iWhat) {}
    RootException () : _what ("No more details") {}
    /** Destructor. */
    virtual ~RootException() throw() {}
    /** Give the details of the exception. */
    const char* what() const throw() { return _what.c_str(); } 
  protected:
    /** Details for the exception. */
    std::string _what;
  };

  class NonInitialisedServiceException : public RootException {
  };

  class MemoryAllocationException : public RootException {
  };

  class BOMObjectNotFoundException : public RootException {
  };

  class InventoryNotFoundException : public BOMObjectNotFoundException {
  };

  class FlightDateNotFoundException : public BOMObjectNotFoundException {
  };

  class SegmentDateNotFoundException : public BOMObjectNotFoundException {
  };

  class SegmentCabinNotFoundException : public BOMObjectNotFoundException {
  };

  class LegDateNotFoundException : public BOMObjectNotFoundException {
  };

  class LegCabinNotFoundException : public BOMObjectNotFoundException {
  };

  class FileException : public RootException {
  public:
    /** Constructor. */
    FileException (const std::string& iWhat) : RootException (iWhat) {}
  };

  class OnDInputFileNotFoundException : public FileException {
  public:
    /** Constructor. */
    OnDInputFileNotFoundException (const std::string& iWhat)
      : FileException (iWhat) {}
  };

  class ScheduleInputFileNotFoundException : public FileException {
  public:
    /** Constructor. */
    ScheduleInputFileNotFoundException (const std::string& iWhat)
      : FileException (iWhat) {}
  };


  // /////////////// Log /////////////
  /** Level of logs. */
  namespace LOG {
    typedef enum {
      CRITICAL = 0,
      ERROR,
      NOTIFICATION,
      WARNING,
      DEBUG,
      VERBOSE,
      LAST_VALUE
    } EN_LogLevel;
  }

  // //////// Type definitions /////////
  /** Define the Duration (e.g., elapsed in-flight time). */
  typedef boost::posix_time::time_duration Duration_T;

  /** Define the Date (e.g., flight-date departure date). */
  typedef boost::gregorian::date Date_T;

  /** Define the Date Offset (e.g., -1 ). */
  typedef boost::gregorian::date_duration DateOffset_T;

  /** Define the Period (e.g., period during which flights depart). */
  typedef boost::gregorian::date_period DatePeriod_T;

}
#endif // __AIRSCHED_AIRSCHED_TYPES_HPP
