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

#include "activecontentservice.h"

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QWeakPointer>

#include <KWindowSystem>

#include "activecontentdbusinterface_p.h"

namespace ActiveContent
{

static const QString SERVICE_NAME("org.kde.activeServiceContent");

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

    static QWeakPointer<ActiveContentDBusInterface> interface;
};

QWeakPointer<ActiveContentDBusInterface> ActiveContentService::Private::interface;

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
    delete d;
}

void ActiveContentService::setActive(bool active)
{
    const bool isActive = d->interface && d->interface.data()->current() == this;
    if (isActive == active) {
        return;
    }

    if (active) {
        if (!d->interface) {
            d->interface = new ActiveContentDBusInterface;
        }

        d->interface.data()->setCurrent(this);
        QDBusConnection::sessionBus().interface()->registerService(SERVICE_NAME,
                                                                   QDBusConnectionInterface::ReplaceExistingService,
                                                                   QDBusConnectionInterface::AllowReplacement);
    } else if (isActive) {
        QDBusConnection::sessionBus().interface()->unregisterService(SERVICE_NAME);
        if (d->interface) {
            d->interface.data()->setCurrent(0);
        }
    }
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
    } else {
        // base it on the URL having something useful in it
        setActive(d->content.url().isValid());
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

} // namespace ActiveContent

#include "activecontentservice.moc"

