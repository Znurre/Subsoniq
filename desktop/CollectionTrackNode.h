#ifndef COLLECTIONTRACKNODE_H
#define COLLECTIONTRACKNODE_H

#include "CollectionNodeBase.h"
#include "Track.h"

class CollectionTrackNode : public ICollectionNode
{
	public:
		CollectionTrackNode(const QJsonObject &object, ICollectionNode *parent, int index);

		QIcon icon() const override;
		QString title() const override;
		QSize sizeHint() const override;

		ICollectionNode *childAt(int index) const override;
		ICollectionNode *parent() const override;

		const Track *track() const override;

		int row() const override;
		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;

		void fetchMore() override;

	private:
		ICollectionNode *m_parent;
		Track m_track;

		QJsonObject m_object;

		int m_index;
};

#endif // COLLECTIONTRACKNODE_H
