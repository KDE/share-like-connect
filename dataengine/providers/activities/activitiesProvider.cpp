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

#include <Nepomuk/Query/Query>
#include <Nepomuk/Resource>
#include <Nepomuk/Query/ResourceTerm>
#include <Nepomuk/Query/Result>
#include <Nepomuk/Query/QueryServiceClient>
#include <Nepomuk/Variant>
#include <nepomuk/comparisonterm.h>

#include <soprano/vocabulary.h>

#include <kactivities/consumer.h>

#include "kext.h"

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

    //find out what activities if any this resource is connected to
    //TODO: restrict the query to only activities, but they aren't part of the ontology yet
    Nepomuk::Query::ComparisonTerm term(Soprano::Vocabulary::NAO::isRelated(), Nepomuk::Query::ResourceTerm(Nepomuk::Resource(resourceUrl)));
    Nepomuk::Query::Query query = Nepomuk::Query::Query(term);
    //FIXME: this should be fast enough?
    QList<Nepomuk::Query::Result> resources = Nepomuk::Query::QueryServiceClient::syncQuery(query);

    QSet<QString> activities;
    foreach (Nepomuk::Query::Result res, resources) {
        Nepomuk::Resource resource = res.resource();
        activities.insert(resource.property(QUrl("http://nepomuk.kde.org/ontologies/2010/11/29/kext#activityIdentifier")).toString());
    }

    //first step
    if (activityIds.isEmpty()) {

        //list activities
        QList<QVariant> result;
        QVariantHash item;
        item["target"] = m_activityConsumer->currentActivity();
        item["name"] = i18n("Current activity");
        item["connected"] = activities.contains(m_activityConsumer->currentActivity());
        result << item;

        foreach (const QString &activity, m_activityConsumer->listActivities()) {
            KActivities::Info *info = new KActivities::Info(activity);
            QVariantHash item;
            item["target"] = activity;
            item["name"] = info->name();
            item["connected"] = activities.contains(activity);
            //kDebug() << "Found activity: " << activity << info->name();

            result << item;
            delete info;
        }
        return result;
    }

    //second step
    QUrl typeUrl;

    Nepomuk::Resource fileRes(resourceUrl);
    //Bookmark?
    if (QUrl(resourceUrl).scheme() == "http" ||
        content.value("Mime Type").toString() == "text/x-html") {
        typeUrl = QUrl("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark");

        QList <QUrl> types;
        types << typeUrl;
        fileRes.setTypes(types);

        fileRes.setDescription(resourceUrl);
        fileRes.setProperty(QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#bookmarks"), resourceUrl);
    } else if (resourceUrl.endsWith(".desktop")) {
        typeUrl = QUrl("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Application");

        QList <QUrl> types;
        types << typeUrl;
        fileRes.setTypes(types);

        KService::Ptr service = KService::serviceByDesktopPath(QUrl(resourceUrl).path());
        if (service) {
            fileRes.setLabel(service->name());
            fileRes.setSymbols(QStringList() << service->icon());
        }
    }

    foreach (const QString &activityId, activityIds) {
        Nepomuk::Resource acRes(activityId, Nepomuk::Vocabulary::KEXT::Activity());
        //remove connection
        if (activities.contains(activityId)) {
            acRes.removeProperty(Soprano::Vocabulary::NAO::isRelated(), fileRes);
        //add connection
        } else {
            acRes.addProperty(Soprano::Vocabulary::NAO::isRelated(), fileRes);
        }
    }

    return true;
}

//K_EXPORT_SLC_PROVIDER(activities, ActivitiesProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<ActivitiesProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_activities"))

#include "activitiesProvider.moc"

