// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class AirlineScheduleTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (AirlineScheduleTestSuite);
  CPPUNIT_TEST (testMemoryExternalManagingMode);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Optimisation functionality.
   <br> The code is aimed at testing the initialization of airline
   inventory-related objects which are mainly implemented in the
   stdair library. That means the memory allocation of these objects
   will be managed by the calling project and not by the called project.
   */
  void testMemoryExternalManagingMode ();

  /** Constructor. */
  AirlineScheduleTestSuite ();
  
protected:
  std::stringstream _describeKey;
};
CPPUNIT_TEST_SUITE_REGISTRATION (AirlineScheduleTestSuite);
