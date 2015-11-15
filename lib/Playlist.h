#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QList>

class Track;
class PlaylistNode;

class Playlist : public QObject
{
	Q_OBJECT

	public:
		Playlist();

		void add(Track *track);
		void remove(PlaylistNode *node);

		void prepare(PlaylistNode *node);
		void execute();

		PlaylistNode *current() const;
		PlaylistNode *nodeAt(int index) const;

		int count() const;

	private:
		PlaylistNode *m_end;
		PlaylistNode *m_current;
		PlaylistNode *m_pending;

		QList<PlaylistNode *> m_playlist;

	signals:
		void playlistChanged();
};

#endif // PLAYLIST_H
