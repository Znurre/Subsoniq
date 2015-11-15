#ifndef METADATACONTROLLER_H
#define METADATACONTROLLER_H

#include <QObject>

class Playlist;
class Track;

class MetadataController : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Playlist *playlist READ playlist WRITE setPlaylist NOTIFY playlistChanged)

	Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
	Q_PROPERTY(QString title READ title NOTIFY titleChanged)
	Q_PROPERTY(QString formattedTitle READ formattedTitle NOTIFY formattedTitleChanged)

	Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)

	public:
		MetadataController();

		Playlist *playlist() const;
		void setPlaylist(Playlist *playlist);

		QString artist() const;
		QString title() const;
		QString formattedTitle() const;

		bool isPlaying() const;

	private:
		void raiseMetadataChanged();

		Track *getCurrentTrack() const;

		Playlist *m_playlist;

	signals:
		void playlistChanged();
		void artistChanged();
		void titleChanged();
		void formattedTitleChanged();
		void isPlayingChanged();
};

#endif // METADATACONTROLLER_H
