#ifndef __STDAIR_FAC_FACBOMABSTRACT_HPP
#define __STDAIR_FAC_FACBOMABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace STDAIR {

  // Forward declarations
  class BomAbstract;
  class BomContent;

  /** Base class for Factory layer. */
  class FacBomAbstract {
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomAbstract*> BomPool_T;

    /** Destructor. */
    virtual ~FacBomAbstract();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

    /** Link the structure/holder object with its corresponding content
        object. */
    static void setContent (BomAbstract&, BomContent&);

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is abstract. */
    FacBomAbstract() {}

    /** List of instantiated Business Objects*/
    BomPool_T _pool;
  };
}
#endif // __STDAIR_FAC_FACBOMABSTRACT_HPP
