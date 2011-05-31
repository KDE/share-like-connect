set(activitiesProvider_SRCS
    activitiesProvider.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/dataengine)
kde4_add_plugin(sharelikeconnect_provider_activities ${activitiesProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_activities ${KDE4_KDECORE_LIBS} ${NEPOMUK_LIBRARIES} sharelikeconnect)

install(TARGETS sharelikeconnect_provider_activities DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-activities.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
