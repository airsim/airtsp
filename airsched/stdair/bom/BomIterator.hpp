#ifndef __STDAIR_BOM_BOMITERATOR_T_HPP
#define __STDAIR_BOM_BOMITERATOR_T_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
#include <map>
// STDAIR
#include <stdair/basic/BasTypes.hpp>

namespace stdair {
  
  /** Template class aimed at iterating a list or a map of children BOM
      structure of a dedicated type. */
  template <typename BOM_CONTENT, typename ITERATOR>
  struct BomConstIterator_T {

  public:
    // Definition allowing to retrieve the corresponding bom structure.
    typedef typename BOM_CONTENT::BomStructure_T BomStructure_T;

    // Define the pair of string and pointer of BOM_CONTENT.
    typedef typename std::pair<std::string, const BOM_CONTENT*> value_type;
    
  public:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Normal constructor. */
    BomConstIterator_T (ITERATOR iIterator)
      : _itBomStructureObject (iIterator) { }

    /** Default constructor. */
    BomConstIterator_T () { }
    
    /** Default copy constructor. */
    BomConstIterator_T (const BomConstIterator_T& iBomIterator)
      : _itBomStructureObject (iBomIterator._itBomStructureObject) { }
    
    /** Destructor. */
    ~BomConstIterator_T() { }

  public:
    // ///////////// Operators //////////////
    /** Incrementing (prefix and postfix) operators. */
    void operator++ () { ++_itBomStructureObject; }
    void operator++ (int) { ++_itBomStructureObject; }

    /** Equality operators. */
    bool operator== (const BomConstIterator_T& iIt) {
      return _itBomStructureObject == iIt._itBomStructureObject;
    }
    bool operator!= (const BomConstIterator_T& iIt) {
      return _itBomStructureObject != iIt._itBomStructureObject;
    }

    /** Dereferencing operators. */
    const BOM_CONTENT& operator* () {
      BomStructure_T* lBomStruct_ptr = *_itBomStructureObject;
      assert (lBomStruct_ptr != NULL);
      BOM_CONTENT* lBomContent_ptr = lBomStruct_ptr->getBomContentPtr ();
      assert (lBomContent_ptr != NULL);
      return *lBomContent_ptr;
    }
    value_type* operator-> () {
      const MapKey_T& lKey = _itBomStructureObject->first;
      BomStructure_T* lBomStruct_ptr = _itBomStructureObject->second;
      assert (lBomStruct_ptr != NULL);
      BOM_CONTENT* lBomContent_ptr = lBomStruct_ptr->getBomContentPtr ();
      assert (lBomContent_ptr != NULL);

      // See the comment below, at the definition of the _intermediateValue
      // attribute
      _intermediateValue.first = lKey;
      _intermediateValue.second = lBomContent_ptr;
      
      return &_intermediateValue;
    }
    
  private:
    ///////////// Attributes //////////////
    /** Iterator for the current BOM structure on the non-ordered list. */
    ITERATOR _itBomStructureObject;

    /** Helper attribute.
        <br>It is necessary to define that value at the attribute
        level, because the operator->() method needs to return a
        pointer on it. If that value be temporary, i.e., created at
        the fly when the operator->() method returns, we would return
        a pointer on a temporary value, which is not good. */
    value_type _intermediateValue;
  };
  
}
#endif // __STDAIR_BOM_BOMITERATOR_T_HPP
