#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QAbstractListModel>

#include "SubsoniqModelBase.h"
#include "SubsonicAdapter.h"
#include "TypeGroupingResolver.h"

class ICollectionNode;

class SearchModel : public SubsoniqModelBase
{
	Q_OBJECT

	public:
		~SearchModel();

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

		int rowCount(const QModelIndex &parent) const override;

	public slots:
		void search(const QString &query);

	private:
		void response(const QJsonObject &envelope);

		SubsonicAdapter m_adapter;
		TypeGroupingResolver m_typeGroupingResolver;

		QList<ICollectionNode *> m_nodes;
};

#endif // SEARCHMODEL_H
