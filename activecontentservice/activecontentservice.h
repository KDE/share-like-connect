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

#ifndef ACTIVECONTENTSERVICE_H
#define ACTIVECONTENTSERVICE_H

#include <QObject>

#include <activecontent.h>

#include "activecontentservice_export.h"

namespace ActiveContent
{

class ACTIVECONTENTSERVICE_EXPORT ActiveContentService : public QObject
{
    Q_OBJECT

public:
    ActiveContentService(const ActiveContent &content, QObject *parent = 0);
    ActiveContentService(QObject *parent = 0);
    ~ActiveContentService();

    void setActiveContent(const ActiveContent &content);
    ActiveContent activeContent() const;

    bool isActive() const;

public Q_SLOTS:
    void setActive(bool active);

public:
    class Private;

private:
    Private * const d;

    Q_PRIVATE_SLOT(d, void activeWindowChanged(WId wid))
};

} // namespace ActiveContent
#endif
