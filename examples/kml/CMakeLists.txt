if(INSTALL_EXAMPLES)
  file(GLOB kml_files "${CMAKE_CURRENT_SOURCE_DIR}/*.kml")
  install(
    FILES ${kml_files}
    DESTINATION examples/kml)
endif()
