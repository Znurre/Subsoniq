#ifndef COLLECTIONNODEBASE_H
#define COLLECTIONNODEBASE_H

#include "ICollectionNode.h"
#include "ICollectionNodeResolver.h"
#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

class CollectionModel;

class CollectionNodeBase : public ICollectionNode
{
	Q_OBJECT

	public:
		CollectionNodeBase();
		~CollectionNodeBase();

		ICollectionNode *childAt(int index) const override;

		Track *track() override;

		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;

		void fetchMore() override;

	private:
		void response(const QJsonObject &envelope);

		ICollectionNodeResolver m_collectionNodeResolver;
		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_children;

		bool m_canFetchMore;
};

#endif // COLLECTIONNODEBASE_H
