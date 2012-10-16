find_package(Kipi REQUIRED)

find_package(NepomukCore REQUIRED)

set(kipiProvider_SRCS
    kipiProvider.cpp
    kipiinterface.cpp
    kipiimagecollectionselector.cpp
    providerimagecollectionshared.cpp
    providerinfoshared.cpp
)



include_directories(${CMAKE_SOURCE_DIR}/dataengine)
kde4_add_plugin(sharelikeconnect_provider_kipi ${kipiProvider_SRCS})
target_link_libraries(sharelikeconnect_provider_kipi ${KDE4_KDECORE_LIBS} ${NEPOMUK_CORE_LIBRARY} ${NEPOMUK_QUERY_LIBRARIES} ${SOPRANO_LIBRARIES} ${SOPRANO_CLIENT_LIBRARIES} ${KIPI_LIBRARIES} ${QT_QTGUI_LIBRARY} sharelikeconnect )

install(TARGETS sharelikeconnect_provider_kipi DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES sharelikeconnect-provider-kipi.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
