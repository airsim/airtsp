// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// MPL
#include <boost/mpl/at.hpp>
#include <boost/mpl/find.hpp>
// STDAIR 
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const BomKey_T& iKey)
    : _parent (NULL), _key (iKey), _firstChildrenList (NULL) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory () {
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::ParentBomStructure_T& Inventory::getBomStructureRoot() const {
    assert (_parent != NULL);
    return *_parent;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Inventory::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::describeFull (std::ostringstream& ioOut) const {
    ioOut << describeShortKey () << std::endl;
    
    // Display the flight-date list.
    displayFlightDateList (ioOut);
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::displayFlightDateList (std::ostringstream& ioOut) const {
    
    // Display the flight-date list.
    ioOut << "FlightDates: " << std::endl;

    assert (_firstChildrenList != NULL);
    _firstChildrenList->describeFull (ioOut);
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Inventory::toString() const {
    return describeKey();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeShortKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::
  setChildrenList (FirstChildrenBomHolder_T& ioChildrenList) {
    _firstChildrenList = &ioChildrenList;
  }

}

