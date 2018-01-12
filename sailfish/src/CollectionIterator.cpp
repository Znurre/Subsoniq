#include "CollectionIterator.h"
#include "CollectionTrackNode.h"

QList<Track *> CollectionIterator::getTracks(INode *parent) const
{
	QList<Track *> tracks;

	getTracks(parent, tracks);

	return tracks;
}

void CollectionIterator::getTracks(INode *parent, QList<Track *> &target) const
{
	for (int i = 0; i < parent->childCount(); i++)
	{
		INode *node = parent->childAt(i);

		CollectionTrackNode *trackNode = qobject_cast<CollectionTrackNode *>(node);

		if (!trackNode)
		{
			if (node->canFetchMore())
			{
				node->fetchMore();
			}

			getTracks(node, target);
		}
		else
		{
			target << trackNode->track();
		}
	}
}
