set(sharelikeconnect_SRCS provider.cpp providerScriptEngine.cpp extension_io.cpp)

kde4_add_library(sharelikeconnect SHARED ${sharelikeconnect_SRCS})
target_link_libraries(sharelikeconnect ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS} ${QT_QTSCRIPT_LIBRARY})
install(TARGETS sharelikeconnect ${INSTALL_TARGETS_DEFAULT_ARGS})

