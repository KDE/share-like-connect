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

ContentTracker::ContentTracker(QObject *parent)
    : Plasma::DataContainer(parent)
{
    connect(KWindowSystem::self(), SIGNAL(activeWindowChanged(WId)),
            this, SLOT(activeWindowChanged(WId)));

    //FIXME: needs to track the actual content.
    setData("URI", "http://kde.org");
    setData("Mime Type", "text/x-html");
    setData("Source", "KDE");
    setData("Title", "KDE - Experience Freedom!");
    setData("Thumbnail", KIcon("konqueror").pixmap(64, 64));
    setData("Window ID", (int)KWindowSystem::activeWindow());
}

void ContentTracker::activeWindowChanged(WId wid)
{
    setData("Window ID", (int)wid);
    checkForUpdate();
    emit changed();
}

