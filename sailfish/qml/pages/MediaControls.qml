import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

DockedPanel
{
	property alias author: slider.author
	property alias title: slider.title
	property alias duration: slider.duration
	property alias position: slider.position

	height: column.height + Theme.paddingLarge * 2
	contentHeight: height
	open: metadataController.isPlaying

	MetadataController
	{
		id: metadataController
		playlist: main.playlist
	}

	Column
	{
		id: column
		width: parent.width
		y: Theme.paddingMedium
		spacing: Theme.paddingLarge

		Slider
		{
			id: slider

			property string author
			property string title
			property int duration
			property int position

			width: parent.width
			handleVisible: false
			valueText: Format.formatDuration(slider.value, Format.DurationShort)

			label: metadataController.formattedTitle

			minimumValue: 0
			maximumValue: 200
			enabled: true
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
