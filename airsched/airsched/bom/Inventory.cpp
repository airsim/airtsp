// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/Inventory.hpp>
// AIRSCHED 
#include <airsched/bom/Inventory.hpp>
#include <airsched/bom/FlightDate.hpp>
#include <airsched/bom/SegmentDate.hpp>
#include <airsched/bom/LegDate.hpp>
#include <airsched/service/Logger.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (BomStructure_T& ioInventoryStructure)
    : _inventoryStructure (ioInventoryStructure) {
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

    _inventoryStructure.describeFull (oStr);
      
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

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_iterator Inventory::flightDateListBegin () const {
    return _inventoryStructure.flightDateListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_iterator Inventory::flightDateListEnd () const {
    return _inventoryStructure.flightDateListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_reverse_iterator Inventory::flightDateListRBegin () const {
    return _inventoryStructure.flightDateListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_reverse_iterator Inventory::flightDateListREnd () const {
    return _inventoryStructure.flightDateListREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_iterator Inventory::flightDateMapBegin () const {
    return _inventoryStructure.flightDateMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_iterator Inventory::flightDateMapEnd () const {
    return _inventoryStructure.flightDateMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_reverse_iterator Inventory::flightDateMapRBegin () const {
    return _inventoryStructure.flightDateMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_reverse_iterator Inventory::flightDateMapREnd () const {
    return _inventoryStructure.flightDateMapREnd ();
  }

}

