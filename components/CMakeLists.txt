project(slccomponents)

include(KDE4Defaults)

install(DIRECTORY menuitems/ DESTINATION ${DATA_INSTALL_DIR}/plasma/slcmenuitems/)

install(FILES CommentForm.qml DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)
install(FILES Confirmation.qml DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)
install(FILES MenuArea.qml DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)
install(FILES MenuItem.qml DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)
install(FILES ServiceMenu.qml DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)
install(FILES TargetChooser.qml DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)
install(FILES SlcMenu.qml DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)

install(FILES qmldir DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/plasma/slccomponents)
