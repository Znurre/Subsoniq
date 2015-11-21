import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

DockedPanel
{
	height: column.height + Theme.paddingLarge * 2
	contentHeight: height
	open: main.metadata.state > 0

	MediaControlsViewModel
	{
		id: model

		pauseIcon: "image://theme/icon-m-pause"
		playIcon: "image://theme/icon-m-play"

		metadata: main.metadata
		player: main.player
	}

	Column
	{
		id: column
		width: parent.width
		y: Theme.paddingMedium
		spacing: Theme.paddingLarge

		Slider
		{
			property var duration: main.metadata.duration
			property var position: main.metadata.position

			width: parent.width
			handleVisible: false
			value: position
			valueText: Format.formatDuration(position, Format.DurationShort)

			label: model.displayTitle

			minimumValue: 0
			maximumValue: duration
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
					source: model.playPauseIcon
				}

				id: pauseButton
				width: parent.width / 3
				onClicked: model.playPause()
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
