#ifndef __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP
#define __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <vector>
#include <string>
#include <map>
//STDAIR 
#include <stdair/bom/BomChildrenHolder.hpp>

namespace stdair {
  
  /** Template class aimed at holding a list and a map of children BOM
      structure of a dedicated type. */
  template <typename BOM_CONTENT_CHILD>
  class BomChildrenHolderImp : public BomChildrenHolder {
    friend class FacBomStructure;

    /** Retrieve associated bom structure type. */
    typedef typename BOM_CONTENT_CHILD::BomStructure_T BomStructure_T;
    
  public:
    /** Define lists of children BOM structures. */
    typedef std::vector<BomStructure_T*> BomChildrenOrderedList_T;
    typedef std::map<const std::string, BomStructure_T*> BomChildrenList_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return std::string (""); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void describeFull (std::ostringstream& ioOut) const {
      // Initialise the index
      unsigned short lIdx = 0;
      
      for (typename BomChildrenOrderedList_T::const_iterator itChild =
             _bomChildrenOrderedList.begin();
           itChild != _bomChildrenOrderedList.end(); ++itChild) {
        const BomStructure_T* lCurrentChild_ptr = *itChild;
        ioOut << "[" << lIdx << "]: ";
        lCurrentChild_ptr->describeFull (ioOut);
        ++lIdx;
      }
    }

    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on bom children structures:
        The current iterator is set on the first bom child structure,
        the next iterator is set on the second one. */
    void bomChildrenListBegin () {
      _itCurrentBomObject = _bomChildrenList.begin ();
    }
    
    /** Iterate for one element (bom child structure). */
    void bomChildrenListIterate () {
      ++_itCurrentBomObject;
    }
    
    /** States whether or not the end of the (bom child structure)
        list has been reached. */
    const bool bomChildrenListHasNotReachedEnd () const {
      return _itCurrentBomObject != _bomChildrenList.end();
    }

    /** Get the current element (bom child structure). */
    BOM_CONTENT_CHILD& getCurrentBomChildrenContent () const {
      const BomStructure_T* lCurrentBomStructure_ptr =
        _itCurrentBomObject->second;
      BOM_CONTENT_CHILD* lCurrentBomContent_ptr =
        lCurrentBomStructure_ptr->getBomContentPtr();
      return *lCurrentBomContent_ptr;
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomChildrenHolderImp () { }
    BomChildrenHolderImp (const BomChildrenHolderImp&);

    /** Destructor. */
    ~BomChildrenHolderImp() { }
    
  private:
    ///////////// Attributes //////////////
    /** List of children BOM structures. */
    BomChildrenList_T _bomChildrenList;

    /** Map of children BOM structures with their key. */
    BomChildrenOrderedList_T _bomChildrenOrderedList;

    /** Iterator for the current BOM structure on the non-ordered list. */
    typename BomChildrenList_T::const_iterator _itCurrentBomObject;
  };
  
}
#endif // __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP

