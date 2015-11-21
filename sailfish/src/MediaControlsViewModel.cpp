#include "MediaControlsViewModel.h"
#include "MetadataController.h"
#include "Player.h"
#include "QStringEx.h"

MediaControlsViewModel::MediaControlsViewModel()
	: m_player(nullptr)
	, m_metadata(nullptr)
{
}

Player *MediaControlsViewModel::player() const
{
	return m_player;
}

void MediaControlsViewModel::setPlayer(Player *player)
{
	m_player = player;

	emit playerChanged();
	emit displayTitleChanged();
	emit playPauseIconChanged();
}

MetadataController *MediaControlsViewModel::metadata() const
{
	return m_metadata;
}

void MediaControlsViewModel::setMetadata(MetadataController *metadata)
{
	m_metadata = metadata;

	connect(m_metadata, &MetadataController::artistChanged, this, &MediaControlsViewModel::displayTitleChanged);
	connect(m_metadata, &MetadataController::titleChanged, this, &MediaControlsViewModel::displayTitleChanged);
	connect(m_metadata, &MetadataController::stateChanged, this, &MediaControlsViewModel::playPauseIconChanged);
	connect(m_metadata, &MetadataController::stateChanged, this, &MediaControlsViewModel::isPlayingChanged);

	emit metadataChanged();
	emit displayTitleChanged();
	emit playPauseIconChanged();
	emit isPlayingChanged();
}

QString MediaControlsViewModel::playIcon() const
{
	return m_playIcon;
}

void MediaControlsViewModel::setPlayIcon(const QString &playIcon)
{
	m_playIcon = playIcon;

	emit playPauseIconChanged();
}

QString MediaControlsViewModel::pauseIcon() const
{
	return m_pauseIcon;
}

void MediaControlsViewModel::setPauseIcon(const QString &pauseIcon)
{
	m_pauseIcon = pauseIcon;

	emit playPauseIconChanged();
}

QString MediaControlsViewModel::displayTitle() const
{
	if (m_metadata)
	{
		const QString &artist = m_metadata->artist();
		const QString &title = m_metadata->title();

		if (!artist.isEmpty())
		{
			return QStringEx::format("%1 - %2", artist, title);
		}

		return title;
	}

	return QString::null;
}

QString MediaControlsViewModel::playPauseIcon() const
{
	if (m_metadata)
	{
		const int state = m_metadata->state();

		switch (state)
		{
			case QMediaPlayer::PausedState:
			{
				return m_playIcon;
			}

			case QMediaPlayer::PlayingState:
			{
				return m_pauseIcon;
			}

			default:
			{
				return QString::null;
			}
		}
	}

	return QString::null;
}

bool MediaControlsViewModel::isPlaying() const
{
	if (m_metadata)
	{
		return m_metadata->state() > QMediaPlayer::StoppedState;
	}

	return false;
}

void MediaControlsViewModel::playPause()
{
	const int state = m_metadata->state();

	switch (state)
	{
		case QMediaPlayer::PausedState:
		{
			return m_player->resume();
		}

		case QMediaPlayer::PlayingState:
		{
			return m_player->pause();
		}

		default:
		{
			return;
		}
	}
}
