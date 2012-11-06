/*
 *   Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *   Copyright 2011 Marco Martin <mart.org>
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

#include "ratingProvider.h"

#include <Nepomuk2/Query/Query>
#include <Nepomuk2/Resource>
#include <Nepomuk2/Variant>
#include <Nepomuk2/Vocabulary/NFO>

#include <soprano/vocabulary.h>

#include "nepomukservicewatcher.h"

RatingProvider::RatingProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args),
      m_nepoWatcher(new NepomukServiceWatcher(this))
{
}

SLC::Provider::Actions RatingProvider::actionsFor(const QVariantHash &content) const
{
    Q_UNUSED(content)

    if (m_nepoWatcher->areServicesRunning(NepomukServiceWatcher::QueryService)) {
        return Like;
    }

    return NoAction;
}

QVariant RatingProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (action != Like) {
        return false;
    }

    const QString resourceUrl = content["URI"].toString();
    int rating = 0;
    const QVariant targets = parameters["Targets"];
    const QVariant::Type dataType = targets.type();
    if (dataType == QVariant::StringList) {
        const QStringList args = targets.toStringList();
        if (!args.isEmpty()) {
            rating = args.first().toInt();
        }
    } else if (dataType == QVariant::Int) {
        rating = targets.toInt();
    } else {
        return false;
    }

    rating = qBound(0, rating, 10);

    //only one step here

    Nepomuk2::Resource fileRes(resourceUrl);
    if (content.value("Mime Type").toString() == QLatin1String("text/html")) {
        QUrl typeUrl = Nepomuk2::Vocabulary::NFO::Bookmark();
        fileRes.addType(typeUrl);
        const QString desc = parameters["Title"].toString();
        if (!desc.isEmpty()) {
            fileRes.setDescription(desc);
        }
    }

    fileRes.setRating(rating);

    return true;
}

//K_EXPORT_SLC_PROVIDER(activities, RatingProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<RatingProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_rating"))

#include "ratingProvider.moc"

