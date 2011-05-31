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

#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>

#include <KGenericFactory>

#include <kdemacros.h>

namespace SLC
{

class KDE_EXPORT Provider : public QObject
{
    Q_OBJECT

public:
    enum Action { NoAction = 0,
                  Share = 1,
                  Like = 2,
                  Connect = 4 };
    Q_DECLARE_FLAGS(Actions, Action)

    Provider(QObject *parent, const QVariantList &args);

    QString name() const;

    virtual Actions actionsFor(const QVariantHash &content) const;

private:
    class Private;
    Private * const d;
};

} // namespace SLC

Q_DECLARE_OPERATORS_FOR_FLAGS(SLC::Provider::Actions)

/**
 * Register a Provider when it is contained in a loadable module
 */
#define K_EXPORT_SLC_PROVIDER(libname, classname) \
K_PLUGIN_FACTORY(slcfactory, registerPlugin<classname>();) \
K_EXPORT_PLUGIN(slcfactory("sharelikeconnect_provider_" #libname))

#endif

