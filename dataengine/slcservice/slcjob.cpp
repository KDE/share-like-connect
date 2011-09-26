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
 * GNU Library General Public License for more details
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "slcjob.h"


#include <kdebug.h>

namespace SLC {

SlcJob::SlcJob(Provider::Action action, Provider *provider, const QString &operation, const QVariantHash &content, QMap<QString, QVariant> &parameters, QObject *parent)
    : ServiceJob(parent->objectName(), operation, parameters, parent),
      m_provider(provider),
      m_content(content),
      m_action(action)
{
}

SlcJob::~SlcJob()
{
}

void SlcJob::start()
{
    if (!m_provider) {
        setResult(false);
        return;
    }

    const QString operation = operationName();

#ifndef NDEBUG
    kDebug() << "starting operation" << operation;
#endif

    if (operation == "executeAction") {
#ifndef NDEBUG
        kDebug() << parameters()["ActionName"].toString();
#endif
        QVariantHash providerParameters;
        providerParameters["Comment"] = parameters()["Comment"];
        providerParameters["Targets"] = parameters()["Targets"];
        QVariant result = m_provider.data()->executeAction(m_action, m_content, providerParameters);
        setResult(result);
        return;
    }
    setResult(false);
}

}

#include "slcjob.moc"
