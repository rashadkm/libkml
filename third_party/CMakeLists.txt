find_package(Boost)
if(Boost_FOUND)
  message(STATUS "Found Boost: ${Boost_VERSION}")
  set(LIBKML_BOOST_INCLUDE_DIRS "${Boost_INCLUDE_DIRS}" CACHE INTERNAL "")
else()
  message(STATUS "Boost not found. we will use internal copy of Boost")
  set(LIBKML_BOOST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/boost CACHE INTERNAL "")
endif()

include_directories(${LIBKML_BOOST_INCLUDE_DIRS})

find_package(EXPAT)
if(EXPAT_FOUND)
  set(LIBKML_EXPAT_INCLUDE_DIRS ${EXPAT_INCLUDE_DIRS} CACHE INTERNAL "")
  set(LIBKML_EXPAT_LIBRARY ${EXPAT_LIBRARY})
else()
  message(STATUS "Expat not found. we will use internal copy of expat")
  add_subdirectory(expat)
  set(LIBKML_EXPAT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/expat/src CACHE INTERNAL "")

  set(LIBKML_EXPAT_LIBRARY ${${CMAKE_BINARY_DIR}/lib/libexpat.so})
endif()

include_directories(${LIBKML_EXPAT_INCLUDE_DIRS})


find_package(UriParser)
if(URIPARSER_FOUND)
  set(LIBKML_URIPARSER_INCLUDE_DIRS ${URIPARSER_INCLUDE_DIRS} CACHE INTERNAL "")
  set(LIBKML_URIPARSER_LIBRARY ${URIPARSER_LIBRARY})
else()  
  message(STATUS "UriParser not found. we will use internal copy of expat")
  file(GLOB LIBKML_URIPARSER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/uriparser/src/*.c)
  set(LIBKML_URIPARSER_INCLUDE_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/uriparser/include CACHE INTERNAL "")
  include_directories(${LIBKML_URIPARSER_INCLUDE_DIRS})
  add_library(kml_uriparser OBJECT ${LIBKML_URIPARSER_SOURCES})
  set(LIBKML_URIPARSER_LIBRARY "$<TARGET_OBJECTS:kml_uriparser>")
endif()

