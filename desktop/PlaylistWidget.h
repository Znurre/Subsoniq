#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>

class PlaylistNode;
class Playlist;

class PlaylistWidget : public QWidget
{
	Q_OBJECT

	public:
		PlaylistWidget(Playlist &playlist);

	private:
		void onDoubleClicked(const QModelIndex &index);

	signals:
		void nodeSelected(PlaylistNode *node);
};

#endif // PLAYLISTWIDGET_H
