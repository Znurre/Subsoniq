#include <QLineEdit>
#include <QListView>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <QPainter>
#include <QTreeView>
#include <QHeaderView>

#include "ItemDelegateBase.h"
#include "PlaylistModel.h"
#include "PlaylistWidget.h"

class PlaylistItemDelegate : public ItemDelegateBase
{
	public:
		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
		{
			const IPlaylistNode *node = (IPlaylistNode *)index.internalPointer();
			const QStyledItemDelegate &delegate = node->delegate();

			delegate.paint(painter, option, index);
		}

		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
		{
			const IPlaylistNode *node = (IPlaylistNode *)index.internalPointer();
			const QStyledItemDelegate &delegate = node->delegate();

			return delegate.sizeHint(option, index);
		}
};

PlaylistWidget::PlaylistWidget(Playlist &playlist)
{
	QLineEdit *searchBox = new QLineEdit();
	searchBox->setPlaceholderText("Search playlist");

	PlaylistModel *model = new PlaylistModel(playlist);

	QTreeView *playlistView = new QTreeView();
	playlistView->setRootIsDecorated(false);
	playlistView->setHeaderHidden(true);
	playlistView->setModel(model);
	playlistView->setItemDelegate(new PlaylistItemDelegate());

	connect(model, &PlaylistModel::layoutChanged, playlistView, &QTreeView::expandAll);

	QHeaderView *header = playlistView->header();
	header->setSectionResizeMode(QHeaderView::Stretch);
	header->setSectionResizeMode(0, QHeaderView::ResizeToContents);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(searchBox);
	layout->addWidget(playlistView, 1);

	connect(playlistView, &QListView::doubleClicked, this, &PlaylistWidget::onDoubleClicked);
}

void PlaylistWidget::onDoubleClicked(const QModelIndex &index)
{
	IPlaylistNode *node = (IPlaylistNode *)index.internalPointer();

	if (node)
	{
		PlaylistNode *playlistNode = node->playlistNode();

		emit nodeSelected(playlistNode);
	}
}

