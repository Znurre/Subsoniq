import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

Page
{
	id: page

	property variant artist

	ListView
	{
		anchors
		{
			fill: parent
		}

		model: VisualDataModel
		{
			id: visualDataModel
			model: collectionModel
			rootIndex: artist
			delegate: BackgroundItem
			{
				width: page.width
				height: Theme.itemSizeSmall

				Label
				{
					anchors
					{
						left: parent.left
						verticalCenter: parent.verticalCenter
						margins: Theme.paddingLarge
					}

					text: name
				}
			}
		}
	}
}
