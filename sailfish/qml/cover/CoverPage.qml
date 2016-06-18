import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

CoverBackground 
{
	MediaControlsViewModel
	{
		id: model

		pauseIcon: "image://theme/icon-cover-pause"
		playIcon: "image://theme/icon-cover-play"

		metadata: main.metadata
		player: main.player
	}

	Column
	{
		anchors
		{
			margins: Theme.paddingMedium
			verticalCenter: parent.verticalCenter
			verticalCenterOffset: -Theme.itemSizeMedium / 2
		}

		x: Theme.paddingMedium
		y: Theme.paddingMedium

		spacing: Theme.paddingSmall
		visible: model.isPlaying
		width: parent.width - 2 * Theme.paddingMedium

		Label
		{
			font
			{
				pixelSize: Theme.fontSizeLarge
			}

			text: main.metadata.artist
			width: parent.width
			horizontalAlignment: Text.AlignHCenter
			color: Theme.highlightColor
			elide: Text.ElideRight
			lineHeightMode: Text.FixedHeight
			lineHeight: Theme.itemSizeMedium / 2
		}

		Label
		{
			font
			{
				pixelSize: Theme.fontSizeLarge
			}

			text: main.metadata.title
			width: parent.width
			horizontalAlignment: Text.AlignHCenter
			maximumLineCount: 3
			wrapMode: Text.WordWrap
			elide: Text.ElideRight
			lineHeightMode: Text.FixedHeight
			lineHeight: Theme.itemSizeMedium / 2
		}
	}

	CoverPlaceholder
	{
		visible: !model.isPlaying
		text: "Nothing playing"
	}

	CoverActionList
	{
		enabled: model.isPlaying

		CoverAction
		{
			iconSource: model.playPauseIcon
			onTriggered: model.playPause()
		}

		CoverAction
		{
			iconSource: "image://theme/icon-cover-next-song"
			onTriggered: main.player.next()
		}
	}
}
