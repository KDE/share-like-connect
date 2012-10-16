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

#include "kipiProvider.h"
#include "kipiinterface.h"

#include <KService>

#include <Nepomuk2/Tag>
#include <Nepomuk2/Resource>
#include <Nepomuk2/Variant>

#include <soprano/vocabulary.h>

#include <libkipi/interface.h>

KipiProvider::KipiProvider(QObject *parent, const QVariantList &args)
    : SLC::Provider(parent, args)
{
     KIPI::Interface *interface = new KIPIInterface(this);
     m_pluginLoader = new KIPI::PluginLoader(0);
     m_pluginLoader->setInterface(interface);
     m_pluginLoader->init();
    //new KIPI::PluginLoader(QStringList(), new KIPIInterface(this), "");
    //m_pluginLoader = KIPI::PluginLoader::instance();
    //m_pluginLoader->init();
}

SLC::Provider::Actions KipiProvider::actionsFor(const QVariantHash &content) const
{
    return Share;
}

KUrl KipiProvider::lastUrl() const
{
    return m_lastUrl;
}

QVariant KipiProvider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (action != Share) {
        return false;
    }

    const QString resourceUrl = content["URI"].toString();
    m_lastUrl = resourceUrl;

    QString targetPlugin;
    if (!parameters["Targets"].toStringList().isEmpty()) {
        targetPlugin = parameters["Targets"].toStringList().first();
    }

    //first step
    if (targetPlugin.isEmpty()) {

        //list kipi
        QList<QVariant> result;
        QVariantHash item;


        KIPI::PluginLoader::PluginList pluginList = m_pluginLoader->pluginList();
kWarning()<<"BBBBBBBBBBBBBBB"<<pluginList;
        Q_FOREACH(KIPI::PluginLoader::Info* pluginInfo, pluginList) {
kWarning()<<"AAAAAAAAAAAAAAA"<<pluginInfo->name();
            if (!pluginInfo->shouldLoad()) {
                continue;
            }
            QVariantHash item;
            item["target"] = pluginInfo->library();
            item["name"] = pluginInfo->name();

            result << item;
        }
        return result;
    }

    //second step

    

    return true;
}

//K_EXPORT_SLC_PROVIDER(activities, KipiProvider)
K_PLUGIN_FACTORY(factory, registerPlugin<KipiProvider>();)
K_EXPORT_PLUGIN(factory("sharelikeconnect_provider_kipi"))

#include "kipiProvider.moc"

