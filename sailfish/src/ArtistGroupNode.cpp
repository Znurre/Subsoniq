#include <QJsonArray>

#include "ArtistGroupNode.h"
#include "CollectionArtistNode.h"

ArtistGroupNode::ArtistGroupNode(const QString &name, const QJsonObject &object)
	: m_name(name)
{
	const QJsonArray &artist = object
		.value("artist")
		.toArray();

	for (const QJsonValue &value : artist)
	{
		const QJsonObject &object = value
			.toObject();

//		m_nodes << new CollectionArtistNode(object);
	}
}

QString ArtistGroupNode::title() const
{
	return m_name;
}

QString ArtistGroupNode::id() const
{
	return QString::null;
}

IArtistModelNode *ArtistGroupNode::childAt(int index) const
{
	return m_nodes[index];
}

int ArtistGroupNode::childCount() const
{
	return m_nodes.count();
}
