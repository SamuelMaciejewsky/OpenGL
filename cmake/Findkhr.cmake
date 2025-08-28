# Locate the khr library
#
# This module defines the following variables:
#
# KHR_INCLUDE_DIR where to find glfw include files.
# KHR_FOUND true if both the KHR_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called KHR_ROOT which points to the root of the khr library
# installation.

# Set directory path
set( _khr_HEADER_SEARCH_DIRS "${CMAKE_SOURCE_DIR}/Dependencies/include" )

# Check enviornment for root search directory
set( _khr_ENV_ROOT $ENV{KHR_ROOT} )
if( NOT KHR_ROOT AND _khr_ENV_ROOT )
    set( KHR ROOT ${_khr_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( KHR_ROOT )
    list ( INSERT _khr_HEADER_SEARCH_DIRS 0 "${KHR_ROOT}/Dependencies/include" )
endif()

# Search for the header
FIND_PATH( KHR_INCLUDE_DIR "KHR/khrplatform.h"
PATHS ${_khr_HEADER_SEARCH_DIRS} )

# Manipulate the search results
INCLUDE( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( KHR DEFAULT_MSG
KHR_INCLUDE_DIR )