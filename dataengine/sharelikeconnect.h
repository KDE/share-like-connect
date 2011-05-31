/*
 *  Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *  Copyright 2011 Marco Martin <mart@kde.org>
 *
 *  This library is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU Library General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This library is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to the
 *  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301, USA.
 */

#ifndef SHARELIKECONNECTENGINE_H
#define SHARELIKECONNECTENGINE_H

#include <Plasma/DataEngine>

namespace SLC
{
    class Provider;
} // namespace SLC

class ShareLikeConnectEngine : public Plasma::DataEngine
{
    Q_OBJECT

public:
    ShareLikeConnectEngine(QObject *parent, const QVariantList &args);
    ~ShareLikeConnectEngine();

    Plasma::Service *serviceForSource(const QString &source);
    QHash<QString, SLC::Provider *> providers() const;
    QVariantHash content();

private Q_SLOTS:
    void contentChanged();

private:
    QHash<QString, SLC::Provider *> m_providers;
};

#endif
