#include "CollectionAlbumItemDelegate.h"
#include "CollectionAlbumNode.h"
#include "CollectionItemDelegate.h"

CollectionAlbumNode::CollectionAlbumNode(const QJsonObject &object, ICollectionNode *parent, int index)
	: CollectionNodeBase(parent, index)
	, m_image("media-album-cover-manager-amarok.png")
	, m_object(object)
{
//	connect(&m_adapter, &SubsonicAdapter::finished, &m_transformer, &IResponseTransformer::handle);
//	connect(&m_transformer, &ImageResponseTransformer::response, this, &CollectionAlbumNode::imageResponse);

	const QString &coverArtId = object
		.value("coverArt")
		.toString();

	m_adapter.getCoverArt(coverArtId, this, &CollectionAlbumNode::imageResponse);
}

QIcon CollectionAlbumNode::icon() const
{
	return m_image;
}

QSize CollectionAlbumNode::sizeHint() const
{
	return QSize(38, 38);
}

QString CollectionAlbumNode::title() const
{
	return m_object
		.value("title")
		.toString();
}

QString CollectionAlbumNode::id() const
{
	return m_object
		.value("id")
		.toString();
}

void CollectionAlbumNode::imageResponse(const QImage &image)
{
	const QPixmap &pixmap = QPixmap::fromImage(image);

	m_image = pixmap;

	emit dataChanged(this);
}
