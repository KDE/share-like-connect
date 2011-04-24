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

class ActiveContentService::Private
{
public:
    Private()
        : isActive(false)
    {
    }

    ActiveContent content;
    bool isActive;
};

ActiveContentService::ActiveContentService(const ActiveContent &content, QObject *parent)
    : QObject(parent),
      d(new Private)
{
    d->content = content;
}

ActiveContentService::ActiveContentService(QObject *parent)
    : QObject(parent),
      d(new Private)
{
}

ActiveContentService::~ActiveContentService()
{
}

void ActiveContentService::activate(bool isActive)
{
    if (d->isActive == isActive) {
        return;
    }

    d->isActive = isActive;
}

bool ActiveContentService::isActive() const
{
    return d->isActive;
}

void ActiveContentService::setActiveContent(const ActiveContent &content)
{
    d->content = content;
}

ActiveContent ActiveContentService::activeContent() const
{
    return d->content;
}

#include "activecontentservice.moc"

