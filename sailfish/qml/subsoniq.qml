import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

import "pages"

ApplicationWindow
{
	Component.onCompleted:
	{
//		pageStack.push("pages/ArtistsPage.qml");
		pageStack.push("pages/StoredPlaylistsPage.qml");
		pageStack.pushAttached(playlistPage)
	}

	ListModel
	{
		id: menuItemModel

		ListElement
		{
			title: "Settings"
			pageUrl: "SettingsPage.qml"
			icon: "../../icon-s-setting.png"
		}

		ListElement
		{
			title: "Playlists"
			pageUrl: "StoredPlaylistsPage.qml"
			icon: "../../icon-s-playlist.png"
		}

//		ListElement
//		{
//			title: "Albums"
//			pageUrl: "AlbumPage.qml"
//			icon: "../../icon-s-album.png"
//		}

		ListElement
		{
			title: "Artists"
			pageUrl: "ArtistsPage.qml"
			icon: "../../icon-s-artists.png"
		}

		ListElement
		{
			title: "Search"
			pageUrl: "SearchPage.qml"
			icon: "../../icon-s-search.png"
		}
	}

	MainViewModel
	{
		id: main
	}

	PlaylistPage
	{
		id: playlistPage
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
