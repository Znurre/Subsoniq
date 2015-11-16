#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(QObject *parent, Flags flags)
	: QMediaPlayer(parent, flags)
{

}

void MediaPlayer::playPause()
{
	switch (state())
	{
		case QMediaPlayer::PlayingState:
		{
			return pause();
		}

		case QMediaPlayer::PausedState:
		{
			return play();
		}

		default:
		{
			return;
		}
	}
}
