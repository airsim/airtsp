#ifndef __STDAIR_FAC_FACBOMCONTENT_HPP
#define __STDAIR_FAC_FACBOMCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>

namespace STDAIR {

  // Forward declarations
  class BomStructure;
  class BomContent;
  
  /** Base class for Factory layer. */
  class FacBomContent {
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::map<const STDAIR::BomContent*, STDAIR::BomStructure*> BomPool_T;

    /** Destructor. */
    virtual ~FacBomContent();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is content. */
    FacBomContent() {}

    /** List of instantiated Business Objects*/
    BomPool_T _pool;
  };
}
#endif // __STDAIR_FAC_FACBOMCONTENT_HPP
