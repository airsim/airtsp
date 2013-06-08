#
# AirTSP Tests
#

##
# Specify each test suite configuration

# * AirTSP Test Suite
module_test_add_suite (airtsp AirlineScheduleTestSuite AirlineScheduleTestSuite.cpp)


##
# Register all the test suites to be built and performed
module_test_build_all ()

