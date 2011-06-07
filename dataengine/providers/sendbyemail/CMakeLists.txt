set(sendbyemailProvider_SRCS
    sendbyemailProvider.cpp
)

find_package(Nepomuk REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/dataengine)
kde4_add_plugin(sharelikeconnect_provider_sendbyemail ${sendbyemailProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_sendbyemail ${KDE4_KDECORE_LIBS} ${NEPOMUK_LIBRARIES} ${NEPOMUK_QUERY_LIBRARIES} ${SOPRANO_LIBRARIES} ${SOPRANO_CLIENT_LIBRARIES} sharelikeconnect)

install(TARGETS sharelikeconnect_provider_sendbyemail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-sendbyemail.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
