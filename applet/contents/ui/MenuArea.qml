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
    property alias menuModel: serviceMenu.model
    property string service
    state: "operations"
    property string pendingState: "operations"

    function runItem(x, y)
    {
        var dialogX = x-dialog.x
        var dialogY = y-dialog.y
        var item = serviceMenu.childAt(dialogX, dialogY)
        print("---------------------------" + item + " " + dialogX + " " + dialogY);
        if (item && typeof item != "undefined") {
            print("You clicked " + item)
            var posInItem = serviceMenu.mapToItem(item, dialogX, dialogY)
            item.run(posInItem.x, posInItem.y)
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
            width:main.width
        }

        CommentForm {
            width:main.width
            id: commentForm
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
                x: -main.width
                height: targetChooser.height
            }
        },
        State {
            name: "comment"
            PropertyChanges {
                target: mainWidget
                x: -main.width*2
                height: commentForm.height
            }
        }
    ]
}