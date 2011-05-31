set(sharelikeconnect_SRCS
    currentcontenttracker.cpp
    sharelikeconnect.cpp
    sharecontainer.cpp
    shareservice/shareservice.cpp
    shareservice/sharejob.cpp
)

kde4_add_plugin(plasma_dataengine_sharelikeconnect ${sharelikeconnect_SRCS})
target_link_libraries(plasma_dataengine_sharelikeconnect ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS})

install(TARGETS plasma_dataengine_sharelikeconnect DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-dataengine-sharelikeconnect.desktop DESTINATION ${SERVICES_INSTALL_DIR} )

install(FILES shareservice/shareservice.operations
        DESTINATION ${DATA_INSTALL_DIR}/plasma/services)
