
include_directories(${LIBKML_EXPAT_INCLUDE_DIRS})
include_directories(${LIBKML_BOOST_INCLUDE_DIRS})

include_directories(${LIBKML_ZLIB_INCLUDE_DIRS})

include_directories(${LIBKML_URIPARSER_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/kml)

add_subdirectory(kml)
if(WITH_SWIG)
add_subdirectory(swig)
endif()

set(LIBKML_TARGETS "${LIBKML_TARGETS}" PARENT_SCOPE)
