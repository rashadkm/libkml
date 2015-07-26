ExternalProject_Add(MINIZIP
  PREFIX MINIZIP
  URL "https://docs.google.com/uc?export=download&id=0BzqbMPUw_a8uVHF3S2sxX21vNWM"
  URL_MD5 d5f74eff74e03e497ea60b2c43623416
  BINARY_DIR ${CMAKE_BINARY_DIR}/MINIZIP/build
  DOWNLOAD_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/download-minizip.cmake
  DEPENDS ${MINIZIP_DEPENDS}
  CMAKE_CACHE_ARGS
  -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR}
  -DCMAKE_BUILD_TYPE:STRING=Release
  -DZLIB_INCLUDE_DIR:PATH=${ZLIB_INCLUDE_DIR}
  -DZLIB_LIBRARY:FILEPATH=${ZLIB_LIBRARY}
  -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS} )

file(WRITE ${CMAKE_BINARY_DIR}/download-minizip.cmake
  "
 file(DOWNLOAD
  \"https://docs.google.com/uc?export=download&id=0BzqbMPUw_a8uVHF3S2sxX21vNWM\"
  \"${CMAKE_BINARY_DIR}/MINIZIP/src/kml-minizip.tar.gz\"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=d5f74eff74e03e497ea60b2c43623416
  # no TIMEOUT
  STATUS status
  LOG log)
 execute_process(COMMAND \"${CMAKE_COMMAND}\" -E tar xfz \"${CMAKE_BINARY_DIR}/MINIZIP/src/kml-minizip.tar.gz\" -C \"${CMAKE_BINARY_DIR}/MINIZIP/src\")
 file(RENAME \"${CMAKE_BINARY_DIR}/MINIZIP/src/minizip\" \"${CMAKE_BINARY_DIR}/MINIZIP/src/MINIZIP\")
")

include_project_vars(MINIZIP)
