#ifndef COLLECTIONARTISTITEMDELEGATE_H
#define COLLECTIONARTISTITEMDELEGATE_H

#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>

#include "ItemDelegateBase.h"

class CollectionArtistItemDelegate : public ItemDelegateBase
{
	public:
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COLLECTIONARTISTITEMDELEGATE_H
