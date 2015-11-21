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

	Q_PROPERTY(QString playIcon READ playIcon WRITE setPlayIcon NOTIFY playIconChanged)
	Q_PROPERTY(QString pauseIcon READ pauseIcon WRITE setPauseIcon NOTIFY pauseIconChanged)

	Q_PROPERTY(QString displayTitle READ displayTitle NOTIFY displayTitleChanged)
	Q_PROPERTY(QString playPauseIcon READ playPauseIcon NOTIFY playPauseIconChanged)

	Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)

	public:
		MediaControlsViewModel();

		Player *player() const;
		void setPlayer(Player *player);

		MetadataController *metadata() const;
		void setMetadata(MetadataController *metadata);

		QString playIcon() const;
		void setPlayIcon(const QString &playIcon);

		QString pauseIcon() const;
		void setPauseIcon(const QString &pauseIcon);

		QString displayTitle() const;
		QString playPauseIcon() const;

		bool isPlaying() const;

	public slots:
		void playPause();

	private:
		Player *m_player;
		MetadataController *m_metadata;

		QString m_playIcon;
		QString m_pauseIcon;

	signals:
		void playerChanged();
		void metadataChanged();
		void playIconChanged();
		void pauseIconChanged();
		void displayTitleChanged();
		void playPauseIconChanged();
		void isPlayingChanged();
};

#endif // MEDIACONTROLSVIEWMODEL_H
