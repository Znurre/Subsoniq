#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>

class Playlist;

class PlaylistModel : public QAbstractListModel
{
	public:
		PlaylistModel(Playlist &playlist);

		int rowCount(const QModelIndex &parent) const override;

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

	private:
		void onPlaylistChanged();

		Playlist &m_playlist;
};

#endif // PLAYLISTMODEL_H
