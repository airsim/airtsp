#ifndef __AIRSCHED_BOM_BOMROOT_HPP
#define __AIRSCHED_BOM_BOMROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomRoot.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline bom root. */
  class BomRoot : public stdair::BomRoot {
    friend class stdair::FacBomContent;

  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (const stdair::BomRoot&);
    
  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::BomRootStructure_T BomStructure_T;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomRoot ();
    BomRoot (const BomRoot&);
    BomRoot (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~BomRoot();

  };

}
#endif // __AIRSCHED_BOM_BOMROOT_HPP
