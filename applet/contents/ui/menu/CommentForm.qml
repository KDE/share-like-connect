/*
 *   Copyright 2011 Marco Martin <mart@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import "plasmapackage:/code/uiproperties.js" as UiProperties

Item {
    implicitWidth: mainColumn.width + 24
    implicitHeight: mainColumn.height + 24

    Column {
        id: mainColumn
        spacing: UiProperties.layoutSpacing
        anchors.centerIn: parent
        PlasmaComponents.TextArea {
            id: commentField
            implicitWidth: theme.defaultFont.mSize.width * 20
            implicitHeight: theme.defaultFont.mSize.height * 5
        }

        PlasmaComponents.Button {
            id: okButton
            text: i18n("OK")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                var service = slcSource.serviceForSource(main.sourceName)
                var operation = service.operationDescription("executeAction")
                operation["ActionName"] = main.providerId
                operation["Comment"] = commentField.text

                service.startOperationCall(operation)
                dialog.visible = false
            }
        }
    }
}
