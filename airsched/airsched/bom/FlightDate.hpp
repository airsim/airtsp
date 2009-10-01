#ifndef __AIRSCHED_BOM_FLIGHTDATE_HPP
#define __AIRSCHED_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomStructureList.hpp>
// AIRSCHED 
#include <airsched/AIRSCHED_Types.hpp>
#include <stdair/bom/BomContent.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
  class BomStructure;
}
  
namespace AIRSCHED {

  // Forward declarations
  class Inventory;
  
  /** Class representing the actual functional/business content for a
      flight-date. */
  class FlightDate : public stdair::BomContent {
    friend class stdair::FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Inventory ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef FlightDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef SegmentDate ContentChild_T;

        /** Definition allowing to retrieve the associated second
         BOM content child type. */
    typedef LegDate SecondContentChild_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _flightStructure;
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (BomStructure_T&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _flightStructure;
  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATE_HPP

