import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem
{
	width: page.width
	height: Theme.itemSizeExtraSmall

	onClicked:
	{
		pageStack.push("DetailedSearchPage.qml", { query: name, type: model.type })
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

		text: "Show more"
		elide: Text.ElideRight
		horizontalAlignment: Text.AlignRight

		font
		{
			pixelSize: Theme.fontSizeSmall
		}
	}
}
