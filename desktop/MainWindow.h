#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Player.h"
#include "MetadataController.h"
#include "SettingsDialog.h"

class MainWindow : public QMainWindow
{
	public:
		MainWindow();

	private:
		SettingsDialog m_settingsDialog;
		MetadataController m_metadata;
		Playlist m_playlist;
		Player m_player;
};

#endif // MAINWINDOW_H
