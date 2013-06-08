// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// AirTSP
#include <airtsp/bom/FareFamilyStruct.hpp>

namespace AIRTSP {

  // //////////////////////////////////////////////////////////////////////
  FareFamilyStruct::
  FareFamilyStruct (const stdair::FamilyCode_T& iFamilyCode,
                    const stdair::CurveKey_T& iFRAT5Key,
                    const stdair::CurveKey_T& iFFDisutilityKey,
                    const stdair::ClassList_String_T& iClasses)
    : _familyCode (iFamilyCode),_frat5CurveKey (iFRAT5Key),
      _ffDisutilityCurveKey (iFFDisutilityKey), _classes (iClasses) {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FareFamilyStruct::describe() const {
    std::ostringstream ostr;
    ostr << "        " << _familyCode << " "
         << _frat5CurveKey << " " << _ffDisutilityCurveKey
         << " " << _classes << ", ";
    return ostr.str();
  }

}
