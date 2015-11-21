#include "Scrobbler.h"
#include "Track.h"

Scrobbler::Scrobbler()
	: m_track(nullptr)
	, m_pending(nullptr)
{
	m_timer.setInterval(30 * 1000);
	m_timer.setSingleShot(true);

	connect(&m_timer, &QTimer::timeout, this, &Scrobbler::prepareForSubmission);
}

void Scrobbler::nowPlaying(Track *track)
{
	if (m_pending)
	{
		m_adapter.scrobble(*m_pending, true);

		m_pending = nullptr;
	}

	if (m_settings.scrobble() && track)
	{
		m_track = track;

		m_adapter.scrobble(*track, false);

		m_timer.start();
	}
}

void Scrobbler::prepareForSubmission()
{
	m_pending = m_track;
}
