#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Player.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
	public:
		MainWindow();

	private:
		Playlist m_playlist;
		Player m_player;
};

#endif // MAINWINDOW_H
