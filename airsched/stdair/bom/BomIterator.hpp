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

    // Define the map of key and pointer of BOM_CONTENT.
    typedef typename std::map<const std::string, BOM_CONTENT*> ContentMap_T;
    
    // Define the pointer type of ContentMap_T;
    typedef typename ContentMap_T::pointer pointer;
    
  public:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Normal constructor. */
    BomIterator_T (ITERATOR iIterator) : _itBomStructureObject (iIterator) { }

    /** Default constructor. */
    BomIterator_T () { }
    
    /** Default copy constructor. */
    BomIterator_T (const BomIterator_T& iBomIterator)
      : _itBomStructureObject (iBomIterator._itBomStructureObject) { }
    
    /** Destructor. */
    ~BomIterator_T() { }

  public:
    // ///////////// Operators //////////////
    /** Incrementing (prefix and postfix) operators. */
    void operator++ () { ++_itBomStructureObject; }
    void operator++ (int) { ++_itBomStructureObject; }

    /** Equality operators. */
    bool operator== (const BomIterator_T& iIt) {
      return _itBomStructureObject == iIt._itBomStructureObject;
    }
    bool operator!= (const BomIterator_T& iIt) {
      return _itBomStructureObject != iIt._itBomStructureObject;
    }

    /** Dereferencing operators. */
    BOM_CONTENT& operator* () {
      BomStructure_T* lBomStruct_ptr = *_itBomStructureObject;
      assert (lBomStruct_ptr != NULL);
      BOM_CONTENT* lBomContent_ptr = lBomStruct_ptr->getBomContentPtr ();
      assert (lBomContent_ptr != NULL);
      return *lBomContent_ptr;
    }
    pointer operator-> () {
      const std::string& lKey = _itBomStructureObject->first;
      BomStructure_T* lBomStruct_ptr = _itBomStructureObject->second;
      assert (lBomStruct_ptr != NULL);
      BOM_CONTENT* lBomContent_ptr = lBomStruct_ptr->getBomContentPtr ();
      assert (lBomContent_ptr != NULL);

      _tempMap.clear();
      const bool insertSucceded =
        _tempMap.insert (typename ContentMap_T::value_type (lKey,
                                                            lBomContent_ptr)).second;
      typename ContentMap_T::iterator itContent = _tempMap.begin();
      
      return &(*itContent);
    }
    
  private:
    ///////////// Attributes //////////////
    /** Iterator for the current BOM structure on the non-ordered list. */
    ITERATOR _itBomStructureObject;

    ContentMap_T _tempMap;
  };
  
}
#endif // __STDAIR_BOM_BOMITERATOR_T_HPP
