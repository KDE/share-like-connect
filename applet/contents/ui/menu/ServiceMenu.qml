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

    //BEGIN: own properties


    //Uri of the resource the current focused app s exposing
    property string resourceUrl: slcSource.data["Current Content"]["URI"]

    //The source we want to expse operations: Share, Like or Connect
    property string sourceName
    //END: own properties

    //BEGIN: Column properties
    spacing: UiProperties.layoutSpacing
    //END: Column properties

    //BEGIN: on*Changed
    //switch all needs switching to share, like or connect
    onSourceNameChanged: {
        switch (sourceName) {
        case "Share": {
            servicesRepeater.model = main.shareModel;
            break;
        }
        case "Like": {
            servicesRepeater.model = main.likeModel;
            break;
        }
        default:
        case "Connect": {
            servicesRepeater.model = main.connectModel;
            break;
        }
        }
    }
    //END: on*Changed

    //BEGIN: graphical internal elements
    Column {
        anchors {
            left: parent.left
            right: parent.right
        }

        Text {
            id: shareTitle
            text: appletRoot.title
            color: theme.textColor
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.6
            elide: Text.ElideMiddle
        }
    }

    Repeater {
        id: servicesRepeater
        model: likeModel

        MenuItem {
            sourceName: menuColumn.sourceName
            resourceUrl: menuColumn.resourceUrl
        }
    }
    //END: graphical internal elements
}
