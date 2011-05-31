/*
 *  Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *  Copyright 2011 Marco Martin <mart@kde.org>
 *
 *  This library is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU Library General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This library is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to the
 *  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301, USA.
 */

#include "sharelikeconnect.h"

#include <KPluginInfo>
#include <KService>
#include <KServiceTypeTrader>

#include "contenttracker.h"
#include "provider.h"
#include "slcservice/slcservice.h"

static const QString TRACKER_SOURCE("Current Content");

ShareLikeConnectEngine::ShareLikeConnectEngine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
{
    setData("Share", QVariantHash());
    setData("Like", QVariantHash());
    setData("Connect", QVariantHash());

    KService::List offers = KServiceTypeTrader::self()->query("Plasma/ShareLikeConnect");
    foreach (const KService::Ptr &offer, offers) {
        QVariantList args;
        args << offer->name();
        QString error;
        SLC::Provider *provider = offer->createInstance<SLC::Provider>(0, args, &error);
        if (!provider) {
            kDebug() << "ShareLikeConnect failed to load" << offer->name() << offer->library() << "due to:" << error;
            continue;
        }

        KPluginInfo info(offer);
        m_providers.insert(info.pluginName(), provider);
    }

    kDebug() << "providers:" << m_providers.keys() << offers.count();
    ContentTracker *tracker = new ContentTracker(this);
    connect(tracker, SIGNAL(changed()), this, SLOT(contentChanged()));
    tracker->setObjectName(TRACKER_SOURCE);
    addSource(tracker);

    contentChanged();
}

ShareLikeConnectEngine::~ShareLikeConnectEngine()
{
    qDeleteAll(m_providers);
}

Plasma::Service *ShareLikeConnectEngine::serviceForSource(const QString &source)
{
    Plasma::Service *service = 0;
    if (source == "Share" || source == "Like" || source == "Connect") {
        return new SLC::SlcService(this);
    } else {
        return 0;
    }
}

void ShareLikeConnectEngine::contentChanged()
{
    const QVariantHash &content = containerForSource(TRACKER_SOURCE)->data();
    removeAllData("Share");
    removeAllData("Like");
    removeAllData("Connect");

    kDebug() << "going to get content for" << content["URI"].toUrl();
    if (content["URI"].value<QUrl>().isEmpty()) {
        return;
    }

    QHashIterator<QString, SLC::Provider *> it(m_providers);
    while (it.hasNext()) {
        it.next();
        SLC::Provider *provider = it.value();
        SLC::Provider::Actions actions = provider->actionsFor(content);
        kDebug() << "checkout" << it.key() << "with" << actions;
        if (actions & SLC::Provider::Share) {
            setData("Share", it.key(), provider->name());
        }

        if (actions & SLC::Provider::Like) {
            setData("Like", it.key(), provider->name());
        }

        if (actions & SLC::Provider::Connect) {
            setData("Connect", it.key(), provider->name());
        }
    }
}

QHash<QString, SLC::Provider *> ShareLikeConnectEngine::providers() const
{
    return m_providers;
}

// export the plugin; use the plugin name and the class name
K_EXPORT_PLASMA_DATAENGINE(org.kde.sharelikeconnect, ShareLikeConnectEngine)

// include the moc file so the build system makes it for us
#include "sharelikeconnect.moc"

