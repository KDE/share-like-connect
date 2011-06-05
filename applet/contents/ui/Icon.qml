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


QIconItem {
    id: iconItem
    signal menuTriggered
    width: height
    property QtObject model
    enabled: model.count>0?true:false
    opacity: enabled?1:0.4
    anchors {
        top: parent.top
        bottom: parent.bottom
    }

    MouseArea {
        enabled: iconItem.enabled
        anchors.fill: parent
        onPressed: {
            if (dialog.visible) {
                dialog.visible = false
            } else {
                menuArea.menuModel = iconItem.model
                var pos = dialog.popupPosition(iconItem)
                dialog.x = pos.x
                dialog.y = pos.y
                dialog.visible = true
            }
        }
    }
}
