#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "ArtistGroupNode.h"
#include "ArtistGroupRow.h"
#include "ArtistsModel.h"
#include "CollectionArtistNode.h"

ArtistsModel::ArtistsModel()
	: m_status(Loading)
{
	m_adapter.getIndexes(this, &ArtistsModel::response);
}

int ArtistsModel::status() const
{
	return m_status;
}

QHash<int, QByteArray> ArtistsModel::roleNames() const
{
	return
	{
		{ Roles::Name, "name" },
		{ Roles::Id, "id" }
	};
}

QModelIndex ArtistsModel::index(int row, int column, const QModelIndex &parent) const
{
	IArtistModelNode *parentNode = (IArtistModelNode *)parent.internalPointer();
	IArtistModelNode *node = getChild(parentNode, row);

	return createIndex(row, column, node);
}

QVariant ArtistsModel::data(const QModelIndex &index, int role) const
{
	IArtistModelNode *node = (IArtistModelNode *)index.internalPointer();

	if (node)
	{
		switch (role)
		{
			case Roles::Name:
			{
				return node->title();
			}

			case Roles::Id:
			{
				return node->id();
			}
		}
	}

	return QVariant();
}

int ArtistsModel::rowCount(const QModelIndex &parent) const
{
	IArtistModelNode *parentNode = (IArtistModelNode *)parent.internalPointer();

	if (parentNode)
	{
		return parentNode->childCount();
	}

	return m_nodes.count();
}

IArtistModelNode *ArtistsModel::getChild(IArtistModelNode *parent, int index) const
{
	if (parent)
	{
		return parent->childAt(index);
	}

	return m_nodes[index];
}

void ArtistsModel::response(const QJsonObject &envelope)
{
	m_status = Finished;

	const QJsonObject &indexes = envelope
		.value("indexes")
		.toObject();

	const QJsonArray &index = indexes
		.value("index")
		.toArray();

	for (const QJsonValue &value : index)
	{
		const QJsonObject &section = value
			.toObject();

		const QString &name = section
			.value("name")
			.toString();

		const QJsonArray &artists = section
			.value("artist")
			.toArray();

		for (const QJsonValue &artist : artists)
		{
			const QJsonObject &object = artist
				.toObject();

//			m_nodes << new CollectionArtistNode(name, object);
		}
	}

	emit statusChanged();
	emit layoutChanged();
}
