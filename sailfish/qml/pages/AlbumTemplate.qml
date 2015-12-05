import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem
{
	width: page.width
	height: Theme.itemSizeSmall

	onClicked:
	{
		pageStack.push("CollectionPage.qml", { index: modelIndex })
		pageStack.pushAttached(playlistPage)
	}

	Image
	{
		anchors
		{
			left: parent.left
			top: parent.top
			bottom: parent.bottom
			margins: Theme.paddingSmall
		}

		id: image
		source: coverUrl
		width: Theme.itemSizeSmall - (Theme.paddingSmall * 2)
		asynchronous: true

		BusyIndicator
		{
			anchors
			{
				fill: parent
			}

			running: image.status === Image.Loading
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
		}

		text: name
		elide: Text.ElideRight
	}
}
