#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

class Utility : public QObject
{
	Q_OBJECT

	public:
		static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

		Q_INVOKABLE QString formatTrack(const QString &artist, const QString &title);
};

#endif // UTILITY_H
