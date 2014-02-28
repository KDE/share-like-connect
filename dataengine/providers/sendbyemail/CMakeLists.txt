set(sendbyemailProvider_SRCS
    sendbyemailProvider.cpp
)


include_directories(${CMAKE_SOURCE_DIR}/dataengine)
add_library(sharelikeconnect_provider_sendbyemail ${sendbyemailProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_sendbyemail
    sharelikeconnect)

install(TARGETS sharelikeconnect_provider_sendbyemail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-sendbyemail.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
