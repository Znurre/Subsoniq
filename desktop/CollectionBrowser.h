#ifndef COLLECTIONBROWSER_H
#define COLLECTIONBROWSER_H

#include <QWidget>

#include "CollectionModelProxy.h"

class Track;

class CollectionBrowserWidget : public QWidget
{
	Q_OBJECT

	public:
		CollectionBrowserWidget();

	private:
		void filter(const QString &filter);
		void onItemDoubleClicked(const QModelIndex &proxyIndex);

		CollectionModelProxy m_model;

	signals:
		void trackSelected(const Track *track);
};

#endif // COLLECTIONBROWSER_H
