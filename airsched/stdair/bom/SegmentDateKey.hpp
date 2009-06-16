#ifndef __STDAIR_BOM_SEGMENTDATEKEY_HPP
#define __STDAIR_BOM_SEGMENTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace STDAIR {

  /** Key of segment-date. */
  class SegmentDateKey : public BomKey {
  public:

    // /////////// Construction ///////////
    /** Constructor. */
    SegmentDateKey (const AirportCode_T& iBoardPoint,
                    const AirportCode_T& iOffPoint)
      : _boardPoint (iBoardPoint), _offPoint (iOffPoint) {
    }

    /** Destructor. */
    ~SegmentDateKey () {
    }
    
    // /////////// Getters //////////
    /** Get the boarding point. */
    const AirportCode_T& getBoardPoint() const {
      return _boardPoint;
    }

    /** Get the arrival point. */
    const AirportCode_T& getOffPoint() const {
      return _offPoint;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique for all the Business Objects,
       whatever their level in the BOM hierarchy.
       <br>For instance, "BA123/10JUN2010" and "BA123/11JUN2010" allow to
       differentiate among two departure dates for the same flight. */
    std::string toString() const;
    
   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-date. */
    std::string toShortString() const;

  private:
    // Attributes
    /** Boarding airport. */
    AirportCode_T _boardPoint;

    /** Arrival airport. */
    AirportCode_T _offPoint;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATEKEY_HPP
