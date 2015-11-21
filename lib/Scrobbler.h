#ifndef SCROBBLER_H
#define SCROBBLER_H

#include <QObject>
#include <QTimer>

#include "Settings.h"
#include "SubsonicAdapter.h"

class Track;

class Scrobbler : public QObject
{
	public:
		Scrobbler();

		void nowPlaying(Track *track);

	private:
		void prepareForSubmission();

		QTimer m_timer;

		Settings m_settings;
		SubsonicAdapter m_adapter;

		Track *m_track;
		Track *m_pending;
};

#endif // SCROBBLER_H
