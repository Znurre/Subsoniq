#ifndef COLLECTIONMODELPROXY_H
#define COLLECTIONMODELPROXY_H

#include <QSortFilterProxyModel>

#include "CollectionModel.h"
#include "ICollectionModel.h"

class CollectionModelProxy
	: public QSortFilterProxyModel
	, public ICollectionModel
{
	Q_OBJECT

	Q_PROPERTY(int status READ status NOTIFY statusChanged)

	public:
		CollectionModelProxy();

		int status() const override;

		Q_INVOKABLE QString getPageTitle(const QModelIndex &index) const override;
		Q_INVOKABLE QObject *getParentNode(const QModelIndex &index) const override;
		Q_INVOKABLE QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;

	private:
		CollectionModel m_subject;

	signals:
		void statusChanged();
};

#endif // COLLECTIONMODELPROXY_H
