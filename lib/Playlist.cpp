#include "Playlist.h"
#include "PlaylistNode.h"
#include "MetadataController.h"
#include "Track.h"

Playlist::Playlist(MetadataController &metadata)
	: m_end(nullptr)
	, m_current(nullptr)
	, m_metadata(metadata)
{

}

void Playlist::add(Track *track)
{
	const int index = count();

	Track *copy = new Track(*track);
	PlaylistNode *node = new PlaylistNode(copy, m_end);

	if (m_end)
	{
		m_end->attach(node);
	}

	m_end = node;
	m_playlist << node;

	emit nodeAppended(index);
}

void Playlist::remove(PlaylistNode *node)
{
	const int index = count();

	if (m_end == node)
	{
		m_end = node->parent();
	}

	if (m_current == node)
	{
		m_current = nullptr;
	}

	m_playlist.removeAll(node);

	emit nodeRemoved(index);
}

void Playlist::prepare(const PendingPlaylistNode &pending)
{
	m_pending = pending;
}

void Playlist::execute()
{
	PlaylistNode *current = m_current;
	PlaylistNode *node = m_pending.node();
	PlaylistNode *safe = node ?: PlaylistNode::invalid();

	if (safe != m_current)
	{
		m_current = node;

		Track *track = safe->track();
		PlaylistStream *stream = m_pending.stream();

		m_metadata.setCurrent(track, stream);

		qDebug() << "Current track changed";

		raiseNodeChanged(current);
		raiseNodeChanged(node);
	}
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

void Playlist::raiseNodeChanged(PlaylistNode *node)
{
	for (int i = 0; i < m_playlist.count(); i++)
	{
		if (m_playlist[i] == node)
		{
			emit nodeChanged(i);
		}
	}
}

void Playlist::clear()
{
	qDeleteAll(m_playlist);

	m_playlist.clear();

	m_end = nullptr;
	m_current = nullptr;
}
