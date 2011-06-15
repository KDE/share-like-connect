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

#include "sendbyemailProvider.h"

#include <KToolInvocation>

SendByEmailProvider::SendByEmailProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
}

SLC::Provider::Actions SendByEmailProvider::actionsFor(const QVariantHash &content) const
{
    KUrl fileUrl(content.value("URI").toString());
    if (fileUrl.isLocalFile()) {
        return Share;
    } else {
        return NoAction;
    }
}

QVariant SendByEmailProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    Q_UNUSED(parameters)

    if (action != Share) {
        return false;
    }

    const QString resourceUrl = content["URI"].toString();

    //only one step
    //TODO: propose some names as second step, fill out some fields
    KToolInvocation::invokeMailer(QString(), QString(),
                                  QString(), QString(),
                                  QString(), QString(),
                                  QStringList() << resourceUrl);

    return true;
}

//K_EXPORT_SLC_PROVIDER(activities, SendByEmailProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<SendByEmailProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_rating"))

#include "sendbyemailProvider.moc"

