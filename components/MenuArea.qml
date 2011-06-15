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


Item {
    id: main
    clip: true
    //FIXME: remove hardcoded sizes
    width: 200
    height: mainWidget.height
    property bool shareVisible: true
    property bool likeVisible: true
    property bool connectVisible: true
    state: "operations"
    property string pendingState: "operations"
    property string confirmationMessage
    property string providerId
    property string sourceName

    property QtObject slcSource: PlasmaCore.DataSource {
        engine: "org.kde.sharelikeconnect"
        connectedSources: ["Current Content", "Share", "Like", "Connect"]
    }

    property QtObject shareModel: PlasmaCore.DataModel {
        id: shareModel
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


    function runItem(x, y)
    {
        var dialogX = x-dialog.x-dialog.margins.right
        var dialogY = y-dialog.y-dialog.margins.top
        var item = serviceMenu.childAt(dialogX, dialogY)
        print("---------------------------" + item + " " + dialogX + " " + dialogY);
        if (item && typeof item != "undefined") {
            print("You clicked " + item)
            var posInItem = serviceMenu.mapToItem(item, dialogX, dialogY)
            item.run(posInItem.x, posInItem.y)
        }
    }

    function highlightItem(x, y)
    {
        var dialogX = x-dialog.x-dialog.margins.right
        var dialogY = y-dialog.y-dialog.margins.top
        var item = serviceMenu.childAt(dialogX, dialogY)

        if (item) {
            var itemPos = serviceMenu.mapFromItem(item, 0, 0)
            highlightFrame.x = itemPos.x
            highlightFrame.y = itemPos.y
            highlightFrame.width = serviceMenu.width
            highlightFrame.height = item.height
            highlightFrame.opacity = 1
        } else {
            highlightFrame.opacity = 0
        }
    }

    PlasmaCore.Svg {
        id: lineSvg
        imagePath: "widgets/line"
    }

    PlasmaCore.FrameSvgItem {
        id: highlightFrame
        imagePath: "widgets/viewitem"
        prefix: "hover"
        opacity: 0
        visible: main.state == "operations"
        Behavior on y {
            NumberAnimation {
                duration: 250
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

    SequentialAnimation {
        id: feedbackMessageAnimation
        property Item target

        NumberAnimation {
            target: feedbackMessageAnimation.target
            properties: "scale"
            to: 2
            duration: 200
            easing.type: "OutCubic"
        }
        PauseAnimation {
            duration: 100
        }
        NumberAnimation {
            target: feedbackMessageAnimation.target
            properties: "scale"
            to: 1
            duration: 250
            easing.type: "OutElastic"
        }
        ScriptAction {
            script: {
                main.state = main.pendingState
                if (main.state == "operations") {
                    dialog.visible = false
                }
            }
        }
    }

    ListModel {
        id: secondStepModel
    }

    Row {
        id: mainWidget
        Behavior on x {
            NumberAnimation {
                duration: 250
                easing.type: Easing.InOutQuad
            }
        }
        ServiceMenu {
            id: serviceMenu
            width: main.width
        }

        TargetChooser {
            id: targetChooser
            visible: main.state == "targets"
            width:main.width
        }

        CommentForm {
            id: commentForm
            visible: main.state == "comment"
            width:main.width
        }

        Confirmation {
            id: confirmation
            width:main.width
        }
    }

    states: [
        State {
            name: "operations"
            PropertyChanges {
                target: mainWidget
                x: 0
                height: serviceMenu.height
            }
        },
        State {
            name: "targets"
            PropertyChanges {
                target: mainWidget
                x: -targetChooser.x
                height: targetChooser.height
            }
        },
        State {
            name: "comment"
            PropertyChanges {
                target: mainWidget
                x: -commentForm.x
                height: commentForm.height
            }
        },
        State {
            name: "confirmation"
            PropertyChanges {
                target: mainWidget
                x: -confirmation.x
                height: confirmation.height
            }
        }
    ]
}