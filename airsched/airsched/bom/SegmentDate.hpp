#ifndef __AIRSCHED_BOM_SEGMENTDATE_HPP
#define __AIRSCHED_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRSCHED 
#include <stdair/bom/BomContent.hpp>

// Forward declarations
namespace STDAIR {
  class SegmentDate;
  class FacBomContent;
}
  
namespace AIRSCHED {

  // Forward declarations
  class FlightDate;

  /** Class representing the actual functional/business content for a
      segment-date. */
  class SegmentDate : public STDAIR::BomContent {
    friend class STDAIR::FacBomContent;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightDate ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef STDAIR::SegmentDate BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef STDAIR::SegmentDateKey BomKey_T;
    
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
    SegmentDate ();
    SegmentDate (const SegmentDate&);
    SegmentDate (const BomStructure_T&);

    /** Destructor. */
    virtual ~SegmentDate();

  private:
    // Attributes
    /** Reference structure. */
    const BomStructure_T& _bomStructure;
  };

}
#endif // __AIRSCHED_BOM_SEGMENTDATE_HPP

