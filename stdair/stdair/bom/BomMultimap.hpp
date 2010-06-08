#ifndef __STDAIR_BOM_BOMMULTIMAP_HPP
#define __STDAIR_BOM_BOMMULTIMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_CONTENT> class BomChildrenHolderImp;
  
  /** Structure which handles the iterators for a bom multimap. */
  template <typename BOM> struct BomMultimap_T {

  public:
    /** Definition that allows to retrieve the corresponding Structure
        associated to the BOM. */
    typedef typename BOM::Structure_T Structure_T;
    /** Define the multimap of bom objects. */
    typedef std::multimap<const MapKey_T, 
                          const Structure_T*> StructureMultimap_T;
    /** Define the bom holder. */
    typedef BomChildrenHolderImp<BOM> BomHolder_T;

    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the bom multimap iterators. */
    typedef BomIterator_T<BOM,
                          typename StructureMultimap_T::const_iterator> iterator;
    typedef BomIterator_T<BOM,
                          typename StructureMultimap_T::const_reverse_iterator
                          > reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
       
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the multimap. */
    iterator begin () const { return _bomHolder.mapBegin(); }
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the multimap. */
    iterator end () const { return _bomHolder.mapEnd(); }

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the multimap. */
    reverse_iterator rbegin () const { return _bomHolder.mapRBegin(); }
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the multimap. */
    reverse_iterator rend () const { return _bomHolder.mapREnd(); }
    
    /** Retrieve, if existing, the Inventory corresponding to the
        given key. */
    iterator find (const MapKey_T& iKey) const {
      return _bomHolder.find (iKey);
    }
    
  public:
    /** Default constructors. */
    BomMultimap_T ();
    BomMultimap_T (const BomMultimap_T& iBomMultimap) 
      : _bomHolder (iBomMultimap._bomHolder) { }
    BomMultimap_T (const BomHolder_T& iBomHolder) : _bomHolder (iBomHolder) { }
    /** Destructor. */
    ~BomMultimap_T() { }

  private:
    // Attributes
    /** Reference structure. */
    const BomHolder_T& _bomHolder;
  };

}
#endif // __STDAIR_BOM_BOMMULTIMULTIMAP_HPP

