#ifndef COLLECTIONBROWSER_H
#define COLLECTIONBROWSER_H

#include <QWidget>

class Track;

class CollectionBrowserWidget : public QWidget
{
	Q_OBJECT

	public:
		CollectionBrowserWidget();

	private:
		void onItemDoubleClicked(const QModelIndex &index);

	signals:
		void trackSelected(const Track *track);
};

#endif // COLLECTIONBROWSER_H
