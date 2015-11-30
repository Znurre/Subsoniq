#ifndef COLLECTIONROOTNODE_H
#define COLLECTIONROOTNODE_H

#include <QJsonObject>

#include "ICollectionNode.h"
#include "SubsonicAdapter.h"

class CollectionModel;

class CollectionRootNode : public ICollectionNode
{
	public:
		CollectionRootNode(CollectionModel *model);
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
		void response(const QJsonObject &envelope);

		CollectionModel *m_model;
		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_children;
};

#endif // COLLECTIONROOTNODE_H
