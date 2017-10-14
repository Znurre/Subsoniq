#include <QFont>
#include <QIcon>
#include <QStyledItemDelegate>
#include <QPainter>

#include "PlaylistModel.h"
#include "Playlist.h"
#include "Track.h"
#include "PlaylistNode.h"
#include "ItemDelegateBase.h"

class PlaylistGroupItemDelegate : public ItemDelegateBase
{
	public:
		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
		{
			QRectF rect = option.rect;
			rect.setHeight(rect.height() - PADDING);

			if (index.row())
			{
				rect.translate(0, PADDING);
			}

			painter->fillRect(rect, option.palette.button());

			const IPlaylistNode *group = (IPlaylistNode *)index.internalPointer();
			const PlaylistNode *playlistNode = group->playlistNode();
			const Track *track = playlistNode->track();

			const QPixmap &image = group->image().pixmap(42, 42);

			const QString &artist = track->artist();
			const QString &album = track->album();

			const QRect top(image.width() + (PADDING * 4), rect.y(), rect.width(), rect.height() / 2);
			const QRect bottom(image.width() + (PADDING * 4), top.bottom(), rect.width(), rect.height() / 2);

			QFont boldFont(option.font);
			boldFont.setBold(true);

			painter->drawPixmap(PADDING * 2, rect.y() + PADDING * 2, image);
			painter->setFont(boldFont);
			painter->drawText(top, Qt::AlignBottom, artist);

			painter->setFont(option.font);
			painter->drawText(bottom, Qt::AlignTop, album);
		}

		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
		{
			Q_UNUSED(option);
			Q_UNUSED(index);

			QSize size(48 + (PADDING * 2), 48 + (PADDING * 3));

			if (index.row())
			{
				size += QSize(0, PADDING);
			}

			return size;
		}
};

class PlaylistGroup : public IPlaylistNode
{
	public:
		PlaylistGroup(int index)
			: m_image(QIcon::fromTheme("media-optical-audio"))
			, m_first(nullptr)
			, m_index(index)
		{

		}

		~PlaylistGroup()
		{
			qDeleteAll(m_children);
		}

		const QStyledItemDelegate &delegate() const override
		{
			return m_delegate;
		}

		void setChildren(const QList<IPlaylistNode *> &children)
		{
			m_children = children;
		}

		PlaylistNode *playlistNode() const override
		{
			return m_first;
		}

		void setPlaylistNode(PlaylistNode *playlistNode)
		{
			m_first = playlistNode;

			const Track *track = playlistNode->track();

			m_adapter.getCoverArt(track->id(), "42", this, &PlaylistGroup::imageResponse);
		}

		IPlaylistNode *parent() const override
		{
			return nullptr;
		}

		IPlaylistNode *childAt(int index) const override
		{
			return m_children.value(index);
		}

		QIcon image() const override
		{
			return m_image;
		}

		int index() const override
		{
			return m_index;
		}

		int childCount() const override
		{
			return m_children.count();
		}

	private:
		void imageResponse(const QImage &image)
		{
			m_image = QPixmap::fromImage(image);
		}

		QList<IPlaylistNode *> m_children;
		QIcon m_image;

		SubsonicAdapter m_adapter;
		PlaylistGroupItemDelegate m_delegate;
		PlaylistNode *m_first;

		int m_index;
};

class PlaylistItem : public IPlaylistNode
{
	public:
		PlaylistItem(PlaylistNode *subject, IPlaylistNode *parent, int index)
			: m_parent(parent)
			, m_subject(subject)
			, m_index(index)
		{

		}

		const QStyledItemDelegate &delegate() const override
		{
			return m_delegate;
		}

		PlaylistNode *playlistNode() const override
		{
			return m_subject;
		}

		IPlaylistNode *parent() const override
		{
			return m_parent;
		}

		IPlaylistNode *childAt(int index) const override
		{
			Q_UNUSED(index);

			return nullptr;
		}

		int index() const override
		{
			return m_index;
		}

		int childCount() const override
		{
			return 0;
		}

	private:
		QStyledItemDelegate m_delegate;

		IPlaylistNode *m_parent;
		PlaylistNode *m_subject;

		int m_index;
};

PlaylistModel::PlaylistModel(Playlist &playlist)
	: m_playlist(playlist)
{
	connect(&m_playlist, &Playlist::nodeAppended, this, &PlaylistModel::onNodeAppended);
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		IPlaylistNode *node = (IPlaylistNode *)parent.internalPointer();

		return node->childCount();
	}

	return m_nodes.count();
}

int PlaylistModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 3;
}

QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(column);
	Q_UNUSED(parent);

	if (parent.isValid())
	{
		IPlaylistNode *node = (IPlaylistNode *)parent.internalPointer();

		return createIndex(row, column, node->childAt(row));
	}

	return createIndex(row, column, m_nodes.value(row));
}

QModelIndex PlaylistModel::parent(const QModelIndex &child) const
{
	IPlaylistNode *node = (IPlaylistNode *)child.internalPointer();

	if (!node)
	{
		return QModelIndex();
	}

	IPlaylistNode *parent = node->parent();

	if (!parent)
	{
		return QModelIndex();
	}

	return createIndex(parent->index(), 0, parent);
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
	const IPlaylistNode *node = (IPlaylistNode *)index.internalPointer();

	if (!node)
	{
		return QVariant();
	}

	const PlaylistNode *playlistNode = node->playlistNode();
	const Track *track = playlistNode->track();

	if (role == Qt::DisplayRole)
	{
		if (index.column() == 0)
		{
			return track->track();
		}

		if (index.column() == 1)
		{
			return track->title();
		}

		if (index.column() == 2)
		{
			return track->artist();
		}
	}

	if (role == Qt::FontRole)
	{
		if (m_playlist.current() == playlistNode)
		{
			QFont font;
			font.setBold(true);

			return font;
		}
	}

	return QVariant();
}

void PlaylistModel::onNodeAppended(int index)
{
	Q_UNUSED(index);

	qDeleteAll(m_nodes);

	m_nodes.clear();

	QHash<QString, QList<PlaylistNode *>> groups;

	for (int i = 0; i < m_playlist.count(); i++)
	{
		PlaylistNode *node = m_playlist.nodeAt(i);

		const Track *track = node->track();

		groups[track->album()] << node;
	}

	int groupIndex = 0;

	for (const QList<PlaylistNode *> &nodes : groups)
	{
		QList<IPlaylistNode *> children;

		PlaylistNode *first = nullptr;
		PlaylistGroup *group = new PlaylistGroup(groupIndex++);

		int childIndex = 0;

		for (PlaylistNode *node : nodes)
		{
			children << new PlaylistItem(node, group, childIndex++);

			if (!first)
			{
				first = node;
			}
		}

		group->setChildren(children);
		group->setPlaylistNode(first);

		m_nodes << group;
	}

	emit layoutChanged();
//	beginInsertRows(QModelIndex(), index, index);

	qDebug() << "Model updated";

//	endInsertRows();
}
