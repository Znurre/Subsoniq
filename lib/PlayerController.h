#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QIODevice>
#include <QMediaContent>
#include <QObject>

class PlayerController : public QObject
{
	Q_OBJECT

	public:
		void play();
		void pause();
		void setMedia(const QMediaContent &media, QIODevice *stream);

	signals:
		void playRequested();
		void pauseRequested();
		void setMediaRequested(const QMediaContent &media, QIODevice *stream);
};

#endif // PLAYERCONTROLLER_H
