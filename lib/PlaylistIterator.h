#ifndef PLAYLISTITERATOR_H
#define PLAYLISTITERATOR_H

class Playlist;
class PlaylistNode;

class PlaylistIterator
{
	public:
		PlaylistIterator(Playlist &playlist);

		PlaylistNode *next();
		PlaylistNode *current();
};

#endif // PLAYLISTITERATOR_H
