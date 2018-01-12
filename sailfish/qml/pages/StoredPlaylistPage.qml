import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	id: page

	property alias playlist: playlistModel.playlist

	StoredPlaylistModel
	{
		id: playlistModel
	}

	SilicaFlickable
	{
		anchors
		{
			fill: parent
		}

		contentHeight: mainColumn.height

		PullDownMenu
		{
			MenuItem
			{
				text: "Queue all"
				onClicked: main.playlistModel.addAll(playlistModel.playlist)
			}

			visible: view.count > 0
		}

		ScrollDecorator {}

		Column
		{
			id: mainColumn
			width: parent.width

			PageHeader
			{
				width: parent.width
				title: playlist.name
			}

			Rectangle
			{
				width: parent.width
				height: childrenRect.height + (Theme.paddingLarge * 2)
				color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity / 2)

				Item
				{
					x: Theme.paddingLarge
					y: Theme.paddingLarge
					width: parent.width - (Theme.paddingLarge * 2)
					height: childrenRect.height

					CoverImage
					{
						size: "192"
						width: 192 * Theme.pixelRatio
						height: 192 * Theme.pixelRatio
						coverId: playlist.coverArt
						id: coverArt
					}

					Column
					{
						id: column
						x: coverArt.x + coverArt.width + Theme.paddingLarge
						width: parent.width - column.x - Theme.paddingLarge
						spacing: Theme.paddingMedium

						Label
						{
							width: parent.width
							wrapMode: Text.Wrap
							color: Theme.highlightColor
							text: playlist.comment

							font
							{
								pixelSize: Theme.fontSizeSmall
							}
						}

						Label
						{
							text: playlist.getCreated()
							color: Theme.secondaryHighlightColor

							font
							{
								pixelSize: Theme.fontSizeExtraSmall
							}
						}
					}
				}
			}

			Item
			{
				width: parent.width
				height: Theme.paddingMedium
			}

			ColumnView
			{
				id: view
				width: parent.width
				itemHeight: Theme.itemSizeSmall
				model: playlistModel
				delegate: TrackTemplate
				{
					showTrackNumber: false
				}
			}

			InfoLabel
			{
				id: placeholder
				text: "The playlist is empty"
				verticalAlignment: Text.AlignVCenter
				height: page.height - placeholder.y
				visible: playlistModel.status === CollectionModel.Empty
			}
		}
	}

	BusyIndicator
	{
		anchors
		{
			centerIn: parent
		}

		size: BusyIndicatorSize.Large
		running: playlistModel.status === CollectionModel.Loading
	}
}
