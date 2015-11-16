#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QList>

class Track;
class PlaylistNode;
class PlaylistStream;
class MetadataController;

class PendingPlaylistNode
{
	public:
		PendingPlaylistNode()
			: m_stream(nullptr)
			, m_node(nullptr)
		{

		}

		PendingPlaylistNode(PlaylistStream *stream, PlaylistNode *node)
			: m_stream(stream)
			, m_node(node)
		{

		}

		PlaylistStream *stream() const
		{
			return m_stream;
		}

		PlaylistNode *node() const
		{
			return m_node;
		}

	private:
		PlaylistStream *m_stream;
		PlaylistNode *m_node;
};

class Playlist : public QObject
{
	Q_OBJECT

	public:
		Playlist(MetadataController &metadata);

		void add(Track *track);
		void remove(PlaylistNode *node);

		void prepare(const PendingPlaylistNode &pending);
		void execute();

		PlaylistNode *current() const;
		PlaylistNode *nodeAt(int index) const;

		int count() const;

	private:
		PlaylistNode *m_end;
		PlaylistNode *m_current;

		PendingPlaylistNode m_pending;

		MetadataController &m_metadata;

		QList<PlaylistNode *> m_playlist;

	signals:
		void playlistChanged();
};

#endif // PLAYLIST_H
