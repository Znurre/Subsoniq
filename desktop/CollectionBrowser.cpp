#include <QHeaderView>
#include <QLineEdit>
#include <QTreeView>
#include <QVBoxLayout>

#include "CollectionBrowser.h"
#include "CollectionItemDelegate.h"
#include "CollectionModel.h"
#include "ICollectionNode.h"

CollectionBrowserWidget::CollectionBrowserWidget()
{
	QLineEdit *searchBox = new QLineEdit();
	searchBox->setPlaceholderText("Search collection");

	CollectionModel *collectionModel = new CollectionModel();

	QTreeView *collectionView = new QTreeView();
	collectionView->setModel(collectionModel);

	CollectionItemDelegate *delegate = new CollectionItemDelegate();

	collectionView->setItemDelegate(delegate);

	QHeaderView *header = collectionView->header();
	header->hide();

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(searchBox);
	layout->addWidget(collectionView, 1);

	connect(collectionView, &QTreeView::doubleClicked, this, &CollectionBrowserWidget::onItemDoubleClicked);
}

void CollectionBrowserWidget::onItemDoubleClicked(const QModelIndex &index)
{
	const ICollectionNode *node = (ICollectionNode *)index.internalPointer();
	const Track *track = node->track();

	if (track)
	{
		emit trackSelected(track);
	}
}

