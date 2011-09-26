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

#include "activecontentwatcher.h"

#include <QDBusInterface>
#include <QDBusServiceWatcher>

#include "activecontentservice_export.h"

namespace ActiveContent
{

class ActiveContentWatcher::Private
{
public:
    Private(ActiveContentWatcher *watcher)
        : q(watcher),
          watch(new QDBusServiceWatcher("org.kde.ActiveContent",
                                        QDBusConnection::sessionBus(),
                                        QDBusServiceWatcher::WatchForOwnerChange,
                                        q)),
          iface(0)
    {
        connect(watch, SIGNAL(serviceOwnerChanged(QString,QString,QString)),
                q, SLOT(serviceOwnerChanged(QString,QString,QString)));
    }

    void serviceOwnerChanged(const QString &serviceName,
                             const QString &oldOwner,
                             const QString &newOwner);
    void activeContentChanged(const QDBusArgument &message);
    ActiveContentWatcher *q;
    QDBusServiceWatcher *watch;
    QDBusInterface *iface;
    ActiveContent content;
};

ActiveContentWatcher::ActiveContentWatcher(QObject *parent)
    : QObject(parent),
      d(new Private(this))
{

}

ActiveContentWatcher::~ActiveContentWatcher()
{
    delete d;
}

ActiveContent ActiveContentWatcher::ActiveContentWatcher::activeContent() const
{
    return d->content;
}

void ActiveContentWatcher::Private::activeContentChanged(const QDBusArgument &message)
{
    message >> content;
    emit q->activeContentChanged(content);
}

void ActiveContentWatcher::Private::serviceOwnerChanged(const QString &serviceName,
                                                        const QString &oldOwner,
                                                        const QString &newOwner)
{
    Q_UNUSED(serviceName)
    Q_UNUSED(oldOwner)

    delete iface;
    iface = 0;

    if (!newOwner.isEmpty()) {
        iface = new QDBusInterface("org.kde.ActiveContent", "/ActiveContent");
        //emit q->activeContentChanged(..); //FIXME: do we need to emit something here?
    }
}

} // namespace ActiveContent

#include "activecontent.moc"
