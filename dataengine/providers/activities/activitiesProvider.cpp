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

#include "activitiesProvider.h"

#include <Nepomuk/Query/Query>
#include <Nepomuk/Resource>
#include <Nepomuk/Variant>

#include <soprano/vocabulary.h>

#include <kactivities/consumer.h>

ActivitiesProvider::ActivitiesProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
    m_activityConsumer = new Activities::Consumer(this);
}

SLC::Provider::Actions ActivitiesProvider::actionsFor(const QVariantHash &content) const
{
    if (content.value("Window ID").toInt() > 0) {
        return Connect;
    }

    return NoAction;
}

QVariant ActivitiesProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (action != Connect) {
        return false;
    }

    const QString resourceUrl = content["URI"].toString();
    QStringList activityIds = parameters["Targets"].toStringList();

    //first step
    if (activityIds.isEmpty()) {
        QList<QVariant> result;
        QVariantHash item;
        item["target"] = m_activityConsumer->currentActivity();
        item["name"] = i18n("Current activity");
        result << item;

        foreach (const QString &activity, m_activityConsumer->listActivities()) {
            Activities::Info *info = new Activities::Info(activity);
            QVariantHash item;
            item["target"] = activity;
            item["name"] = info->name();
            //kDebug() << "Found activity: " << activity << info->name();
            result << item;
            delete info;
        }
        return result;
    //second step
    } else {
        QUrl typeUrl;

        Nepomuk::Resource fileRes(resourceUrl);
        if (content.value("Mime Type").toString() == "text/x-html") {
            typeUrl = QUrl("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark");
            fileRes.addType(typeUrl);
            fileRes.setDescription(resourceUrl);
            fileRes.setProperty(QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#bookmarks"), resourceUrl);
        }

        foreach (const QString &activityId, activityIds) {
            Nepomuk::Resource acRes("activities://" + activityId);
            acRes.addProperty(Soprano::Vocabulary::NAO::isRelated(), fileRes);
        }

        return true;
    }
}

//K_EXPORT_SLC_PROVIDER(activities, ActivitiesProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<ActivitiesProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_activities"))

#include "activitiesProvider.moc"

