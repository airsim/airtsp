#ifndef __STDAIR_FAC_FACFLIGHTDATE_HPP
#define __STDAIR_FAC_FACFLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/factory/FacBomAbstract.hpp>

namespace STDAIR {

  // Forward declarations.
  class FlightDate;
  class FlightDateKey;
  
  /** Factory for FlightDate objects. */
  class FacFlightDate : public FacBomAbstract {
  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used
        @return FacFlightDate& */
    static FacFlightDate& instance();

    /** Destructor.
        <br>The Destruction put the _instance to NULL
        in order to be clean for the next FacFlightDate::instance() */
    virtual ~FacFlightDate();

    /** Create a new FlightDate object.
        <br>This new object is added to the list of instantiated objects.
        @return FlightDate& The newly created object. */
    FlightDate& create (const FlightDateKey&);

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacFlightDate () {}

  private:
    /** The unique instance.*/
    static FacFlightDate* _instance;
  };

}
#endif // __STDAIR_FAC_FACFLIGHTDATE_HPP

