#ifndef COLLECTIONROOTNODE_H
#define COLLECTIONROOTNODE_H

#include <QJsonObject>

#include "ICollectionNode.h"
#include "SubsonicAdapter.h"

class CollectionModel;

class CollectionRootNode : public ICollectionNode
{
	public:
		CollectionRootNode();
		~CollectionRootNode();

		QIcon icon() const override;

		QString title() const override;
		QString viewTemplate() const override;
		QString id() const override;
		QString grouping() const override;

		ICollectionNode *childAt(int index) const override;

		Track *track() override;

		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;
		bool fetchMore() override;

	private:
		void response(const QJsonObject &envelope);

		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_children;

		bool m_canFetchMore;
};

#endif // COLLECTIONROOTNODE_H
