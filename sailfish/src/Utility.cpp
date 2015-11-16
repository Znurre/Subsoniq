#include "Utility.h"
#include "QStringEx.h"

QObject *Utility::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine);
	Q_UNUSED(scriptEngine);

	static Utility instance;

	return &instance;
}

QString Utility::formatTrack(const QString &artist, const QString &title)
{
	return QStringEx::format("%1 - %2", artist, title);
}
