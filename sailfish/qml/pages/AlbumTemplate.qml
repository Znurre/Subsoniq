import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

BackgroundItem
{
	width: page.width
	height: Theme.itemSizeSmall

	onClicked:
	{
		pageStack.push("CollectionPage.qml", { index: modelIndex })
		pageStack.pushAttached(playlistPage)
	}

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
