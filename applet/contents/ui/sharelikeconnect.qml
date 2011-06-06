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

import Qt 4.7
import org.kde.qtextracomponents 0.1
import org.kde.plasma.mobilecomponents 0.1 as MobileComponents
import org.kde.plasma.core 0.1 as PlasmaCore

Row {
    width: 48
    height: 16
    spacing: 5
    Icon {
      icon: QIcon("system-users")
      model: shareModel
      service: "Share"
    }
    Icon {
      icon: QIcon("emblem-favorite")
      model: likeModel
      service: "Like"
    }
    Icon {
      icon: QIcon("network-connect")
      model: connectModel
      service: "Connect"
    }

    PlasmaCore.Theme {
        id: theme
    }

    PlasmaCore.Svg {
        id: lineSvg
        imagePath: "widgets/line"
    }

    PlasmaCore.DataSource {
        id: slcSource
        engine: "org.kde.sharelikeconnect"
        connectedSources: ["Current Content", "Share", "Like", "Connect"]
    }

    PlasmaCore.DataModel {
        id: shareModel
        dataSource: slcSource
        sourceFilter: "Share"
        keyRoleFilter: ".*"
    }

    PlasmaCore.DataModel {
        id: likeModel
        dataSource: slcSource
        sourceFilter: "Like"
        keyRoleFilter: ".*"
    }

    PlasmaCore.DataModel {
        id: connectModel
        dataSource: slcSource
        sourceFilter: "Connect"
        keyRoleFilter: ".*"
    }

    PlasmaCore.Dialog {
        id: dialog
        mainItem: MenuArea {
            id: menuArea
            width: 200
            height: 200
        }
    }
}

