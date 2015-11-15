#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioDecoder>
#include <QBuffer>
#include <QFile>
#include <QThread>
#include <QWaitCondition>

#include "Playlist.h"
#include "PlaylistStream.h"

class Track;

class PlayerController : public QObject
{
	Q_OBJECT

	public:
		void play()
		{
			emit playRequested();
		}

		void pause()
		{
			emit pauseRequested();
		}

		void setMedia(const QMediaContent &media, QIODevice *stream)
		{
			emit setMediaRequested(media, stream);
		}

	signals:
		void playRequested();
		void pauseRequested();
		void setMediaRequested(const QMediaContent &media, QIODevice *stream);
};

class Player : public QThread
{
	Q_OBJECT

	public:
		Player(Playlist &playlist);
		~Player();

	public slots:
		void play(PlaylistNode *node);
		void playPause();
		void previous();
		void next();

	private:
		void run() override;
		void onStateChanged(QMediaPlayer::State state);

		Playlist &m_playlist;
		PlayerController m_controller;

	signals:
		void playRequested(PlaylistStream *stream);
};

#endif // PLAYER_H
