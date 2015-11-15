import QtQuick 2.0
import Sailfish.Silica 1.0

Page
{
	ListModel
	{
		id: model

		ListElement
		{
			title: "Artists"
			pageUrl: "CollectionPage.qml"
		}

		ListElement
		{
			title: "Search"
		}

		ListElement
		{
			title: "Settings"
			pageUrl: "SettingsPage.qml"
		}
	}

	ListView
	{
		anchors
		{
			fill: parent
		}

		model: model

		delegate: BackgroundItem
		{
			onClicked:
			{
				pageStack.push(pageUrl)
				pageStack.pushAttached(playlistPage)
			}

			id: delegate

			Label
			{
				anchors
				{
					left: parent.left
					verticalCenter: parent.verticalCenter
					margins: Theme.paddingLarge
				}

				text: title
				color: delegate.highlighted ?
					Theme.highlightColor :
					Theme.primaryColor
			}
		}
	}
}
