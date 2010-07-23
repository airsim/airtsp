# airsched/batches
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in


# Binaries (batches)
bin_PROGRAMS = airsched

airsched_SOURCES = $(airsched_batches_h_sources) $(airsched_batches_cc_sources)
airsched_CXXFLAGS = $(BOOST_CFLAGS)
airsched_LDADD = 
airsched_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/core/libstdair.la \
	$(top_builddir)/airsched/core/libairsched.la
