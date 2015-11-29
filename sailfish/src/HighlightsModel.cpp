#include <QJsonArray>

#include "CollectionAlbumNode.h"
#include "HighlightsModel.h"
#include "NodeHelper.h"

HighlightsModel::HighlightsModel()
{
	m_adapter
		.getAlbumList("starred", this, &HighlightsModel::starredResponse)
		.getAlbumList("frequent", this, &HighlightsModel::frequentResponse);
}

int HighlightsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_nodes.count();
}

QHash<int, QByteArray> HighlightsModel::roleNames() const
{
	return
	{
		{ CoverUrl, "coverUrl" }
	};
}

QModelIndex HighlightsModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	ICollectionNode *node = m_nodes[row];

	return createIndex(row, column, node);
}

QVariant HighlightsModel::data(const QModelIndex &index, int role) const
{
	ICollectionNode *node = (ICollectionNode *)index.internalPointer();

	switch (role)
	{
		case CoverUrl:
		{
			return NodeHelper::getCoverUrl(node, "192");
		}
	}

	return QVariant();
}

void HighlightsModel::starredResponse(const QJsonObject &envelope)
{
	response(envelope, true);
}

void HighlightsModel::frequentResponse(const QJsonObject &envelope)
{
	response(envelope, false);
}

void HighlightsModel::response(const QJsonObject &envelope, bool starred)
{
	Q_UNUSED(starred);

	const QJsonObject &albumList = envelope
		.value("albumList")
		.toObject();

	const QJsonArray &albums = albumList
		.value("album")
		.toArray();

	for (const QJsonValue &value : albums)
	{
		const QJsonObject &album = value.toObject();

		m_nodes << new CollectionAlbumNode(album, nullptr, 0);
	}

	emit layoutChanged();
}
