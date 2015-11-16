#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>

class MediaPlayer : public QMediaPlayer
{
	public:
		MediaPlayer(QObject *parent, Flags flags);

	public slots:
		void playPause();
};

#endif // MEDIAPLAYER_H
