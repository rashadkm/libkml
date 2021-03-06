file(GLOB BASE_SRCS "*.cc"
  contrib/minizip/unzip.c
  contrib/minizip/iomem_simple.c)

if(WIN32)
  list(APPEND BASE_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/contrib/strptime.c")
  list(REMOVE_ITEM BASE_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/file_posix.cc")
  if(MINGW)
      #use unicode functions from the windows api
      add_definitions(-DUNICODE -D_UNICODE)
      #supress long-long warning for mingw
      set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/time_util.cc COMPILE_FLAGS "-Wno-long-long")
  endif()
else()
  list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/file_win32.cc")
  #supress long-long warning for linux
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/zip_file.cc COMPILE_FLAGS "-Wno-long-long")
endif()

set(BASE_INCS
  attributes.h
  csv_splitter.h
  date_time.h
  color32.h
  expat_handler.h
  expat_handler_ns.h
  expat_parser.h
  file.h
  math_util.h
  memory_file.h
  mimetypes.h
  net_cache.h
  referent.h
  string_util.h
  tempfile.h
  time_util.h
  util.h
  vec3.h
  version.h
  xml_element.h
  xml_file.h
  xml_namespaces.h
  xmlns.h
  zip_file.h)


if(NOT LIBKML_URIPARSER_LIBRARY)
  set(BASE_SRCS ${BASE_SRCS} $<TARGET_OBJECTS:uriparser>)
endif()

if(NOT LIBKML_MINIZIP_LIBRARY)
  set(BASE_SRCS ${BASE_SRCS} $<TARGET_OBJECTS:minizip>)
endif()

set(base_SRCS ${BASE_SRCS} PARENT_SCOPE)
set(base_INCS ${BASE_INCS} PARENT_SCOPE)
