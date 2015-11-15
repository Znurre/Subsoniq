#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "CollectionAlbumNode.h"
#include "CollectionArtistNode.h"

CollectionArtistNode::CollectionArtistNode(const QString &grouping, const QJsonObject &object, ICollectionNode *parent, int index)
	: CollectionNodeBase(parent, index)
	, m_grouping(grouping)
	, m_object(object)
{

}

QIcon CollectionArtistNode::icon() const
{
	return QIcon::fromTheme("view-media-artist");
}

QString CollectionArtistNode::title() const
{
	return m_object
		.value("name")
		.toString();
}

QString CollectionArtistNode::id() const
{
	return m_object
		.value("id")
		.toString();
}

QString CollectionArtistNode::viewTemplate() const
{
	return "ArtistTemplate.qml";
}

QString CollectionArtistNode::grouping() const
{
	return m_grouping;
}
