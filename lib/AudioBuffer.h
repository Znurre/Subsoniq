#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <QBuffer>

class AudioBuffer : public QBuffer
{
	Q_OBJECT

	public:
		AudioBuffer(QByteArray *buffer);

	private:
		qint64 readData(char *data, qint64 maxlen) override;

	signals:
		void bufferUnderrun();
};

#endif // AUDIOBUFFER_H
