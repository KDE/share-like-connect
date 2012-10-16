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

#include "tagsProvider.h"

#include <KService>

#include <Nepomuk2/Tag>
#include <Nepomuk2/Resource>
#include <Nepomuk2/Variant>

#include <soprano/vocabulary.h>

TagsProvider::TagsProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
}

SLC::Provider::Actions TagsProvider::actionsFor(const QVariantHash &content) const
{
    return Connect;
}

QVariant TagsProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (action != Connect) {
        return false;
    }

    const QString resourceUrl = content["URI"].toString();
    Nepomuk2::Resource fileRes(resourceUrl);

    QStringList targetTags = parameters["Targets"].toStringList();

    //if a comments was set take it as tag name
    if (!parameters.value("Comment").toString().isEmpty()) {
        targetTags << parameters.value("Comment").toString();
    }

    //first step
    if (targetTags.isEmpty()) {

        //list tags
        QList<QVariant> result;
        QVariantHash item;

        item["target"] = " ";
        item["name"] = i18n("New Tag");
        item["connected"] = false;
        result << item;

        foreach (const Nepomuk2::Tag &tag, Nepomuk2::Tag::allTags()) {
            QVariantHash item;
            item["target"] = tag.uri();
            item["name"] = tag.genericLabel();
            item["connected"] = (bool)(fileRes.tags().contains(tag));

            result << item;
        }
        return result;

    //second step

    //Empty tag name: should ask for tag name?
    //FIXME: this assumes there is only one tag
    } else if (targetTags.first().trimmed().isEmpty()) {
        return "Comment";
    }

    //finally, apply the tag
    QUrl typeUrl;

    //FIXME: this stuff should be put in a common place
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

    foreach (const QString &tagName, targetTags) {
        Nepomuk2::Tag tag(tagName);
        QList<Nepomuk2::Tag> tags = fileRes.tags();

        //remove connection
        if (tags.contains(tag)) {
            tags.removeAll(tag);
            fileRes.setTags(tags);
        //add connection
        } else {
            fileRes.addTag(tag);
        }
    }

    return true;
}

//K_EXPORT_SLC_PROVIDER(activities, TagsProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<TagsProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_tags"))

#include "tagsProvider.moc"

