import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem
{
	width: page.width
	height: Theme.itemSizeSmall

	onClicked: main.playlistModel.add(modelData)

	Item
	{
		anchors
		{
			left: parent.left
			verticalCenter: parent.verticalCenter
			margins: Theme.paddingSmall
		}

		id: trackNumber
		width: Theme.itemSizeSmall - (Theme.paddingSmall * 2)
		height: column.height

		Label
		{
			anchors
			{
				top: parent.top
				right: parent.right
			}

			color: Theme.highlightColor
			text: modelData.trackNumber
			visible: text !== "0"
		}
	}

	Column
	{
		anchors
		{
			left: trackNumber.right
			right: parent.right
			verticalCenter: parent.verticalCenter
			margins: Theme.paddingLarge
			leftMargin: Theme.paddingMedium
		}

		id: column

		Label
		{
			anchors
			{
				left: parent.left
				right: parent.right
			}

			id: labelTitle
			text: modelData.title
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
			text: modelData.artist
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
