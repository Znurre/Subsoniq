#include <QIcon>

#include "PlaylistModel.h"
#include "Playlist.h"
#include "Track.h"
#include "PlaylistNode.h"

PlaylistModel::PlaylistModel(Playlist &playlist)
	: m_playlist(playlist)
{
//	connect(&m_playlist, &Playlist::playlistChanged, this, &PlaylistModel::onPlaylistChanged);
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_playlist.count();
}

QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(column);
	Q_UNUSED(parent);

	PlaylistNode *node = m_playlist.nodeAt(row);

	return createIndex(row, column, node);
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
	PlaylistNode *node = (PlaylistNode *)index.internalPointer();

	if (role == Qt::DisplayRole)
	{
		const Track *track = node->track();

		return track->title();
	}

	if (role == Qt::DecorationRole)
	{
		if (m_playlist.current() == node)
		{
			return QIcon::fromTheme("arrow-right");
		}
	}

	return QVariant();
}

void PlaylistModel::onPlaylistChanged()
{
	qDebug() << "Model updated";

	emit layoutChanged();
}

