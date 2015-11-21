#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>

class Settings
{
	const QString ServerUrl = "ServerUrl";
	const QString Username = "Username";
	const QString Password = "Password";
	const QString BitRate = "BitRate";

	public:
		QString serverUrl() const;
		void setServerUrl(const QString &serverUrl);

		QString username() const;
		void setUsername(const QString &username);

		QString password() const;
		void setPassword(const QString &password);

		int bitRate() const;
		void setBitRate(int bitRate);

	private:
		template<class T>
		T value(const QString &key, const QVariant &defaultValue = QVariant()) const
		{
			return m_subject
				.value(key, defaultValue)
				.value<T>();
		}

		QSettings m_subject;
};

#endif // SETTINGS_H
