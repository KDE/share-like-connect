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

#ifndef SLCJOB_H
#define SLCJOB_H

// plasma
#include <Plasma/ServiceJob>

#include "provider.h"

namespace SLC {

class SlcJob : public Plasma::ServiceJob
{

Q_OBJECT

public:
    SlcJob(Provider::Action action, Provider *provider, const QString &operation, const QVariantHash &content, QMap<QString, QVariant> &parameters, QObject *parent = 0);
    ~SlcJob();

protected:
    void start();

private:
    QWeakPointer<Provider> m_provider;
    QVariantHash m_content;
    Provider::Action m_action;
};

}

#endif
