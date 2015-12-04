#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QAbstractListModel>

#include "SubsonicAdapter.h"

class SearchModel : public QAbstractListModel
{
	public:
		SearchModel();

		QHash<int, QByteArray> roleNames() const override;

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;

		int rowCount(const QModelIndex &parent) const override;

		QVariant data(const QModelIndex &index, int role) const override;

	public slots:
		void search(const QString &query);

	private:
		void response(const QJsonObject &envelope);

		SubsonicAdapter m_adapter;
};

#endif // SEARCHMODEL_H
