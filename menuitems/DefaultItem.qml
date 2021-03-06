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
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents


Item {
    id: itemRoot

    signal operationCompleted()

    width: Math.max(implicitWidth, parent.width)
    implicitWidth: menuItemBody.paintedWidth
    implicitHeight: Math.max(30, menuItemBody.paintedHeight)

    PlasmaComponents.Label {
        id: menuItemBody
        //font.pointSize: 14
        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: name

        function checkResult(serviceJob)
        {
            main.providerId = providerId

            //TODO: error message?
            if (serviceJob.result === true || serviceJob.result === false) {
                itemRoot.operationCompleted()
                main.state = "operations"
                main.sourceName = ""
            //is it asking for confirmation?
            } else if (serviceJob.result["Confirmation"]) {
                confirmationMessage = serviceJob.result["Confirmation"]
                main.state = "confirmation"
                main.sourceName = sourceName
            //is it asking for a comment?
            } else if (serviceJob.result == "Comment") {
                main.state = "comment"
                main.sourceName = sourceName
            //is it proposing a series of targets?
            } else {
                secondStepModel.clear()
                for (i in serviceJob.result) {
                    secondStepModel.append({"target": serviceJob.result[i]["target"], "name": serviceJob.result[i]["name"], "connected": serviceJob.result[i]["connected"]})
                }

                main.state = "targets"
                main.sourceName = sourceName
            }
        }
    }

    function run(x, y)
    {
        var service = slcSource.serviceForSource(sourceName)
        if (!service) {
            service = slcSource.serviceForSource(main.sourceName)
        }
        var operation = service.operationDescription("executeAction")
        if (model["providerId"]) {
            operation["ActionName"] = model["providerId"]
        } else {
            operation["ActionName"] = main.providerId
        }
        if (model["target"] !== undefined) {
            operation["Targets"] = [String(model["target"])]
        }

        job = service.startOperationCall(operation)

        job.finished.connect(menuItemBody.checkResult)
    }
}