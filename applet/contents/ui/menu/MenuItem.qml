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
import org.kde.plasma.extras 0.1 as PlasmaExtras

Item {
    id: menuItem

    property string resourceUrl
    property string sourceName

    implicitHeight: itemLoader.height
    implicitWidth: itemLoader.width

    PlasmaExtras.FallbackComponent {
        id: fallback
        basePath: "plasma"
        candidates: ["slcmenuitems/" + providerId,  "slcmenuitems/Default"]
    }

    Loader {
        id: itemLoader
        width: item ? Math.max(item.implicitWidth, serviceMenu.width) : 0
        height: item ? item.implicitHeight : 0

        source: fallback.filePath("Item.qml")

        MouseArea {
            anchors.fill: parent
            onClicked: {
                menuItem.run(mouse.x, mouse.y)
            }
        }
    }

    Connections {
        target: itemLoader.item
        onOperationCompleted: {
            dialog.visible = false
        }
    }

    function run(x, y)
    {
        itemLoader.item.run(x, y)
        if (itemLoader.item.operationCompleted === undefined) {
            dialog.visible = false
        }
    }
}
