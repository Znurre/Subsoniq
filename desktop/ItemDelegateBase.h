#ifndef ITEMDELEGATEBASE
#define ITEMDELEGATEBASE

#include <QStyledItemDelegate>

class ItemDelegateBase : public QStyledItemDelegate
{
	public:
		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

	protected:
		int PADDING = 3;
};

#endif // ITEMDELEGATEBASE

