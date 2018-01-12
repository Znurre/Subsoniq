#include <QtQuick>

#include <sailfishapp.h>

#include "SettingsPageViewModel.h"
#include "MediaControlsViewModel.h"
#include "PlaylistPageViewModel.h"
#include "MainViewModel.h"

#include "Track.h"
#include "CollectionModel.h"
#include "CollectionModelProxy.h"
#include "HighlightsModel.h"
#include "CoverArtImageProvider.h"
#include "SearchModel.h"
#include "MetadataController.h"
#include "ICollectionNode.h"
#include "ICollectionNodeProxy.h"
#include "CoverImage.h"
#include "PlaylistNode.h"
#include "DetailedSearchModel.h"
#include "StoredPlaylistsModel.h"
#include "StoredPlaylistModel.h"

int main(int argc, char *argv[])
{
	qmlRegisterType<SettingsPageViewModel>("harbour.subsoniq", 1, 0, "SettingsPageViewModel");
	qmlRegisterType<PlaylistPageViewModel>("harbour.subsoniq", 1, 0, "PlaylistPageViewModel");
	qmlRegisterType<MainViewModel>("harbour.subsoniq", 1, 0, "MainViewModel");
	qmlRegisterType<MediaControlsViewModel>("harbour.subsoniq", 1, 0, "MediaControlsViewModel");
	qmlRegisterType<CoverImage>("harbour.subsoniq", 1, 0, "CoverImage");

	qmlRegisterType<CollectionModel>("harbour.subsoniq", 1, 0, "CollectionModel");
	qmlRegisterType<CollectionModelProxy>("harbour.subsoniq", 1, 0, "CollectionModelProxy");
	qmlRegisterType<HighlightsModel>("harbour.subsoniq", 1, 0, "HighlightsModel");
	qmlRegisterType<SearchModel>("harbour.subsoniq", 1, 0, "SearchModel");
	qmlRegisterType<DetailedSearchModel>("harbour.subsoniq", 1, 0, "DetailedSearchModel");
	qmlRegisterType<StoredPlaylistsModel>("harbour.subsoniq", 1, 0, "StoredPlaylistsModel");
	qmlRegisterType<StoredPlaylistModel>("harbour.subsoniq", 1, 0, "StoredPlaylistModel");
//	qmlRegisterType<MetadataController>("harbour.subsoniq", 1, 0, "MetadataController");

	qmlRegisterType<Player>();
	qmlRegisterType<PlaylistNode>();
	qmlRegisterType<Playlist>();
	qmlRegisterType<StoredPlaylist>();
	qmlRegisterType<MetadataController>();
	qmlRegisterType<ICollectionNode>();
	qmlRegisterType<INode>();
	qmlRegisterType<ICollectionNodeProxy>();

	// SailfishApp::main() will display "qml/template.qml", if you need more
	// control over initialization, you can use:
	//
	//   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
	//   - SailfishApp::createView() to get a new QQuickView * instance
	//   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
	//
	// To display the view, call "show()" (will show fullscreen on device).

	QGuiApplication *application = SailfishApp::application(argc, argv);
	QQuickView *view = SailfishApp::createView();

	CoverArtImageProvider coverArtImageProvider;

	QQmlEngine *engine = view->engine();
	engine->addImageProvider("cover", &coverArtImageProvider);

	const QUrl &path = SailfishApp::pathTo("qml/subsoniq.qml");

	view->setSource(path);
	view->show();

	return application->exec();
}

