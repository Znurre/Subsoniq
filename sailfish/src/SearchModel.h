#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QAbstractListModel>

#include "SubsonicAdapter.h"
#include "TypeGroupingResolver.h"

class ICollectionNode;

class SearchModel : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(int status READ status NOTIFY statusChanged)

	Q_ENUMS(Status)

	public:
		enum Roles
		{
			ModelData = Qt::UserRole,
			Title = Qt::UserRole + 1,
			Icon = Qt::UserRole + 2,
			ViewTemplate = Qt::UserRole + 3,
			CoverUrl = Qt::UserRole + 4,
			Grouping = Qt::UserRole + 5,
			ModelIndex = Qt::UserRole + 6
		};

		enum Status
		{
			Loading,
			Finished
		};

		SearchModel();
		~SearchModel();

		int status() const;
		void setStatus(int status);

		QHash<int, QByteArray> roleNames() const override;

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;

		int rowCount(const QModelIndex &parent) const override;

		QVariant data(const QModelIndex &index, int role) const override;

	public slots:
		void search(const QString &query);

	private:
		void response(const QJsonObject &envelope);

		SubsonicAdapter m_adapter;
		TypeGroupingResolver m_typeGroupingResolver;

		QList<ICollectionNode *> m_nodes;

		int m_status;

	signals:
		void statusChanged();
};

#endif // SEARCHMODEL_H
