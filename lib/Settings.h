#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>

class Settings
{
	const QString ServerUrl = "ServerUrl";
	const QString Username = "Username";
	const QString Password = "Password";

	public:
		QString serverUrl() const;
		void setServerUrl(const QString &serverUrl);

		QString username() const;
		void setUsername(const QString &username);

		QString password() const;
		void setPassword(const QString &password);

	private:
		template<class T>
		T value(const QString &key) const
		{
			return m_subject
				.value(key)
				.value<T>();
		}

		QSettings m_subject;
};

#endif // SETTINGS_H
