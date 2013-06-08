#include <airtsp/basic/BasConst_General.hpp>
#include <airtsp/basic/BasConst_AIRTSP_Service.hpp>

namespace AIRTSP {

  /** Default value for the number of draws within the Monte-Carlo
      Integration algorithm. */
  const int DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION = 100000;

  /** Default value for the minimum time between the request and the
      departure time. */
  const stdair::Duration_T MINIMUM_TIME_BETWEEN_REQUEST_AND_DEPARTURE (4, 0, 0);

}
