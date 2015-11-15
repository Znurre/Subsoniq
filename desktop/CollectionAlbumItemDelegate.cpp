#include <QPainter>

#include "CollectionAlbumItemDelegate.h"
#include "ICollectionNode.h"

QSize CollectionAlbumItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);

	return QSize(38, 38);
}

