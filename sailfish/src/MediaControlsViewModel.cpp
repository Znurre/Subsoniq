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

	emit metadataChanged();
	emit displayTitleChanged();
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
				return "image://theme/icon-m-play";
			}

			case QMediaPlayer::PlayingState:
			{
				return "image://theme/icon-m-pause";
			}

			default:
			{
				return QString::null;
			}
		}
	}

	return QString::null;
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
