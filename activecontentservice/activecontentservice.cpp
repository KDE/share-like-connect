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

#include "activecontentservice.h"

#include <KWindowSystem>

class ActiveContentService::Private
{
public:
    Private(ActiveContentService *obj)
        : q(obj),
          active(false)
    {
    }

    void activeWindowChanged(WId wid);

    ActiveContentService *q;
    ActiveContent content;
    bool active;
};

ActiveContentService::ActiveContentService(const ActiveContent &content, QObject *parent)
    : QObject(parent),
      d(new Private(this))
{
    setActiveContent(content);
}

ActiveContentService::ActiveContentService(QObject *parent)
    : QObject(parent),
      d(new Private(this))
{
}

ActiveContentService::~ActiveContentService()
{
}

void ActiveContentService::setActive(bool active)
{
    if (d->active == active) {
        return;
    }

    d->active = active;
}

bool ActiveContentService::isActive() const
{
    return d->active;
}

void ActiveContentService::setActiveContent(const ActiveContent &content)
{
    const bool hadWindow = d->content.windowId();
    d->content = content;
    if (d->content.windowId()) {
        connect(KWindowSystem::self(), SIGNAL(activeWindowChanged(WId)),
                this, SLOT(activeWindowChanged(WId)), Qt::UniqueConnection);
        d->activeWindowChanged(KWindowSystem::activeWindow());
    } else if (hadWindow) {
        disconnect(KWindowSystem::self(), SIGNAL(activeWindowChanged(WId)),
                   this, SLOT(activeWindowChanged(WId)));
        setActive(false);
    }
}

ActiveContent ActiveContentService::activeContent() const
{
    return d->content;
}

void ActiveContentService::Private::activeWindowChanged(WId wid)
{
    q->setActive(content.windowId() == wid);
}

#include "activecontentservice.moc"

