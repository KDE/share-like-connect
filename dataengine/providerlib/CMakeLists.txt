set(sharelikeconnect_SRCS provider.cpp providerScriptEngine.cpp extension_io.cpp)

add_library(sharelikeconnect SHARED ${sharelikeconnect_SRCS})
target_link_libraries(sharelikeconnect
    KF5::Plasma
    KF5::KIOCore
    KF5::KIOWidgets
    KF5::KDE4Support
    Qt5::Script)
install(TARGETS sharelikeconnect ${INSTALL_TARGETS_DEFAULT_ARGS})

