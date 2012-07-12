
find_package(Soprano)
  macro_log_feature(Soprano_FOUND "Soprano" "Semantic Desktop Storing" "http://soprano.sourceforge.net"
  TRUE "${SOPRANO_MIN_VERSION}" "Soprano is needed for Nepomuk")

set(activitiesProvider_SRCS
    activitiesProvider.cpp
)

find_package(NepomukCore REQUIRED)
find_package(KActivities REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/dataengine)
kde4_add_plugin(sharelikeconnect_provider_activities ${activitiesProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_activities ${KDE4_KDECORE_LIBS} ${NEPOMUK_CORE_LIBRARY} ${NEPOMUK_QUERY_LIBRARIES} ${SOPRANO_LIBRARIES} ${SOPRANO_CLIENT_LIBRARIES} ${KACTIVITIES_LIBS} sharelikeconnect)

install(TARGETS sharelikeconnect_provider_activities DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-activities.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
