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
import org.kde.plasma.extras 0.1 as PlasmaExtras
import "menu"

Row {
    id: main
    property int minimumWidth: childrenRect.width
    property int minimumHeight: theme.smallIconSIze

    spacing: 4

    Component.onCompleted: {
        plasmoid.aspectRatioMode = "IgnoreAspectRatio"
    }

    // central access to the slc dataengine
    PlasmaCore.DataSource {
        id: slcSource
        engine: "org.kde.sharelikeconnect"
        connectedSources: ["Current Content", "Share", "Like", "Connect"]
    }

    Icon {
        source: "slc-share"
        service: "Share"
        model: dialog.mainItem.shareModel
    }
    Icon {
        source: "slc-like"
        service: "Like"
        model: dialog.mainItem.likeModel
    }
    Icon {
        source: "slc-connect"
        service: "Connect"
        model: dialog.mainItem.connectModel
    }

    SlcMenu {
        id: dialog
        location: plasmoid.location
    }
}

