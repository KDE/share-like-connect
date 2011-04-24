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
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ACTIVECONTENT_H
#define ACTIVECONTENT_H

#include <QString>
#include <qwindowdefs.h>

#include <KUrl>

#include "activecontentservice_export.h"

class ACTIVECONTENTSERVICE_EXPORT ActiveContent
{
public:
    ActiveContent();
    ActiveContent(KUrl &url,
                  const QString &title = QString(),
                  const QString &mimetype = QString(),
                  const QString &serviceIdentifier = QString(),
                  WId windowId = 0);
    ActiveContent(const ActiveContent &other);
    const ActiveContent &operator=(const ActiveContent &rhs);

    KUrl url() const;
    void setUrl(const KUrl &url);

    QString title() const;
    void setTitle(const QString &title);

    QString mimetype() const;
    void setMimeType(const QString &mimetype);

    QString serviceIdentifier() const;
    void setServiceIdentifier(const QString &serviceIdentifier) const;

    WId windowId() const;
    void setWindowId(const WId &windowId);

private:
    class Private;
    Private * const d;
};

#endif
