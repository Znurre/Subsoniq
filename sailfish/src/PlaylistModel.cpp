#include "PlaylistModel.h"
#include "PlaylistNode.h"
#include "Playlist.h"
#include "Track.h"
#include "ICollectionNode.h"
#include "QStringEx.h"
#include "CollectionTrackNode.h"
#include "CollectionIterator.h"

PlaylistModel::PlaylistModel(Playlist &playlist)
	: m_playlist(playlist)
{
	connect(&playlist, &Playlist::nodeChanged, this, &PlaylistModel::onNodeChanged);
	connect(&playlist, &Playlist::nodeAppended, this, &PlaylistModel::onNodeAppended);
	connect(&playlist, &Playlist::nodeRemoved, this, &PlaylistModel::onNodeRemoved);
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_playlist.count();
}

QHash<int, QByteArray> PlaylistModel::roleNames() const
{
	return
	{
		{ Roles::ModelData, "modelData", },
		{ Roles::Artist, "artist" },
		{ Roles::Title, "title" },
		{ Roles::IsPlaying, "isPlaying" },
		{ Roles::NodeId, "nodeId" }
	};
}

QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	PlaylistNode *node = m_playlist.nodeAt(row);

	return createIndex(row, column, node);
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
	PlaylistNode *node = (PlaylistNode *)index.internalPointer();
	Track *track = node->track();

	switch (role)
	{
		case Roles::ModelData:
		{
			return QVariant::fromValue(node);
		}

		case Roles::Artist:
		{
			return track->artist();
		}

		case Roles::Title:
		{
			return track->title();
		}

		case Roles::IsPlaying:
		{
			return node == m_playlist.current();
		}

		case Roles::NodeId:
		{
			return track->id();
		}
	}

	return QVariant();
}

void PlaylistModel::add(ICollectionNode *node)
{
	Track *track = node->track();

	const QString &message = QStringEx::format("%1 added to the playlist", track);

	m_notification.setPreviewBody(message);
	m_notification.setExpireTimeout(1000);
	m_notification.publish();

	m_playlist.add(track);
}

void PlaylistModel::addAll(INode *parent)
{
	CollectionIterator iterator;

	const QList<Track *> &tracks = iterator.getTracks(parent);
	const QString &message = QStringEx::format("%1 songs added to the playlist", tracks.count());

	for (Track *track : tracks)
	{
		m_playlist.add(track);
	}

	m_notification.setPreviewBody(message);
	m_notification.setExpireTimeout(1000);
	m_notification.publish();
}

void PlaylistModel::remove(PlaylistNode *node)
{
	m_playlist.remove(node);
}

void PlaylistModel::clear()
{
	m_playlist.clear();

	emit layoutChanged();
	emit playlistCleared();
}

void PlaylistModel::onNodeChanged(int nodeIndex)
{
	const QModelIndex &topLeft = index(nodeIndex, 0, NoParent);

	emit dataChanged(topLeft, topLeft);
}

void PlaylistModel::onNodeAppended(int index)
{
	beginInsertRows(NoParent, index, index);
	endInsertRows();
}

void PlaylistModel::onNodeRemoved(int index)
{
	beginRemoveRows(NoParent, index, index);
	endRemoveRows();

	if (m_playlist.count() <= 0)
	{
		emit playlistCleared();
	}
}

void PlaylistModel::onPlaylistChanged()
{
	emit layoutChanged();
}
