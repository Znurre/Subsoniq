#ifndef ICOLLECTIONNODERESOLVER_H
#define ICOLLECTIONNODERESOLVER_H

#include <QJsonObject>

class ICollectionNode;

class ICollectionNodeResolver
{
	public:
		ICollectionNodeResolver(ICollectionNode *parent);

		ICollectionNode *resolve(const QJsonObject &object, int index) const;

	private:
		ICollectionNode *m_parent;
};

#endif // ICOLLECTIONNODERESOLVER_H
