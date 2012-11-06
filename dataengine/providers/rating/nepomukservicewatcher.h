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

#ifndef NEPOMUKSERVICEWATCHER_H
#define NEPOMUKSERVICEWATCHER_H

#include <QObject>

class NepomukServiceWatcher : public QObject
{
    Q_OBJECT

public:
    enum Service { NoService = 0,
                   StorageService = 1,
                   QueryService = 2,
                   OntologyService = 4,
                   AllServices = 0xFFFFFF
                 };

    Q_DECLARE_FLAGS(Services, Service)

    NepomukServiceWatcher(QObject *parent = 0);

    bool areServicesRunning(Services services) const;

Q_SIGNALS:
    void servicesStarted(Services services);
    void servicesStopped(Services services);

private:
    class Private;
    Private * const d;

    Q_PRIVATE_SLOT(d, void serviceRegistered(const QString &service));
    Q_PRIVATE_SLOT(d, void serviceUnregistered(const QString &service));
    Q_PRIVATE_SLOT(d, void notifyOfServiceChanges());
};

Q_DECLARE_OPERATORS_FOR_FLAGS(NepomukServiceWatcher::Services)

#endif

