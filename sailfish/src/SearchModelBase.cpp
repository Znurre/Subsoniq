#include "SearchModelBase.h"

SearchModelBase::SearchModelBase()
{

}

QVariant SearchModelBase::data(const QModelIndex &index, int role) const
{
	ICollectionNode *node = (ICollectionNode *)index.internalPointer();

	switch (role)
	{
		case Roles::ModelData:
		{
			return QVariant::fromValue(node);
		}

		case Roles::Title:
		{
			return node->title();
		}

		case Roles::Icon:
		{
			return node->icon();
		}

		case Roles::ViewTemplate:
		{
			return node->viewTemplate();
		}

		case Roles::NodeId:
		{
			return node->id();
		}

		case Roles::Type:
		{
			return node->type();
		}

		case Roles::Grouping:
		{
			return m_typeGroupingResolver.resolve(node);
		}

		case Roles::ModelIndex:
		{
			return index;
		}
	}

	return QVariant();
}

