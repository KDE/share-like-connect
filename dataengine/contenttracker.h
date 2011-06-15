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

#ifndef CONTENTTRACKER_H
#define CONTENTTRACKER_H

#include <Plasma/DataContainer>

class QDBusPendingCallWatcher;
class OrgKdeActivityManagerSLCInterface;

class ContentTracker : public Plasma::DataContainer
{
    Q_OBJECT

public:
    ContentTracker(QObject *parent = 0);

Q_SIGNALS:
    void changed();

protected:
    void connectToActivityManager();

private Q_SLOTS:
    void focusChanged(const QString &uri, const QString &mimetype);
    void focusedResourceUriCallback(const QString &result);
    void serviceChange(const QString& name, const QString& oldOwner, const QString& newOwner);

private:
    OrgKdeActivityManagerSLCInterface *activityManagerIface;
};

#endif
