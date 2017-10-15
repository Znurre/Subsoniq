import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

Page
{
	id: page
	backNavigation: !context.isEditMode

	Connections
	{
		target: main.playlistModel
		onPlaylistCleared: context.leaveEditMode()
	}

	RemorsePopup
	{
		id: remorse
	}

	PlaylistPageViewModel
	{
		id: context

		onPlayRequested: main.player.play(node)
		onClearRequested: main.playlistModel.clear()
	}

	SilicaListView
	{
		ViewPlaceholder
		{
			enabled: view.count == 0
			text: "The playlist is empty"
		}

		PullDownMenu
		{
			MenuItem
			{
				text: "Clear"
				onClicked: remorse.execute("Clearing", context.clear, 3000)
			}

			visible: !context.isEditMode && view.count > 0
		}

		anchors
		{
			fill: parent
		}

		header: PageHeader
		{
			title: "Playlist"
		}

		id: view
		model: main.playlistModel

		displaced: Transition
		{
			NumberAnimation
			{
				properties: "y"
				duration: 250

				easing
				{
					type: Easing.OutCubic
				}
			}
		}

		remove: Transition
		{
			NumberAnimation
			{
				to: 0
				property: "opacity"
				duration: 250
			}
		}

		delegate: BackgroundItem
		{
			x: -(removeButton.width + Theme.horizontalPageMargin)
			width: page.width - x
			height: Theme.itemSizeSmall
			id: item

			onClicked: context.itemActivated(modelData)
			onPressAndHold: context.enterEditMode()

			Behavior on x
			{
				PropertyAnimation
				{
					duration: 250

					easing
					{
						type: Easing.OutCubic
					}
				}
			}

			states: State
			{
				when: context.isEditMode

				PropertyChanges
				{
					target: item
					x: 0
				}

				PropertyChanges
				{
					target: removeButton
					opacity: 1
				}
			}

			Image
			{
				anchors
				{
					verticalCenter: parent.verticalCenter
				}

				id: removeButton
				source: "image://theme/icon-m-clear"
				opacity: 0
				x: Theme.horizontalPageMargin

				Behavior on opacity
				{
					PropertyAnimation
					{
						duration: 250

						easing
						{
							type: Easing.OutCubic
						}
					}
				}

				MouseArea
				{
					anchors
					{
						fill: parent
					}

					onClicked: main.playlistModel.remove(modelData)
				}
			}

			CoverImage
			{
				id: image
				coverId: nodeId
				height: parent.height - (Theme.paddingSmall * 2)
				width: Theme.itemSizeSmall - (Theme.paddingSmall * 2)
				x: removeButton.x + removeButton.width + Theme.horizontalPageMargin
				y: Theme.paddingSmall

				BusyIndicator
				{
					anchors
					{
						fill: parent
					}

					running: !image.isReady
				}
			}

			Column
			{
				anchors
				{
					verticalCenter: parent.verticalCenter
				}

				x: image.x + image.width + Theme.paddingLarge
				width: item.width - x - Theme.horizontalPageMargin

				Label
				{
					id: labelTitle
					text: title
					elide: Text.ElideRight
					width: parent.width

					states: State
					{
						when: isPlaying

						PropertyChanges
						{
							target: labelTitle
							color: Theme.highlightColor
						}
					}
				}

				Label
				{
					id: labelArtist
					text: artist
					color: Theme.secondaryColor
					elide: Text.ElideRight
					width: parent.width

					font
					{
						pixelSize: Theme.fontSizeExtraSmall
					}

					states: State
					{
						when: isPlaying

						PropertyChanges
						{
							target: labelArtist
							color: Theme.highlightColor
						}
					}
				}
			}
		}
	}
}
