#include <QDebug>

#include "MetadataController.h"
#include "Playlist.h"
#include "PlaylistNode.h"
#include "Track.h"
#include "QStringEx.h"

MetadataController::MetadataController()
	: m_playlist(nullptr)
{
}

Playlist *MetadataController::playlist() const
{
	return m_playlist;
}

void MetadataController::setPlaylist(Playlist *playlist)
{
	qDebug() << playlist;

	m_playlist = playlist;

	if (playlist)
	{
		connect(playlist, &Playlist::playlistChanged, this, &MetadataController::raiseMetadataChanged);
	}

	raiseMetadataChanged();
}

QString MetadataController::artist() const
{
	Track *track = getCurrentTrack();

	if (track)
	{
		return track->artist();
	}

	return QString::null;
}

QString MetadataController::title() const
{
	Track *track = getCurrentTrack();

	if (track)
	{
		return track->title();
	}

	return QString::null;
}

QString MetadataController::formattedTitle() const
{
	Track *track = getCurrentTrack();

	if (track)
	{
		const QString &artist = this->artist();
		const QString &title = this->title();
		const QString &formatted = QStringEx::format("%1 - %2", artist, title);

		return formatted;
	}

	return QString::null;
}

bool MetadataController::isPlaying() const
{
	return getCurrentTrack();
}

void MetadataController::raiseMetadataChanged()
{
	emit playlistChanged();
	emit artistChanged();
	emit titleChanged();
	emit formattedTitleChanged();
	emit isPlayingChanged();
}

Track *MetadataController::getCurrentTrack() const
{
	if (m_playlist)
	{
		PlaylistNode *current = m_playlist->current();

		if (current)
		{
			return current->track();
		}
	}

	return nullptr;
}
