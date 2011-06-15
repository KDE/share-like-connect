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
    spacing: 8

    PlasmaCore.FrameSvgItem {
        imagePath: "widgets/extender-dragger"
        prefix: "grouped"
        visible: shareVisible&&shareModel.count>0
        anchors {
            left: parent.left
            right: parent.right
        }
        height: childrenRect.height+margins.top+margins.bottom
        Text {
            y: parent.margins.top
            text: i18n("Share")
            color: theme.textColor
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
        }
    }
    Repeater {
        id: shareRepeater
        model: shareModel

        MenuItem {
            visible: shareVisible
            sourceName: "Share"
            resourceUrl: slcSource.data["Current Content"]["URI"]
        }
    }

    PlasmaCore.FrameSvgItem {
        imagePath: "widgets/extender-dragger"
        prefix: "grouped"
        visible: likeVisible&&likeModel.count>0
        anchors {
            left: parent.left
            right: parent.right
        }
        height: childrenRect.height+margins.top+margins.bottom
        Text {
            y: parent.margins.top
            text: i18n("Like")
            color: theme.textColor
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
        }
    }

    Repeater {
        id: likeRepeater
        model: likeModel

        MenuItem {
            visible: likeVisible
            sourceName: "Like"
            resourceUrl: slcSource.data["Current Content"]["URI"]
        }
    }

    PlasmaCore.FrameSvgItem {
        imagePath: "widgets/extender-dragger"
        prefix: "grouped"
        visible: connectVisible&&connectModel.count>0
        anchors {
            left: parent.left
            right: parent.right
        }
        height: childrenRect.height+margins.top+margins.bottom
        Text {
            y: parent.margins.top
            text: i18n("Connect")
            color: theme.textColor
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
        }
    }
    Repeater {
        id: connectRepeater
        model: connectModel

        MenuItem {
            visible: connectVisible
            sourceName: "Connect"
            resourceUrl: slcSource.data["Current Content"]["URI"]
        }
    }
}
