#ifndef COLLECTIONROOTNODE_H
#define COLLECTIONROOTNODE_H

#include <QJsonObject>

#include "ICollectionNode.h"
#include "SubsonicAdapter.h"

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
		ICollectionNode *parent() const override;

		Status status() const override;
		Track *track() override;

		int row() const override;
		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;

		void fetchMore() override;

	private:
		void response(const QJsonObject &envelope);

		Status m_status;
		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_children;
};

#endif // COLLECTIONROOTNODE_H
