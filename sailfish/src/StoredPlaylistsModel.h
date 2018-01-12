#ifndef STOREDPLAYLISTSMODEL_H
#define STOREDPLAYLISTSMODEL_H

#include "SubsoniqModelBase.h"
#include "SubsonicAdapter.h"
#include "StoredPlaylistEnvelope.h"

class StoredPlaylistsModel : public SubsoniqModelBase
{
	public:
		StoredPlaylistsModel();

		int rowCount(const QModelIndex &parent) const override;

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

	private:
		void response(const QJsonObject &response);

		SubsonicAdapter m_adapter;
		StoredPlaylistEnvelope m_envelope;
};

#endif // STOREDPLAYLISTSMODEL_H
