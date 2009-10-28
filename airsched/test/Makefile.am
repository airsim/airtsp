## test sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS = com architecture

EXTRA_DIST =
##

check_PROGRAMS = AirlineScheduleTestSuite
TESTS = $(check_PROGRAMS)
XFAIL_TESTS = #IndexBuildingTestSuite

AirlineScheduleTestSuite_SOURCES = AirlineScheduleTestSuite.hpp AirlineScheduleTestSuite.cpp
AirlineScheduleTestSuite_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
AirlineScheduleTestSuite_LDADD = 
AirlineScheduleTestSuite_LDFLAGS = $(BOOST_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/test/com/libcppunitcore.la \
	$(top_builddir)/@PACKAGE@/core/lib@PACKAGE@.la \
	$(top_builddir)/stdair/core/libstdair.la \
	$(top_builddir)/@PACKAGE@/core/lib@PACKAGE@.la

