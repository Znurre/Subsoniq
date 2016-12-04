#ifndef COLLECTIONMODELPROXY_H
#define COLLECTIONMODELPROXY_H

#include <QSortFilterProxyModel>

#include "CollectionModel.h"

class CollectionModelProxy : public QSortFilterProxyModel
{
	public:
		CollectionModelProxy();

	private:
		CollectionModel m_subject;
};

#endif // COLLECTIONMODELPROXY_H
