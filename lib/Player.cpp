#include "Player.h"
#include "PlaylistNode.h"
#include "Track.h"

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
	m_controller.pause();
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
	QMediaPlayer player(nullptr, QMediaPlayer::StreamPlayback);

	connect(&player, (void (QMediaPlayer::*)())&QMediaPlayer::metaDataChanged, &m_playlist, &Playlist::execute);
	connect(&player, &QMediaPlayer::stateChanged, this, &Player::onStateChanged);

	connect(&m_controller, &PlayerController::setMediaRequested, &player, &QMediaPlayer::setMedia);
	connect(&m_controller, &PlayerController::playRequested, &player, &QMediaPlayer::play);
	connect(&m_controller, &PlayerController::pauseRequested, &player, &QMediaPlayer::pause);

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
