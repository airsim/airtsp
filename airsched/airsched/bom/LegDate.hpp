#ifndef __AIRSCHED_BOM_LEGDATE_HPP
#define __AIRSCHED_BOM_LEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/LegDate.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline leg-date. */
  class LegDate : public stdair::LegDate {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::LegDateStructure_T BomStructure_T;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegDate ();
    LegDate (const LegDate&);
    LegDate (BomStructure_T&);

    /** Destructor. */
    virtual ~LegDate();

  };

}
#endif // __AIRSCHED_BOM_LEGDATE_HPP
