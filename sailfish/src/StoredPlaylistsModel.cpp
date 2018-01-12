#include <QJsonArray>
#include <QJsonSerializer>

#include "StoredPlaylistsModel.h"
#include "StoredPlaylistEnvelope.h"

StoredPlaylistsModel::StoredPlaylistsModel()
{
	setStatus(Loading);

	m_adapter.getPlaylists(this, &StoredPlaylistsModel::response);
}

int StoredPlaylistsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_envelope
		.playlists()
		.count();
}

QModelIndex StoredPlaylistsModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	StoredPlaylist *playlist = m_envelope
		.playlists()
		.at(row);

	return createIndex(row, column, playlist);
}

QVariant StoredPlaylistsModel::data(const QModelIndex &index, int role) const
{
	StoredPlaylist *playlist = (StoredPlaylist *)index.internalPointer();

	switch (role)
	{
		case Title:
		{
			return playlist->name();
		}

		case CoverArt:
		{
			return playlist->coverArt();
		}

		case ModelData:
		{
			return QVariant::fromValue(playlist);
		}
	}

	return QVariant();
}

void StoredPlaylistsModel::response(const QJsonObject &response)
{
	const QJsonObject &object = response
		.value("playlists")
		.toObject();

	QJsonSerializer serializer;
	serializer.deserialize(object, &m_envelope);

	const bool isEmpty = m_envelope
		.playlists()
		.empty();

	if (isEmpty)
	{
		return setStatus(Empty);
	}

	setStatus(Finished);

	emit layoutChanged();
}
