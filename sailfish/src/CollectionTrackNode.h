#ifndef COLLECTIONTRACKNODE_H
#define COLLECTIONTRACKNODE_H

#include "CollectionNodeBase.h"
#include "Track.h"

class CollectionTrackNode : public ICollectionNode
{
	Q_OBJECT

	Q_PROPERTY(QString trackNumber READ trackNumber CONSTANT)
	Q_PROPERTY(QString artist READ artist CONSTANT)
	Q_PROPERTY(QString title READ title CONSTANT)

	public:
		CollectionTrackNode(const QJsonObject &object);

		QIcon icon() const override;

		QString trackNumber() const;
		QString artist() const;
		QString title() const override;
		QString viewTemplate() const override;
		QString id() const override;
		QString grouping() const override;

		ICollectionNode *childAt(int trackNumber) const override;

		Track *track() override;

		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;

		void fetchMore() override;

	private:
		Track m_track;

		QJsonObject m_object;
};

#endif // COLLECTIONTRACKNODE_H
