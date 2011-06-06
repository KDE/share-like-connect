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


Text {
    id: menuItemBody
    //font.pointSize: 14

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    property int preferredWidth: paintedWidth
    property int preferredHeight: Math.max(30, paintedHeight)

    text: name

    PlasmaCore.Theme {
        id: theme
    }
    color: theme.textColor

    function checkResult(serviceJob)
    {
        //TODO: error message?
        if (serviceJob.result == true || serviceJob.result == false) {
            main.pendingState = "operations"
        } else if (serviceJob.result == "Comment") {
            main.pendingState = "comment"
        } else {
            secondStepModel.clear()
            for (i in serviceJob.result) {
                secondStepModel.append({"target": i, "name": serviceJob.result[i], "providerId": providerId})
            }
            main.pendingState = "targets"
        }
    }

    function run(x, y)
    {
        var service = slcSource.serviceForSource(main.service)
        var operation = service.operationDescription("executeAction")
        operation["ActionName"] = model["providerId"]
        if (model["target"] != undefined) {
            operation["Targets"] = [model["target"]]
        }

        job = service.startOperationCall(operation)

        job.finished.connect(checkResult)
    }
}
