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

	Q_PROPERTY(int status READ status NOTIFY statusChanged)

	Q_ENUMS(Status)

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

		enum Status
		{
			Loading,
			Finished
		};

		CollectionModel();

		int status() const;
		void setStatus(int status);

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
		Q_INVOKABLE QString getHeaderTemplate(const QModelIndex &index) const;

		Q_INVOKABLE QObject *getParentNode(const QModelIndex &index) const;

	private:
		ICollectionNode *getNode(const QModelIndex &index) const;

		CollectionRootNode m_scopedRoot;
		CollectionRootNode *m_root;

		SubsonicAdapter m_adapter;

		int m_status;

	signals:
		void statusChanged();
};

#endif // COLLECTIONMODEL_H
