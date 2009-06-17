#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/SegmentDateList.hpp>

namespace STDAIR {

  // Forward declaration
  class FlightDateKey;

  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific FlightDate class (for instance,
      in the AIRSCHED library). */
  class FlightDate : public BomAbstract {
    friend class FacFlightDate;
  public:
    // /////////// Getters /////////////
    /** Get the flight-date key. */
    const FlightDateKey& getKey() const;

    /** Get the list of segment-dates. */
    const SegmentDateList_T& getSegmentList() const {
      return _segmentList;
    }
    
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
    FlightDate (const FlightDateKey&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** List of segment-dates. */
    SegmentDateList_T _segmentList;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

