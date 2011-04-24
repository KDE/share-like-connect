set(activecontetnservice_SRCS
   activecontent.cpp
   activecontentdbusinterface_p.cpp
   activecontentservice.cpp
   activecontentwatcher.cpp
)

set(activecontentservice_HEADERS
   activecontent.h
   activecontentservice.h
)

kde4_add_library(activecontentservice ${activecontetnservice_SRCS})
target_link_libraries(activecontentservice ${KDE4_KDECORE_LIBS})

install(TARGETS activecontentservice ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${activecontentservice_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/activecontentservice COMPONENT Devel)
