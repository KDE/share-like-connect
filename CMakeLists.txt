cmake_minimum_required(VERSION 2.8.9)
project(share-like-connect)

find_package(KDE4 REQUIRED)
find_package(KDE4Internal REQUIRED)

include(KDE4Defaults)
include (MacroLibrary)

add_definitions(${KDE4_DEFINITIONS})
include_directories(${KDE4_INCLUDES})
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

add_subdirectory(applet)
add_subdirectory(dataengine)


install(DIRECTORY menuitems/ DESTINATION ${DATA_INSTALL_DIR}/plasma/slcmenuitems/)
