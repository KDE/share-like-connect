set(sharelikeconnect_SRCS
    sharelikeconnect.cpp
    contenttracker.cpp
)

set(activitymanagerslc_xml org.kde.ActivityManager.SLC.xml)
QT5_ADD_DBUS_INTERFACE(sharelikeconnect_SRCS ${activitymanagerslc_xml} activitymanagerslc_interface)

add_library(plasma_applet_sharelikeconnect MODULE ${sharelikeconnect_SRCS})

kcoreaddons_desktop_to_json(plasma_applet_sharelikeconnect package/metadata.desktop)


target_link_libraries(plasma_applet_sharelikeconnect
                      Qt5::Gui
                      Qt5::DBus
                      Qt5::Qml
                      KF5::Plasma
                      KF5::I18n
                      KF5::WindowSystem)


install(TARGETS plasma_applet_sharelikeconnect DESTINATION ${PLUGIN_INSTALL_DIR})
#install(FILES plasma-sharelikeconnect-default.desktop DESTINATION ${SERVICES_INSTALL_DIR})

plasma_install_package(package org.kde.plasma.sharelikeconnect)

