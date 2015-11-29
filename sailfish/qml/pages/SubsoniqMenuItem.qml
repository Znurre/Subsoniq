import QtQuick 2.0
import QtGraphicalEffects 1.0

import Sailfish.Silica 1.0

MenuItem
{
	property alias text: label.text
	property alias image: image.source

	id: item

	Row
	{
		spacing: Theme.paddingSmall
		height: parent.height

		anchors
		{
			centerIn: parent
		}

		Item
		{
			anchors
			{
				verticalCenter: parent.verticalCenter
			}

			width: childrenRect.width
			height: childrenRect.height

			Image
			{
				id: image
				visible: false
			}

			ColorOverlay
			{
				anchors
				{
					fill: image
				}

				source: image
				color: item.color
			}
		}

		Label
		{
			anchors
			{
				verticalCenter: parent.verticalCenter
			}

			id: label
			color: item.color
		}
	}
}
