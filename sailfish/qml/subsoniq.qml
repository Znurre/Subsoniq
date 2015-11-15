import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

import "pages"

ApplicationWindow
{
	Component.onCompleted:
	{
		pageStack.push("pages/HubPage.qml");
		pageStack.pushAttached(playlistPage)
	}

	MainViewModel
	{
		id: main
	}

	PlaylistPage
	{
		id: playlistPage
	}

	CollectionModel
	{
		id: collectionModel
	}

	cover: Qt.resolvedUrl("cover/CoverPage.qml")
	bottomMargin: mediaControls.visibleSize

	MediaControls
	{
		id: mediaControls
		width: parent.width
		dock: Dock.Bottom
		z: 1
	}
}
