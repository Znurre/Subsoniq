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

QVariant SearchModel::data(const QModelIndex &index, int role) const
{
	ICollectionNode *node = (ICollectionNode *)index.internalPointer();

	switch (role)
	{
		case Roles::ModelData:
		{
			return QVariant::fromValue(node);
		}

		case Roles::Title:
		{
			return node->title();
		}

		case Roles::Icon:
		{
			return node->icon();
		}

		case Roles::ViewTemplate:
		{
			return node->viewTemplate();
		}

		case Roles::CoverUrl:
		{
			return NodeHelper::getCoverUrl(node, "64");
		}

		case Roles::Grouping:
		{
			return m_typeGroupingResolver.resolve(node);
		}

		case Roles::ModelIndex:
		{
			return index;
		}
	}

	return QVariant();
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
	m_adapter.search2(query, this, &SearchModel::response);

	setStatus(Finished);

	emit layoutChanged();
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

	const QJsonArray &album = searchResult2
		.value("album")
		.toArray();

	for (const QJsonValue &value : album)
	{
		const QJsonObject &object = value.toObject();

		m_nodes << new CollectionAlbumNode(object);
	}

	const QJsonArray &song = searchResult2
		.value("song")
		.toArray();

	for (const QJsonValue &value : song)
	{
		const QJsonObject &object = value.toObject();

		m_nodes << new CollectionTrackNode(object);
	}
}
