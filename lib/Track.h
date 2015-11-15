#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QJsonObject>
#include <QMetaType>

class Track : public QObject
{
	Q_OBJECT

	public:
		Track(const QJsonObject &object);

		QString id() const;
		QString artist() const;
		QString title() const;
		QString coverArt() const;

		int size() const;

		operator QString() const;

	private:
		QJsonObject m_object;
};

Q_DECLARE_METATYPE(Track *)

#endif // TRACK_H
