#ifndef COLLECTIONNODEBASE_H
#define COLLECTIONNODEBASE_H

#include "ICollectionNode.h"
#include "ICollectionNodeResolver.h"
#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

class CollectionNodeBase : public ICollectionNode
{
	Q_OBJECT

	public:
		CollectionNodeBase(ICollectionNode *parent, int index);
		~CollectionNodeBase();

		ICollectionNode *childAt(int index) const override;
		ICollectionNode *parent() const override;

		Track *track() override;
		Status status() const override;

		int row() const override;
		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;

		void fetchMore() override;

	private:
		void response(const QJsonObject &envelope);

		ICollectionNode *m_parent;
		ICollectionNodeResolver m_collectionNodeResolver;

		Status m_status;
		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_children;

		int m_fetches;
		int m_index;
};

#endif // COLLECTIONNODEBASE_H
