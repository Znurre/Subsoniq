import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	id: page

	CollectionModelProxy
	{
		id: collectionModel
	}

	SilicaListView
	{
		PullDownMenu
		{
			Repeater
			{
				model: menuItemModel

				SubsoniqMenuItem
				{
					text: title
					image: icon
					enabled: pageUrl != "ArtistsPage.qml"

					onClicked: navigate(pageUrl);
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
			running: collectionModel.status === CollectionModel.Loading
		}

		anchors
		{
			fill: parent
		}

		header: SearchField
		{
			id: searchField
			width: parent.width
			placeholderText: "Filter"

			onTextChanged: collectionModel.setFilterFixedString(searchField.text)
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
			model: collectionModel

			delegate: Loader
			{
				id: loader
				source: viewTemplate
			}
		}
	}
}
