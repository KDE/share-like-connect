set(sharelikeconnect_SRCS provider.cpp)

kde4_add_library(sharelikeconnect SHARED ${sharelikeconnect_SRCS})
target_link_libraries(sharelikeconnect ${QT_QTCORE_LIBRARY})
install(TARGETS sharelikeconnect ${INSTALL_TARGETS_DEFAULT_ARGS})

set(sharelikeconnectengine_SRCS
    contenttracker.cpp
    sharelikeconnect.cpp
    shareservice/shareservice.cpp
    shareservice/sharejob.cpp
)

kde4_add_plugin(plasma_dataengine_sharelikeconnect ${sharelikeconnectengine_SRCS})
target_link_libraries(plasma_dataengine_sharelikeconnect ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS} sharelikeconnect)

install(TARGETS plasma_dataengine_sharelikeconnect DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-dataengine-sharelikeconnect.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install(FILES plasma-sharelikeconnect-provider.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR} )

install(FILES shareservice/shareservice.operations DESTINATION ${DATA_INSTALL_DIR}/plasma/services)

add_subdirectory(providers)

