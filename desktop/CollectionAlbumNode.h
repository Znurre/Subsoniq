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
		CollectionAlbumNode(const QJsonObject &object, ICollectionNode *parent, int index);

		QIcon icon() const override;
		QSize sizeHint() const override;

		QString title() const override;
		QString id() const override;

	private:
		void imageResponse(const QImage &image);

		SubsonicAdapter m_adapter;

		QIcon m_image;
		QJsonObject m_object;
};

#endif // COLLECTIONALBUMNODE_H
