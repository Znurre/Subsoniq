#include "CollectionModelProxy.h"

CollectionModelProxy::CollectionModelProxy()
{
	setSourceModel(&m_subject);
	setFilterRole(CollectionModel::Title);
	setFilterCaseSensitivity(Qt::CaseInsensitive);

	connect(&m_subject, &CollectionModel::statusChanged, this, &CollectionModelProxy::statusChanged);
}

int CollectionModelProxy::status() const
{
	return m_subject.status();
}

QString CollectionModelProxy::getPageTitle(const QModelIndex &index) const
{
	const QModelIndex &mapped = mapToSource(index);

	return m_subject.getPageTitle(mapped);
}

QObject *CollectionModelProxy::getParentNode(const QModelIndex &index) const
{
	const QModelIndex &mapped = mapToSource(index);

	return m_subject.getParentNode(mapped);
}

QModelIndex CollectionModelProxy::mapToSource(const QModelIndex &proxyIndex) const
{
	return QSortFilterProxyModel::mapToSource(proxyIndex);
}
