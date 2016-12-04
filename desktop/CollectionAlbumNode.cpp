#include "CollectionAlbumItemDelegate.h"
#include "CollectionAlbumNode.h"
#include "CollectionItemDelegate.h"

CollectionAlbumNode::CollectionAlbumNode(const QJsonObject &object, CollectionModel *model, ICollectionNode *parent, int index)
	: CollectionNodeBase(model, parent, index)
	, m_image(ICON_DEFAULT)
	, m_object(object)
{
	const QString &coverArtId = object
		.value("coverArt")
		.toString();

	m_adapter.getCoverArt(coverArtId, "64", this, &CollectionAlbumNode::imageResponse);
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

	if (!pixmap.isNull())
	{
		m_image = pixmap;
	}

	raiseDataChanged();
}
