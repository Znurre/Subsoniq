#ifndef MEDIACONTROLSVIEWMODEL_H
#define MEDIACONTROLSVIEWMODEL_H

#include <QObject>

class Player;
class MetadataController;

class MediaControlsViewModel : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Player *player READ player WRITE setPlayer NOTIFY playerChanged)
	Q_PROPERTY(MetadataController *metadata READ metadata WRITE setMetadata NOTIFY metadataChanged)

	Q_PROPERTY(QString displayTitle READ displayTitle NOTIFY displayTitleChanged)
	Q_PROPERTY(QString playPauseIcon READ playPauseIcon NOTIFY playPauseIconChanged)

	public:
		MediaControlsViewModel();

		Player *player() const;
		void setPlayer(Player *player);

		MetadataController *metadata() const;
		void setMetadata(MetadataController *metadata);

		QString displayTitle() const;
		QString playPauseIcon() const;

	public slots:
		void playPause();

	private:
		Player *m_player;
		MetadataController *m_metadata;

	signals:
		void playerChanged();
		void metadataChanged();
		void displayTitleChanged();
		void playPauseIconChanged();
};

#endif // MEDIACONTROLSVIEWMODEL_H
