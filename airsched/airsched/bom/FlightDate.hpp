#ifndef __AIRSCHED_BOM_FLIGHTDATE_HPP
#define __AIRSCHED_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED 
#include <stdair/bom/BomContent.hpp>

// Forward declarations
namespace STDAIR {
  class FlightDate;
  class FacBomContent;
}
  
namespace AIRSCHED {

  /** Class representing the actual functional/business content for a
      flight-date. */
  class FlightDate : public STDAIR::BomContent {
    friend class FacFlightDate;
    friend class STDAIR::FacBomContent;
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
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (const STDAIR::FlightDate&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** Reference structure. */
    const STDAIR::FlightDate& _flightStructure;
  };

}
#endif // __AIRSCHED_BOM_FLIGHTDATE_HPP

