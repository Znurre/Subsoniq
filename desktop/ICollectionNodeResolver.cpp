#include "CollectionAlbumNode.h"
#include "CollectionTrackNode.h"
#include "ICollectionNodeResolver.h"

ICollectionNodeResolver::ICollectionNodeResolver(ICollectionNode *parent)
	: m_parent(parent)
{

}

ICollectionNode *ICollectionNodeResolver::resolve(const QJsonObject &object, int index) const
{
	const bool isDirectory = object
		.value("isDir")
		.toBool();

	if (isDirectory)
	{
		return new CollectionAlbumNode(object, m_parent, index);
	}

	return new CollectionTrackNode(object, m_parent, index);
}

