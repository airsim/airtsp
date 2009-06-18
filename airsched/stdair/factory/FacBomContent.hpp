#ifndef __STDAIR_FAC_FACBOMCONTENT_HPP
#define __STDAIR_FAC_FACBOMCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/factory/FacBomStructure.hpp>

namespace STDAIR {

  // Forward declarations
  class BomStructure;
  class BomContent;
  class BomContentRoot;
  
  /** Base class for Factory layer. */
  class FacBomContent {
    friend class FacSupervisor;
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::map<const STDAIR::BomContent*,
                     STDAIR::BomStructure*> StructureMapFromContent_T;

  public:
    /** Create the root of the BOM tree, i.e., a pair of linked
        BomStructureRoot and BomContentRoot objects. */
    BomContentRoot& createBomRoot ();
    
    /** Create a (child) content object, given a key.
        <br>A structure object is created, under the hood, with the given key.
        That structure object then gets a pointer on the content object. */
    template <typename BOM_KEY,
              typename BOM_STRUCTURE_PARENT, typename BOM_STRUCTURE_CHILD,
              typename BOM_CHILDREN_LIST,
              typename BOM_CONTENT_PARENT, typename BOM_CONTENT_CHILD>
    BOM_CONTENT_CHILD& create (BOM_CONTENT_PARENT& ioContentChild,
                               const BOM_KEY& iKey) {

      // Create the child structure object for the given key
      BOM_CONTENT_CHILD& lBomContentChild =
        createInternal<BOM_KEY, BOM_STRUCTURE_CHILD, BOM_CONTENT_CHILD> (iKey);

      // Retrieve the child structure object
      BOM_STRUCTURE_CHILD* lBomStructureChild_ptr =
        getBomStructure<BOM_STRUCTURE_CHILD,
                        BOM_CONTENT_CHILD> (lBomContentChild);
      assert (lBomStructureChild_ptr != NULL);

      // Retrieve the parent structure object
      BOM_STRUCTURE_PARENT* lBomStructureParent_ptr =
        getBomStructure<BOM_STRUCTURE_PARENT,
                        BOM_CONTENT_PARENT> (ioContentChild);
      assert (lBomStructureParent_ptr != NULL);

      // Link both the parent and child structure objects
      const bool hasLinkBeenSuccessful = FacBomStructure::
        linkBomParentWithBomChild<BOM_STRUCTURE_PARENT, BOM_STRUCTURE_CHILD,
        BOM_KEY, BOM_CHILDREN_LIST>  (*lBomStructureParent_ptr,
                                      *lBomStructureChild_ptr);

      if (hasLinkBeenSuccessful == false) {
        throw new MemoryAllocationException();
      }

      return lBomContentChild;
    }

    
  private:
    /** Create a content object, given a key.
        <br>A structure object is created, under the hood, with the given key.
        That structure object then gets a pointer on the content object. */
    template <typename BOM_KEY, typename BOM_STRUCTURE, typename BOM_CONTENT>
    BOM_CONTENT& createInternal (const BOM_KEY& iKey) {
    
      // Create the structure/holder object
      BOM_STRUCTURE& lBomStructure =
        FacBomStructure::instance().create<BOM_KEY, BOM_STRUCTURE> (iKey);

      // The created flight-date content (BomContent) object gets a constant
      // reference on its corresponding flight-date structure/holder object
      BOM_CONTENT* aBomContent_ptr = new BOM_CONTENT (lBomStructure);
      assert (aBomContent_ptr != NULL);

      // Link the structure/holder object with its corresponding content object
      setContent (lBomStructure, *aBomContent_ptr);

      // The new content object is added to the pool of content objects
      const bool hasInsertBeenSuccessful = _structureMap.
        insert (StructureMapFromContent_T::value_type (aBomContent_ptr,
                                                       &lBomStructure)).second;
      if (hasInsertBeenSuccessful == false) {
        throw new MemoryAllocationException();
      }
    
      return *aBomContent_ptr;
    }

    /** Retrieve the structure object associated to the given content object. */
    template <typename BOM_STRUCTURE, typename BOM_CONTENT>
    BOM_STRUCTURE* getBomStructure (const BOM_CONTENT& iBomContent) {
      BOM_STRUCTURE* oBomStructure_ptr = NULL;
    
      StructureMapFromContent_T::iterator itBomStructure =
        _structureMap.find (&iBomContent);
      if (itBomStructure != _structureMap.end()) {
        oBomStructure_ptr= dynamic_cast<BOM_STRUCTURE*> (itBomStructure->second);
      }
      return oBomStructure_ptr;
    }
  

  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBomContent& */
    static FacBomContent& instance();

    
  private:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is content. */
    FacBomContent() {}

    /** Destructor. */
    virtual ~FacBomContent();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

    
  private:
    /** Link the structure/holder object with its corresponding content
        object. */
    static void setContent (BomStructure&, BomContent&);

    
  private:
    /** The unique instance.*/
    static FacBomContent* _instance;
    
  private:
    /** Map of the structure objects corresponding to content objects (they
        both get a copy of the same key). */
    StructureMapFromContent_T _structureMap;
  };
}
#endif // __STDAIR_FAC_FACBOMCONTENT_HPP
