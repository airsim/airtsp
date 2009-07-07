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
#include <stdair/bom/BomChildrenHolder.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const BomKey_T& iKey)
    : _parent (NULL), _key (iKey) {
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
    
    // Get the position of the SegmentDate type in the list of children
    // types of FlightDate.
    const unsigned int segmentDatePos =
      boost::mpl::find<ChildrenBomTypeList_T, SegmentDate>::type::pos::value;

    // Retrive the bom children holder corresponding to the segment-date type.
    BomChildrenHolder<SegmentDate>* lSegmentDateHolder_ptr =
      dynamic_cast<BomChildrenHolder<SegmentDate>*>(_childrenList.
                                                   at (segmentDatePos));
    assert (lSegmentDateHolder_ptr != NULL);

    lSegmentDateHolder_ptr->describeFull (ioOut);
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::displayLegDateList (std::ostringstream& ioOut) const {

    // Display the leg-date list.
    ioOut << "LegDates: " << std::endl;
    
    // Get the position of the LegDate type in the list of children
    // types of FlightDate.
    const unsigned int legDatePos =
      boost::mpl::find<ChildrenBomTypeList_T, LegDate>::type::pos::value;

    // Retrive the bom children holder corresponding to the leg-date type.
    BomChildrenHolder<LegDate>* lLegDateHolder_ptr =
      dynamic_cast<BomChildrenHolder<LegDate>*>(_childrenList.
                                                   at (legDatePos));
    assert (lLegDateHolder_ptr != NULL);

    lLegDateHolder_ptr->describeFull (ioOut);
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

}

