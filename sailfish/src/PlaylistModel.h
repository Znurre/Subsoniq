#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>

class Playlist;
class Track;
class ICollectionNode;

class PlaylistModel : public QAbstractListModel
{
	Q_OBJECT

	public:
		enum Roles
		{
			ModelData = Qt::UserRole,
			Artist = Qt::UserRole + 1,
			Title = Qt::UserRole + 2,
			CoverUrl = Qt::UserRole + 3,
			IsPlaying = Qt::UserRole + 4
		};

		PlaylistModel(Playlist &playlist);

		int rowCount(const QModelIndex &parent) const override;

		QHash<int, QByteArray> roleNames() const override;
		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

	public slots:
		void add(ICollectionNode *node);
		void addAll(ICollectionNode *parent);
		void clear();

	private:
		void onPlaylistChanged();

		Playlist &m_playlist;
};

#endif // PLAYLISTMODEL_H
