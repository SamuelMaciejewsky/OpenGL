# Locate the myLib library
#
# This module defines the following variables:
#
# myLib_INCLUDE_DIR where to find myLib include files.
# myLib_FOUND true if both the myLib_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called myLib_ROOT which points to the root of the myLib library
# installation.

# Set directory path
set( _myLib_HEADER_SEARCH_DIRS "${CMAKE_SOURCE_DIR}/Dependencies/include" )

# Check enviornment for root search directory
set( _myLib_ENV_ROOT $ENV{myLib_ROOT} )
if( NOT myLib_ROOT AND _myLib_ENV_ROOT )
    set( myLib ROOT ${_myLib_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( myLib_ROOT )
    list ( INSERT _myLib_HEADER_SEARCH_DIRS 0 "${myLib_ROOT}/Dependencies/include" )
endif()

# Search for the header
FIND_PATH( myLib_INCLUDE_DIR "myLib/logcomponent.h"
PATHS ${_myLib_HEADER_SEARCH_DIRS} )

# Manipulate the search results
INCLUDE( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( myLib DEFAULT_MSG
myLib_INCLUDE_DIR )