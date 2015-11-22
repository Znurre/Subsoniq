#include "MetadataController.h"
#include "Playlist.h"
#include "Track.h"

MetadataController::MetadataController()
	: m_current(nullptr)
	, m_stream(nullptr)
	, m_state(QMediaPlayer::StoppedState)
	, m_position(0)
	, m_previous(0)
{

}

QString MetadataController::artist() const
{
	if (m_current)
	{
		return m_current->artist();
	}

	return QString::null;
}

QString MetadataController::title() const
{
	if (m_current)
	{
		return m_current->title();
	}

	return QString::null;
}

int MetadataController::state() const
{
	return m_state;
}

int MetadataController::duration() const
{
	if (m_current)
	{
		return m_current->duration();
	}

	return 0;
}

int MetadataController::position() const
{
	return (m_position - m_previous) / 1000;
}

void MetadataController::setCurrent(Track *current, PlaylistStream *stream)
{
	qDebug() << current;

	m_current = current;

	if (m_current == EndOfPlaylist)
	{
		m_state = QMediaPlayer::StoppedState;

		emit stateChanged();
	}

	if (m_stream != stream)
	{
		m_stream = stream;
		m_previous = 0;
	}
	else
	{
		m_previous += m_position;
	}

	m_scrobbler.nowPlaying(m_current);

	emit artistChanged();
	emit titleChanged();
	emit durationChanged();
}

void MetadataController::setState(QMediaPlayer::State state)
{
	qDebug() << "State change requested" << state;

	if (state != QMediaPlayer::StoppedState)
	{
		m_state = state;

		qDebug() << "State set to" << state;

		emit stateChanged();
	}
}

void MetadataController::setPosition(int position)
{
	m_position = position;

	emit positionChanged();
}
