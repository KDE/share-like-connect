set(bookmarksProvider_SRCS
    bookmarksProvider.cpp
)

find_package(Nepomuk REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/dataengine)
kde4_add_plugin(sharelikeconnect_provider_bookmarks ${bookmarksProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_bookmarks ${KDE4_KDECORE_LIBS} ${NEPOMUK_LIBRARIES} ${NEPOMUK_QUERY_LIBRARIES} ${SOPRANO_LIBRARIES} ${SOPRANO_CLIENT_LIBRARIES} sharelikeconnect)

install(TARGETS sharelikeconnect_provider_bookmarks DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-bookmarks.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
