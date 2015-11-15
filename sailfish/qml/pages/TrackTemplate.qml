import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem
{
	width: page.width
	height: Theme.itemSizeSmall

	onClicked: main.playlistModel.add(modelData)

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
