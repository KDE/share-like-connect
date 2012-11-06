/*
 *   Copyright 2012 Aaron Seigo <aseigo@kde.org>
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

#include "nepomukservicewatcher.h"

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusServiceWatcher>
#include <QTimer>

class NepomukServiceWatcher::Private
{
public:
    Private(NepomukServiceWatcher *parent);

    void serviceRegistered(const QString &service);
    void serviceUnregistered(const QString &service);
    void notifyOfServiceChanges();

    NepomukServiceWatcher *q;
    QHash<QString, Service> watchServices;
    QHash<Service, bool> serviceStatus;
    Services startedServices;
    Services stoppedServices;
    QTimer *updateTimer;
};

NepomukServiceWatcher::Private::Private(NepomukServiceWatcher *parent)
    : q(parent),
      startedServices(NoService),
      stoppedServices(NoService),
      updateTimer(new QTimer(q))
{
    updateTimer->setInterval(50);
    updateTimer->setSingleShot(true);
    connect(updateTimer, SIGNAL(timeout()), q, SLOT(notifyOfServiceChanges()));

    watchServices.insert("org.kde.nepomuk.services.nepomukstorage", StorageService);
    watchServices.insert("org.kde.nepomuk.services.nepomukqueryservice", QueryService);
    watchServices.insert("org.kde.nepomuk.services.nepomukontologyloader", OntologyService);

    QDBusServiceWatcher *watcher = new QDBusServiceWatcher(q);
    watcher->setConnection(QDBusConnection::sessionBus());
    connect(watcher, SIGNAL(serviceRegistered(QString)), q, SLOT(serviceRegistered(QString)));
    connect(watcher, SIGNAL(serviceUnregistered(QString)), q, SLOT(serviceUnregistered(QString)));

    QDBusConnectionInterface *interface = watcher->connection().interface();
    QHashIterator<QString, Service> it(watchServices);
    while (it.hasNext()) {
        it.next();
        watcher->addWatchedService(it.key());
        serviceStatus.insert(it.value(), interface->isServiceRegistered(it.key()));
    }
}

void NepomukServiceWatcher::Private::serviceRegistered(const QString &service)
{
    Service s = watchServices.value(service);
    startedServices |= s;
    stoppedServices ^= s;
    serviceStatus.insert(s, true);
    updateTimer->start();
}

void NepomukServiceWatcher::Private::serviceUnregistered(const QString &service)
{
    Service s = watchServices.value(service);
    stoppedServices |= s;
    startedServices ^= s;
    serviceStatus.insert(s, false);
    updateTimer->start();
}

void NepomukServiceWatcher::Private::notifyOfServiceChanges()
{
    if (startedServices != NoService) {
        emit q->servicesStarted(startedServices);
        startedServices = NoService;
    }

    if (stoppedServices != NoService) {
        emit q->servicesStopped(stoppedServices);
        stoppedServices = NoService;
    }
}

NepomukServiceWatcher::NepomukServiceWatcher(QObject *parent)
    : QObject(parent),
      d(new Private(this))
{
}

bool NepomukServiceWatcher::areServicesRunning(Services services) const
{
    QHashIterator<QString, Service> it(d->watchServices);
    while (it.hasNext()) {
        it.next();
        if (services & it.value() && !d->serviceStatus[it.value()]) {
            return false;
        }
    }

    return true;
}

#include "nepomukservicewatcher.moc"

