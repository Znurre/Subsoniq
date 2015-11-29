import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	id: page

	SilicaFlickable
	{
		anchors
		{
			fill: parent
		}

		HighlightsModel
		{
			id: highlights
		}

		PageHeader
		{
			id: header
			title: "Highlights \u25bc"
		}

		PullDownMenu
		{
			Repeater
			{
				model: menuItemModel

				SubsoniqMenuItem
				{
					text: title
					image: icon
					enabled: pageUrl != "AlbumPage.qml"

					onClicked: navigate(pageUrl);
				}
			}
		}

		Grid
		{
			id: grid

			anchors
			{
				top: header.bottom
				left: parent.left
				right: parent.right
				bottom: parent.bottom
			}

			rows: height / (width / columns)
			columns: 3
			clip: true

			Repeater
			{
				model: highlights

				Image
				{
					width: parent.width / grid.columns
					height: width

					id: image
					source: coverUrl
					asynchronous: true

					BusyIndicator
					{
						anchors
						{
							fill: parent
						}

						running: image.status === Image.Loading
					}
				}
			}
		}

//		SilicaListView
//		{
//			anchors
//			{
//				left: parent.left
//				right: parent.right
//				bottom: parent.bottom
//			}

//			id: list
//			model: model
//			interactive: false
//			height: childrenRect.height

//			delegate: MouseArea
//			{
//				property var color: pressed
//					? Theme.highlightColor
//					: Theme.primaryColor

//				id: root
//				width: parent.width
//				implicitHeight: Theme.itemSizeMedium

//				onClicked:
//				{
//					pageStack.push(pageUrl)
//					pageStack.pushAttached(playlistPage)
//				}

//				Rectangle
//				{
//					anchors
//					{
//						fill: parent
//					}

//					gradient: Gradient
//					{
//						GradientStop
//						{
//							position: 0.0
//							color: Theme.rgba(Theme.highlightBackgroundColor, 0.1)
//						}

//						GradientStop
//						{
//							position: 1.0
//							color: "transparent"
//						}
//					}
//				}

//				Image
//				{
//					id: icon

//					anchors
//					{
//						right: parent.right
//						rightMargin: Theme.horizontalPageMargin
//						verticalCenter: parent.verticalCenter
//					}

//					source: "image://theme/icon-m-right?" + root.color
//				}

//				Label
//				{
//					id: label
//					truncationMode: TruncationMode.Fade
//					color: root.color
//					horizontalAlignment: Text.AlignRight
//					text: title

//					anchors
//					{
//						left: parent.left
//						leftMargin: Theme.horizontalPageMargin
//						verticalCenter: parent.verticalCenter
//						right: icon.left
//						rightMargin: Theme.paddingMedium
//					}
//				}
//			}
//		}
	}
}
