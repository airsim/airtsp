#ifndef __STDAIR_FAC_FACBOMSTRUCTURE_HPP
#define __STDAIR_FAC_FACBOMSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace STDAIR {

  // Forward declarations
  class BomStructure;
  class BomContent;

  /** Base class for Factory layer. */
  class FacBomStructure {
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomStructure*> BomPool_T;

    /** Destructor. */
    virtual ~FacBomStructure();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

    /** Link the structure/holder object with its corresponding content
        object. */
    static void setContent (BomStructure&, BomContent&);

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is structure. */
    FacBomStructure() {}

    /** List of instantiated Business Objects*/
    BomPool_T _structurePool;
  };
}
#endif // __STDAIR_FAC_FACBOMSTRUCTURE_HPP
