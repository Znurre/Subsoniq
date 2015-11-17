#include "Playlist.h"
#include "PlaylistNode.h"
#include "MetadataController.h"

Playlist::Playlist(MetadataController &metadata)
	: m_end(nullptr)
	, m_current(nullptr)
	, m_metadata(metadata)
{

}

void Playlist::add(Track *track)
{
	PlaylistNode *node = new PlaylistNode(track, m_end);

	if (m_end)
	{
		m_end->attach(node);
	}

	m_end = node;
	m_playlist << node;

	emit playlistChanged();
}

void Playlist::remove(PlaylistNode *node)
{
	if (m_end == node)
	{
		m_end = node->parent();
	}

	if (m_current == node)
	{
		m_current = nullptr;
	}

	m_playlist.removeAll(node);

	emit playlistChanged();
}

void Playlist::prepare(const PendingPlaylistNode &pending)
{
	m_pending = pending;
}

void Playlist::execute()
{
	PlaylistNode *node = m_pending.node();
	PlaylistNode *safe = node ?: PlaylistNode::invalid();

	m_current = node;

	Track *track = safe->track();
	PlaylistStream *stream = m_pending.stream();

	m_metadata.setCurrent(track, stream);

	qDebug() << "Current track changed";

	emit playlistChanged();
}

PlaylistNode *Playlist::current() const
{
	return m_current ?: PlaylistNode::invalid();
}

PlaylistNode *Playlist::nodeAt(int index) const
{
	return m_playlist[index];
}

int Playlist::count() const
{
	return m_playlist.count();
}

void Playlist::clear()
{
	qDeleteAll(m_playlist);

	m_playlist.clear();

	m_end = nullptr;
	m_current = nullptr;
}
