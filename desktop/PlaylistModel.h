#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QStyledItemDelegate>

class Playlist;
class PlaylistNode;

class IPlaylistNode
{
	public:
		virtual ~IPlaylistNode() = default;

		virtual const QStyledItemDelegate &delegate() const = 0;

		virtual PlaylistNode *playlistNode() const = 0;

		virtual IPlaylistNode *parent() const = 0;
		virtual IPlaylistNode *childAt(int index) const = 0;

		virtual QIcon image() const
		{
			return QIcon();
		}

		virtual int index() const = 0;
		virtual int childCount() const = 0;
};

class PlaylistModel : public QAbstractItemModel
{
	public:
		enum Roles
		{
			Artist = Qt::UserRole,
			Title = Qt::UserRole + 1
		};

		PlaylistModel(Playlist &playlist);

		int rowCount(const QModelIndex &parent) const override;
		int columnCount(const QModelIndex &parent) const override;

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QModelIndex parent(const QModelIndex &child) const override;

		QVariant data(const QModelIndex &index, int role) const override;

	private:
		void onNodeAppended(int index);

		QList<IPlaylistNode *> m_nodes;

		Playlist &m_playlist;
};

#endif // PLAYLISTMODEL_H
