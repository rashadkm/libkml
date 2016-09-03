
find_package(Boost QUIET)
if(Boost_FOUND)
  message(STATUS "Found Boost: ${Boost_VERSION}")
  set(LIBKML_BOOST_INCLUDE_DIRS "${Boost_INCLUDE_DIRS}" CACHE INTERNAL "")
else()
  message(STATUS "Boost not found. We will use third_party/boost")
  set(LIBKML_BOOST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/boost CACHE INTERNAL "")
endif()

find_package(EXPAT QUIET)
if(EXPAT_FOUND)
  set(LIBKML_EXPAT_INCLUDE_DIRS ${EXPAT_INCLUDE_DIRS} CACHE INTERNAL "")
  set(LIBKML_EXPAT_LIBRARY ${EXPAT_LIBRARY})
else()
  message(STATUS "Expat not found. We will use third_party/expat")
  add_subdirectory(expat)
  set(LIBKML_EXPAT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/expat/lib CACHE INTERNAL "")
  set(LIBKML_EXPAT_LIBRARY ${CMAKE_BINARY_DIR}/lib/expat.lib CACHE INTERNAL "")
endif()

find_package(ZLIB QUIET)
if(ZLIB_FOUND)
  set(LIBKML_ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS} CACHE INTERNAL "")
  set(LIBKML_ZLIB_LIBRARY ${ZLIB_LIBRARY})
else()
  message(STATUS "zlib not found.  We will use third_party/zlib")
  add_subdirectory(zlib)
  set(LIBKML_ZLIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/;${CMAKE_CURRENT_SOURCE_DIR}/zlib;${CMAKE_CURRENT_BINARY_DIR}/zlib" CACHE INTERNAL "")
  list(APPEND LIBKML_ZLIB_INCLUDE_DIRS )
  set(LIBKML_ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/lib/zlibd.lib CACHE INTERNAL "")
endif()

find_package(URIPARSER QUIET)
if(URIPARSER_FOUND)
  set(LIBKML_URIPARSER_INCLUDE_DIRS ${URIPARSER_INCLUDE_DIR} CACHE INTERNAL "")
  set(LIBKML_URIPARSER_LIBRARY ${URIPARSER_LIBRARY})
else()  
  message(STATUS "UriParser not found. We will use third_party/uriparser")
  file(GLOB LIBKML_URIPARSER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/uriparser/src/*.c)
  set(LIBKML_URIPARSER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/uriparser/include CACHE INTERNAL "")
  include_directories(${LIBKML_URIPARSER_INCLUDE_DIRS})
  add_library(uriparser OBJECT ${LIBKML_URIPARSER_SOURCES})
endif()


find_package(MINIZIP QUIET)
if(MINIZIP_FOUND)
  set(LIBKML_MINIZIP_INCLUDE_DIRS ${MINIZIP_INCLUDE_DIR} CACHE INTERNAL "")
  set(LIBKML_MINIZIP_LIBRARY ${MINIZIP_LIBRARY})
else()  
  message(STATUS "minizip not found. We will use third_party/zlib/contrib/minizip")
  set(LIBKML_MINIZIP_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/unzip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/zip.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/iowin32.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/mztools.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip/ioapi.c 
    )
  set(LIBKML_MINIZIP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/zlib/contrib/minizip CACHE INTERNAL "")

  include_directories(${LIBKML_ZLIB_INCLUDE_DIRS})

  include_directories(${LIBKML_MINIZIP_INCLUDE_DIRS})

  add_library(minizip OBJECT ${LIBKML_MINIZIP_SOURCES})
endif()


