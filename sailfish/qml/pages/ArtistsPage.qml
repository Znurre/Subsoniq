import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

Page
{
	property var index: null
	property var parentNode: collectionModel.getParentNode(index)

	id: page

	SilicaListView
	{
		PullDownMenu
		{
			MenuItem
			{
				text: "Play all"
				enabled: index != null
				onClicked: main.playlistModel.addAll(parentNode.subject)
			}
		}

		anchors
		{
			fill: parent
		}

		header: PageHeader
		{
			title: collectionModel.getPageTitle(index)
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
			rootIndex: index

			delegate: Loader
			{
				id: loader
				source: viewTemplate
			}
		}
	}
}
