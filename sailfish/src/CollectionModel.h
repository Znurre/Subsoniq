#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include "JsonResponseTransformer.h"
#include "CollectionRootNode.h"
#include "SubsonicAdapter.h"

#include <QAbstractItemModel>

class ICollectionNode;

class CollectionModel : public QAbstractItemModel
{
	Q_OBJECT

	public:
		enum Roles
		{
			ModelData = Qt::UserRole,
			Title = Qt::UserRole + 1,
			Icon = Qt::UserRole + 2,
			ViewTemplate = Qt::UserRole + 3,
			CoverUrl = Qt::UserRole + 4,
			Grouping = Qt::UserRole + 5
		};

		CollectionModel();

		QHash<int, QByteArray> roleNames() const override;

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QModelIndex parent(const QModelIndex &child) const override;

		int rowCount(const QModelIndex &parent) const override;
		int columnCount(const QModelIndex &parent) const override;

		QVariant data(const QModelIndex &index, int role) const override;

		bool hasChildren(const QModelIndex &parent) const override;

		bool canFetchMore(const QModelIndex &parent) const override;
		void fetchMore(const QModelIndex &parent) override;

		Q_INVOKABLE QString getPageTitle(const QModelIndex &index) const;
		Q_INVOKABLE QObject *getParentNode(const QModelIndex &index) const;

	private:
		void response(const QJsonObject &envelope);

		CollectionRootNode m_root;
		CollectionRootNode *m_kask;

		SubsonicAdapter m_adapter;

	signals:
		void statusChanged();
};

#endif // COLLECTIONMODEL_H
