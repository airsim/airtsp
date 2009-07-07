#ifndef __STDAIR_BOM_PRINTBOMCONTENT_HPP
#define __STDAIR_BOM_PRINTBOMCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// MPL
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
// STDAIR
#include <stdair/bom/BomChildrenHolder.hpp>

namespace stdair {
  
  /** .*/
  class PrintBomContent {

  public:
    /** Dump a BomContent object into an output stream.*/
    template <typename BOM_STRUCTURE>
    static void printContent (const BOM_STRUCTURE& ioBomStructure,
                              std::ostringstream& ioStr, unsigned short& ioIdx) {
      // Type for the list of children bom holders
      typedef typename BOM_STRUCTURE::ChildrenBomList_T CHILDREN_BOM_LIST_T;

      // Type for the list of children bom types
      typedef typename BOM_STRUCTURE::ChildrenBomTypeList_T CHILDREN_BOM_TYPE_LIST_T;
      
      // Retrive the list of children holders.
      const CHILDREN_BOM_LIST_T& lBomStructureList =
        ioBomStructure.getChildrenList();

      // Get the number of children types
      const int lNbOfTypes =
        boost::mpl::size <CHILDREN_BOM_TYPE_LIST_T>::type::value;
      
      if (lNbOfTypes > 0) {
        // Type for the first children type
        typedef typename boost::mpl::at_c<CHILDREN_BOM_TYPE_LIST_T,0>::type
          FIRST_CHILDREN_TYPE_T;

        // Type for the holder of children of the first type
        typedef BomChildrenHolder<FIRST_CHILDREN_TYPE_T> FIRST_CHILDREN_HOLDER_T;

        FIRST_CHILDREN_HOLDER_T* lFirstChildrenHolder_ptr =
          dynamic_cast<FIRST_CHILDREN_HOLDER_T*> (lBomStructureList.at(0));
        assert (lFirstChildrenHolder_ptr != NULL);


      if (lNbOfTypes > 1) {

      }
    }
  };

}
#endif // __STDAIR_BOM_PRINTBOMCONTENT_HPP

