#
cmake_minimum_required (VERSION 2.6)

##
# CMake macros for the project
include (config/project_config_embeddable.cmake)

##
# Project info
set_project_names (airsched AirSched)
set_project_brief ("C++ Simulated Airline Schedule Manager Library")
set_project_versions (0 1 4)

##
# Project options
# The parameters are:
#  * whether or not the documentation must be built and installed
set_project_options (on)


#####################################
##            Packaging            ##
#####################################
#
packaging_init (${PROJECT_NAME})
packaging_set_summary ("${PROJECT_NAME} aims at providing a clean API and a simple implementation, as a C++ library, of a Airline Schedule Management System. It is intended to be used in simulated environments only: it is not designed to work in the real-world of Airline IT operations.

${PROJECT_NAME} makes an extensive use of existing open-source libraries for
increased functionality, speed and accuracy. In particular the
Boost (C++ Standard Extensions: http://www.boost.org) library is used")
packaging_set_contact ("Denis Arnaud <denis_arnaud - at - users dot sourceforge dot net>")
packaging_set_vendor ("Denis Arnaud")

#
packaging_set_other_options (TBZ2 "TBZ2;TGZ")


########################################
##            Dependencies            ##
########################################
#
get_external_libs (git "boost 1.41" mysql "soci 3.0" "stdair 0.35" doxygen)


##############################################
##           Build, Install, Export         ##
##############################################
##
# Initialise the building process
init_build ()

##
# Sub-modules
add_modules (${PROJECT_NAME})

##
# For other projects to use Airsched, install a few helpers for standard
# build/packaging systems: CMake, GNU Autotools (M4), pkgconfig/pc, 
# airsched-config
install_dev_helper_files ()

##
# Basic documentation (i.e., AUTHORS, NEWS, README, INSTALL)
install_basic_documentation ()


##########################################
##            Documentation             ##
##########################################
handle_html_doc ()

##
# Subdirs
add_subdirectory (man)


#####################################
##              Tests              ##
#####################################
##
# Test suites
add_test_suites (${PROJECT_NAME})


#######################################
##          Overall Status           ##
#######################################
display_status ()


#######################################
##         CMake Cache Storage       ##
#######################################
store_in_cache ()
