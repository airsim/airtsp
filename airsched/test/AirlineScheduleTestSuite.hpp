// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class AirlineScheduleTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (AirlineScheduleTestSuite);
  CPPUNIT_TEST (testAirlineSchedule);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Optimisation functionality. */
  void testAirlineSchedule ();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  AirlineScheduleTestSuite ();
  
protected:
  std::stringstream _describeKey;
};
CPPUNIT_TEST_SUITE_REGISTRATION (AirlineScheduleTestSuite);
