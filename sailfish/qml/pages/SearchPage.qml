import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	id: page

	SearchModel
	{
		id: searchModel
	}

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

		header: SearchField
		{
			anchors
			{
				left: parent.left
				right: parent.right
				rightMargin: Theme.paddingLarge
			}

			id: searchField
			placeholderText: "Search"

			Keys.onReturnPressed: searchModel.search(searchField.text)
		}

		section
		{
			property: "grouping"
			delegate: SectionHeader
			{
				text: section
			}
		}

		model: VisualDataModel
		{
			id: visualDataModel
			model: searchModel

			delegate: Loader
			{
				id: loader
				source: viewTemplate
			}
		}
	}
}
