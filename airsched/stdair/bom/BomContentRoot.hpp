#ifndef __STDAIR_BOM_BOMCONTENTROOT_HPP
#define __STDAIR_BOM_BOMCONTENTROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BomStructureRoot.hpp>

namespace stdair {

  /** Class representing the actual functional/business content
      for the Bom root.
      <br>That class is just an utility tool to mark the root
      of the Bom tree. */
  template <typename BOM_CHILD>
  class BomContentRoot : public BomContent {
    friend class FacBomContent;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BomStructureRoot<BomContentRoot> BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomStructureRootKey BomKey_T;

    /** Definition allowing to retrieve the associated first
         BOM content child type. */
    typedef BOM_CHILD FirstContentChild_T;
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomContentRoot ();
    BomContentRoot (const BomContentRoot&);
    BomContentRoot (const BomStructure_T& iBomStructure)
      : _bomStructure (iBomStructure) { }

    /** Destructor. */
    virtual ~BomContentRoot() { }

  private:
    // Attributes
    /** Reference structure. */
    const BomStructure_T& _bomStructure;
  };

}
#endif // __STDAIR_BOM_BOMCONTENTROOT_HPP
