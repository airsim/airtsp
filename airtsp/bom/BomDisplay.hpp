#ifndef __AIRTSP_BOM_BOMDISPLAY_HPP
#define __AIRTSP_BOM_BOMDISPLAY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// Airtsp

/// Forward declarations
namespace stdair {
  class BomRoot;
}

namespace AIRTSP {

  /// Forward declarations
  class ReachableUniverse;

  /**
   * @brief Utility class to display AirTSP objects with a pretty
   * format.
   */
  class BomDisplay {
  public:
    // //////////////// Display support methods /////////////////
    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const stdair::EventQueue& Root of the BOM tree to be displayed.
     */
    static std::string csvDisplay (const stdair::BomRoot&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const ReachableUniverse& Root of the BOM tree to be displayed.
     */
    static void csvDisplay (std::ostream&, const ReachableUniverse&);
  };
  
}
#endif // __AIRTSP_BOM_BOMDISPLAY_HPP
