#ifndef __AIRSCHED_BOM_BOOKINGCLASS_HPP
#define __AIRSCHED_BOM_BOOKINGCLASS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BookingClass.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
}

namespace AIRSCHED {
  /** Class representing the actual business functions for
      an airline booking class. */
  class BookingClass : public stdair::BookingClass {
    friend class stdair::FacBomContent;

  public:
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef stdair::BookingClassStructure_T BomStructure_T;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BookingClass ();
    BookingClass (const BookingClass&);
    BookingClass (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~BookingClass();

  };

}
#endif // __AIRSCHED_BOM_BOOKINGCLASS_HPP
