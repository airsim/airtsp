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

// Forward declarations.
namespace stdair {
  template <typename BOM_CONTENT> class BomStructureRoot;
  template <typename BOM_CONTENT> class BomStructureRootKey;
  template <typename BOM_CHILD> class BomContentRoot;
  template <typename BOM_CONTENT> class Inventory;
  template <typename BOM_CONTENT> class InventoryKey;
  template <typename BOM_CONTENT> class FlightDate;
  template <typename BOM_CONTENT> class FlightDateKey;
  template <typename BOM_CONTENT> class SegmentDate;
  template <typename BOM_CONTENT> class SegmentDateKey;
  template <typename BOM_CONTENT> class LegDate;
  template <typename BOM_CONTENT> class LegDateKey;
}

namespace AIRSCHED {

   // ///////// Exceptions ///////////
  class RootException : public std::exception {
  };

  class FileNotFoundException : public RootException {
  };
  
  class NonInitialisedServiceException : public RootException {
  };

  class MemoryAllocationException : public RootException {
  };

  class ObjectNotFoundException : public RootException {
  };

  class DocumentNotFoundException : public RootException {
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

  // Forward declarations.
  class Inventory;
  class FlightDate;
  class SegmentDate;
  class LegDate;

  // //////// Type definitions /////////
  /** Define the Duration (e.g., elapsed in-flight time). */
  typedef boost::posix_time::time_duration Duration_T;

  /** Define the Date (e.g., flight-date departure date). */
  typedef boost::gregorian::date Date_T;

  /** Define the BomContentRoot. */
  typedef stdair::BomContentRoot<Inventory> BomContentRoot_T;

  /** Define the BomStructureRoot. */
  typedef stdair::BomStructureRoot<BomContentRoot_T> BomStructureRoot_T;

  /** Define the BomStructureRootKey. */
  typedef stdair::BomStructureRootKey<BomContentRoot_T> BomStructureRootKey_T;

  /** Define the flight-date structure. */
  typedef stdair::FlightDate<FlightDate> FlightDateStructure_T;

  /** Define the flight-date key. */
  typedef stdair::FlightDateKey<FlightDate> FlightDateKey_T;

  /** Define the segment-date structure. */
  typedef stdair::SegmentDate<SegmentDate> SegmentDateStructure_T;

  /** Define the segment-date key. */
  typedef stdair::SegmentDateKey<SegmentDate> SegmentDateKey_T;

  /** Define the leg-date structure. */
  typedef stdair::LegDate<LegDate> LegDateStructure_T;

  /** Define the leg-date key. */
  typedef stdair::LegDateKey<LegDate> LegDateKey_T;

}
#endif // __AIRSCHED_AIRSCHED_TYPES_HPP
