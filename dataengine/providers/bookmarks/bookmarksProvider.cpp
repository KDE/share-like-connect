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

#include "bookmarksProvider.h"

#include <Nepomuk2/Query/Query>
#include <Nepomuk2/Resource>
#include <Nepomuk2/Variant>

#include <soprano/vocabulary.h>


BookmarksProvider::BookmarksProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
}

SLC::Provider::Actions BookmarksProvider::actionsFor(const QVariantHash &content) const
{
    QUrl url(content.value("URI").toString());
    if (content.value("Window ID").toInt() > 0 &&
        (url.scheme() == "http" ||
         content.value("Mime Type").toString() == QLatin1String("text/html"))) {
        return Like;
    }

    return NoAction;
}

QString BookmarksProvider::actionName(const QVariantHash &content, Action action)
{
    QUrl url(content.value("URI").toString());
    if (content.value("Window ID").toInt() > 0 &&
        (url.scheme() == "http" ||
         content.value("Mime Type").toString() == "text/html")) {
        Nepomuk2::Resource bookmarkRes(url.toString());
        if (bookmarkRes.exists() && bookmarkRes.types().contains(QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark"))) {
            return i18n("Remove bookmark");
        } else {
            return i18n("Add bookmark");
        }
    }
    return Provider::actionName(content, action);
}

QVariant BookmarksProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (action != Like) {
        return false;
    }

    const QUrl resourceUrl(content.value("URI").toString());
    Nepomuk2::Resource bookmarkRes(resourceUrl.toString());
    bool confirmed = false;
    if (!parameters["Targets"].toStringList().isEmpty()) {
        confirmed = (parameters["Targets"].toStringList().first() == "confirmed");
    }

    //the bookmark exists already? remove
    if (bookmarkRes.exists() && bookmarkRes.types().contains(QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark"))) {
        //delete is dangerous: ask confirmation
        if (confirmed) {
            bookmarkRes.remove();
            emit changed();
            return true;
        } else {
            QVariantHash result;
            result["Confirmation"] = i18n("Are you sure to delete this bookmark? \nAll of its associations with activities will be removed as well.");
            return result;
        }
    //create bookmark
    } else {
        QUrl typeUrl;

        if (resourceUrl.scheme().startsWith("http") ||
            content.value("Mime Type").toString() == "text/html") {
            typeUrl = QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark");

            QList <QUrl> types;
            types << typeUrl;
            bookmarkRes.setTypes(types);

            bookmarkRes.setDescription(resourceUrl.toString());
            bookmarkRes.setProperty(QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#bookmarks"), resourceUrl.toString());
            emit changed();
        }


        return true;
    }
}

//K_EXPORT_SLC_PROVIDER(bookmarks, BookmarksProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<BookmarksProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_bookmarks"))

#include "bookmarksProvider.moc"

