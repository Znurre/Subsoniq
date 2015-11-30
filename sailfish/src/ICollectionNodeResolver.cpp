#include "CollectionAlbumNode.h"
#include "CollectionTrackNode.h"
#include "ICollectionNodeResolver.h"

ICollectionNodeResolver::ICollectionNodeResolver(ICollectionNode *parent, CollectionModel *model)
	: m_parent(parent)
	, m_model(model)
{

}

ICollectionNode *ICollectionNodeResolver::resolve(const QJsonObject &object, int index) const
{
	const bool isDirectory = object
		.value("isDir")
		.toBool();

	if (isDirectory)
	{
		return new CollectionAlbumNode(object, m_parent, m_model, index);
	}

	return new CollectionTrackNode(object, m_parent, index);
}

