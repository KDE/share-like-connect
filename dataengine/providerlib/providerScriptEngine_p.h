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

#ifndef PROVIDERSCRIPTENGINE_H
#define PROVIDERSCRIPTENGINE_H

#include <QScriptEngine>

namespace Plasma
{
    class Package;
} // namespace Plasma

namespace SLC
{

class ProviderScriptEngine : public QScriptEngine
{
    Q_OBJECT

public:
    enum AllowedUrl { NoUrls = 0,
                      HttpUrls = 1,
                      NetworkUrls = 2,
                      LocalUrls = 4,
                      AppLaunching = 8};
    Q_DECLARE_FLAGS(AllowedUrls, AllowedUrl)

    explicit ProviderScriptEngine(Plasma::Package *package, QObject *parent = 0);

    bool include(const QString &path);
    bool callEventListeners(const QString &event, const QScriptValueList &args);
    QScriptValue callFunction(QScriptValue &func, const QScriptValueList &args = QScriptValueList(), const QScriptValue &activator = QScriptValue());

private:
    void registerGetUrl(QScriptValue &obj);
    void registerOpenUrl(QScriptValue &obj);
    void reportError();
    bool checkForErrors(bool fatal);
    bool addEventListener(const QString &event, const QScriptValue &func);
    bool removeEventListener(const QString &event, const QScriptValue &func);

    // helpers
    static ProviderScriptEngine * findProviderScriptEngine(QScriptEngine *engine) { return qobject_cast<ProviderScriptEngine *>(engine); }

    // for the script env
    static QScriptValue addEventListener(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue removeEventListener(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue openUrl(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue getUrl(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue userDataPath(QScriptContext *context, QScriptEngine *engine);

private:
    QHash<QString, QScriptValueList> m_eventListeners;
    Plasma::Package *m_package;
    AllowedUrls m_allowedUrls;
};

} // namespace SLC

#endif

