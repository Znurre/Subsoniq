#ifndef SETTINGSPAGEVIEWMODEL_H
#define SETTINGSPAGEVIEWMODEL_H

#include <QObject>

#include "Settings.h"

class SettingsPageViewModel : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString serverUrl READ serverUrl WRITE setServerUrl NOTIFY serverUrlChanged)
	Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
	Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
	Q_PROPERTY(int bitRate READ bitRate WRITE setBitRate NOTIFY bitRateChanged)

	public:
		SettingsPageViewModel();

		QString serverUrl() const;
		void setServerUrl(const QString &serverUrl);

		QString username() const;
		void setUsername(const QString &username);

		QString password() const;
		void setPassword(const QString &password);

		int bitRate() const;
		void setBitRate(int bitRate);

	private:
		Settings m_settings;

	signals:
		void serverUrlChanged();
		void usernameChanged();
		void passwordChanged();
		void bitRateChanged();
};

#endif // SETTINGSPAGEVIEWMODEL_H
