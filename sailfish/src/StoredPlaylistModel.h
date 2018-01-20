#ifndef STOREDPLAYLISTMODEL_H
#define STOREDPLAYLISTMODEL_H

#include "StoredPlaylist.h"
#include "SubsoniqModelBase.h"
#include "SubsonicAdapter.h"

class StoredPlaylistModel : public SubsoniqModelBase
{
	Q_OBJECT

	Q_PROPERTY(StoredPlaylist *playlist READ playlist WRITE setPlaylist NOTIFY playlistChanged)

	public:
		StoredPlaylistModel();

		StoredPlaylist *playlist();
		void setPlaylist(StoredPlaylist *playlist);

		int rowCount(const QModelIndex &parent) const override;

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

	private:
		void response(const QJsonObject &response);

		SubsonicAdapter m_adapter;

		StoredPlaylist *m_playlist;

	signals:
		void playlistChanged();
};

#endif // STOREDPLAYLISTMODEL_H
