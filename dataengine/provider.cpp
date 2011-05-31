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

#include "provider.h"

namespace SLC
{

class Provider::Private
{
public:
    QString name;
};

Provider::Provider(QObject *parent, const QVariantList &args)
    : QObject(parent),
      d(new Private)
{
    d->name = args.isEmpty() ? QString("Unnamed") : args[0].toString();
}

Provider::Actions Provider::actionsFor(const QVariantHash &content) const
{
    Q_UNUSED(content)
    return NoAction;
}

QVariant Provider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    Q_UNUSED(action)
    Q_UNUSED(content)
    Q_UNUSED(parameters)
    return false;
}

QString Provider::name() const
{
    return d->name;
}

} // namespace SLC

#include "provider.moc"
