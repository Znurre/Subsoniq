#ifndef COLLECTIONITERATOR_H
#define COLLECTIONITERATOR_H

#include <QList>
#include <QObject>

#include "ICollectionNode.h"

class CollectionIterator
{
	public:
		QList<Track *> getTracks(ICollectionNode *parent) const;

	private:
		void getTracks(ICollectionNode *parent, QList<Track *> &target) const;
};

#endif // COLLECTIONITERATOR_H
