#ifndef ICOLLECTIONNODERESOLVER_H
#define ICOLLECTIONNODERESOLVER_H

#include <QJsonObject>

class ICollectionNode;
class CollectionModel;

class ICollectionNodeResolver
{
	public:
		ICollectionNode *resolve(const QJsonObject &object) const;

	private:
		ICollectionNode *m_parent;
		CollectionModel *m_model;
};

#endif // ICOLLECTIONNODERESOLVER_H
