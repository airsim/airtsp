// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateList.hpp>

namespace STDAIR {

  // ////////////////////////////////////////////////////////////////////
  BomContentRoot::BomContentRoot (const BomStructureRoot& iBomStructure)
    : _bomStructure (iBomStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomContentRoot::~BomContentRoot () {
  }

  // //////////////////////////////////////////////////////////////////////
  void BomContentRoot::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void BomContentRoot::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string BomContentRoot::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Retrieve the list of flight-date holders
    const FlightDateList_T& lFlightList = _bomStructure.getFlightList();

    // Browse the tree structure, i.e., the flight-dates
    unsigned short idx = 0;
    for (FlightDateList_T::const_iterator itFlight = lFlightList.begin();
         itFlight != lFlightList.end(); ++itFlight, ++idx) {
      const FlightDate* lFlightStructure_ptr = itFlight->second;
      assert (lFlightStructure_ptr != NULL);

      // Get the content out of the structure/holder
      const FlightDate& lFlightDate =
        lFlightStructure_ptr->getContent<FlightDate>();

      oStr << "[" << idx << "]: " << lFlightDate.toString() << std::endl;
    }
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string BomContentRoot::describeKey() const {
    return _bomStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string BomContentRoot::describeShortKey() const {
    return _bomStructure.describeShortKey();
  }

}

