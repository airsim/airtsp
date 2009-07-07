#ifndef __STDAIR_BOM_BOMCHILDRENHOLDER_HPP
#define __STDAIR_BOM_BOMCHILDRENHOLDER_HPP

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
#include <stdair/bom/BomStructure.hpp>

namespace stdair {
  
  /** Template class aimed at holding a list and a map of children BOM
      structure of a dedicated type. */
  template <typename BOM_CHILD>
  class BomChildrenHolder : public BomStructure {
    friend class FacBomStructure;
    friend class PrintBomContent;
    
  public:
    /** Define lists of children BOM structures. */
    typedef std::vector<BOM_CHILD*> BomChildrenOrderedList_T;
    typedef std::map<const std::string, BOM_CHILD*> BomChildrenList_T;

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
        const BOM_CHILD* lCurrentChild_ptr = *itChild;
        ioOut << "[" << lIdx << "]: ";
        lCurrentChild_ptr->describeFull (ioOut);
        ++lIdx;
      }
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomChildrenHolder () { }
    BomChildrenHolder (const BomChildrenHolder&);

    /** Destructor. */
    ~BomChildrenHolder() { }
    
  private:
    ///////////// Attributes //////////////
    /** List of children BOM structures. */
    BomChildrenList_T _bomChildrenList;

    /** Map of children BOM structures with their key. */
    BomChildrenOrderedList_T _bomChildrenOrderedList;
  };
  
}
#endif // __STDAIR_BOM_BOMCHILDRENHOLDER_HPP

