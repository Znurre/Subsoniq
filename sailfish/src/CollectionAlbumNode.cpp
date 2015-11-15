#include "CollectionAlbumNode.h"

CollectionAlbumNode::CollectionAlbumNode(const QJsonObject &object, ICollectionNode *parent, int index)
	: CollectionNodeBase(parent, index)
	, m_image("media-album-cover-manager-amarok.png")
	, m_object(object)
{

}

QIcon CollectionAlbumNode::icon() const
{
	return m_image;
}

QString CollectionAlbumNode::title() const
{
	return m_object
		.value("title")
		.toString();
}

QString CollectionAlbumNode::id() const
{
	return m_object
		.value("id")
		.toString();
}

QString CollectionAlbumNode::viewTemplate() const
{
	return "AlbumTemplate.qml";
}

QString CollectionAlbumNode::grouping() const
{
	return QString::null;
}
