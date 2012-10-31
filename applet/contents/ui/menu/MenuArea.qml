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
import org.kde.plasma.components 0.1 as PlasmaComponents
import "plasmapackage:/code/uiproperties.js" as UiProperties


MouseArea {
    id: main

    //BEGIN: geometry
    width: Math.max(theme.defaultFont.mSize.width * 15, mainStack.currentPage ? mainStack.currentPage.implicitWidth : serviceMenu.implicitWidth)
    height: mainStack.currentPage ? mainStack.currentPage.implicitHeight : serviceMenu.implicitHeight
    //END: geometry

    //BEGIN: own properties
    //Always one of: "Share", "Like", "Connect"
    property string sourceName

    //if we need to display a confirmation message, display it here
    property string confirmationMessage

    //id of the slc provider: tags, activities, rate etc
    property string providerId


    // central access to the slc dataengine

    // models that list all the actions of Share, Like, and Connect respectively
    property QtObject shareModel: PlasmaCore.DataModel {
        dataSource: slcSource
        sourceFilter: "Share"
        keyRoleFilter: ".*"
    }

    property QtObject likeModel: PlasmaCore.DataModel {
        dataSource: slcSource
        sourceFilter: "Like"
        keyRoleFilter: ".*"
    }

    property QtObject connectModel: PlasmaCore.DataModel {
        dataSource: slcSource
        sourceFilter: "Connect"
        keyRoleFilter: ".*"
    }
    //END: own properties

    //BEGIN: mousearea properties
    hoverEnabled: !UiProperties.touchInput
    state: "operations"
    //END: mousearea properties

    //BEGIN: on*Changed
    onPositionChanged: highlightItem(mouse.x, mouse.y)
    onExited: highlightFrame.opacity = 0
    onStateChanged: {
        if (main.state == "operations") {
            mainStack.pop(serviceMenu)
            dialog.visible = false
        } else if (main.state == "targets") {
            mainStack.push(Qt.createComponent("TargetChooser.qml"))
        } else if (main.state == "comment") {
            mainStack.push(Qt.createComponent("CommentForm.qml"))
        } else if (main.state == "confirmation") {
            mainStack.push(Qt.createComponent("Confirmation.qml"))
        }
    }
    //END: on*Changed


    //BEGIN: functions
    function runItemAtGlobalPos(x, y)
    {
        var dialogX = x-dialog.x-dialog.margins.right
        var dialogY = y-dialog.y-dialog.margins.top
        runItem(dialogX, dialogY)
    }

    function runItem(x, y)
    {
        var item = serviceMenu.childAt(x, y)
        print("---------------------------" + item + " " + x + " " + y);
        if (item && typeof item != "undefined") {
            print("You clicked " + item)
            var posInItem = serviceMenu.mapToItem(item, x, y)
            item.run(posInItem.x, posInItem.y)
        }
    }

    function highlightItemAtGlobalPos(x, y)
    {
        var dialogX = x-dialog.x-dialog.margins.right
        var dialogY = y-dialog.y-dialog.margins.top
        highlightItem(dialogX, dialogY);
    }

    function highlightItem(x, y)
    {
        var item = mainStack.currentPage.childAt(x, y)

        if (item && item.sourceName) {
            var itemPos = mainStack.currentPage.mapFromItem(item, 0, 0)

            highlightFrame.x = itemPos.x
            highlightFrame.y = itemPos.y
            highlightFrame.width = mainStack.currentPage.width
            highlightFrame.height = item.height
            highlightFrame.opacity = 1
        } else {
            highlightFrame.opacity = 0
        }
    }
    //END: functions

    //BEGIN: non graphical internal
    Connections {
        target: dialog
        onVisibleChanged: {
            if (!dialog.visible) {
                highlightFrame.opacity = 0
            }
        }
    }

    ListModel {
        id: secondStepModel
    }
    //END: non graphical internal

    //BEGIN: graphical internals
    PlasmaCore.FrameSvgItem {
        id: highlightFrame
        imagePath: "widgets/viewitem"
        prefix: "selected+hover"
        opacity: 0
        visible: main.state == "operations" || main.state == "targets"
        Behavior on y {
            NumberAnimation {
                duration: highlightFrame.opacity == 0 ? 0 : 250
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on opacity {
            NumberAnimation {
                duration: 250
                easing.type: Easing.InOutQuad
            }
        }
    }

    PlasmaComponents.PageStack {
        id: mainStack
        initialPage: ServiceMenu {
            id: serviceMenu
            sourceName: main.sourceName
        }
    }
    //END: graphical internals
}
