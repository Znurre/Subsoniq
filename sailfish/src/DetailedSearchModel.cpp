#include <QJsonArray>

#include "CollectionArtistNode.h"
#include "CollectionTrackNode.h"
#include "DetailedSearchModel.h"

const int WINDOW = 50;

DetailedSearchModel::DetailedSearchModel()
	: m_self(this)
	, m_canFetch(true)
{

}

QString DetailedSearchModel::query() const
{
	return m_query;
}

void DetailedSearchModel::setQuery(const QString &query)
{
	m_query = query;
}

QString DetailedSearchModel::type() const
{
	return m_type;
}

void DetailedSearchModel::setType(const QString &type)
{
	m_type = type;
}

QModelIndex DetailedSearchModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	ICollectionNode *node = m_nodes.value(row, &m_end);

	return createIndex(row, column, node);
}

QVariant DetailedSearchModel::data(const QModelIndex &index, int role) const
{
	ICollectionNode *node = (ICollectionNode *)index.internalPointer();
	ICollectionNode *fetchMore = dynamic_cast<CollectionEndNode *>(node);

	if (fetchMore)
	{
		if (m_canFetch)
		{
			m_self->fetch();
		}

		return QVariant();
	}

	return SearchModelBase::data(index, role);
}

int DetailedSearchModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_nodes.count() + 1;
}

void DetailedSearchModel::fetch()
{
	setStatus(Loading);

	m_adapter.search2(m_query, WINDOW, LIMIT + m_nodes.count(), this, &DetailedSearchModel::response);
}

void DetailedSearchModel::response(const QJsonObject &envelope)
{
	qDebug() << m_type << m_query;

	const int first = m_nodes.count();

	const QJsonObject &searchResult2 = envelope
		.value("searchResult2")
		.toObject();

	const QJsonArray &result = searchResult2
		.value(m_type)
		.toArray();

	qDebug() << result;

	for (const QJsonValue &value : result)
	{
		const QJsonObject &object = value.toObject();

		m_nodes << new CollectionTrackNode(object);
	}

	if (result.count() < WINDOW)
	{
		m_canFetch = false;
	}

	const int last = m_nodes.count();

	beginInsertRows(NoParent, first, last);
	endInsertRows();

	setStatus(Finished);
}
