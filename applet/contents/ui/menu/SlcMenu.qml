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
import org.kde.qtextracomponents 0.1
import org.kde.plasma.core 0.1 as PlasmaCore

PlasmaCore.Dialog {
    id: dialog
    property Item parentItem
    windowFlags: Qt.Popup

    mainItem: MenuArea {
        id: menuArea
    }

    function open(item)
    {
        parentItem = item
        dialog.x = -1000
        dialog.y = -1000
        visible = true
    }

    function adjustPosition()
    {
        var pos = dialog.popupPosition(parentItem, Qt.AlignCenter)
        dialog.x = pos.x
        dialog.y = pos.y
    }

    onHeightChanged: {
        adjustPosition()
    }

    onWidthChanged: {
        adjustPosition()
    }

    onVisibleChanged: {
        // setAttribute(Qt.WA_X11NetWmWindowTypePopupMenu, true)
        if (!visible) {
            menuArea.state = "operations"
        }
    }
}
