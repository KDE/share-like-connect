set(tagsProvider_SRCS
    tagsProvider.cpp
)

find_package(NepomukCore REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/dataengine)
kde4_add_plugin(sharelikeconnect_provider_tags ${tagsProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_tags ${KDE4_KDECORE_LIBS} ${NEPOMUK_CORE_LIBRARY} ${NEPOMUK_QUERY_LIBRARIES} ${SOPRANO_LIBRARIES} ${SOPRANO_CLIENT_LIBRARIES} sharelikeconnect )

install(TARGETS sharelikeconnect_provider_tags DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-tags.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
