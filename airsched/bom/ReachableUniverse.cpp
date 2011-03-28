// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
// AirSched
#include <airsched/bom/ReachableUniverse.hpp>
#include <airsched/bom/SegmentPathPeriod.hpp>

namespace AIRSCHED {

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverse::ReachableUniverse()
    : _key (stdair::DEFAULT_ORIGIN), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverse::ReachableUniverse (const ReachableUniverse&)
    : _key (stdair::DEFAULT_ORIGIN), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverse::ReachableUniverse (const Key_T& iKey)
    : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverse::~ReachableUniverse() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string ReachableUniverse::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void ReachableUniverse::
  addSegmentPathPeriod (const SegmentPathPeriod& iSegmentPathPeriod) {
    const stdair::NbOfSegments_T& lNbOfSegments =
      iSegmentPathPeriod.getNbOfSegments ();
    assert (lNbOfSegments > 0
            && lNbOfSegments <= stdair::MAXIMAL_NUMBER_OF_SEGMENTS_IN_OND);

    // If needed, initialise the list of lists with empty fixed-length
    // segment path period lists.
    while (_segmentPathPeriodListList.size() < lNbOfSegments) {
      SegmentPathPeriodLightList_T lSegmentPathPeriodLightList;
      _segmentPathPeriodListList.push_back (lSegmentPathPeriodLightList);
    }

    // Retrieve the i-fixed-length segment path period list (i = number of
    // segments).
    SegmentPathPeriodLightList_T& lSegmentPathPeriodLightList =
      _segmentPathPeriodListList.at (lNbOfSegments-1);

    // Add the SegmentPathPeriod to that fixed-length-path list.
    lSegmentPathPeriodLightList.push_back (&iSegmentPathPeriod);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void ReachableUniverse::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void ReachableUniverse::serialize (Archive& ioArchive,
                                     const unsigned int iFileVersion) {
    //ioArchive & _key;
  }

}

