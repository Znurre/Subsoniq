#include <QPainter>

#include "CollectionArtistItemDelegate.h"
#include "ICollectionNode.h"

QSize CollectionArtistItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);

	return QSize(22, 22);
}
