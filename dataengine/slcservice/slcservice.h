/*
 *   Copyright 2011 Marco Martin <mart@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
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

#ifndef SLC_SERVICE_H
#define SLC_SERVICE_H


#include <Plasma/Service>
#include <Plasma/ServiceJob>

#include "sharelikeconnect.h"
#include "provider.h"

namespace SLC {

class SlcService : public Plasma::Service
{
    Q_OBJECT

public:
    SlcService(const QString &action, ShareLikeConnectEngine *parent = 0, const QVariantList &args = QVariantList());
    Plasma::ServiceJob *createJob(const QString &operation,
                          QMap<QString, QVariant> &parameters);

private:
    QString m_id;
    QWeakPointer<ShareLikeConnectEngine> m_slcEngine;
    QVariantHash m_content;
    Provider::Action m_action;
};

}

#endif
