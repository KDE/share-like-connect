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
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 1.0
import org.kde.qtextracomponents 0.1
import org.kde.plasma.core 0.1 as PlasmaCore

Column {
    id: menuColumn
    width:200
    height: 200
    spacing: 5
    property alias menuModel: menuRepeater.model

    Repeater {
        id: menuRepeater
        model: shareModel

        Text {
            text: name
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var service = activitySource.serviceForSource("Connect")
                    var operation = service.operationDescription("executeAction")
                    operatin["ActionName"] = providerId

                    service.startOperationCall(operation)
                    slcSource.data["Current Content"]["URI"]
                }
            }
        }

        /*MobileComponents.MenuItem {
            id: menuItem
            resourceUrl: slcSource.data["Current Content"]["URI"]
        }*/
    }
}
