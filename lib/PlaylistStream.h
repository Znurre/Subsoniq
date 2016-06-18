#ifndef PLAYLISTSTREAM_H
#define PLAYLISTSTREAM_H

#include <QIODevice>
#include <QWaitCondition>
#include <QThread>
#include <QBuffer>
#include <QMutex>

#include "SubsonicAdapter.h"
#include "AudioBuffer.h"

class Playlist;
class PlaylistNode;
class MetadataController;

class PlaylistStream : public QIODevice
{
	Q_OBJECT

	enum Status
	{
		Idle,
		Buffering,
		End
	};

	public:
		PlaylistStream(Playlist &playlist);

		void queue(PlaylistNode *node);
		void requestNext();

	private:
		bool isSequential() const override;
		bool atEnd() const override;

		qint64 bytesAvailable() const override;
		qint64 pos() const override;
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

		void onBufferUnderrun();
		void onReadyRead(QNetworkReply *reply);
		void onFinished(QNetworkReply *reply);
		void onError();

		mutable QWaitCondition m_wait;
		mutable QMutex m_waitMutex;
		mutable QMutex m_dataMutex;

		QByteArray m_array;

		AudioBuffer m_readBuffer;
		AudioBuffer m_writeBuffer;

		Playlist &m_playlist;
		SubsonicAdapter m_adapter;
		Status m_status;
};

#endif // PLAYLISTSTREAM_H
