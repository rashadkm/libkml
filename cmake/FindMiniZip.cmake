# Find the Minizip library
# Defines:

#  MINIZIP_INCLUDE_DIR - minizip include directory
#  MINIZIP_LIBRARY     - minizip library file
#  MINIZIP_FOUND       - TRUE if minizip is found

set(MINIZIP_FOUND FALSE)
find_path(MINIZIP_INCLUDE_DIR NAMES unzip.h PATH_SUFFIXES minizip)
set(MINIZIP_INCLUDE_DIR ${MINIZIP_INCLUDE_DIR}/minizip CACHE PATH "MiniZip includes")

find_library(MINIZIP_LIBRARY NAMES minizip)
if (MINIZIP_INCLUDE_DIR AND MINIZIP_LIBRARY)
  set(MINIZIP_FOUND TRUE)
endif ()

if(NOT MINIZIP_FIND_QUIETLY)
  include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
  find_package_handle_standard_args(MINIZIP 
    REQUIRED_VARS MINIZIP_LIBRARY MINIZIP_INCLUDE_DIR
    VERSION_VAR MINIZIP_VERSION_STRING)
endif()
