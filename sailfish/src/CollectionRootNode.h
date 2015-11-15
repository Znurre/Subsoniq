#ifndef COLLECTIONROOTNODE_H
#define COLLECTIONROOTNODE_H

#include <QJsonObject>

#include "ICollectionNode.h"

class CollectionRootNode : public ICollectionNode
{
	public:
		CollectionRootNode(const QJsonObject &root);
		~CollectionRootNode();

		QIcon icon() const override;

		QString title() const override;
		QString viewTemplate() const override;
		QString id() const override;
		QString grouping() const override;

		ICollectionNode *childAt(int index) const override;
		ICollectionNode *parent() const override;

		Track *track() override;

		int row() const override;
		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;

		void fetchMore() override;

	private:
		QJsonObject m_root;
		QList<ICollectionNode *> m_children;
};

#endif // COLLECTIONROOTNODE_H
