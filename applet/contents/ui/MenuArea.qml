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
    height: 200
    property alias menuModel: serviceMenu.model
    property string service
    state: "operations"
    property string pendingState: "operations"

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
            width: 200
            height: 200
        }

        TargetChooser {
            id: targetChooser
            width:200
            height: 200
        }

        CommentForm {
            width:200
            height: 200
            id: commentForm
        }
    }

    states: [
        State {
            name: "operations"
            PropertyChanges {
                target: mainWidget
                x: 0
            }
        },
        State {
            name: "targets"
            PropertyChanges {
                target: mainWidget
                x: -200
            }
        },
        State {
            name: "comment"
            PropertyChanges {
                target: mainWidget
                x: -400
            }
        }
    ]
}