#ifndef PLAYLISTPAGEVIEWMODEL_H
#define PLAYLISTPAGEVIEWMODEL_H

#include <QObject>

class PlaylistNode;

class PlaylistPageViewModel : public QObject
{
	Q_OBJECT

	Q_PROPERTY(bool isEditMode READ isEditMode NOTIFY isEditModeChanged)

	public:
		PlaylistPageViewModel();

		bool isEditMode() const;

	public slots:
		void itemActivated(PlaylistNode *node);
		void enterEditMode();
		void leaveEditMode();
		void clear();

	private:
		bool m_editMode;

	signals:
		void isEditModeChanged();
		void playRequested(PlaylistNode *node);
		void clearRequested();
};

#endif // PLAYLISTPAGEVIEWMODEL_H
