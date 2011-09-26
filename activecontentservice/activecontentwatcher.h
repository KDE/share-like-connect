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

#ifndef ACTIVECONTENTWATCHER_H
#define ACTIVECONTENTWATCHER_H

#include <QObject>

#include <activecontent.h>

#include "activecontentservice_export.h"

namespace ActiveContent
{

class ACTIVECONTENTSERVICE_EXPORT ActiveContentWatcher : public QObject
{
    Q_OBJECT

public:
    ActiveContentWatcher(QObject *parent = 0);
    ~ActiveContentWatcher();

    ActiveContent activeContent() const;

Q_SIGNALS:
    void activeContentChanged(const ActiveContent &content);

public:
    class Private;

private:
    Private * const d;

    Q_PRIVATE_SLOT(d, serviceOwnerChanged(QString,QString,QString));
};

} // namespace ActiveContent
#endif
