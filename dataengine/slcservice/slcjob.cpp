/*
 * Copyright 2011 Marco Martin <mart@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License version 2 as
 * published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "slcjob.h"


#include <kdebug.h>

SlcJob::SlcJob(const QString &operation, QMap<QString, QVariant> &parameters, QObject *parent)
    : ServiceJob(parent->objectName(), operation, parameters, parent)
{
}

SlcJob::~SlcJob()
{
}

void SlcJob::start()
{
    const QString operation = operationName();

    kDebug() << "starting operation" << operation;

    if (operation == "executeAction") {
        kDebug() << parameters()["ActionName"].toString()
                 << parameters()["Description"].toString();
        setResult(true);
        return;
    }
    setResult(false);
}

#include "slcjob.moc"
