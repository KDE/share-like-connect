project(LIBKTORRENT)

find_package(KDE4 REQUIRED)
find_package(KDE4Internal REQUIRED)

include(KDE4Defaults)
include (MacroLibrary)

add_definitions(${KDE4_DEFINITIONS})
include_directories(${KDE4_INCLUDES})

add_subdirectory(activecontentservice)
add_subdirectory(applet)
add_subdirectory(dataengine)
add_subdirectory(components)

