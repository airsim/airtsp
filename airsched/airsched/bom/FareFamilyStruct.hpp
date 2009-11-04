#ifndef __AIRSCHED_BOM_FAREFAMILYSTRUCT_HPP
#define __AIRSCHED_BOM_FAREFAMILYSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/StructAbstract.hpp>

namespace AIRSCHED {

  /** Utility Structure for the parsing of fare family details. */
  struct FareFamilyStruct_T : public stdair::StructAbstract {
    // Attributes
    stdair::FamilyCode_T _familyCode;
    stdair::ClassList_String_T _classes;

    /** Constructors. */
    FareFamilyStruct_T (const stdair::FamilyCode_T&,
                        const stdair::ClassList_String_T&);
      
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;
  };

  /** List of FareFamily-Detail structures. */
  typedef std::vector<FareFamilyStruct_T> FareFamilyStructList_T;

}
#endif // __AIRSCHED_BOM_FAREFAMILYSTRUCT_HPP
