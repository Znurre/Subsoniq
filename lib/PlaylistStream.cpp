#include <QDebug>

#include "PlaylistStream.h"
#include "Playlist.h"
#include "PlaylistNode.h"
#include "Track.h"
#include "SenderInjector.h"
#include "MetadataController.h"

PlaylistStream::PlaylistStream(Playlist &playlist)
	: m_readBuffer(&m_array)
	, m_writeBuffer(&m_array)
	, m_playlist(playlist)
	, m_status(Idle)
{
	m_readBuffer.open(QIODevice::ReadOnly);
	m_writeBuffer.open(QIODevice::WriteOnly);

	setOpenMode(QIODevice::ReadOnly);

	connect(&m_readBuffer, &AudioBuffer::bufferUnderrun, this, &PlaylistStream::onBufferUnderrun);
}

void PlaylistStream::queue(PlaylistNode *node)
{
	PendingPlaylistNode pending(this, node);

	m_playlist.prepare(pending);

	if (node)
	{
		Track *track = node->track();

		QNetworkReply *reply = m_adapter.stream(*track);

		ISenderInjector *readyRead = SenderInjector::create(reply, this, &PlaylistStream::onReadyRead);
		ISenderInjector *finished = SenderInjector::create(reply, this, &PlaylistStream::onFinished);

		connect(reply, &QNetworkReply::readyRead, readyRead, &ISenderInjector::invoke);
		connect(reply, &QNetworkReply::finished, finished, &ISenderInjector::invoke);
		connect(reply, (void (QNetworkReply::*)(QNetworkReply::NetworkError))&QNetworkReply::error, this, &PlaylistStream::onError);

		m_status = Buffering;
	}
	else
	{
		m_status = End;

		qDebug() << "This is the end";
	}
}

void PlaylistStream::requestNext()
{
	qDebug() << "Request next";

	PlaylistNode *current = m_playlist.current();
	PlaylistNode *next = current->child();

//	if (!next)
//	{
//		qDebug() << "We've reached the end of the playlist";

//		static const PendingPlaylistNode pending;

//		m_playlist.prepare(pending);
//		m_playlist.execute();
//	}
//	else
//	{
		queue(next);
//	}
}

bool PlaylistStream::isSequential() const
{
	return true;
}

bool PlaylistStream::atEnd() const
{
	const QMutexLocker dataLock(&m_dataMutex);

	return m_readBuffer.atEnd();
}

void PlaylistStream::onBufferUnderrun()
{
	if (m_status == Idle)
	{
		requestNext();
	}
}

qint64 PlaylistStream::bytesAvailable() const
{
	while (atEnd() && m_status != End)
	{
		const QMutexLocker waitLock(&m_waitMutex);

		m_wait.wait(&m_waitMutex);
	}

	const QMutexLocker dataLock(&m_dataMutex);

	return m_readBuffer.bytesAvailable();
}

qint64 PlaylistStream::pos() const
{
	const QMutexLocker dataLock(&m_dataMutex);

	return m_readBuffer.pos();
}

void PlaylistStream::onReadyRead(QNetworkReply *reply)
{
	const QMutexLocker dataLock(&m_dataMutex);
	const QByteArray &data = reply->readAll();

	m_writeBuffer.write(data);
	m_wait.wakeAll();
}

void PlaylistStream::onFinished(QNetworkReply *reply)
{
	if (m_status != End)
	{
		m_status = Idle;
	}

	reply->deleteLater();
}

void PlaylistStream::onError()
{
	qDebug() << "Error";

	m_status = End;
}

qint64 PlaylistStream::readData(char *data, qint64 maxlen)
{
	const QMutexLocker dataLock(&m_dataMutex);

	return m_readBuffer.read(data, maxlen);
}

qint64 PlaylistStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}
