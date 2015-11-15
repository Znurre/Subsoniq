#ifndef COLLECTIONALBUMITEMDELEGATE_H
#define COLLECTIONALBUMITEMDELEGATE_H

#include <QStyledItemDelegate>

#include "ItemDelegateBase.h"

class CollectionAlbumItemDelegate : public ItemDelegateBase
{
	public:
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COLLECTIONALBUMITEMDELEGATE_H
