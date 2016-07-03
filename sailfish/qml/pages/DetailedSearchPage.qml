import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	property alias query: searchModel.query
	property alias type: searchModel.type

	id: page

	DetailedSearchModel
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

		BusyIndicator
		{
			anchors
			{
				centerIn: parent
			}

			size: BusyIndicatorSize.Large
			running: searchModel.status === CollectionModel.Loading
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
