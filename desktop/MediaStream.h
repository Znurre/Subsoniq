#ifndef STREAM_H
#define STREAM_H

#include <QNetworkReply>
#include <QIODevice>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QBuffer>

#include "SubsonicAdapter.h"

class Track;

class MediaStream : public QIODevice
{
	public:
		MediaStream(const Track *track);

		bool open(OpenMode mode) override;
		bool isSequential() const override;

		qint64 bytesAvailable() const override;
		qint64 pos() const override;

	private:
		void onReadyRead();

		const Track *m_track;

		SubsonicAdapter m_adapter;

		QNetworkReply *m_reply;

		qint64 m_pos;

		// QIODevice interface
	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;
};

#endif // STREAM_H
