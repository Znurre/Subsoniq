import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	id: page

	SilicaListView
	{
		anchors
		{
			fill: parent
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
					enabled: pageUrl != "SearchPage.qml"

					onClicked: navigate(pageUrl);
				}
			}
		}

		ViewPlaceholder
		{
			text: "Nothing here yet"
			enabled: true
		}
	}
}
