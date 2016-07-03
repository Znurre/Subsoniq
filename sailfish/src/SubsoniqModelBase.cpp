#include "SubsoniqModelBase.h"
#include "ICollectionNode.h"

SubsoniqModelBase::SubsoniqModelBase()
	: m_status(Finished)
{

}

QHash<int, QByteArray> SubsoniqModelBase::roleNames() const
{
	return
	{
		{ ModelData, "modelData" },
		{ Title, "name" },
		{ Icon, "icon" },
		{ ViewTemplate, "viewTemplate" },
		{ NodeId, "nodeId" },
		{ Grouping, "grouping" },
		{ ModelIndex, "modelIndex" },
		{ Type, "type" }
	};
}

QModelIndex SubsoniqModelBase::parent(const QModelIndex &child) const
{
	Q_UNUSED(child);

	return QModelIndex();
}

int SubsoniqModelBase::status() const
{
	return m_status;
}

void SubsoniqModelBase::setStatus(int status)
{
	m_status = status;

	emit statusChanged();
}

int SubsoniqModelBase::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 1;
}
