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

#include "ratingProvider.h"

#include <Nepomuk/Query/Query>
#include <Nepomuk/Resource>
#include <Nepomuk/Variant>

#include <soprano/vocabulary.h>

RatingProvider::RatingProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
}

SLC::Provider::Actions RatingProvider::actionsFor(const QVariantHash &content) const
{
    return Like;
}

QVariant RatingProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (action != Connect) {
        return false;
    }

    const QString resourceUrl = content["URI"].toString();
    //FIXME: this is pretty ugly and type unsafe
    int rating = parameters["Targets"].toStringList().first().toInt();

    //only one step here
    QUrl typeUrl;

    Nepomuk::Resource fileRes(resourceUrl);
    if (content.value("Mime Type").toString() == "text/x-html") {
        typeUrl = QUrl("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark");
        fileRes.addType(typeUrl);
        fileRes.setDescription(resourceUrl);
    }

    fileRes.setRating(rating);

    return true;
}

//K_EXPORT_SLC_PROVIDER(activities, RatingProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<RatingProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_rating"))

#include "ratingProvider.moc"

