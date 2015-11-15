#include "Playlist.h"
#include "PlaylistNode.h"

Playlist::Playlist()
	: m_end(nullptr)
	, m_current(nullptr)
	, m_pending(nullptr)
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

void Playlist::prepare(PlaylistNode *node)
{
	m_pending = node;
}

void Playlist::execute()
{
	m_current = m_pending;

	qDebug() << "Current track changed";

	emit playlistChanged();
}

PlaylistNode *Playlist::current() const
{
	return m_current;
}

PlaylistNode *Playlist::nodeAt(int index) const
{
	return m_playlist[index];
}

int Playlist::count() const
{
	return m_playlist.count();
}
