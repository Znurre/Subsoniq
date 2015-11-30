#ifndef COLLECTIONARTISTNODE_H
#define COLLECTIONARTISTNODE_H

#include <QJsonValue>

#include "CollectionNodeBase.h"
#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

class CollectionArtistNode : public CollectionNodeBase
{
	public:
		CollectionArtistNode(const QString &grouping, const QJsonObject &object, ICollectionNode *parent, CollectionModel *model, int index);

		QIcon icon() const override;

		QString title() const override;
		QString id() const override;
		QString viewTemplate() const override;
		QString grouping() const;

	private:
		QString m_grouping;
		QJsonObject m_object;
};

#endif // COLLECTIONARTISTNODE_H
