#ifndef STREAMER_H
#define STREAMER_H

#include "SubsonicAdapter.h"

#include <QObject>
#include <QByteArray>

class Track;

class Streamer : public QObject
{
	Q_OBJECT

	public:
		Streamer();

		void stream(const Track *track);

	private:
		void onFinished(QNetworkReply *reply);
		void onReadyRead(QNetworkReply *reply);

		QNetworkReply *m_reply;

//		SubsonicAdapter m_adapter;

	signals:
		void dataAvailable(const QByteArray &data);
};

#endif // STREAMER_H
