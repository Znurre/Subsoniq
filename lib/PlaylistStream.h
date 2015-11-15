#ifndef PLAYLISTSTREAM_H
#define PLAYLISTSTREAM_H

#include <QIODevice>
#include <QWaitCondition>
#include <QThread>
#include <QBuffer>
#include <QMutex>

#include "SubsonicAdapter.h"

class Playlist;
class PlaylistNode;

class AudioBuffer : public QBuffer
{
	Q_OBJECT

	public:
		AudioBuffer(QByteArray *buffer)
			: QBuffer(buffer)
		{

		}

	private:
		qint64 readData(char *data, qint64 maxlen) override
		{
			const qint64 size = QBuffer::readData(data, maxlen);

			if (size < maxlen)
			{
				emit bufferUnderrun();
			}

			return size;
		}

	signals:
		void bufferUnderrun();
};

class PlaylistStream : public QIODevice
{
	Q_OBJECT

	enum Status
	{
		Idle,
		Buffering
	};

	public:
		PlaylistStream(Playlist &playlist);

		qint64 bytesAvailable() const override;
		qint64 pos() const override;

		void queue(PlaylistNode *node);
		void requestNext();

	private:
		bool isSequential() const override;
		bool atEnd() const override;

		void onBufferUnderrun();
		void onReadyRead(QNetworkReply *reply);
		void onFinished(QNetworkReply *reply);

		mutable QWaitCondition m_wait;
		mutable QMutex m_waitMutex;
		mutable QMutex m_dataMutex;

		QByteArray m_array;

		AudioBuffer m_readBuffer;
		AudioBuffer m_writeBuffer;

		Playlist &m_playlist;
		SubsonicAdapter m_adapter;
		Status m_status;

		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;
};

#endif // PLAYLISTSTREAM_H
