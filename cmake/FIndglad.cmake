# Locate the glad library
#
# This module defines the following variables:
#
# GLAD_INCLUDE_DIR where to find glad include files.
# GLAD_FOUND true if both the GLAD_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called GLAD_ROOT which points to the root of the glad library
# installation.

# Set directory path
set( _glad_HEADER_SEARCH_DIRS "${CMAKE_SOURCE_DIR}/Dependencies/include" )

# Check enviornment for root search directory
set( _glad_ENV_ROOT $ENV{GLAD_ROOT} )
if( NOT GLAD_ROOT AND _glad_ENV_ROOT )
    set( GLAD ROOT ${_glad_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( GLAD_ROOT )
    list ( INSERT _glad_HEADER_SEARCH_DIRS 0 "${GLAD_ROOT}/Dependencies/include" )
endif()

# Search for the header
FIND_PATH( GLAD_INCLUDE_DIR "glad/glad.h"
PATHS ${_glad_HEADER_SEARCH_DIRS} )

# Manipulate the search results
INCLUDE( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( GLAD DEFAULT_MSG
GLAD_INCLUDE_DIR )