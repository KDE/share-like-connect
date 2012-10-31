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

Flow {
    id: appletRoot

    //BEGIN: own properties
    property int minimumWidth: vertical ? theme.smallIconSize : shareIcon.width * 3 + 8
    property int minimumHeight: vertical ? shareIcon.height * 3 + 8 : theme.smallIconSIze

    //Title of the menu: derived from the resource uri
    property string title

    //true if we are on a vertical formfactor:
    // we can't just bind to plasmoid.formfactor because since it has been registered with QScript
    property bool vertical
    //END: own properties


    //BEGIN: Flow properties
    spacing: 4
    //END: Flow properties


    //BEGIN: non graphical implementation objects
    Component.onCompleted: {
        plasmoid.aspectRatioMode = "IgnoreAspectRatio"
    }

    Connections {
        target: plasmoid
        onFormFactorChanged: vertical = (plasmoid.formFactor == Vertical)
    }

    // central access to the slc dataengine
    PlasmaCore.DataSource {
        id: slcSource
        engine: "org.kde.sharelikeconnect"
        connectedSources: ["Current Content", "Share", "Like", "Connect"]

        //some heuristic to know what to display as title based on url
        onDataChanged: {
            var text = slcSource.data["Current Content"]["Title"]

            if (!text) {
                //fallback to the url
                text = String(slcSource.data["Current Content"]["URI"]);

                if (text.indexOf("file://") == 0) {
                    text = text.substring(text.lastIndexOf("/") + 1);
                } else if (text.indexOf("http") == 0) {
                    text = text.replace("http://", "");
                    text = text.replace("https://", "");
                    text = text.replace("www.", "");
                    text = text.substring(0, text.indexOf("/"));;
                } else {
                    text = "";
                }
            }

            title = text;
        }
    }

    PlasmaCore.Svg {
        id: svgIcon
        //this has to be done in an imperative way because of Plasma::Svg api
        Component.onCompleted: {
            svgIcon.resize(theme.enormousIconSize, theme.enormousIconSize)
            shareToolTip.image = svgIcon.pixmap("slc-share")
            likeToolTip.image = svgIcon.pixmap("slc-like")
            connectToolTip.image = svgIcon.pixmap("slc-connect")
        }
    }
    //END: non graphical implementation objects


    //BEGIN: graphical implementation objects
    Icon {
        id: shareIcon

        source: "slc-share"
        service: "Share"
        model: dialog.mainItem.shareModel
    }
    Icon {
        id: likeIcon

        source: "slc-like"
        service: "Like"
        model: dialog.mainItem.likeModel
    }
    Icon {
        id: connectIcon

        source: "slc-connect"
        service: "Connect"
        model: dialog.mainItem.connectModel
    }

    PlasmaCore.ToolTip {
        id: shareToolTip

        target: shareIcon
        mainText: i18n("Share")
        subText: title
    }
    PlasmaCore.ToolTip {
        id: likeToolTip

        target: likeIcon
        mainText: i18n("Like")
        subText: title
    }
    PlasmaCore.ToolTip {
        id: connectToolTip

        target: connectIcon
        mainText: i18n("Connect")
        subText: title
    }

    SlcMenu {
        id: dialog
        location: plasmoid.location
    }
    //END: graphical implementation objects
}

