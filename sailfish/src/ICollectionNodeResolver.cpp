#include "CollectionAlbumNode.h"
#include "CollectionTrackNode.h"
#include "ICollectionNodeResolver.h"

ICollectionNode *ICollectionNodeResolver::resolve(const QJsonObject &object) const
{
	const bool isDirectory = object
		.value("isDir")
		.toBool();

	if (isDirectory)
	{
		return new CollectionAlbumNode(object);
	}

	return new CollectionTrackNode(object);
}

