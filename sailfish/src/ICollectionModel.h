#ifndef ICOLLECTIONMODEL_H
#define ICOLLECTIONMODEL_H

#include <QModelIndex>

class ICollectionModel
{
	public:
		virtual int status() const = 0;

		virtual QString getPageTitle(const QModelIndex &index) const = 0;
		virtual QObject *getParentNode(const QModelIndex &index) const = 0;
};

#endif // ICOLLECTIONMODEL_H
