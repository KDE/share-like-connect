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

#include "activitiesProvider.h"

#include <KService>

#include <Nepomuk2/Query/Query>
#include <Nepomuk2/Resource>
#include <Nepomuk2/Query/ResourceTerm>
#include <Nepomuk2/Query/Result>
#include <Nepomuk2/Query/QueryServiceClient>
#include <Nepomuk2/Variant>
#include <nepomuk2/comparisonterm.h>

#include <soprano/vocabulary.h>

#include <kactivities/consumer.h>

ActivitiesProvider::ActivitiesProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
    m_activityConsumer = new KActivities::Consumer(this);
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

        //list activities
        QList<QVariant> result;
        QVariantHash item;
        KActivities::Info *info = new KActivities::Info(m_activityConsumer->currentActivity());
        item["target"] = m_activityConsumer->currentActivity();
        item["name"] = i18n("Current activity");
        item["connected"] = (bool)info->linkedResources().contains(resourceUrl);
        result << item;

        foreach (const QString &activity, m_activityConsumer->listActivities()) {
            KActivities::Info *info = new KActivities::Info(activity);
            QVariantHash item;
            item["target"] = activity;
            item["name"] = info->name();
            item["connected"] = (bool)info->linkedResources().contains(resourceUrl);
            kDebug() << "Found activity: " << activity << info->name();

            result << item;
            delete info;
        }
        return result;
    }

    //second step
    QUrl typeUrl;

    Nepomuk2::Resource fileRes(resourceUrl);
    //Bookmark?
    if (QUrl(resourceUrl).scheme().startsWith("http") ||
        content.value("Mime Type").toString() == "text/html") {
        typeUrl = QUrl("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark");

        QList <QUrl> types;
        types << typeUrl;
        fileRes.setTypes(types);

        fileRes.setDescription(resourceUrl);
        fileRes.setProperty(QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#bookmarks"), resourceUrl);
    } else if (resourceUrl.endsWith(".desktop")) {
        KService::Ptr service = KService::serviceByDesktopPath(QUrl(resourceUrl).path());
        if (service) {
            fileRes = Nepomuk2::Resource(service->entryPath());
            typeUrl = QUrl("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Application");

            QList <QUrl> types;
            types << typeUrl;
            fileRes.setTypes(types);


            fileRes.setLabel(service->name());
            fileRes.setSymbols(QStringList() << service->icon());
        }
    }

    foreach (const QString &activityId, activityIds) {
        KActivities::Info *info = new KActivities::Info(activityId);
        //remove connection
        if ((bool)info->linkedResources().contains(resourceUrl)) {
            info->unlinkResource(fileRes.uri());
        //add connection
        } else {
            info->linkResource(fileRes.uri());
        }
    }

    return true;
}

//K_EXPORT_SLC_PROVIDER(activities, ActivitiesProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<ActivitiesProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_activities"))

#include "activitiesProvider.moc"

