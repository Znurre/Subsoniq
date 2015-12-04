#include "SearchModel.h"

SearchModel::SearchModel()
{
}

QHash<int, QByteArray> SearchModel::roleNames() const
{
	return
	{

	};
}

QModelIndex SearchModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(row);
	Q_UNUSED(column);
	Q_UNUSED(parent);

	return QModelIndex();
}

int SearchModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 0;
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
{
	Q_UNUSED(index);
	Q_UNUSED(role);

	return QVariant();
}

void SearchModel::search(const QString &query)
{
	m_adapter.search2(query, this, &SearchModel::response);
}

void SearchModel::response(const QJsonObject &envelope)
{

}
