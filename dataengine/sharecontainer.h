/*
 *   Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *   Copyright 2011 Marco Martin <notmart@gmail.com>
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

#ifndef SHARECONTAINER_H
#define SHARECONTAINER_H

#include <Plasma/DataContainer>

namespace KIO
{
    class Job;
};

class ShareContainer : public Plasma::DataContainer
{
    Q_OBJECT

public:
    ShareContainer(QObject *parent = 0);
};

#endif
