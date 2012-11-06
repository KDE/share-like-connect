set(ratingProvider_SRCS
    nepomukservicewatcher.cpp
    ratingProvider.cpp
)

find_package(NepomukCore REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/dataengine)
kde4_add_plugin(sharelikeconnect_provider_rating ${ratingProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_rating ${KDE4_KDECORE_LIBS} ${NEPOMUK_CORE_LIBRARY} ${NEPOMUK_QUERY_LIBRARIES} ${SOPRANO_LIBRARIES} ${SOPRANO_CLIENT_LIBRARIES} sharelikeconnect )

install(TARGETS sharelikeconnect_provider_rating DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-rating.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
