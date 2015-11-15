#ifndef ARTISTSMODEL_H
#define ARTISTSMODEL_H

#include <QAbstractListModel>

#include "SubsonicAdapter.h"

class IArtistModelNode;

class ArtistsModel : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(int status READ status NOTIFY statusChanged)

	Q_ENUMS(Status)

	public:
		enum Roles
		{
			Name = Qt::UserRole,
			Id = Qt::UserRole + 1
		};

		enum Status
		{
			Loading,
			Finished
		};

		ArtistsModel();

		int status() const;

		QHash<int, QByteArray> roleNames() const override;
		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

		int rowCount(const QModelIndex &parent) const override;

	private:
		IArtistModelNode *getChild(IArtistModelNode *parent, int index) const;

		void response(const QJsonObject &envelope);

		QList<IArtistModelNode *> m_nodes;

		SubsonicAdapter m_adapter;

		int m_status;

	signals:
		void statusChanged();
};

#endif // ARTISTSMODEL_H
