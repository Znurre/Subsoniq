#include "StoredPlaylist.h"
#include "QStringEx.h"

QString StoredPlaylist::id() const
{
	return m_id;
}

void StoredPlaylist::setId(const QString &id)
{
	m_id = id;
}

QString StoredPlaylist::name() const
{
	return m_name;
}

void StoredPlaylist::setName(const QString &name)
{
	m_name = name;
}

QString StoredPlaylist::coverArt() const
{
	return m_coverArt;
}

void StoredPlaylist::setCoverArt(const QString &coverArt)
{
	m_coverArt = coverArt;
}

QString StoredPlaylist::comment() const
{
	if (m_comment.isEmpty())
	{
		return "This playlist has no comment";
	}

	return m_comment;
}

void StoredPlaylist::setComment(const QString &comment)
{
	m_comment = comment;
}

QDateTime StoredPlaylist::created() const
{
	return m_created;
}

void StoredPlaylist::setCreated(const QDateTime &created)
{
	m_created = created;
}

QList<CollectionTrackNode *> StoredPlaylist::tracks() const
{
	return m_tracks;
}

void StoredPlaylist::setTracks(QList<CollectionTrackNode *> tracks)
{
	m_tracks = tracks;
}

QString StoredPlaylist::getCreated() const
{
	return QStringEx::format("Created %1", m_created);
}

StoredPlaylist::operator QString() const
{
	return m_id;
}
