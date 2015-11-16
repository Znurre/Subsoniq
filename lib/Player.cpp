#include "Player.h"
#include "PlaylistNode.h"
#include "Track.h"
#include "MetadataController.h"
#include "MediaPlayer.h"

Player::Player(Playlist &playlist, MetadataController &metadata)
	: m_playlist(playlist)
	, m_metadata(metadata)
{
	start();
}

Player::~Player()
{
	quit();
}

void Player::play(PlaylistNode *node)
{
	if (node)
	{
		PlaylistStream *stream = new PlaylistStream(m_playlist);
		stream->queue(node);

		m_controller.setMedia(nullptr, stream);
		m_controller.play();
	}
}

void Player::playPause()
{
	m_controller.playPause();
}

void Player::previous()
{
	PlaylistNode *current = m_playlist.current();

	if (current)
	{
		PlaylistNode *previous = current->parent();

		play(previous);
	}
}

void Player::next()
{
	PlaylistNode *current = m_playlist.current();

	if (current)
	{
		PlaylistNode *next = current->child();

		play(next);
	}
}

void Player::run()
{
	MediaPlayer player(nullptr, QMediaPlayer::StreamPlayback);

	connect(&player, (void (QMediaPlayer::*)())&QMediaPlayer::metaDataChanged, &m_playlist, &Playlist::execute);
	connect(&player, &QMediaPlayer::stateChanged, &m_playlist, &Playlist::execute);

	connect(&player, &QMediaPlayer::stateChanged, &m_metadata, &MetadataController::setState);
	connect(&player, &QMediaPlayer::positionChanged, &m_metadata, &MetadataController::setPosition);

	connect(&m_controller, &PlayerController::setMediaRequested, &player, &MediaPlayer::setMedia);
	connect(&m_controller, &PlayerController::playRequested, &player, &MediaPlayer::play);
	connect(&m_controller, &PlayerController::playPauseRequested, &player, &MediaPlayer::playPause);

	exec();
}

void Player::onStateChanged(QMediaPlayer::State state)
{
	qDebug() << state;

//	if (state == QMediaPlayer::StoppedState)
//	{
//		m_playlist.prepare(nullptr);
//		m_playlist.execute();
//	}
}
