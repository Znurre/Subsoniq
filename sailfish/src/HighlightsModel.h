#ifndef HIGHLIGHTSMODEL_H
#define HIGHLIGHTSMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>

#include "SubsonicAdapter.h"

class ICollectionNode;

class HighlightsModel : public QAbstractListModel
{
	enum Roles
	{
		CoverUrl = Qt::UserRole
	};

	public:
		HighlightsModel();

		int rowCount(const QModelIndex &parent) const override;

		QHash<int, QByteArray> roleNames() const override;
		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

	private:
		void starredResponse(const QJsonObject &envelope);
		void frequentResponse(const QJsonObject &envelope);
		void response(const QJsonObject &envelope, bool starred);

		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_nodes;
};

#endif // HIGHLIGHTSMODEL_H
