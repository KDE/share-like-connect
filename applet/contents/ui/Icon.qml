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

import QtQuick 1.0
import org.kde.qtextracomponents 0.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.qtextracomponents 0.1
import "plasmapackage:/code/uiproperties.js" as UiProperties

Item {
    id: iconItem

    width: appletRoot.vertical ? appletRoot.width : Math.min(appletRoot.height * UiProperties.iconProportions, theme.hugeIconSize)

    height: appletRoot.vertical ? Math.min(appletRoot.width * UiProperties.iconProportions, theme.hugeIconSize) : appletRoot.height


    property QtObject model
    property string service
    property alias source: iconLoader.source
    PlasmaCore.IconItem {
        id: iconLoader
        signal menuTriggered
        width: Math.min(parent.width, parent.height)
        height: width
        anchors.centerIn: parent

        enabled: model.count > 0 ? true : false
    }
    MouseEventListener {
        enabled: iconLoader.enabled
        anchors.fill: parent
        onPressed: {
            if (dialog.visible) {
                dialog.visible = false
            } else {
                dialog.mainItem.sourceName = iconItem.service
                dialog.open(iconItem)
            }
        }

        onPositionChanged: {
            dialog.mainItem.highlightItemAtGlobalPos(mouse.screenX, mouse.screenY)
        }

        onReleased: {
            dialog.mainItem.runItemAtGlobalPos(mouse.screenX, mouse.screenY)
        }
    }
}
