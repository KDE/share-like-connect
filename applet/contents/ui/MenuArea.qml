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
    property alias menuModel: menuRepeater.model
    property string actionName
    property string service

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
            width: 200
            height: 200
        }

        TargetChooser {
            width:200
            height: 200
        }
    }
}