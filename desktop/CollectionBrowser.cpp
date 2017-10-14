#include <QHeaderView>
#include <QLineEdit>
#include <QTreeView>
#include <QVBoxLayout>

#include "CollectionBrowser.h"
#include "CollectionItemDelegate.h"
#include "ICollectionNode.h"

CollectionBrowserWidget::CollectionBrowserWidget()
{
	QLineEdit *searchBox = new QLineEdit();
	searchBox->setPlaceholderText("Search collection");

	QTreeView *collectionView = new QTreeView();
	collectionView->setModel(&m_model);

	CollectionItemDelegate *delegate = new CollectionItemDelegate();

	collectionView->setItemDelegate(delegate);

	QHeaderView *header = collectionView->header();
	header->hide();

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(searchBox);
	layout->addWidget(collectionView, 1);

	connect(collectionView, &QTreeView::doubleClicked, this, &CollectionBrowserWidget::onItemDoubleClicked);
	connect(searchBox, &QLineEdit::textChanged, this, &CollectionBrowserWidget::filter);
}

void CollectionBrowserWidget::filter(const QString &filter)
{
	m_model.setFilterFixedString(filter);
}

void CollectionBrowserWidget::onItemDoubleClicked(const QModelIndex &proxyIndex)
{
	const QModelIndex &index = m_model.mapToSource(proxyIndex);

	const ICollectionNode *node = (ICollectionNode *)index.internalPointer();
	const Track *track = node->track();

	if (track)
	{
		emit trackSelected(track);
	}
}

