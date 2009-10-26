#ifndef __AIRSCHED_BOM_LEGCABIN_HPP
#define __AIRSCHED_BOM_LEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/LegCabin.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline leg-cabin. */
  class LegCabin : public stdair::LegCabin {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::LegCabinStructure_T BomStructure_T;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegCabin ();
    LegCabin (const LegCabin&);
    LegCabin (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~LegCabin();

  };

}
#endif // __AIRSCHED_BOM_LEGCABIN_HPP
