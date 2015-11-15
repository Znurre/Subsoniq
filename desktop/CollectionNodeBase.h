#ifndef COLLECTIONNODEBASE_H
#define COLLECTIONNODEBASE_H

#include "ICollectionNode.h"
#include "ICollectionNodeResolver.h"
#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

class CollectionNodeBase : public ICollectionNode
{
	public:
		CollectionNodeBase(ICollectionNode *parent, int index);
		~CollectionNodeBase();

		ICollectionNode *childAt(int index) const override;
		ICollectionNode *parent() const override;

		const Track *track() const override;

		int row() const override;
		int childCount() const override;

		bool hasChildren() const override;
		bool canFetchMore() const override;

		void fetchMore() override;

	protected:
		virtual QString id() const = 0;

	private:
		void response(const QJsonObject &envelope);

		ICollectionNode *m_parent;
		ICollectionNodeResolver m_collectionNodeResolver;

//		JsonResponseTransformer m_transformer;
		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_children;

		int m_fetches;
		int m_index;
};

#endif // COLLECTIONNODEBASE_H
