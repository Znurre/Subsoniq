#include "TypeGroupingResolver.h"
#include "CollectionArtistNode.h"
#include "CollectionAlbumNode.h"
#include "CollectionTrackNode.h"
#include "FetchMoreNode.h"

TypeGroupingResolver::TypeGroupingResolver()
{
	m_resolvers =
	{
		new Resolver<CollectionArtistNode>("Artists"),
		new Resolver<CollectionAlbumNode>("Albums"),
		new Resolver<CollectionTrackNode>("Songs")
	};
}

TypeGroupingResolver::~TypeGroupingResolver()
{
	qDeleteAll(m_resolvers);
}

QString TypeGroupingResolver::resolve(ICollectionNode *node) const
{
	for (IResolver *resolver : m_resolvers)
	{
		if (resolver->canHandle(node))
		{
			return resolver->grouping();
		}
	}

	return "Unknown";
}
