#ifndef STOREDPLAYLISTENVELOPE_H
#define STOREDPLAYLISTENVELOPE_H

#include <QObject>
#include <QJsonSerializer>

#include "StoredPlaylist.h"

class StoredPlaylistEnvelope : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Array<StoredPlaylist *> playlist READ playlists WRITE setPlaylists)

	public:
		Q_INVOKABLE StoredPlaylistEnvelope() = default;

		Array<StoredPlaylist *> playlists() const;
		void setPlaylists(const Array<StoredPlaylist *> &playlists);

	private:
		Array<StoredPlaylist *> m_playlists;
};

#endif // STOREDPLAYLISTENVELOPE_H
