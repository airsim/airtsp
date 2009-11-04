// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// AIRSCHED
#include <airsched/bom/FareFamilyStruct.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  FareFamilyStruct_T::
  FareFamilyStruct_T (const stdair::FamilyCode_T& iFamilyCode,
                      const stdair::ClassList_String_T& iClasses)
    : _familyCode (iFamilyCode),
      _classes (iClasses) {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FareFamilyStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << "        " << _familyCode << " " << _classes << ", ";
    return ostr.str();
  }

}
