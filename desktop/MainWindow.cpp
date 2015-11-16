#include <QHBoxLayout>
#include <QMenuBar>

#include "CollectionBrowser.h"
#include "MainWindow.h"
#include "PlaylistWidget.h"
#include "PlaylistNode.h"
#include "Track.h"

MainWindow::MainWindow()
	: m_playlist(m_metadata)
	, m_player(m_playlist, m_metadata)
{
	CollectionBrowserWidget *collectionBrowser = new CollectionBrowserWidget();
	PlaylistWidget *playlist = new PlaylistWidget(m_playlist);

	QWidget *centralWidget = new QWidget();
	QHBoxLayout *layout = new QHBoxLayout(centralWidget);
	layout->addWidget(collectionBrowser, 1);
	layout->addWidget(playlist, 2);

	setCentralWidget(centralWidget);

	QMenuBar *menuBar = new QMenuBar();
	menuBar->addAction("Settings");

	setMenuBar(menuBar);

//	connect(collectionBrowser, &CollectionBrowserWidget::trackSelected, &m_playlist, &Playlist::add);
	connect(playlist, &PlaylistWidget::nodeSelected, &m_player, &Player::play);
}

