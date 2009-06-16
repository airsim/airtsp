#ifndef __STDAIR_FAC_FACSEGMENTDATE_HPP
#define __STDAIR_FAC_FACSEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/factory/FacBomAbstract.hpp>

namespace STDAIR {

  // Forward declarations.
  class SegmentDate;
  class SegmentDateKey;
  
  /** Factory for SegmentDate objects. */
  class FacSegmentDate : public FacBomAbstract {
  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used
        @return FacSegmentDate& */
    static FacSegmentDate& instance();

    /** Destructor.
        <br>The Destruction put the _instance to NULL
        in order to be clean for the next FacSegmentDate::instance() */
    virtual ~FacSegmentDate();

    /** Create a new SegmentDate object.
        <br>This new object is added to the list of instantiated objects.
        @return SegmentDate& The newly created object. */
    SegmentDate& create (const SegmentDateKey&);

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacSegmentDate () {}

  private:
    /** The unique instance.*/
    static FacSegmentDate* _instance;
  };

}
#endif // __STDAIR_FAC_FACSEGMENTDATE_HPP

