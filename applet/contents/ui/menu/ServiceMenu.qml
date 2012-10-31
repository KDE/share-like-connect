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
import "plasmapackage:/code/uiproperties.js" as UiProperties

Column {
    id: menuColumn
    spacing: UiProperties.layoutSpacing
    //width: Math.max(childrenRect.width, )


    property string resourceUrl: slcSource.data["Current Content"]["URI"]
    property string contentTitle

    onResourceUrlChanged: {
        var title = slcSource.data["Current Content"]["Title"]

        if (!title) {
            //fallback to the url
            title = String(menuColumn.resourceUrl)

            if (title.indexOf("file://") == 0) {
                title = title.substring(title.lastIndexOf("/") + 1)
            } else if (title.indexOf("http") == 0) {
                title = title.replace("http://", "");
                title = title.replace("https://", "");
                title = title.replace("www.", "");
                title = title.substring(0, title.indexOf("/"))
            } else {
                title = ""
            }
        }

        contentTitle = title
    }

    Column {
        visible: shareVisible && shareModel.count > 0 && !likeVisible && !connectVisible
        anchors {
            left: parent.left
            right: parent.right
        }

        Text {
            id: shareTitle
            text: i18n("Share")
            color: theme.textColor
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
            elide: Text.ElideMiddle
        }
        Text {
            id: shareContentTitle
            text: contentTitle
            visible: text != ''
            color: theme.textColor
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
            elide: Text.ElideRight
        }
    }

    Repeater {
        id: shareRepeater
        model: shareModel

        MenuItem {
            visible: shareVisible
            sourceName: "Share"
            resourceUrl: menuColumn.resourceUrl
        }
    }

    Column {
        visible: likeVisible && likeModel.count > 0 && !shareVisible && !connectVisible
        anchors {
            left: parent.left
            right: parent.right
        }
        Text {
            id: likeTitle
            text: i18n("Like")
            color: theme.textColor
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
        }
        Text {
            id: likeContentTitle
            text: contentTitle
            visible: text != ''
            color: theme.textColor
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
            elide: Text.ElideRight
        }
    }

    Repeater {
        id: likeRepeater
        model: likeModel

        MenuItem {
            visible: likeVisible
            sourceName: "Like"
            resourceUrl: menuColumn.resourceUrl
        }
    }

    Column {
        visible: connectVisible && connectModel.count > 0 && !shareVisible && !likeVisible
        anchors {
            left: parent.left
            right: parent.right
        }
        Text {
            id: connectTitle
            text: i18n("Connect")
            color: theme.textColor
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
            elide: Text.ElideMiddle
        }
        Text {
            id: connectContentTitle
            text: contentTitle
            visible: text != ""
            color: theme.textColor
            anchors {
                left: parent.left
                right: parent.right
            }
            horizontalAlignment: Text.AlignHCenter
            opacity: 0.6
            elide: Text.ElideRight
        }
    }

    Repeater {
        id: connectRepeater
        model: connectModel

        MenuItem {
            visible: connectVisible
            sourceName: "Connect"
            resourceUrl: menuColumn.resourceUrl
        }
    }
}
