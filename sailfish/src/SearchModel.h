#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QAbstractListModel>

#include "SubsoniqModelBase.h"
#include "SubsonicAdapter.h"
#include "TypeGroupingResolver.h"
#include "SearchModelBase.h"

class ICollectionNode;

class SearchModel : public SearchModelBase
{
	Q_OBJECT

	public:
		~SearchModel();

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;

		int rowCount(const QModelIndex &parent) const override;

	public slots:
		void search(const QString &query);

	private:
		void response(const QJsonObject &envelope);

		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_nodes;
		QString m_query;
};

#endif // SEARCHMODEL_H
