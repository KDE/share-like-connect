include_directories(${CMAKE_CURRENT_SOURCE_DIR}/providerlib)
add_subdirectory(providerlib)
add_subdirectory(providers)

set(sharelikeconnectengine_SRCS
    contenttracker.cpp
    packageStructure.cpp
    sharelikeconnect.cpp
    slcservice/slcservice.cpp
    slcservice/slcjob.cpp
)

set(activitymanagerslc_xml org.kde.ActivityManager.SLC.xml)
QT4_ADD_DBUS_INTERFACE(sharelikeconnectengine_SRCS ${activitymanagerslc_xml} activitymanagerslc_interface)

kde4_add_plugin(plasma_dataengine_sharelikeconnect ${sharelikeconnectengine_SRCS})
target_link_libraries(plasma_dataengine_sharelikeconnect ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS} sharelikeconnect)

install(TARGETS plasma_dataengine_sharelikeconnect DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-dataengine-sharelikeconnect.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install(FILES plasma-sharelikeconnect-provider.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR} )

install(FILES slcservice/slcservice.operations DESTINATION ${DATA_INSTALL_DIR}/plasma/services)

