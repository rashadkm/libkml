

add_library(helloutil STATIC print.cc)
target_link_libraries(helloutil ${KML_MINIZIP_LIBRARY})

add_executable(createkml createkml.cc)
target_link_libraries(createkml libkml)

add_executable(circlegen circlegen.cc)
target_link_libraries(circlegen libkml)

add_executable(checklinks checklinks.cc)
target_link_libraries(checklinks libkml)

add_executable(countkml countkml.cc)
target_link_libraries(countkml libkml)

add_executable(helloattrs helloattrs.cc)
target_link_libraries(helloattrs libkml)

add_executable(helloenum helloenum.cc)
target_link_libraries(helloenum libkml)

add_executable(hellofeatures hellofeatures.cc)
add_dependencies(hellofeatures helloutil)
target_link_libraries(hellofeatures libkml helloutil)

add_executable(hellofolder hellofolder.cc)
target_link_libraries(hellofolder libkml)

add_executable(hellogeometry hellogeometry.cc)
target_link_libraries(hellogeometry libkml)

add_executable(hellohref hellohref.cc)
add_dependencies(hellohref helloutil)
target_link_libraries(hellohref libkml helloutil)

add_executable(hellokmz hellokmz.cc)
target_link_libraries(hellokmz libkml)

add_executable(helloregion helloregion.cc)
add_dependencies(helloregion helloutil)
target_link_libraries(helloregion libkml  helloutil)

add_executable(helloworld helloworld.cc)
target_link_libraries(helloworld libkml)

add_executable(parsekml parsekml.cc)
target_link_libraries(parsekml libkml)

add_executable(parsens parsens.cc)
target_link_libraries(parsens libkml)

add_executable(prettykml prettykml.cc)
target_link_libraries(prettykml libkml)

add_executable(printgeometry printgeometry.cc)
target_link_libraries(printgeometry libkml)

add_executable(sharedstyles sharedstyles.cc)
target_link_libraries(sharedstyles libkml)

add_executable(simplifylines simplifylines.cc)
target_link_libraries(simplifylines libkml)

add_executable(sortplacemarks sortplacemarks.cc)
target_link_libraries(sortplacemarks libkml)


if(INSTALL_EXAMPLES)
file(GLOB eg_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")
install(FILES ${eg_files}  DESTINATION ${KML_EXAMPLES_DIR} COMPONENT Development)
install(FILES print.h
  DESTINATION ${KML_EXAMPLES_DIR}
  COMPONENT Examples)
endif()
