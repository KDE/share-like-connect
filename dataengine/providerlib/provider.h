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

#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>

#include <KGenericFactory>

#include <kdemacros.h>

#include <Plasma/Package>

namespace SLC
{

class KDE_EXPORT Provider : public QObject
{
    Q_OBJECT

public:
    /**
     * SLC supports 3 action types:
     * * Share
     * * Like
     * * Connect
     * each plugin may support any combination of those 3 actions, depending from what is being shared: may depend from the url or the mimetype of the object, and the plugin can say that supports none, one two or all 3 of them. They can be combined as a as a flag.
     */
    enum Action { NoAction = 0,
                  Share = 1,
                  Like = 2,
                  Connect = 4 };
    Q_ENUMS(Action)
    Q_DECLARE_FLAGS(Actions, Action)

    Provider(QObject *parent, const QVariantList &args);
    Provider(QObject *parent, const Plasma::Package &package, const QString &pluginName);
    virtual ~Provider();

    /**
     * @return The localized name of this plugin. It is set an "Name" entry in its desktop file
     */
    QString name() const;

    /**
     * @return Or value of supported actions for a given content.
     * A plugin may support all three actions of Like, Share and Connect, or just one or two of the three.
     * This is dependent from the content, because more or less actions may be supported depending
     * for instance from the url in particular or from the mimetype, contained in content.
     * The default implementation returns NoAction.
     *
     * @param content the content we want to ask actions for. This hash should contain at least the keys "URI", "Mime Type" and "Window ID".
     */
    virtual Actions actionsFor(const QVariantHash &content) const;

    /**
     * @return A localized and user readable name for the action.
     * Depending from the url, mimeType or other content,
     * the plugin may want to have a different localized name for the action.
     * The default implementation returns the localized name of the plugin desktop file.
     *
     *  @param content the content we want to ask the action name for. This hash should contain at least the keys "URI", "Mime Type" and "Window ID".
     *
     *  @param action The action we want an user readable name of.
     */
    virtual QString actionName(const QVariantHash &content, Action action) const;

    /**
     * Executes an action.
     * @param action The action to execute, one of Share, Like and Connect
     *
     * @param content The content the action is about. This hash should contain at least the keys "URI", "Mime Type" and "Window ID".
     *
     * @param parameters It's an hash that contains any extra parameter the plugin wants, and is plugin-dependent. The default implementation supports an extra parameter called "Targets", that is a list of URIs. Different plugins may want different extra parameters of different type. Use of custom extra parameters may require a custom QML delegate to render actions of this type.
     *
     * @returns In case of success or failure, the variant will contain true or false respectively.
     *  In case the plugin needs a text written down by the user (in parameters), the variant will contain the string "Comment".
     *  In case the plugin needs more data to perform the action (in parameters), will return a list hashes in which each element represents a choice. Expected keys in the hash are:
     * * target: the value it will be sent to the plugin in the next step
     * * name: user readable name: it can be used to be shown in a menu
     * * connected: in the case represents an url already connected (or an object we know has already been shared) this value will be true, false otherwise.
     * A plugin may have its own special cases as return values. It will probably need a specialized QML delegate to render menu items from the given plugin.
     *
     * The default implementation does nothing.
     */
    virtual QVariant executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters);

Q_SIGNALS:
    void changed();

private:
    class Private;
    Private * const d;
};

} // namespace SLC

Q_DECLARE_OPERATORS_FOR_FLAGS(SLC::Provider::Actions)

/**
 * Register a Provider when it is contained in a loadable module
 */
#define K_EXPORT_SLC_PROVIDER(libname, classname) \
K_PLUGIN_FACTORY(slcfactory, registerPlugin<classname>();) \
K_EXPORT_PLUGIN(slcfactory("sharelikeconnect_provider_" #libname))

#endif

