/*
 *   Copyright 2011 Sebastian Kügler <sebas@kde.org>
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
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.qtextracomponents 0.1


Item {
    id: containerItem
    property int score

    implicitHeight: 32
    implicitWidth: 32*5

    signal rateClicked(int newRating)


    PlasmaCore.DataSource {
        id: metadataSource
        engine: "org.kde.active.metadata"
        connectedSources: [resourceUrl]
        onDataChanged: {
            containerItem.score = metadataSource.data[resourceUrl]["numericRating"] != undefined ? metadataSource.data[resourceUrl]["numericRating"] : 0
        }
    }

    Row {
        id: iconRow
        anchors.centerIn: parent
        spacing: 0
        Repeater {
            model: 5

            QIconItem {
                id: rating2
                width: 22
                height: 22
                icon: QIcon("rating")
                property int baseRating: (index+1)*2
                enabled: (score > index*2)
            }
        }
    }

    function rateResource(resourceUrl, rating)
    {
        var service = slcSource.serviceForSource(sourceName)
        var operation = service.operationDescription("executeAction")
        operation["ActionName"] = model["providerId"]
        operation["Targets"] = [rating]


        job = service.startOperationCall(operation)
    }

    function run(x, y)
    {
        var pos = iconRow.mapFromItem(containerItem, x, y)
        var star = iconRow.childAt(pos.x, pos.y);

        if (star && star.baseRating) {
            print("released with rating " + star.baseRating + " Item: " + resourceUrl);
            rateResource(resourceUrl, star.baseRating);
        } else{
            print("released but could not figure out rating" + star);
        }
    }
}
