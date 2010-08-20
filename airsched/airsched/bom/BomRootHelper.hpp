#ifndef __AIRSCHED_BOM_BOMROOTHELPER_HPP
#define __AIRSCHED_BOM_BOMROOTHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations.
namespace stdair {
  class BomRoot;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline bom root. */
  class BomRootHelper {
  public:
    // ////////// Business Methods /////////
    /** Fill the attributes derived from the routing legs (e.g., board
        and off dates). */
    static void fillFromRouting (const stdair::BomRoot&);
  };

}
#endif // __AIRSCHED_BOM_BOMROOTHELPER_HPP
