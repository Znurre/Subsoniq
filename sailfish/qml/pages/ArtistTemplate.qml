import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem
{
	width: page.width
	height: Theme.itemSizeSmall

	onClicked:
	{
		pageStack.push("CollectionPage.qml", { index: visualDataModel.modelIndex(index) })
		pageStack.pushAttached(playlistPage)
	}

	Label
	{
		anchors
		{
			left: parent.left
			right: parent.right
			verticalCenter: parent.verticalCenter
			margins: Theme.paddingLarge
		}

		text: name
		elide: Text.ElideRight
	}
}
