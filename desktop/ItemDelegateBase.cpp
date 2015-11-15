#include <QPainter>

#include "ICollectionNode.h"
#include "ItemDelegateBase.h"

void ItemDelegateBase::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	const QSize padding(PADDING, PADDING);
	const QSize &iconSize = sizeHint(option, index) - padding * 2;

	QStyleOptionViewItem cloned = option;
	cloned.decorationSize = iconSize;

	QStyledItemDelegate::paint(painter, cloned, index);
}
