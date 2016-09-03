# Find the UriParser library
# Defines:

#  URIPARSER_INCLUDE_DIR - uriparser include directory
#  URIPARSER_LIBRARY     - uriparser library file
#  URIPARSER_FOUND       - TRUE if uriparser is found

set(URIPARSER_FOUND FALSE)
find_path(URIPARSER_INCLUDE_DIR NAMES Uri.h PATH_SUFFIXES uriparser)
set(URIPARSER_INCLUDE_DIR ${URIPARSER_INCLUDE_DIR}/uriparser CACHE PATH "uriparser includes")

find_library(URIPARSER_LIBRARY NAMES uriparser)
if (URIPARSER_INCLUDE_DIR AND URIPARSER_LIBRARY)
  set(URIPARSER_FOUND TRUE)
endif ()

if(NOT URIPARSER_FIND_QUIETLY)
  include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
  find_package_handle_standard_args(URIPARSER 
    REQUIRED_VARS URIPARSER_LIBRARY URIPARSER_INCLUDE_DIR
    VERSION_VAR URIPARSER_VERSION_STRING)
endif()
