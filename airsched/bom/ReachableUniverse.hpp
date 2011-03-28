#ifndef __AIRSCHED_BOM_REACHABLEUNIVERSE_HPP
#define __AIRSCHED_BOM_REACHABLEUNIVERSE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/bom/BomAbstract.hpp>
// AirSched
#include <airsched/bom/ReachableUniverseKey.hpp>
#include <airsched/bom/ReachableUniverseTypes.hpp>
#include <airsched/bom/SegmentPathPeriodTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

/// Forward declarations
namespace stdair {
  template <typename BOM> class FacBom;
  class FacBomManager;
}

namespace AIRSCHED {

  /**
   * @brief Class representing the root of the schedule-related BOM tree.
   */
  class ReachableUniverse : public stdair::BomAbstract {
    template <typename BOM> friend class stdair::FacBom;
    friend class stdair::FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef ReachableUniverseKey Key_T;

  public:
    // /////////// Getters /////////////
    /**
     * Get the universe key (airport code representing the departure
     * point of the "reachable universe").
     */
    const Key_T& getKey() const {
      return _key;
    }

    /**
     * Get the parent object.
     */
    stdair::BomAbstract* const getParent() const {
      return _parent;
    }
    
    /**
     * Get the (origin) airport (part of the primary key).
     */
    const stdair::AirportCode_T& getOrigin() const {
      return _key.getBoardingPoint();
    }

    /**
     * Get the SegmentPathPeriodListList.
     */
    const SegmentPathPeriodListList_T& getSegmentPathPeriodListList() const {
      return _segmentPathPeriodListList;
    }

    /**
     * Get the map of children holders.
     */
    const stdair::HolderMap_T& getHolderMap() const {
      return _holderMap;
    }


  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString();
    }

    /**
     * Read a Business Object from an input stream.
     *
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn) {
    }

    /**
     * Get the serialised version of the Business Object.
     */
    std::string toString() const;
    
    /**
     * Get a string describing the  key.
     */
    const std::string describeKey() const {
      return _key.toString();
    }
    

  public:
    // //////////// Business Methods //////////////
    /**
     * Add a segment path period to the dedicated list.
     */
    void addSegmentPathPeriod (const SegmentPathPeriod&);    
           

  public:
    // /////////// (Boost) Serialisation support methods /////////
    /**
     * Serialisation.
     */
    template<class Archive>
    void serialize (Archive& ar, const unsigned int iFileVersion);

  private:
    /**
     * Serialisation helper (allows to be sure the template method is
     * instantiated).
     */
    void serialisationImplementation();


  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Default constructor.
     */
    ReachableUniverse (const Key_T&);

    /**
     * Destructor.
     */
    ~ReachableUniverse();

  private:
    /**
     * Default constructor.
     */
    ReachableUniverse();

    /**
     * Copy constructor.
     */
    ReachableUniverse (const ReachableUniverse&);


  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (origin airport code).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (BomRoot).
     */
    stdair::BomAbstract* _parent;

    /**
     * Map holding the children ( objects).
     */
    stdair::HolderMap_T _holderMap;
    
    /**
     * The list of lists of SegmentPathPeriods, used solely for the
     * construction of the main list of SegmentPathPeriods within the
     * ReachableUniverseStructure.
     */
    SegmentPathPeriodListList_T _segmentPathPeriodListList;
  };

}
#endif // __AIRSCHED_BOM_REACHABLEUNIVERSE_HPP

