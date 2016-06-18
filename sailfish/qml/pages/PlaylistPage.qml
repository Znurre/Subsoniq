import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

Page
{
	id: page
	backNavigation: !context.isEditMode

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
				enabled: view.count > 0
				onClicked: remorse.execute("Clearing", context.clear)
			}
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
			width: page.width
			height: Theme.itemSizeSmall

			onClicked: context.itemActivated(modelData)
			onPressAndHold: context.enterEditMode()

			Image
			{
				anchors
				{
					left: parent.left
					leftMargin: -64
					verticalCenter: parent.verticalCenter
					margins: Theme.paddingLarge

					Behavior on leftMargin
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
				}

				id: removeButton
				source: "image://theme/icon-m-clear"
				opacity: 0

				states: State
				{
					when: context.isEditMode

					PropertyChanges
					{
						target: removeButton.anchors
						leftMargin: Theme.paddingLarge
					}

					PropertyChanges
					{
						target: removeButton
						opacity: 1
					}
				}

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
				anchors
				{
					left: removeButton.right
					top: parent.top
					bottom: parent.bottom
					margins: Theme.paddingSmall
					leftMargin: Theme.paddingLarge
				}

				id: image
				coverId: nodeId
				width: Theme.itemSizeSmall - (Theme.paddingSmall * 2)

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
					left: image.right
					right: parent.right
					verticalCenter: parent.verticalCenter
					margins: Theme.paddingLarge
				}

				Label
				{
					anchors
					{
						left: parent.left
						right: parent.right
					}

					id: labelTitle
					text: title
					elide: Text.ElideRight

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
					anchors
					{
						left: parent.left
						right: parent.right
					}

					id: labelArtist
					text: artist
					color: Theme.secondaryColor
					elide: Text.ElideRight

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
