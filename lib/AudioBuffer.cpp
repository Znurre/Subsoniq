#include "AudioBuffer.h"

AudioBuffer::AudioBuffer(QByteArray *buffer)
	: QBuffer(buffer)
{

}

qint64 AudioBuffer::readData(char *data, qint64 maxlen)
{
	const qint64 size = QBuffer::readData(data, maxlen);

	if (size < maxlen)
	{
		emit bufferUnderrun();
	}

	return size;
}
