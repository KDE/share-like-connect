/*
 *  Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *  Copyright 2011 Marco Martin <mart@kde.org>
 *
 *  This library is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU Library General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This library is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to the
 *  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301, USA.
 */

#include "sharelikeconnect.h"

#include "currentcontenttracker.h"
#include "sharecontainer.h"
#include "shareservice/shareservice.h"

ShareLikeConnectEngine::ShareLikeConnectEngine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
{
    addSource(new CurrentContentTracker(this));
    m_shareContainer = new ShareContainer(this);
    m_shareContainer->setObjectName("Share");
    addSource(m_shareContainer);
}

Plasma::Service *ShareLikeConnectEngine::serviceForSource(const QString &source)
{
    Plasma::Service *service = 0;
    if (source == "Share") {
        service = new ShareService(this);
    } else if (source == "Like") {
    } else if (source == "Connect") {
    }

    return service;
}

// export the plugin; use the plugin name and the class name
K_EXPORT_PLASMA_DATAENGINE(org.kde.sharelikeconnect, ShareLikeConnectEngine)

// include the moc file so the build system makes it for us
#include "sharelikeconnect.moc"

