cmd_h_sources = $(top_srcdir)/airsched/command/CmdAbstract.hpp \
				$(top_srcdir)/airsched/command/Simulator.hpp \
				$(top_srcdir)/airsched/command/FileMgr.hpp \
				$(top_srcdir)/airsched/command/ScheduleParser.hpp \
				$(top_srcdir)/airsched/command/ScheduleParserHelper.hpp \
				$(top_srcdir)/airsched/command/NetworkGenerator.hpp \
				$(top_srcdir)/airsched/command/InventoryGenerator.hpp \
				$(top_srcdir)/airsched/command/TravelSolutionProvider.hpp
cmd_cc_sources = $(top_srcdir)/airsched/command/CmdAbstract.cpp \
				$(top_srcdir)/airsched/command/Simulator.cpp \
				$(top_srcdir)/airsched/command/FileMgr.cpp \
				$(top_srcdir)/airsched/command/ScheduleParser.cpp \
				$(top_srcdir)/airsched/command/ScheduleParserHelper.cpp \
				$(top_srcdir)/airsched/command/NetworkGenerator.cpp \
				$(top_srcdir)/airsched/command/InventoryGenerator.cpp \
				$(top_srcdir)/airsched/command/TravelSolutionProvider.cpp
