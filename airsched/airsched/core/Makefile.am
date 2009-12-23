include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = libairsched.la

libairsched_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libairsched_la_LIBADD = \
	$(top_builddir)/airsched/basic/libbas.la \
	$(top_builddir)/airsched/bom/libbom.la \
	$(top_builddir)/airsched/factory/libfac.la \
	$(top_builddir)/airsched/command/libcmd.la \
	$(top_builddir)/airsched/service/libsvc.la
libairsched_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/core/libstdair.la \
	-version-info $(GENERIC_LIBRARY_VERSION)
