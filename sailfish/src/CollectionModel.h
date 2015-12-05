#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include "SubsoniqModelBase.h"
#include "CollectionRootNode.h"
#include "SubsonicAdapter.h"
#include "ICollectionModel.h"

class ICollectionNode;

class CollectionModel
	: public SubsoniqModelBase
	, public ICollectionModel
{
	public:
		CollectionModel();

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;

		int status() const;
		int rowCount(const QModelIndex &parent) const override;

		QVariant data(const QModelIndex &index, int role) const override;

		bool hasChildren(const QModelIndex &parent) const override;
		bool canFetchMore(const QModelIndex &parent) const override;

		void fetchMore(const QModelIndex &parent) override;

		Q_INVOKABLE QString getPageTitle(const QModelIndex &index) const;
		Q_INVOKABLE QObject *getParentNode(const QModelIndex &index) const;

	private:
		ICollectionNode *getNode(const QModelIndex &index) const;

		CollectionRootNode m_scopedRoot;
		CollectionRootNode *m_root;

		SubsonicAdapter m_adapter;
};

#endif // COLLECTIONMODEL_H
