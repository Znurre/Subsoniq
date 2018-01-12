#include "StoredPlaylistEnvelope.h"

Array<StoredPlaylist *> StoredPlaylistEnvelope::playlists() const
{
	return m_playlists;
}

void StoredPlaylistEnvelope::setPlaylists(const Array<StoredPlaylist *> &playlists)
{
	m_playlists = playlists;
}
