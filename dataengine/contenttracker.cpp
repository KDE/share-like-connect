/*
 *   Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
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

#include "contenttracker.h"

#include <KIcon>
#include <KWindowSystem>

#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusMessage>
#include <QDBusServiceWatcher>
#include <QDBusConnection>

#include "activitymanagerslc_interface.h"

ContentTracker::ContentTracker(QObject *parent)
    : Plasma::DataContainer(parent)
{
    connect(KWindowSystem::self(), SIGNAL(activeWindowChanged(WId)),
            this, SLOT(activeWindowChanged(WId)));

    connectToActivityManager();
    QDBusServiceWatcher *watcher = new QDBusServiceWatcher("org.kde.kactivitymanagerd", QDBusConnection::sessionBus(),
                                             QDBusServiceWatcher::WatchForOwnerChange, this);
    connect(watcher, SIGNAL(serviceOwnerChanged(QString,QString,QString)),
            this, SLOT(serviceChange(QString,QString,QString)));
}

void ContentTracker::activeWindowChanged(WId wid)
{
    setData("Window ID", (int)wid);
    checkForUpdate();
    emit changed();
}

void ContentTracker::focusedResourceUriCallback(const QString &result)
{
    kWarning()<<result;
}

void ContentTracker::focusChanged(const QString &uri, const QString &mimetype)
{
    kDebug()<< uri<< mimetype;
    setData("URI", uri);
    setData("Mime Type", mimetype);
    setData("Source", "KDE");
    setData("Title", "KDE - Experience Freedom!");
    setData("Thumbnail", KIcon("konqueror").pixmap(64, 64));
    setData("Window ID", (int)KWindowSystem::activeWindow());
}

void ContentTracker::connectToActivityManager()
{
    activityManagerIface = new OrgKdeActivityManagerSLCInterface("org.kde.kactivitymanagerd", "/SLC",
                                    QDBusConnection::sessionBus());
    if (activityManagerIface->isValid()) {
        activityManagerIface->callWithCallback("focussedResourceURI", QList<QVariant>(), this, SLOT(focusedResourceUriCallback(const QString &)));

        connect(activityManagerIface, SIGNAL(focusChanged(const QString &, const QString &)), this, SLOT(focusChanged(const QString &, const QString &)));
    } else {
        delete activityManagerIface;
        activityManagerIface = 0;
        kWarning() << "activityManager not reachable";
    }
}

void ContentTracker::serviceChange(const QString& name, const QString& oldOwner, const QString& newOwner)
{
    kDebug()<< "Service" << name << "status change, old owner:" << oldOwner << "new:" << newOwner;

    if (newOwner.isEmpty()) {
        //unregistered
        delete activityManagerIface;
        activityManagerIface = 0;
    } else if (oldOwner.isEmpty()) {
        //registered
        connectToActivityManager();
    }
}

#include "contenttracker.h"

