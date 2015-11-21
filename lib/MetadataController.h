#ifndef METADATACONTROLLER_H
#define METADATACONTROLLER_H

#include <QMediaPlayer>
#include <QObject>

#include "Settings.h"
#include "SubsonicAdapter.h"

class Track;
class PlaylistStream;

class MetadataController : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
	Q_PROPERTY(QString title READ title NOTIFY titleChanged)

	Q_PROPERTY(int state READ state NOTIFY stateChanged)
	Q_PROPERTY(int duration READ duration NOTIFY durationChanged)
	Q_PROPERTY(int position READ position NOTIFY positionChanged)

	public:
		MetadataController();

		QString artist() const;
		QString title() const;

		int state() const;
		int duration() const;
		int position() const;

		void setCurrent(Track *current, PlaylistStream *stream);
		void setState(QMediaPlayer::State state);
		void setPosition(int position);

	private:
		Track *m_current;
		Track *m_pending;

		PlaylistStream *m_stream;

		Settings m_settings;
		SubsonicAdapter m_adapter;

		int m_state;
		int m_position;
		int m_previous;

	signals:
		void artistChanged();
		void titleChanged();
		void stateChanged();
		void durationChanged();
		void positionChanged();
};

#endif // METADATACONTROLLER_H
