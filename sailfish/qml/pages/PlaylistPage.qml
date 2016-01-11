import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

Page
{
	id: page

	RemorsePopup
	{
		id: remorse
	}

	SilicaListView
	{
		ViewPlaceholder
		{
			enabled: view.count == 0
			text: "The playlist is empty"
		}

		PullDownMenu
		{
			MenuItem
			{
				text: "Clear"
				enabled: view.count > 0
				onClicked: remorse.execute("Clearing", main.playlistModel.clear)
			}
		}

		anchors
		{
			fill: parent
		}

		header: PageHeader
		{
			title: "Playlist"
		}

		id: view
		model: main.playlistModel

		delegate: BackgroundItem
		{
			width: page.width
			height: Theme.itemSizeSmall

			onClicked: main.player.play(modelData)

			CoverImage
			{
				anchors
				{
					left: parent.left
					top: parent.top
					bottom: parent.bottom
					margins: Theme.paddingSmall
				}

				id: image
				coverId: nodeId
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

			Column
			{
				anchors
				{
					left: image.right
					right: parent.right
					verticalCenter: parent.verticalCenter
					margins: Theme.paddingLarge
				}

				Label
				{
					anchors
					{
						left: parent.left
						right: parent.right
					}

					id: labelTitle
					text: title
					elide: Text.ElideRight

					states: State
					{
						when: isPlaying

						PropertyChanges
						{
							target: labelTitle
							color: Theme.highlightColor
						}
					}
				}

				Label
				{
					anchors
					{
						left: parent.left
						right: parent.right
					}

					id: labelArtist
					text: artist
					color: Theme.secondaryColor
					elide: Text.ElideRight

					font
					{
						pixelSize: Theme.fontSizeExtraSmall
					}

					states: State
					{
						when: isPlaying

						PropertyChanges
						{
							target: labelArtist
							color: Theme.highlightColor
						}
					}
				}
			}
		}
	}
}
