#include "CollectionIterator.h"
#include "CollectionTrackNode.h"

QList<Track *> CollectionIterator::getTracks(ICollectionNode *parent) const
{
	QList<Track *> tracks;

	getTracks(parent, tracks);

	return tracks;
}

void CollectionIterator::getTracks(ICollectionNode *parent, QList<Track *> &target) const
{
	for (int i = 0; i < parent->childCount(); i++)
	{
		ICollectionNode *node = parent->childAt(i);
		ICollectionNode *track = qobject_cast<CollectionTrackNode *>(node);

		if (!track)
		{
			if (node->canFetchMore())
			{
				node->fetchMore();
			}

			getTracks(node, target);
		}
		else
		{
			target << node->track();
		}
	}
}
