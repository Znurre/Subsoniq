import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	id: page

	StoredPlaylistsModel
	{
		id: playlistsModel
	}

	SilicaListView
	{
		PullDownMenu
		{
			Repeater
			{
				model: menuItemModel

				SubsoniqMenuItem
				{
					text: title
					image: icon
					enabled: pageUrl != "StoredPlaylistsPage.qml"

					onClicked: navigate(pageUrl);
				}
			}
		}

		BusyIndicator
		{
			anchors
			{
				centerIn: parent
			}

			size: BusyIndicatorSize.Large
			running: playlistsModel.status === CollectionModel.Loading
		}

		ViewPlaceholder
		{
			enabled: playlistsModel.status === CollectionModel.Empty
			text: "You have no playlists"
		}

		anchors
		{
			fill: parent
		}

		header: PageHeader
		{
			title: "Playlists"
		}

		model: playlistsModel
		delegate: BackgroundItem
		{
			width: page.width
			height: Theme.itemSizeSmall

			onClicked:
			{
				pageStack.push("StoredPlaylistPage.qml", { playlist: modelData });
				pageStack.pushAttached(playlistPage);
			}

			CoverImage
			{
				anchors
				{
					left: parent.left
					top: parent.top
					bottom: parent.bottom
					margins: Theme.paddingSmall
					leftMargin: Theme.paddingLarge
				}

				id: image
				coverId: coverArt
				width: Theme.itemSizeSmall - (Theme.paddingSmall * 2)

				BusyIndicator
				{
					anchors
					{
						fill: parent
					}

					running: !image.isReady
				}
			}

			Label
			{
				anchors
				{
					left: image.right
					right: parent.right
					verticalCenter: parent.verticalCenter
					margins: Theme.paddingLarge
					leftMargin: Theme.paddingMedium
				}

				text: name
			}
		}
	}
}
