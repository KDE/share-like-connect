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
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "bookmarksProvider.h"

#include <Nepomuk/Query/Query>
#include <Nepomuk/Resource>
#include <Nepomuk/Variant>

#include <soprano/vocabulary.h>


BookmarksProvider::BookmarksProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
}

SLC::Provider::Actions BookmarksProvider::actionsFor(const QVariantHash &content) const
{
    QUrl url(content.value("URI").toString());
    if (content.value("Window ID").toInt() > 0 && url.scheme() == "http") {
        return Like;
    }

    return NoAction;
}

QVariant BookmarksProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (action != Connect) {
        return false;
    }

    const QUrl resourceUrl(content.value("URI").toString());
    Nepomuk::Resource bookmarkRes(resourceUrl.toString());

    //the bookmark exists already? remove
    if (bookmarkRes.exists()) {
        //TODO: ask for confirmation
        bookmarkRes.remove();
        return true;
    //create bookmark
    } else {
        QUrl typeUrl;

        if (resourceUrl.scheme() == "http" ||
            content.value("Mime Type").toString() == "text/x-html") {
            typeUrl = QUrl("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Bookmark");
            bookmarkRes.addType(typeUrl);
            bookmarkRes.setDescription(resourceUrl.toString());
            bookmarkRes.setProperty(QUrl::fromEncoded("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#bookmarks"), resourceUrl.toString());
        }


        return true;
    }
}

//K_EXPORT_SLC_PROVIDER(bookmarks, BookmarksProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<BookmarksProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_bookmarks"))

#include "bookmarksProvider.moc"

