#include "MediaStream.h"
#include "SenderInjector.h"
#include "Track.h"

MediaStream::MediaStream(const Track *track)
	: m_track(track)
	, m_reply(nullptr)
	, m_pos(0)
{
//	m_readBuffer.open(QIODevice::ReadOnly);
//	m_writeBuffer.open(QIODevice::WriteOnly);

//	setOpenMode(QIODevice::ReadOnly);

	qDebug() << "Thread" << QThread::currentThreadId();
}

bool MediaStream::open(QIODevice::OpenMode mode)
{
	setOpenMode(mode);

//	QMetaObject::invokeMethod(&m_foo, "stream", Qt::QueuedConnection);

	m_reply = m_adapter.stream(*m_track);

	connect(m_reply, &QIODevice::readyRead, this, &MediaStream::readyRead);

	qDebug() << "open";

	return true;
}

bool MediaStream::isSequential() const
{
	return true;
}

qint64 MediaStream::bytesAvailable() const
{
	const int size = m_reply->bytesAvailable();

	if (!size)
	{
		if (m_reply->isFinished())
		{
			return 0;
		}

		return -1;
	}

	return size;
}

qint64 MediaStream::pos() const
{
	return m_pos;
}

void MediaStream::onReadyRead()
{
	qDebug() << "onReadyRead" << QThread::currentThreadId();
}

qint64 MediaStream::readData(char *data, qint64 maxlen)
{
	const int size = m_reply->read(data, maxlen);

	m_pos += size;

	return size;
}

qint64 MediaStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}
