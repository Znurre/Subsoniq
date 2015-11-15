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
#include "PlayerController.h"

class Track;

class Player : public QThread
{
	Q_OBJECT

	public:
		Player(Playlist &playlist, MetadataController &metadata);
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
		MetadataController &m_metadata;

		PlayerController m_controller;

	signals:
		void playRequested(PlaylistStream *stream);
};

#endif // PLAYER_H
