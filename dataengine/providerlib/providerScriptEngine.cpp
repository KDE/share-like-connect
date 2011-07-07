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

#include "providerScriptEngine_p.h"

#include <QFile>
#include <QScriptEngine>

#include <KGlobal>
#include <KStandardDirs>

#include <Plasma/Package>

namespace SLC
{

ProviderScriptEngine::ProviderScriptEngine(Plasma::Package *package, QObject *parent)
    : QScriptEngine(parent),
      m_package(package),
      m_allowedUrls(HttpUrls)
{
    QScriptValue value = globalObject();
    value.setProperty("addEventListener", newFunction(ProviderScriptEngine::addEventListener));
    value.setProperty("removeEventListener", newFunction(ProviderScriptEngine::removeEventListener));
    registerOpenUrl(value);
    registerGetUrl(value);
}

bool ProviderScriptEngine::include(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        kWarning() << i18n("Unable to load scriptEngine file: %1", path);
        return false;
    }

    const QString script = file.readAll();

    // change the context to the parent context so that the include is actually
    // executed in the same context as the caller; seems to be what javascriptEngine
    // coders expect :)
    QScriptContext *context = currentContext();
    if (context && context->parentContext()) {
        context->setActivationObject(context->parentContext()->activationObject());
        context->setThisObject(context->parentContext()->thisObject());
    }

    evaluate(script, path);
    return !checkForErrors(false);
}

bool ProviderScriptEngine::checkForErrors(bool fatal)
{
    if (hasUncaughtException()) {
        reportError();
        if (!fatal) {
            clearExceptions();
        }
        return true;
    }

    return false;
}

void ProviderScriptEngine::reportError()
{
    const QScriptValue error = uncaughtException();
    QString file = error.property("fileName").toString();
    file.remove(m_package->path());

    const QString failureMsg = i18n("Error in %1 on line %2.<br><br>%3",
                                    file, error.property("lineNumber").toString(),
                                    error.toString());
    kDebug() << failureMsg;
    kDebug() << uncaughtExceptionBacktrace();
}

QScriptValue ProviderScriptEngine::callFunction(QScriptValue &func, const QScriptValueList &args, const QScriptValue &activator)
{
    if (!func.isFunction()) {
        return undefinedValue();
    }

    QScriptContext *ctx = pushContext();
    ctx->setActivationObject(activator);
    QScriptValue rv = func.call(activator, args);
    popContext();

    if (hasUncaughtException()) {
        clearExceptions();
        return undefinedValue();
    }

    return rv;
}

bool ProviderScriptEngine::callEventListeners(const QString &event, const QScriptValueList &args)
{
    if (!m_eventListeners.contains(event.toLower())) {
        return false;
    }

    QScriptValueList funcs = m_eventListeners.value(event.toLower());
    QMutableListIterator<QScriptValue> it(funcs);
    while (it.hasNext()) {
        callFunction(it.next(), args);
    }

    return true;
}

QScriptValue ProviderScriptEngine::addEventListener(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() < 2) {
        return false;
    }

    ProviderScriptEngine *env = qobject_cast<ProviderScriptEngine *>(engine);
    if (!env) {
        return false;
    }

    return env->addEventListener(context->argument(0).toString(), context->argument(1));
}

QScriptValue ProviderScriptEngine::removeEventListener(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() < 2) {
        return false;
    }

    ProviderScriptEngine *env = qobject_cast<ProviderScriptEngine *>(engine);
    if (!env) {
        return false;
    }

    return env->removeEventListener(context->argument(0).toString(), context->argument(1));
}

bool ProviderScriptEngine::addEventListener(const QString &event, const QScriptValue &func)
{
    if (func.isFunction() && !event.isEmpty()) {
        m_eventListeners[event.toLower()].append(func);
        return true;
    }

    return false;
}

bool ProviderScriptEngine::removeEventListener(const QString &event, const QScriptValue &func)
{
    bool found = false;

    if (func.isFunction()) {
        QScriptValueList funcs = m_eventListeners.value(event);
        QMutableListIterator<QScriptValue> it(funcs);
        while (it.hasNext()) {
            if (it.next().equals(func)) {
                it.remove();
                found = true;
            }
        }

        if (funcs.isEmpty()) {
            m_eventListeners.remove(event.toLower());
        } else {
            m_eventListeners.insert(event.toLower(), funcs);
        }
    }

    return found;
}

}

#include "providerScriptEngine_p.moc"

