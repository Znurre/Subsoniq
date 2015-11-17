#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H

#include <QObject>
#include <QNetworkReply>

#include "SubsonicAdapter.h"

class Track;

class PlaylistNode : public QObject
{
	Q_OBJECT

	public:
		PlaylistNode(Track *track, PlaylistNode *parent);

		Track *track() const;

		void attach(PlaylistNode *child);

		PlaylistNode *parent() const;
		PlaylistNode *child() const;

		static PlaylistNode *invalid();

	private:
		PlaylistNode();

		Track *m_track;

		PlaylistNode *m_parent;
		PlaylistNode *m_child;

		SubsonicAdapter m_adapter;
};

Q_DECLARE_METATYPE(PlaylistNode *)

#endif // PLAYLISTNODE_H
