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
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::BomRootStructure_T Structure_T;

  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (const stdair::BomRoot&);

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    BomRoot (const Key_T&, Structure_T&);
    /** Destructor. */
    ~BomRoot();
    /** Default constructors. */
    BomRoot ();
    BomRoot (const BomRoot&);

  };

}
#endif // __AIRSCHED_BOM_BOMROOT_HPP
