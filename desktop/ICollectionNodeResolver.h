#ifndef ICOLLECTIONNODERESOLVER_H
#define ICOLLECTIONNODERESOLVER_H

#include <QJsonObject>

class CollectionModel;
class ICollectionNode;

class ICollectionNodeResolver
{
	public:
		ICollectionNodeResolver(CollectionModel *model, ICollectionNode *parent);

		ICollectionNode *resolve(const QJsonObject &object, int index) const;

	private:
		CollectionModel *m_model;
		ICollectionNode *m_parent;
};

#endif // ICOLLECTIONNODERESOLVER_H
