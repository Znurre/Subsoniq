#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>

class Playlist;
class Track;
class ICollectionNode;
class PlaylistNode;

class PlaylistModel : public QAbstractListModel
{
	Q_OBJECT

	const QModelIndex NoParent;

	public:
		enum Roles
		{
			ModelData = Qt::UserRole,
			Artist = Qt::UserRole + 1,
			Title = Qt::UserRole + 2,
			IsPlaying = Qt::UserRole + 3,
			NodeId = Qt::UserRole + 4
		};

		PlaylistModel(Playlist &playlist);

		int rowCount(const QModelIndex &parent) const override;

		QHash<int, QByteArray> roleNames() const override;
		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

	public slots:
		void add(ICollectionNode *node);
		void addAll(ICollectionNode *parent);
		void remove(PlaylistNode *node);
		void clear();

	private:
		void onNodeChanged(int nodeIndex);
		void onNodeAppended(int index);
		void onNodeRemoved(int index);
		void onPlaylistChanged();

		Playlist &m_playlist;

	signals:
		void playlistCleared();
};

#endif // PLAYLISTMODEL_H
