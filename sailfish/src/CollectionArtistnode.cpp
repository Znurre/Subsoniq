#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "CollectionArtistNode.h"

CollectionArtistNode::CollectionArtistNode(const QJsonObject &object, ICollectionNode *parent, int index)
	: CollectionNodeBase(parent, index)
	, m_object(object)
{

}

QIcon CollectionArtistNode::icon() const
{
	return QIcon::fromTheme("view-media-artist");
}

QSize CollectionArtistNode::sizeHint() const
{
	return QSize(22, 22);
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
