#ifndef __STDAIR_FAC_FACBOMCHILDRENHOLDER_HPP
#define __STDAIR_FAC_FACBOMCHILDRENHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/bom/BomChildrenHolder.hpp>

namespace stdair {

  // Forward declarations

  /** Base class for Factory layer. */
  class FacBomChildrenHolder {
  public:

    /** Define the list (pool) of Bom objects. */
   //  typedef std::vector<BomChildrenHolder<class BOM_CHILD>*> BomChildrenHolderPool_T;
    typedef std::vector<BomChildrenHolder*> BomChildrenHolderPool_T;

    /** Destructor. */
    virtual ~FacBomChildrenHolder();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is structure. */
    FacBomChildrenHolder() {}

  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBomChildrenHolder& */
    static FacBomChildrenHolder& instance();
    
    /** Create a bom children holder object. */
//     template <typename BOM_CHILD>
//     BomChildrenHolder<BOM_CHILD>& create () {
//       BomChildrenHolder<BOM_CHILD>* aBomChildrenHolder_ptr = NULL;

//       aBomChildrenHolder_ptr = new BomChildrenHolder<BOM_CHILD> ();
//       assert (aBomChildrenHolder_ptr != NULL);
      
//       // The new object is added to the pool of ChildrenHolder objects
//       _childrenHolderPool.push_back (aBomChildrenHolder_ptr);
      
//       return *aBomChildrenHolder_ptr;
//     }
    
    BomChildrenHolder& create () {
      BomChildrenHolder* aBomChildrenHolder_ptr = NULL;

      aBomChildrenHolder_ptr = new BomChildrenHolder ();
      assert (aBomChildrenHolder_ptr != NULL);
      
      // The new object is added to the pool of ChildrenHolder objects
      _childrenHolderPool.push_back (aBomChildrenHolder_ptr);
      
      return *aBomChildrenHolder_ptr;
    }
    
  private:
    /** The unique instance.*/
    static FacBomChildrenHolder* _instance;
    
  private:
    /** List of instantiated Business Objects*/
    BomChildrenHolderPool_T _childrenHolderPool;
  };
}
#endif // __STDAIR_FAC_FACBOMCHILDRENHOLDER_HPP
