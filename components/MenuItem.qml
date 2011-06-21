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
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.mobilecomponents 0.1 as MobileComponents

Item {
    id: menuItem
    property string resourceUrl
    property string sourceName
    height: childrenRect.height
    width: childrenRect.width
    Column {
        spacing: 5
        //height: Math.min(30, itemLoader.preferredHeight)

        PlasmaCore.SvgItem {
            svg: lineSvg
            elementId: "horizontal-line"
            width: parent.width
            height: lineSvg.elementSize("horizontal-line").height
            visible: menuItem.y > 0
        }

        MobileComponents.FallbackComponent {
            id: fallback
        }

        Loader {
            id: itemLoader
            width: Math.max(item.preferredWidth, menuColumn.width)
            height: item.preferredHeight

            source: fallback.resolvePath("slcmenuitems", [providerId+"Item.qml", "DefaultItem.qml"])

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    menuItem.run(mouse.x, mouse.y)
                }
            }
        }
    }

    function run(x, y)
    {
        itemLoader.item.run(x, y)
        feedbackMessageAnimation.target = itemLoader
        feedbackMessageAnimation.running = true
    }
}
