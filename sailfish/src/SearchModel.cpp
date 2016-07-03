#include <QJsonArray>

#include "CollectionAlbumNode.h"
#include "CollectionArtistNode.h"
#include "CollectionTrackNode.h"
#include "NodeHelper.h"
#include "SearchModel.h"

SearchModel::~SearchModel()
{
	qDeleteAll(m_nodes);
}

QModelIndex SearchModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	ICollectionNode *node = m_nodes[row];

	return createIndex(row, column, node);
}

int SearchModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_nodes.count();
}

void SearchModel::search(const QString &query)
{
	setStatus(Loading);

	qDeleteAll(m_nodes);

	m_nodes.clear();
	m_query = query;

	m_adapter.search2(query, LIMIT, 0, this, &SearchModel::response);
}

void SearchModel::response(const QJsonObject &envelope)
{
	const QJsonObject &searchResult2 = envelope
		.value("searchResult2")
		.toObject();

	const QJsonArray &artist = searchResult2
		.value("artist")
		.toArray();

	for (const QJsonValue &value : artist)
	{
		const QJsonObject &object = value.toObject();

		m_nodes << new CollectionArtistNode(QString::null, object);
	}

	if (artist.count() == LIMIT)
	{
		m_nodes << new FetchMoreNode<CollectionArtistNode>(m_query, "artist");
	}

	const QJsonArray &album = searchResult2
		.value("album")
		.toArray();

	for (const QJsonValue &value : album)
	{
		const QJsonObject &object = value.toObject();

		m_nodes << new CollectionAlbumNode(object);
	}

	if (album.count() == LIMIT)
	{
		m_nodes << new FetchMoreNode<CollectionAlbumNode>(m_query, "album");
	}

	const QJsonArray &song = searchResult2
		.value("song")
		.toArray();

	for (const QJsonValue &value : song)
	{
		const QJsonObject &object = value.toObject();

		m_nodes << new CollectionTrackNode(object);
	}

	if (song.count() == LIMIT)
	{
		m_nodes << new FetchMoreNode<CollectionTrackNode>(m_query, "song");
	}

	setStatus(Finished);

	emit layoutChanged();
}
