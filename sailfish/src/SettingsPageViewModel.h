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

	public:
		SettingsPageViewModel();

		QString serverUrl() const;
		void setServerUrl(const QString &serverUrl);

		QString username() const;
		void setUsername(const QString &username);

		QString password() const;
		void setPassword(const QString &password);

	private:
		Settings m_settings;

	signals:
		void serverUrlChanged();
		void usernameChanged();
		void passwordChanged();
};

#endif // SETTINGSPAGEVIEWMODEL_H
