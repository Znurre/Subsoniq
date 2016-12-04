#include "CollectionAlbumNode.h"
#include "CollectionTrackNode.h"
#include "ICollectionNodeResolver.h"

ICollectionNodeResolver::ICollectionNodeResolver(CollectionModel *model, ICollectionNode *parent)
	: m_model(model)
	, m_parent(parent)
{

}

ICollectionNode *ICollectionNodeResolver::resolve(const QJsonObject &object, int index) const
{
	const bool isDirectory = object
		.value("isDir")
		.toBool();

	if (isDirectory)
	{
		return new CollectionAlbumNode(object, m_model, m_parent, index);
	}

	return new CollectionTrackNode(object, m_parent, index);
}

