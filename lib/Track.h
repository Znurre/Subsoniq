#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QJsonObject>

class Track
{
	public:
		Track(const QJsonObject &object);

		QString id() const;
		QString artist() const;
		QString title() const;
		QString coverArt() const;
		QString album() const;

		int duration() const;
		int size() const;
		int track() const;

		operator QString() const;

	private:
		QJsonObject m_object;
};

#endif // TRACK_H
