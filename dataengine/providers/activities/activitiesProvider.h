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
 *   GNU Library General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ACTIVITIESPROVIDER_H
#define ACTIVITIESPROVIDER_H

#include <provider.h>

namespace Activities {
    class Consumer;
}

class ActivitiesProvider : public SLC::Provider
{
    Q_OBJECT

public:
    ActivitiesProvider(QObject *parent, const QVariantList &args);
    Actions actionsFor(const QVariantHash &content) const;

    QVariant executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters);

    QString actionName(const QVariantHash &content, Action action);

private:
    Activities::Consumer *m_activityConsumer;
};

#endif

