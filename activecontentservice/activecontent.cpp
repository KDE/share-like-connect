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

#include "activecontent.h"

namespace ActiveContent
{

class ActiveContent::Private
{
public:
    KUrl url;
    QString title;
    QString mimetype;
    QString serviceIdentifier;
    WId windowId;
};

ActiveContent::ActiveContent()
    : d(new Private)
{
}

ActiveContent::ActiveContent(KUrl &url,
                             const QString &title,
                             const QString &mimetype,
                             const QString &serviceIdentifier,
                             WId windowId)
    : d(new Private)
{
    d->url = url;
    d->title = title;
    d->mimetype = mimetype;
    d->serviceIdentifier = serviceIdentifier;
    d->windowId = windowId;
};

ActiveContent::ActiveContent(const ActiveContent &other)
    : d(new Private(*other.d))
{
}

const ActiveContent &ActiveContent::operator=(const ActiveContent &rhs)
{
    if (this != &rhs) {
        *d = *rhs.d;
    }

    return *this;
}

KUrl ActiveContent::url() const
{
    return d->url;
}

void ActiveContent::setUrl(const KUrl &url)
{
    d->url = url;
}

QString ActiveContent::title() const
{
    return d->title;
}

void ActiveContent::setTitle(const QString &title)
{
    d->title = title;
}

QString ActiveContent::mimetype() const
{
    return d->mimetype;
}

void ActiveContent::setMimeType(const QString &mimetype)
{
    d->mimetype = mimetype;
}

QString ActiveContent::serviceIdentifier() const
{
    return d->serviceIdentifier;
}

void ActiveContent::setServiceIdentifier(const QString &serviceIdentifier) const
{
    d->serviceIdentifier = serviceIdentifier;
}

WId ActiveContent::windowId() const
{
    return d->windowId;
}

void ActiveContent::setWindowId(const WId &windowId)
{
    d->windowId = windowId;
}

} // namespace ActiveContent

