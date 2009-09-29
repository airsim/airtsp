#ifndef __STDAIR_BOM_BOMITERATOR_T_HPP
#define __STDAIR_BOM_BOMITERATOR_T_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <vector>
#include <map>

namespace stdair {
  
  /** Template class aimed at iterating a list or a map of children BOM
      structure of a dedicated type. */
  template <typename BOM_CONTENT, typename ITERATOR>
  struct BomIterator_T {

  public:
    // Definition allowing to retrieve the corresponding bom structure.
    typedef typename BOM_CONTENT::BomStructure_T BomStructure_T;
    
  public:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Normal constructor. */
    BomIterator_T (ITERATOR iIterator) : _itCurrentBomObject (iIterator) { }

    /** Default constructor. */
    BomIterator_T () { }
    
    /** Default copy constructor. */
    BomIterator_T (const BomIterator_T& iBomIterator)
      : _itCurrentBomObject (iBomIterator._itCurrentBomObject) { }
    
    /** Destructor. */
    ~BomIterator_T() { }

  public:
    // ///////////// Operators //////////////
    /** Increment operator. */
    void operator++ () { ++_itCurrentBomObject; }

    /** Equality operators. */
    bool operator== (const BomIterator_T& iIt) {
      return _itCurrentBomObject == iIt._itCurrentBomObject;
    }

    bool operator!= (const BomIterator_T& iIt) {
      return _itCurrentBomObject != iIt._itCurrentBomObject;
    }

    BOM_CONTENT& operator* () {
      BomStructure_T* lBomStruct_ptr = *_itCurrentBomObject;
      BOM_CONTENT* lBomContent_ptr = lBomStruct_ptr->getBomContentPtr ();
      return *lBomContent_ptr;
    }
    
  private:
    ///////////// Attributes //////////////
    /** Iterator for the current BOM structure on the non-ordered list. */
    ITERATOR _itCurrentBomObject;
  };
  
}
#endif // __STDAIR_BOM_BOMITERATOR_T_HPP
