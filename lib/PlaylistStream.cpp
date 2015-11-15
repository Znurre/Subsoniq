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
	m_playlist.prepare(node);

	const Track *track = node->track();

	QNetworkReply *reply = m_adapter.stream(*track);

	ISenderInjector *readyRead = SenderInjector::create(reply, this, &PlaylistStream::onReadyRead);
	ISenderInjector *finished = SenderInjector::create(reply, this, &PlaylistStream::onFinished);

	connect(reply, &QNetworkReply::readyRead, readyRead, &ISenderInjector::invoke);
	connect(reply, &QNetworkReply::finished, finished, &ISenderInjector::invoke);

	m_status = Buffering;
}

void PlaylistStream::requestNext()
{
	qDebug() << "Request next";

	PlaylistNode *current = m_playlist.current();
	PlaylistNode *next = current->child();

	if (!next)
	{
		qDebug() << "We've reached the end of the playlist";

		m_playlist.prepare(nullptr);
		m_playlist.execute();
	}
	else
	{
		queue(next);
	}
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
	while (atEnd())
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
	m_status = Idle;

	reply->deleteLater();
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
