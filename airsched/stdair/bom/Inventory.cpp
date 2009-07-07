// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// MPL
#include <boost/mpl/at.hpp>
#include <boost/mpl/find.hpp>
// STDAIR 
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/BomChildrenHolder.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const BomKey_T& iKey)
    : _parent (NULL), _key (iKey) {
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
    
    // Get the position of the FlightDate type in the list of children
    // types of Inventory.
    const unsigned int flightDatePos =
      boost::mpl::find<ChildrenBomTypeList_T, FlightDate>::type::pos::value;

    // Retrive the bom children holder corresponding to the flight-date type.
    BomChildrenHolder<FlightDate>* lFlightDateHolder_ptr =
      dynamic_cast<BomChildrenHolder<FlightDate>*>(_childrenList.
                                                   at (flightDatePos));
    assert (lFlightDateHolder_ptr != NULL);

    lFlightDateHolder_ptr->describeFull (ioOut);
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

}

