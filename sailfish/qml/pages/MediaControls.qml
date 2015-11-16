import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

DockedPanel
{
	height: column.height + Theme.paddingLarge * 2
	contentHeight: height
	open: main.metadata.state > 0

	Column
	{
		id: column
		width: parent.width
		y: Theme.paddingMedium
		spacing: Theme.paddingLarge

		Slider
		{
			property var author: main.metadata.artist
			property var title: main.metadata.title
			property var duration: main.metadata.duration
			property var position: main.metadata.position

			width: parent.width
			handleVisible: false
			value: duration
			valueText: Format.formatDuration(duration, Format.DurationShort)

			label: "%1 - %2".arg(author, title)

			minimumValue: 0
			maximumValue: 200
			enabled: false
		}

		Row
		{
			id: navigation
			width: parent.width

			IconButton
			{
				anchors
				{
					verticalCenter: parent.verticalCenter
				}

				icon
				{
					source: "image://theme/icon-m-previous"
				}

				width: parent.width / 3
				onClicked: main.player.previous()
			}

			IconButton
			{
				icon
				{
					source: "image://theme/icon-m-pause"
				}

				width: parent.width / 3
				onClicked: main.player.playPause()
			}

			IconButton
			{
				anchors
				{
					verticalCenter: parent.verticalCenter
				}

				icon
				{
					source: "image://theme/icon-m-next"
				}

				width: parent.width / 3
				onClicked: main.player.next()
			}
		}
	}
}
