#include "CollectionTrackNode.h"
#include "StoredPlaylistModel.h"

StoredPlaylistModel::StoredPlaylistModel()
	: m_playlist(nullptr)
{
	setStatus(Loading);
}

StoredPlaylist *StoredPlaylistModel::playlist()
{
	return m_playlist;
}

void StoredPlaylistModel::setPlaylist(StoredPlaylist *playlist)
{
	m_playlist = playlist;

	if (playlist)
	{
		m_adapter.getPlaylist(*playlist, this, &StoredPlaylistModel::response);
	}

	emit playlistChanged();
}

int StoredPlaylistModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	if (m_playlist)
	{
		const QList<CollectionTrackNode *> &tracks = m_playlist->tracks();

		return tracks.count();
	}

	return 0;
}

QModelIndex StoredPlaylistModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	const QList<CollectionTrackNode *> &tracks = m_playlist->tracks();

	return createIndex(row, column, tracks[row]);
}

QVariant StoredPlaylistModel::data(const QModelIndex &index, int role) const
{
	CollectionTrackNode *node = (CollectionTrackNode *)index.internalPointer();

	if (role == ModelData)
	{
		return QVariant::fromValue(node);
	}

	return QVariant();
}

void StoredPlaylistModel::response(const QJsonObject &response)
{
	const QJsonObject &playlist = response
		.value("playlist")
		.toObject();

	const QJsonArray &entries = playlist
		.value("entry")
		.toArray();

	QList<CollectionTrackNode *> tracks;

	for (const QJsonValue &entry : entries)
	{
		const QJsonObject &object = entry
			.toObject();

		tracks << new CollectionTrackNode(object);
	}

	m_playlist->setTracks(tracks);

	if (tracks.isEmpty())
	{
		return setStatus(Empty);
	}

	setStatus(Finished);

	emit layoutChanged();
}
