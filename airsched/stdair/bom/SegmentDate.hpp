#ifndef __STDAIR_BOM_SEGMENTDATE_HPP
#define __STDAIR_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomAbstract.hpp>

namespace STDAIR {

  // Forward declaration
  class SegmentDateKey;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific SegmentDate class (for instance,
      in the AIRSCHED library). */
  class SegmentDate : public BomAbstract {
    friend class FacSegmentDate;
  public:
    // /////////// Getters /////////////
    /** Get the segment-date key. */
    const SegmentDateKey& getKey() const {
      return _key;
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
    SegmentDate ();
    SegmentDate (const SegmentDate&);
    SegmentDate (const SegmentDateKey&);

    /** Destructor. */
    virtual ~SegmentDate();

  private:
    // Attributes
    /** Segment-date key (e.g., allowing to specify "LHR-SYD"). */
    const SegmentDateKey& _key;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATE_HPP
