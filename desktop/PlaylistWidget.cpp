#include <QLineEdit>
#include <QListView>
#include <QVBoxLayout>

#include "PlaylistModel.h"
#include "PlaylistWidget.h"

PlaylistWidget::PlaylistWidget(Playlist &playlist)
{
	QLineEdit *searchBox = new QLineEdit();
	searchBox->setPlaceholderText("Search playlist");

	PlaylistModel *model = new PlaylistModel(playlist);

	QListView *playlistView = new QListView();
	playlistView->setModel(model);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(searchBox);
	layout->addWidget(playlistView, 1);

	connect(playlistView, &QListView::doubleClicked, this, &PlaylistWidget::onDoubleClicked);
}

void PlaylistWidget::onDoubleClicked(const QModelIndex &index)
{
	PlaylistNode *node = (PlaylistNode *)index.internalPointer();

	if (node)
	{
		emit nodeSelected(node);
	}
}

