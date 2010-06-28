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
  };

  class NonInitialisedServiceException : public RootException {
  };

  class MemoryAllocationException : public RootException {
  };

  class ObjectNotFoundException : public RootException {
  };

  class InventoryNotFoundException : public RootException {
  };

  class FlightDateNotFoundException : public RootException {
  };

  class SegmentDateNotFoundException : public RootException {
  };

  class SegmentCabinNotFoundException : public RootException {
  };

  class LegDateNotFoundException : public RootException {
  };

  class LegCabinNotFoundException : public RootException {
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
