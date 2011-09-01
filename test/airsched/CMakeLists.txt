#
# AirSched Tests
#
module_set_name (airsched)


##
# Specify each test suite configuration

# * AirSched Test Suite
module_test_add_suite (AirlineScheduleTestSuite AirlineScheduleTestSuite.cpp)


##
# Register all the test suites to be built and performed
module_test_build_all ()
