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

#ifndef ACTIVECONTENTSERVICE_H
#define ACTIVECONTENTSERVICE_H

#include <QObject>

#include <activecontent.h>

#include "activecontentservice_export.h"

class ACTIVECONTENTSERVICE_EXPORT ActiveContentService : public QObject
{
    Q_OBJECT

public:
    ActiveContentService(const ActiveContent &content, QObject *parent = 0);
    ActiveContentService(QObject *parent = 0);
    ~ActiveContentService();

    bool isActive() const;
    void setActiveContent(const ActiveContent &content);
    ActiveContent activeContent() const;

public Q_SLOTS:
    void activate(bool isActive);

private:
    class Private;
    Private * const d;
};

#endif
