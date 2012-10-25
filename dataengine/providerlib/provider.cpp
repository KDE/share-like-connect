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

#include "provider.h"

#include <KStandardDirs>

#include "providerScriptEngine_p.h"

namespace SLC
{

class Provider::Private
{
public:
    Private()
        : scriptEngine(0),
          package(0)
    {
    }


    ~Private()
    {
        delete scriptEngine;
        delete package;
    }

    QString pluginName;
    QString name;
    ProviderScriptEngine *scriptEngine;
    Plasma::Package *package;
};

Provider::Provider(QObject *parent, const QVariantList &args)
    : QObject(parent),
      d(new Private)
{
    d->pluginName = args.isEmpty() ? QString("Unnamed") : args[0].toString();
    d->name = args.length() < 2 ? QString("Unnamed") : args[1].toString();
}

Provider::Provider(QObject *parent, const Plasma::Package &package, const QString &pluginName)
    : QObject(parent),
      d(new Private)
{
    d->pluginName = pluginName;
    d->name = package.metadata().name();

    const QString mainscriptEngine = package.filePath("mainscript");
    if (mainscriptEngine.isEmpty()) {
#ifndef NDEBUG
        kDebug() << "no main scriptEngine, should not be possible!";
#endif
        return;
    }

    d->package = new Plasma::Package(package);
    d->scriptEngine = new ProviderScriptEngine(d->package, this);

    const QString translationsPath = package.filePath("translations");
    if (!translationsPath.isEmpty()) {
        KGlobal::dirs()->addResourceDir("locale", translationsPath);
        KGlobal::locale()->insertCatalog(package.metadata().pluginName());
    }

    if (!d->scriptEngine->include(mainscriptEngine)) {
#ifndef NDEBUG
        kDebug() << "no main scriptEngine, should not be possible!";
#endif
        delete d->scriptEngine;
        d->scriptEngine = 0;
        delete d->package;
        d->package = 0;
    }
}

Provider::~Provider()
{
    if (d->package) {
        const QString translationsPath = d->package->filePath("translations");
        if (!translationsPath.isEmpty()) {
            //FIXME: KGlobal::dirs()->removeResourceDir("locale", translationsPath);
            KGlobal::locale()->removeCatalog(d->package->metadata().pluginName());
        }
    }

    delete d;
}

template <class M>
QScriptValue qScriptValueFromMap(QScriptEngine *eng, const M &map)
{
#ifndef NDEBUG
    //kDebug() << "qScriptValueFromMap called";
#endif
    QScriptValue obj = eng->newObject();
    typename M::const_iterator begin = map.constBegin();
    typename M::const_iterator end = map.constEnd();
    typename M::const_iterator it;
    for (it = begin; it != end; ++it) {
        if (it.value().type() == QVariant::Hash) {
            obj.setProperty(it.key(), qScriptValueFromMap(eng, it.value().toHash()));
        } else if (it.value().type() == QVariant::Map) {
            obj.setProperty(it.key(), qScriptValueFromMap(eng, it.value().toMap()));
        } else {
            obj.setProperty(it.key(), qScriptValueFromValue(eng, it.value()));
        }
    }

    return obj;
}

Provider::Actions Provider::actionsFor(const QVariantHash &content) const
{
    if (d->scriptEngine) {
        QScriptValue func = d->scriptEngine->globalObject().property("actionsFor");
        QScriptValueList args;
        args << qScriptValueFromValue(d->scriptEngine, content);
        return static_cast<Provider::Actions>(d->scriptEngine->callFunction(func, args).toInt32());
    }

    return NoAction;
}

QString Provider::actionName(const QVariantHash &content, Action action)
{
    if (d->scriptEngine) {
        QScriptValue func = d->scriptEngine->globalObject().property("actionName");

        if (!func.isValid()) {
            return d->name;
        }

        QScriptValueList args;
        args << qScriptValueFromValue(d->scriptEngine, content);
        args << qScriptValueFromValue(d->scriptEngine, (int)action);
        QString result = d->scriptEngine->callFunction(func, args).toString();
        if (!result.isEmpty()) {
            return result;
        }
    }

    return d->name;
}

QVariant Provider::executeAction(SLC::Provider::Action action, const QVariantHash &content, const QVariantHash &parameters)
{
    if (d->scriptEngine) {
        QScriptValueList args;
        args << action;
        args << qScriptValueFromValue(d->scriptEngine, content);
        args << qScriptValueFromValue(d->scriptEngine, parameters);
        return d->scriptEngine->callEventListeners("executeAction", args);
    }

    return false;
}

QString Provider::name() const
{
    return d->name;
}

} // namespace SLC

#include "provider.moc"
