// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// MPL
#include <boost/mpl/at.hpp>
#include <boost/mpl/find.hpp>
// STDAIR 
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const BomKey_T& iKey)
    : _parent (NULL), _key (iKey), _firstChildrenList (NULL),
      _secondChildrenList (NULL) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::ParentBomStructure_T& FlightDate::getInventory() const {
    assert (_parent != NULL);
    return *_parent;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FlightDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::describeFull (std::ostringstream& ioOut) const {
    ioOut << describeShortKey () << std::endl;
    
    // Display the segment-date list.
    displaySegmentDateList (ioOut);
    
    // Display the leg-date list.
    displayLegDateList (ioOut);
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::displaySegmentDateList (std::ostringstream& ioOut) const {

    // Display the segment-date list.
    ioOut << "SegmentDates: " << std::endl;

    assert (_firstChildrenList != NULL);
    _firstChildrenList->describeFull (ioOut);
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::displayLegDateList (std::ostringstream& ioOut) const {

    // Display the leg-date list.
    ioOut << "LegDates: " << std::endl;
    
    assert (_secondChildrenList != NULL);
    _secondChildrenList->describeFull (ioOut);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FlightDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string FlightDate::toString() const {
    return describeKey();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeShortKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::
  setChildrenList (FirstChildrenBomHolder_T& ioChildrenList) {
    _firstChildrenList = &ioChildrenList;
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::
  setChildrenList (SecondChildrenBomHolder_T& ioChildrenList) {
    _secondChildrenList = &ioChildrenList;
  }

}

