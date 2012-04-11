#ifndef __AIRSCHED_BAS_BASCONST_GENERAL_HPP
#define __AIRSCHED_BAS_BASCONST_GENERAL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_date_time_types.hpp>

namespace AIRSCHED {

  /** Default value for the number of draws within the Monte-Carlo
      Integration algorithm. */
  extern const int DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION;

  /** Default value for the minimum time between the request and the
      departure time. */
  extern const stdair::Duration_T MINIMUM_TIME_BETWEEN_REQUEST_AND_DEPARTURE;

}
#endif // __AIRSCHED_BAS_BASCONST_GENERAL_HPP
