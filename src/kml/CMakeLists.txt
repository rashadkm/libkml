set(LIBKML_SRCS)
set(LIBKML_INCS)

add_subdirectory(base)
add_subdirectory(dom)
add_subdirectory(engine)
add_subdirectory(convenience)
add_subdirectory(xsd)
add_subdirectory(regionator)

add_library(libkml ${LIBKML_SRCS})
target_link_libraries(libkml ${LIBKML_LINK_LIBRARIES})

install(  FILES dom.h engine.h
          DESTINATION ${INCLUDE_INSTALL_DIR}
          COMPONENT Development)

        
