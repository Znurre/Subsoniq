#ifndef COLLECTIONALBUMNODE_H
#define COLLECTIONALBUMNODE_H

#include <QJsonObject>

#include "CollectionNodeBase.h"
#include "ImageResponseTransformer.h"
#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

class CollectionAlbumNode : public CollectionNodeBase
{
	public:
		CollectionAlbumNode(const QJsonObject &object, ICollectionNode *parent, CollectionModel *model, int index);

		QIcon icon() const override;

		QString title() const override;
		QString id() const override;
		QString viewTemplate() const override;
		QString grouping() const override;

	private:
		QIcon m_image;
		QJsonObject m_object;
};

#endif // COLLECTIONALBUMNODE_H
