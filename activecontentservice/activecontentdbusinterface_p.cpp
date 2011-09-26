/*
 *   Copyright 2011 by Aaron Seigo <aseigo@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
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

#include "activecontentdbusinterface_p.h"

#include <QDBusConnection>

#include "activecontentservice.h"

namespace ActiveContent
{

ActiveContentDBusInterface::ActiveContentDBusInterface(QObject *parent)
    : QObject(parent),
      m_current(0)
{
    QDBusConnection::sessionBus().registerObject("/ActiveContent", this);
}

ActiveContentService *ActiveContentDBusInterface::current() const
{
    return m_current;
}

ActiveContent ActiveContentDBusInterface::activeContent() const
{
    if (m_current) {
        return m_current->activeContent();
    }

    return ActiveContent();
}

void ActiveContentDBusInterface::setCurrent(ActiveContentService *service)
{
    if (!service) {
        currentDestroyed(m_current);
    } else {
        connect(service, SIGNAL(destroyed(QObject*)), this, SLOT(currentDestroyed(QObject*)), Qt::UniqueConnection);
    }

    m_current = service;
}

void ActiveContentDBusInterface::currentDestroyed(QObject *object)
{
    if (object != m_current) {
        return;
    }

    m_current = 0;
    deleteLater();
}

} // namespace ActiveContent

#include "activecontentdbusinterface_p.moc"

