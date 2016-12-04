#ifndef COLLECTIONARTISTNODE_H
#define COLLECTIONARTISTNODE_H

#include <QJsonValue>

#include "CollectionNodeBase.h"
#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

class CollectionArtistNode : public CollectionNodeBase
{
	public:
		CollectionArtistNode(const QJsonObject &object, CollectionModel *model, ICollectionNode *parent, int index);

		QIcon icon() const override;
		QSize sizeHint() const override;

		QString title() const override;
		QString id() const override;

	private:
		QJsonObject m_object;
};

#endif // COLLECTIONARTISTNODE_H
