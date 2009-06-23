// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
// AIRSCHED 
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const BomStructure_T& iInventoryStructure)
    : _inventoryStructure (iInventoryStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory () {
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Inventory::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Retrieve the list of flight-date holders
    const stdair::BomStructureList_T& lBomStructureList =
      _inventoryStructure.getChildrenList();

    // Browse the tree structure, i.e., the flight-dates
    oStr << "FlightDates:" << std::endl;
    unsigned short idx = 0;
    for (stdair::BomStructureList_T::const_iterator itBomStructure =
           lBomStructureList.begin();
         itBomStructure != lBomStructureList.end(); ++itBomStructure, ++idx) {
      const stdair::BomStructure* lBomStructure_ptr = itBomStructure->second;

      const stdair::FlightDate* lFlightStructure_ptr =
        dynamic_cast<const stdair::FlightDate*> (lBomStructure_ptr);
      assert (lFlightStructure_ptr != NULL);

      // Get the content out of the structure/holder
      const FlightDate& lFlightDate =
        lFlightStructure_ptr->getContent<FlightDate>();

      oStr << "[" << idx << "]: " << lFlightDate.toString();
    }
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeKey() const {
    return _inventoryStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeShortKey() const {
    return _inventoryStructure.describeShortKey();
  }

}

